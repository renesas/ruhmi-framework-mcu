import argparse
import sys
import re
import json
from pathlib import Path

__version__ = "1.0.0"

# =============================================================================
# Helper script to measure Model Metrics
# =============================================================================

def detect_platform(src_dir: Path) -> str:
    """
    Detect if the build is CPU or NPU based.
    Checks for 'ethosu_common.h' in the source directory.
    """
    if (src_dir / "ethosu_common.h").exists():
        return "NPU"
    return "CPU"

def parse_compute_signature(c_file_path: Path):
    """
    Parses a compute_sub_XXXX.c file to extract the function signature and arguments.
    Returns:
        func_name (str): Name of the function (e.g., compute_sub_0000)
        args (list): List of dicts with keys: 'name', 'type', 'is_pointer', 'is_const', 'array_size', 'is_arena'
    """
    if not c_file_path.exists():
        return None, []

    content = c_file_path.read_text()
    
    # Regex to find function definition: void compute_sub_XXXX(...)
    match = re.search(r'void\s+(compute_sub_\w+)\s*\(([^)]+)\)', content, re.DOTALL)
    if not match:
        return None, []

    func_name = match.group(1)
    args_str = match.group(2)

    # Clean comments
    args_str_clean = re.sub(r'//.*', '', args_str)
    args_str_clean = re.sub(r'/\*.*?\*/', '', args_str_clean, flags=re.DOTALL)
    
    arg_list = [a.strip() for a in args_str_clean.split(',') if a.strip()]
    
    parsed_args = []
    
    for arg in arg_list:
        info = {
            'original': arg,
            'is_const': 'const' in arg,
            'is_pointer': '*' in arg,
            'is_arena': 'main_storage' in arg,
            'array_size': None,
            'type': 'uint8_t', # Default
            'name': 'unknown'
        }
        
        clean = arg.replace('const', '').strip()
        
        if '[' in clean:
            # Array: int8_t Identity_70012[12]
            parts = clean.split('[')
            name_part = parts[0].strip()
            size_part = parts[1].split(']')[0].strip()
            info['array_size'] = size_part
            
            tokens = name_part.split()
            if tokens:
                info['name'] = tokens[-1]
                if len(tokens) > 1:
                    info['type'] = ' '.join(tokens[:-1])
            
        else:
            # Pointer: uint8_t* main_storage
            clean_no_ptr = clean.replace('*', '').strip()
            tokens = clean_no_ptr.split()
            if tokens:
                info['name'] = tokens[-1]
                if len(tokens) > 1:
                    info['type'] = ' '.join(tokens[:-1])
            if info['is_pointer']:
                 # If type was parsed without *, add it back or assume ptr behavior
                 # Usually type is just data type.
                 pass

        parsed_args.append(info)
        
    return func_name, parsed_args

def get_type_size(type_str: str) -> int:
    """Simple helper to get size of C types."""
    type_str = type_str.strip()
    if 'int8' in type_str or 'uint8' in type_str or 'char' in type_str:
        return 1
    if 'int16' in type_str or 'uint16' in type_str:
        return 2
    if 'int32' in type_str or 'uint32' in type_str or 'float' in type_str:
        return 4
    if 'int64' in type_str or 'uint64' in type_str or 'double' in type_str:
        return 8
    return 1 # Default

# =============================================================================
# Main Analysis Logic
# =============================================================================

def parse_memory_stats(deploy_dir: Path):
    deploy_path = Path(deploy_dir)
    if not deploy_path.exists():
        print(f"Error: Directory not found: {deploy_dir}")
        return

    # Compiler defined structure:
    # Root -> deploy/
    #         └── build/
    #             └── MCU/
    #                 ├── model_subgraphs.json
    #                 └── compilation/
    #                     └── src/ (C code)

    mcu_dir = None
    
    # Check if we were given the root (containing 'deploy')
    if (deploy_path / "deploy" / "build" / "MCU").exists():
        mcu_dir = deploy_path / "deploy" / "build" / "MCU"
    
    # Check if we were given 'deploy' directly
    elif (deploy_path / "build" / "MCU").exists():
        mcu_dir = deploy_path / "build" / "MCU"
        
    # Check if we were given the MCU folder itself
    elif deploy_path.name == "MCU" or (deploy_path / "model_subgraphs.json").exists():
         # Fallback: assume the current dir is the MCU base if json is here
         if (deploy_path / "compilation" / "src").exists():
             mcu_dir = deploy_path

    if not mcu_dir:
        print(f"Error: Could not locate 'deploy/build/MCU' structure in {deploy_dir}, likely compilation failed")
        return

    src_dir = mcu_dir / "compilation" / "src"
    if not src_dir.exists():
        # User requested strictness, but let's be safe.
        print(f"Error: Source directory not found at {src_dir}")
        print("  -> This likely means the compilation step FAILED.")
        return

    json_path = mcu_dir / "model_subgraphs.json"
    if not json_path.exists():
        print(f"Warning: model_subgraphs.json not found at {json_path}")
        json_path = None

    platform = detect_platform(src_dir)
    print(f"  Detected Platform: {platform}")

    arena_bytes = 0
    flash_bytes = 0
    stats_source = "Unknown"

    if platform == "NPU":
        # --- NPU Logic (from original check_memory.py) ---
        stats_source = "NPU C-Code (sub_*.c)"
        npu_arena_pattern = re.compile(r'\{\s*".*",\s*\d+,\s*(\d+),\s*"ARENA"')
        npu_model_pattern = re.compile(r'\{\s*".*",\s*\d+,\s*(\d+),\s*"MODEL"')
        
        # Updated to handle suffix: sub_XXXX_tensors[_suffix].c
        npu_files = list(src_dir.glob("sub_*_tensors*.c"))
        
        for c_file in npu_files:
            try:
                content = c_file.read_text()
                # Find ARENA sizes (Tensor Arena / RAM)
                for match in npu_arena_pattern.finditer(content):
                    size = int(match.group(1))
                    if size > arena_bytes:
                        arena_bytes = size
                
                # Find MODEL sizes (Flash / Parameters)
                for match in npu_model_pattern.finditer(content):
                    flash_bytes += int(match.group(1))
            except Exception as e:
                 print(f"Warning: Failed to parse {c_file.name}: {e}")

    else:
        # --- CPU Logic (Enhanced with postprocessing logic) ---
        stats_source = "CPU C-Code (compute_*.c parsed signatures)"
        
        # 1. Flash (Weights) from compute_sub_*.c signatures
        compute_files = sorted(list(src_dir.glob("compute_sub_*.c")))
        
        for c_file in compute_files:
            func_name, args = parse_compute_signature(c_file)
            if not func_name:
                continue
            
            # Re-reading C content to find static const arrays directly is better for Flash
            # because the signature only passes pointers.
            
            content = c_file.read_text()
            
            # Regex to find array definitions and sizes
            # static const int8_t name[1234]
            # matches: type, name, size
            array_defs = re.finditer(r'static\s+const\s+([\w\s]+)\s+[\w\d_]+\s*\[(\d+)\]', content)
            
            for match in array_defs:
                type_str = match.group(1)
                count = int(match.group(2))
                item_size = get_type_size(type_str)
                total_size = count * item_size
                flash_bytes += total_size
                # print(f"    Found Weight: {total_size} bytes ({type_str} [{count}])")

        # 2. RAM (Tensor Arena) from compute_sub_*.h
        # MERA generates kBufferSize as an enum member (not a #define), e.g.:
        #   enum BufferSize_sub_0000 { kBufferSize_sub_0000 = 6015360 };
        # so we match the '= <number>' assignment syntax.
        cpu_h_files = list(src_dir.glob("compute_sub_*.h"))
        cpu_buffer_pattern = re.compile(r'kBufferSize_sub_\d+(?:_\w+)?\s*=\s*(\d+)')
        
        for h_file in cpu_h_files:
             try:
                content = h_file.read_text()
                for match in cpu_buffer_pattern.finditer(content):
                    size = int(match.group(1))
                    if size > arena_bytes:
                        arena_bytes = size
             except Exception:
                 pass

    mac_count = 0
    npu_mac_count = 0
    
    if json_path:
        # print(f"  Found JSON: {json_path}")
        try:
            with open(json_path) as f:
                data = json.load(f)
            
            for subgraph in data.get("subgraphs", []):
                target = subgraph.get("target_name", "UNKNOWN")
                subgraph_macs = 0
                
                for node in subgraph.get("nodes", []):
                    node_data = node.get("node_data", {})
                    subgraph_macs += node_data.get("mac_count", 0)
                
                mac_count += subgraph_macs
                
                if target == "ARM_ETHOS_U55":
                    npu_mac_count += subgraph_macs
                    
        except Exception as e:
            print(f"Warning: Failed to parse JSON for MACCs: {e}")


    # --- Report ---
    print(f"\nMemory Analysis for: {deploy_dir}")
    print(f"--------------------------------------------------")
    print(f"Platform: {platform}")
    
    print(f"RAM (Tensor Arena)   : {arena_bytes:>12,} bytes  ({arena_bytes/1024**2:.2f} MB)")
    print(f"Flash (Parameters)   : {flash_bytes:>12,} bytes  ({flash_bytes/1024**2:.2f} MB)")
    
    mac_m = mac_count / 1_000_000
    print(f"MAC Operations       : {mac_count:>12,} ops    ({mac_m:.2f} M)")
    
    if mac_count > 0:
        npu_ratio = (npu_mac_count / mac_count) * 100
        print(f"NPU Acceleration     : {npu_ratio:>11.1f}%      ({npu_mac_count:,} / {mac_count:,} ops)")
        
    print(f"--------------------------------------------------\n")

    return (arena_bytes, flash_bytes, mac_count)

def main():
    parser = argparse.ArgumentParser(description="Check Model Metrics for MERA compiled models.")
    parser.add_argument("deploy_dir", type=Path, help="Path to the deployment/build directory")
    parser.add_argument('--version', '-v', action='version', version=f'%(prog)s {__version__}')
    args = parser.parse_args()
    
    parse_memory_stats(args.deploy_dir)

if __name__ == "__main__":
    main()
