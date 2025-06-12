mera Documentation
Release 2.3.2

## CONTENTS  
1 High Level Design  
1.1 Quantizer  
1.2 Interpreter  
1.3 Deployer  
1.4 C Codegen  

2 User manual  
2.1 Introduction  
2.2 Installation - Ubuntu Linux  
2.3 Installation - Windows  
2.4 How to deploy models  
2.5 Quantize and deploy models  
2.6 FUll quantization demo  
2.7 Guide to the generated C source code  
2.8 External Licenses Overview  

3 Integration Test Condition and Report  
3.1 CCodegen Test Report  
3.2 MERA Quantizer Integration Testing  

4 AI model compile API Specification  
4.1 Module contents  

5 MERA Error List  

6 Current Limitations  
6.1 MERA Quantizer Limitations  
6.2 C-Codegen Limitations  


## HIGH LEVEL DESIGN  

Below is a component diagram detailing how the different pieces interact with each other while quantizing a TFLite,
ONNX or ExecuTorch model as well as deploying a pre-quantized TFLite or MERA quantized model.  

## 1.1 Quantizer  
The MERA Quantizer is a sophisticated tool designed to convert an unquantized machine learning (ML)
model—originally represented in 32-bit floating-point precision (float32)—into an optimized, quantized model that
operates using integer arithmetic. This transformation significantly reduces computational overhead and memory foot-
print while maintaining model accuracy, making it ideal for deployment on resource-constrained hardware.

## 1.1.1 Supported Input Frameworks
The MERA Quantizer is compatible with models exported from the following industry-standard frameworks:
    - ExecuTorch (PyTorch’s serialized model format)
    - ONNX (Open Neural Network Exchange format)
    - TFLite (TensorFlow Lite models)

## 1.1.2 Quantization Process
The quantization process relies on a realistic calibration dataset provided by the user. This dataset should be represen-
tative of the model’s operational input distribution, allowing the MERA Quantizer to:
     - Analyze the dynamic range of activations and weights.
     - Compute optimal quantization thresholds (scales and zero-points).
     - Convert floating-point operations into efficient integer-based computations.

The result can be saved to a file as a .mera model, which can later be deployed using MERA for different type of targets.

## 1.2 MERA Interpreter

The MERA Interpreter is a versatile tool that enables software-based emulation of machine learning (ML) model opera-
tions across multiple frameworks. It serves as a critical component for model validation, quantization, and performance
analysis, offering a unified interface for executing and inspecting models in a controlled environment.

### 1.2.1 Key Capabilities
**1. Cross-Framework Model Emulation**  
Provides a standardized API to execute and debug ML models from supported frameworks, including:
    – PyTorch (via ExecuTorch)  
    – TensorFlow (via TFLite)  
    – ONNX (Open Neural Network Exchange)  
    – MERA-quantized models (.mera format)  
    – Simulates model behavior without hardware dependencies, enabling pre-deployment validation.  

**2. Quantization Support & Calibration Data Processing**
Used by the MERA Quantizer to:  
    • Analyze activation ranges from user-provided calibration datasets, ensuring optimal quantization scaling.
    • Track tensor distributions and weight dynamics to minimize precision loss during integer conversion.
    • Generates quantization quality metrics (e.g., PSNR, MSE, per-layer error analysis) by comparing quantized vs. floating-point outputs on an evaluation dataset.

**3. Diagnostic and Debugging Features**  
    • Layer-by-layer introspection: Inspect intermediate tensor values to identify accuracy bottlenecks.
    • Performance profiling: Measure theoretical latency/memory usage for different target architectures.
    • Cross-framework consistency checks: Validate numerical equivalence between original and quantized models.

## 1.3 MERA Deployer
The model deployment component serves as a critical pipeline stage for executing optimized neural networks on target
hardware platforms. This subsystem accepts quantized models in either of the following formats:
    1. .mera -  Quantized models with RUHMI quantizer.
                This is the Intermediate Representation.  
    2. TFLite - Pre-quantized TensorFlow Lite models.

### 1.3.1 Deployment Workflow
The component performs the following key transformations:

1. Operator Lowering:
• Converts high-level operations to device-specific implementations
• Applies precision mapping (int8/uint8/int16) per target requirements  

2. Region Partitioning:  
• Analyzes computational graph dependencies
• Segments model into executable regions based on:
• Target device capabilities (CPU vs MCU)
• Memory bandwidth constraints
• Parallelization opportunities

## 1.4 C Codegen
The CCodegen will receive MERA IR subgraphs and will produce a list of C compute files that can be compiled to run
on CPU.


# MERA USER MANUAL

## 2.1 Introduction

### 2.1.1 Description
The EdgeCortix© MERA™ software stack provides a compiler and the necessary tools to convert machine learning
models into C source code compatible with range of Renesas MCUs powered by Arm Ethos-U NPUs.

MERA software stack generates C source code while ensuring compatibility and tight integration the with Renesas e2
studio.

It also ships with MERA Quantizer, a post-training static INT8 quantizer, allowing more demanding models to meet
the memory and latency constraints typical of microcontrollers and Ethos-U accelerators.

### 2.1.2 Overall workflow
• Import MERA accept models from the most used ML frameworks as PyTorch, TensorFlow Lite and ONNX.  

• Compile the compiler lowers the graph, applies operator fusion, inserts fast math libraries, and emits plain C99
source code that calls either CMSIS-NN (for Cortex-M CPUs) or the Ethos-U driver depending on the platform.
This C code builds inside Renesas e2 studio providing support for HAL, Ethos-U drivers, OSPI Flash drivers,
CMSIS-NN/CMSIS DSP libraries and other stacks necessary to run machine learning models on the different
supported platform.

• Quantize when targeting more resource limited devices, MERA Quantizer helps to convert weights and activa-
tions to INT8 precision. This tool performs layer-wise calibration on representative data, calculates quantization
parameters and emits a quantized model that can be further compiled by the MERA compiler.

• Build & deploy Renesas e2 studio is compatible with the code generated by MERA software stack. The same flow works for pure MCU platforms or for MCU + NPU combinations.

### 2.1.3 Supported embedded platforms
Currently, MERA software stack provides support for Renesas embedded platforms:
***EK-RA8P1 board (device R7KA8P1KFLCAC)***  

### 2.1.4 Software components overview

MERA software stack  
Provided as a Python PIP package for Ubuntu 22.04 LTS that can be installed on a Python 3.10 virtual environment.

MERA provides a Python API to import and compile machine learning models to several platforms including Renesas
MCUs. Some of these Renesas MCUs offer extra acceleration thanks to the integrated Arm Ethos-U NPU. The way
these platforms are selected in MERA is through options specified during compilation.


    import mera
    from mera import Platform, Target

    with mera.Deployer(deploy_dir, overwrite=True) as deployer:

    # ...
    deployer.deploy(model,

    mera_platform=Platform.MCU_ETHOS  # or Platform.MCU_CPU,
    target=Target.MCU ...)

Targets on the context of C code generation and microcontrollers should usually be set to the generic target mera.Target.MCU. The platform on the other side specify the actual hardware we want to deploy for. In the con-
text of Renesas MCUs platforms such as Platform.MCU_CPU and Platform.MCU_ETHOS are available. Note that Platform.MCU_ETHOS implies to support a combination of Arm Ethos-U NPU but always having the MCU as the
fallback platform. This generally means that when an acceleration platform is selected it can be assumed that not every operation will be supported on the accelerator. Non supported operations will be executed on CPU.

**MERA operator support (under active development)**

The following list are orientative to have an idea of the level of support given by the MERA software stack to the different operators that can found on several machine learning frameworks such as TFLite (.tflite), ONNX (.onnx)
or ExecuTorch (.pte) models. Imported models into MERA software stack are processed differently according to the selected Platforms and Targets and not every combination of support should be expected for every operator in these
lists.

The following is a list of operators supported on the MERA front-ends:

Table 1: MERA TFLite front-end operator support

|TFLite operator|MERA TFLite front-end operator|
|---|---|
|tfl.abs|TFL::AbsOp|  
|tfl.add|TFL::AddOp|  
|tfl.average_pool_2d|TFL::AveragePool2DOp|  
|tfl.batch_to_space_nd|TFL::BatchToSpaceNdOp|  
|tfl.concatenation|TFL::ConcatenationOp|  
|tfl.conv_2d|TFL::Conv2DOp|  
|tfl.depthwise_conv_2d|TFL::DepthwiseConv2DOp|  
|tfl.dequantize|TFL::DequantizeOp|  
|tfl.exp|TFL::ExpOp|  
|tfl.expand_dims|TFL::ExpandDimsOp|  
|tfl.fully_connected|TFL::FullyConnectedOp|  
|tfl.hard_swish|TFL::HardSwishOp|  
|tfl.leaky_relu|TFL::LeakyReluOp|  
|tfl.log|TFL::LogOp|  
|tfl.log_softmax|TFL::LogSoftmaxOp|  
|tfl.logistic|TFL::LogisticOp|  
|tfl.max_pool_2d|TFL::MaxPool2DOp|  
|tfl.mean|TFL::MeanOp|  
|tfl.minimum|TFL::MinimumOp|  
|tfl.mirror_pad|TFL::MirrorPadOp|  
|tfl.mul|TFL::MulOp|  
|tfl.neg|TFL::NegOp|  
|tfl.pack|TFL::PackOp|  
|tfl.pad|TFL::PadOp|  
|tfl.padv2|TFL::PadV2Op|  
|tfl.pow|TFL::PowOp|  
|tfl.prelu|TFL::PReluOp|  
|tfl.quantize|TFL::QuantizeOp|  
|tfl.reduce_max|TFL::ReduceMaxOp|  
|tfl.relu|TFL::ReluOp|  
|tfl.relu6|TFL::Relu6Op|  
|tfl.reshape|TFL::ReshapeOp|  
|tfl.resize_bilinear|TFL::ResizeBilinearOp|  
|tfl.resize_nearest_neighbor|TFL::ResizeNearestNeighborOp|
|tfl.rsqrt|TFL::RsqrtOp|  
|tfl.slice|TFL::SliceOp|  
|tfl.softmax|TFL::SoftmaxOp|  
|tfl.space_to_batch_nd|TFL::SpaceToBatchNdOp|  
|tfl.split|TFL::SplitOp|  
|tfl.split_v|TFL::SplitVOp|  
|tfl.sqrt|TFL::SqrtOp|  
|tfl.squared_difference|TFL::SquaredDifferenceOp|  
|tfl.strided_slice|TFL::StridedSliceOp|  
|tfl.sub|TFL::SubOp|  
|tfl.sum|TFL::SumOp|  
|tfl.tanh|TFL::TanhOp|  
|tfl.transpose|TFL::TransposeOp|  
|tfl.transpose_conv|TFL::TransposeConvOp|  
|tfl.unpack|TFL::UnpackOp|  


**Table 2: MERA ONNX front-end operator support**
|ONNX operator|
|---|
|Add|
|ArgMax|
|AveragePool|
|BatchNormalization|
|Cast|
|Clip|
|Concat|
|Constant|
|Conv|
|ConvTranspose|
|Cos|
|CumSum|
|DepthToSpace|
|Div|
|Equal|
|Erf|
|Exp|
|Expand|
|Flatten|
|Gather|
|Gemm|
|GlobalAveragePool|
|HardSigmoid|
|HardSwish|
|InstanceNormalization|
|LayerNormalization|
|LeakyRelu|
|Log|
|LRN|
|MatMul|
|Max|
|MaxPool|
|Mul|
|Neg|
|Not|
|Pad|
|Pow|
|PRelu|
|RandomNormalLike|
|ReduceL2|
|ReduceMax|
|ReduceMean|
|ReduceSum|
|Relu|
|Reshape|
|Resize|
|ScatterND|
|Shape|
|Sigmoid|
|Sin|
|Slice|
|Softmax|
|SpaceToDepth|
|Split|
|Sqrt|
|Squeeze|
|Sub|
|Sum|
|Tanh|
|TopK|
|Transpose|
|Unsqueeze|
|Upsample|
|Where|

Table 3: MERA ExecuTorch/EXIR front-end operator support
|ExecuTorch/EXIR front-end operator|
|---|
|aten::addmm.out|
|aten::add.out|
|aten::alias_copy.out|
|aten::any.out|
|aten::arange.start_out|
|aten::as_strided_copy.out|
|aten::avg_pool2d.out|
|aten::bmm.out|
|aten::cat.out|
|aten::clamp.out|
|aten::clone.out|
|aten::constant_pad_nd.out|
|aten::convolution.out|
|aten::cos.out|
|aten::div.out|
|aten::eq.Scalar_out|
|aten::eq.Tensor_out|
|aten::expand_copy.out|
|aten::full_like.out|
|aten::gelu.out|
|aten::hardtanh.out|
|aten::index.Tensor_out|
|aten::logical_not.out|
|aten::max_pool2d_with_indices.out|
|aten::mean.out|
|aten::mm.out|
|aten::mul.out|
|aten::mul.Scalar_out|
|aten::_native_batch_norm_legit_no_training.out|
|aten::native_layer_norm.out|
|aten::permute_copy.out|
|aten::relu.out|
|aten::sigmoid.out|
|aten::sin.out|
|aten::slice_copy.Tensor_out|
|aten::_softmax.out|
|aten::split_with_sizes_copy.out|
|aten::squeeze_copy.dims_out|
|aten::sub.out|
|aten::_to_copy.out|
|aten::unsqueeze_copy.out|
|aten::upsample_bilinear2d.vec_out|
|aten::upsample_nearest2d.vec_out|
|aten::view_copy.out|
|aten::where.self_out|
|dim_order_ops::_to_dim_order_copy.out|
|executorch_prim::et_view.default|

The following is the list of operators supported on the MERA C code generator. Note that all these operators refer to TFLite. This is because the codegen is built around microcontroller technologies that rely on TFLite kernels as
a reference. This is the case for CMSIS-NN libraries and the Ethos-U hardware for example, the optimized kernels of these libraries and the hardware used to compute several operators replicate the behaviour of the reference kernel
implementations found on TensorFlow Lite and Tensorflow Lite Micro. MERA compiler is able to import operators from other frameworks such as ONNX and ExecuTorch but eventually the compilation flow will lower these operators
into TFLite dialect because of these reasons.

**Table 4: MERA C99 codegen operator support**
|C99 codegen operator|
|---|
|TFLiteAbs|
|TFLiteBatchToSpaceNd|
|TFLiteConcatenate|
|TFLiteDequantize|
|TFLiteExp|
|TFLiteFullyConnected|
|TFLiteFullyConnectedBias|
|TFLiteHardSwish|
|TFLiteLeakyReLU|
|TFLiteLog|
|TFLiteLogSoftmax|
|TFLiteMaxPool|
|TFLiteMean|
|TFLiteMinimum|
|TFLiteMirrorPad|
|TFLiteMul|
|TFLiteNeg|
|TFLitePack|
|TFLitePad|
|TFLitePadV2|
|TFLitePRelu|
|TFLiteQAdd|
|TFLiteQConv2d|
|TFLiteQuantize|
|TFLiteReduceMax|
|TFLiteRelu|
|TFLiteRelu6|
|TFLiteResizeBilinear|
|TFLiteResizeNearest|
|TFLiteSigmoid|
|TFLiteSlice|
|TFLiteSoftmax|
|TFLiteSpaceToBatchNd|
|TFLiteSquaredDifference|
|TFLiteStridedSlice|
|TFLiteSub|
|TFLiteSum|
|TFLiteTanh|
|TFLiteTranspose|
|TFLiteTransposeConv2d|

Please note that ONNX and PyTorch Frontends are currently only meant to be used with Quantizer flow.

**ARM Vela compiler**

When targeting a Renesas device powered by Arm Ethos-U NPU the MERA software stack will automatically leverage the Arm Vela compiler. Those parts of the machine learning model that can accelerated with the NPU will be processed
with the Arm Vela compiler in order to obtain valid assembly for the Ethos-U NPU.  
The version of ARM Vela compiler used to compile those subgraphs assigned to the Ethos-U55 platform is 4.2.0. Note that when installing the MERA software stack PIP package it will automatically pull Arm Vela as a dependency.

## 2.2 MERA Installation - Ubuntu Linux
In order to install MERA 2.3.1 MCU on supported environment you will need:

• A machine with Ubuntu 22.04 installation is recommended as this was the version used for testing
• A working installation of PyEnv or other Python virtual environment management system that provides Python version 3.10.x.

### 2.2.1 Installation steps
System dependencies necessary to create environments and run demos:

    sudo apt update; sudo apt install build-essential cmake python3-venv python3-pip
    sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
    sudo apt update && sudo apt -y install libstdc++6

**Recommended: use the default Python installation**

Because MERA software stack is compatible by default with the base system Python version provided by Ubuntu 22.04 we can create a virtual environment as follows:

    python3 -m venv mera-env
    source mera-env/bin/activate
    pip install --upgrade pip && pip install decorator typing_extensions psutil attrs pybind11

Your prompt should now show that you are under a virtual environment mera-env:

    (mera-env) user@compute:~$

**Alternative: PyEnv installation**
If PyEnv is preferred over the base system Python installation you can get started with:

    # pyenv dependencies
    sudo apt update; sudo apt install build-essential libssl-dev zlib1g-dev \
    libbz2-dev libreadline-dev libsqlite3-dev curl git cmake \
    libncursesw5-dev xz-utils tk-dev libxml2-dev libxmlsec1-dev libffi-dev liblzma-dev

    # actual installation of PyEnv
    curl https://pyenv.run | bash

The installation of PyEnv recommends to do some post-installation steps that involve to modify your .bashrc file in order to easily create virtual environments:

    echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bashrc
    echo '[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bashrc
    echo 'eval "$(pyenv init - bash)"' >> ~/.bashrc

To create a Python Virtual Environment for MERA named “mera-env” using PyEnv:

    MENV=mera-env; pyenv install 3.10.15 && pyenv virtualenv 3.10.15 $MENV && pyenv activate $MENV && \
    pip install --upgrade pip && \
    pip install decorator typing_extensions psutil attrs pybind11

Your prompt should now show that you are under a virtual environment mera-env:

    (mera-env) user@compute:~$

**MERA installation**
Finally install MERA on the virtual environment mera-env:

    pip install ./mera-2.3.1+pkg.1503-cp310-cp310-manylinux_2_27_x86_64.whl

where the versions may vary depending on the MERA release used.
At this point MERA should be ready to use. You can confirm with the following example:

    python -c "import mera;print(dir(mera))"

## 2.3 MERA Installation - Windows
MERA software stack is also provided as PIP package compatible with Windows 11.

In order to install MERA 2.3.2 MCU on supported environment you will need:
• A machine with Windows 10 or 11. Windows 11 is recommended as this was the version used for testing
• A working installation of PyEnv or other Python virtual environment management system that provides Python version 3.10.x.
• Microsoft C++ runtime libraries
    – Please download and install this package in order to provide these libraries.

## 2.3.1 Setup virtual environment
***PowerShell***

    python3.10 -m venv mera-env
    .\myenv\Scripts\Activate.ps1
    pip install --upgrade pip && pip install decorator typing_extensions psutil attrs pybind11

In case VisualStudio build tools are used the following environment variables have to be set. This will setup Clang to be used to compile the generated code.

    $env:CMAKE_GENERATOR="Visual Studio 17 2022"
    $env:CMAKE_GENERATOR_TOOLSET="ClangCl"

***Command***

    python3.10 -m venv mera-env
    myenv\Scripts\Activate.bat
    pip install --upgrade pip && pip install decorator typing_extensions psutil attrs pybind11

In case VisualStudio build tools are used the following environment variables have to be set. This will setup Clang to be used to compile the generated code.

    set CMAKE_GENERATOR="Visual Studio 17 2022"
    set CMAKE_GENERATOR_TOOLSET="ClangCl"

### 2.3.2 Installation steps

    pip install mera-2.3.2-cp310-cp310-win_amd64.whl

Please check that all your path settings of your environment are correct. After installation you should be able to successfully complete the following commands

    vela --version
    python -c "import mera;print(dir(mera))"

### 2.4 How to deploy models with MERA
The following code shows how to use the MERA deployment API to compile an already quantized TFLite model on a board with Ethos-U55 support:

    import os
    import mera

    from mera import Platform, Target

    def needs_ospi(file, size_mb):

    return os.path.getsize(file) / (1024 * 1024) > size_mb

    def deploy_mcu(model_path, deploy_dir, with_ethos, with_ospi, with_ref_data):

    try:

    with mera.Deployer(deploy_dir, overwrite=True) as deployer:

    model = mera.ModelLoader(deployer).from_tflite(model_path)

    platform = Platform.MCU_ETHOS if with_ethos else Platform.MCU_CPU

    # ARM Vela options
    # only effective if Platform.MCU_ETHOS is selected, ignored otherwise
    vela_config = {}
    vela_config['enable_ospi'] = needs_ospi(model_path, 1.5)
    vela_config['sys_config'] = 'RA8P1'
    vela_config['memory_mode'] = 'Sram_Only'
    vela_config['accel_config'] = 'ethos-u55-256'
    vela_config['optimise'] = 'Performance'
    vela_config['verbose_all'] = False

    # MCU C code generation options
    mcu_config = {}
    mcu_config['suffix'] = ''
    mcu_config['weight_location'] = 'flash' # other option is: 'iram'

    # On other scripts we could use True and it will not generate
    # x86 related source code (python bindings for example)
    mcu_config['use_x86'] = False

    # generation of reference data from original model format
    # using the original runtime is only supported for TFLite models
    enable_ref_data = with_ref_data and model_path.suffix == '.tflite'

    deployer.deploy(model,

    mera_platform=platform,
    target=Target.MCU,
    vela_config=vela_config,
    mcu_config=mcu_config,
    enable_ref_data=enable_ref_data)

    except Exception as e:
    print(str(e))

This release provides some tested models, if the models provided are for example:

    models_int8/
    |-- ad_medium_int8.tflite
    |-- kws_micronet_m.tflite
    |-- mobilenet_v2_1.0_224_INT8.tflite
    |-- person-det.tflite
    |-- rnnoise_INT8.tflite
    |-- vww4_128_128_INT8.tflite
    |-- wav2letter_int8.tflite
    |-- yolo-fastest_192_face_v4.tflite


Then by running the provided script scripts/mcu_deploy.py we can compile the model for MCU only:

    cd scripts/
    python mcu_deploy.py --ref_data ../models_int8 deploy_qtzed

you will get the following results:

    deploy_qtzed
    |-- ad_medium_int8_no_ospi
    |-- kws_micronet_m_no_ospi
    |-- mobilenet_v2_1.0_224_INT8_ospi
    |-- person-det_no_ospi
    |-- rnnoise_INT8_no_ospi
    |-- vww4_128_128_INT8_no_ospi
    |-- wav2letter_int8_ospi
    |-- yolo-fastest_192_face_v4_no_ospi

same but enabling Ethos-U support:

    cd scripts/
    python mcu_deploy.py --ethos --ref_data ../models_int8 deploy_qtzed_ethos

When Ethos-U support is enabled, each of the directories contain a deployment of the corresponding model for MCU + Ethos-U55 platform:

    person-det_no_ospi
    |-- build
        |-- MCU
                compilation
                mera.plan
    src # compilation results: C source code and C++ testing support code # HAL entry example

    CMakeLists.txt
    compare.cpp
    compute_sub_0000.c # CPU subgraph generated C source code
    compute_sub_0000.h
    ...
    ethosu_common.h
    hal_entry.c
    kernel_library_int.c # kernel library if CPU subgraphs are present
    ...
    model.c
    model.h
    model_io_data.c
    model_io_data.h
    python_bindings.cpp
    sub_0001_command_stream.c # Ethos-U55 subgraph generated C source code
    sub_0001_command_stream.h
    sub_0001_invoke.c
    sub_0001_invoke.h
    ...

    ...

    deploy_cfg.json
    ir_dumps

    person-det_can.dot
    ...

    person-det_after_canonicalization.dot
    person-det_subgraphs.dot

    logs
    model

    input_desc.json

    project.mdp

Please reference to the provided pre-generated e2studio projects to see how the generated C code under build/MCU/compilation/src can be incorporated into a e2studio project.

## 2.5 Quantize and deploy models with MERA
If the starting point it is a Float32 precision model it is possible to use the MERA Quantizer to first quantize the model and finally deploy with MCU/Ethos-U55 support.

The following is a sample of how to quantize a model with the MERA Quantizer API:

    with mera.Deployer(str(deploy_dir), overwrite=True) as deployer:
    if model_path.suffix == '.tflite':
        mera_model = mera.ModelLoader(deployer).from_tflite(str(model_path))
    elif model_path.suffix == '.onnx':
        mera_model = mera.ModelLoader(deployer).from_onnx(str(model_path), shape_mapping=SYMBOLIC_DIMS)
    elif model_path.suffix == '.pte':
        mera_model = mera.ModelLoader(deployer).from_executorch(str(model_path))
    else:
        raise ValueError("Unsupported model format: " + model_path.suffix)

    cal_data = generate_input_data(mera_model, num_cal)
    qtzer = mera.Quantizer(deployer,mera_model,quantizer_config=quantizer_config,mera_platform=platform)
    qtz_path = Path(result_path)
    res_path = qtz_path / 'model.mera'
    qty = qtzer.calibrate(cal_data).quantize().evaluate_quality(cal_data[:1])
    Q = qty[0].out_summary()[0]
    if Q["psnr"] < 5:

    model.status = Status.ERROR_PSNR
    model.last_error = f'PSNR too low: {Q["psnr"]}'
    return {'inputs': None, 'outputs': None}

    qtzer.save_to(res_path)
    print(f'Successfully quantized model with quality: {Q["psnr"]} psnr, {Q["score"]} score')
    return res_path

Once quantized, we can deploy the quantized model by using using .from_quantized_mera() instead of .from_tflite():

    with mera.Deployer(str(deploy_dir), overwrite=True) as deployer:
    mera_model = mera.ModelLoader(deployer).from_quantized_mera(model_path)
    platform = Platform.MCU_ETHOS if with_ethos else Platform.MCU_CPU
    \# ARM Vela options
    \# only effective if Platform.MCU_ETHOS is selected, ignored otherwise
    vela_config = {}
    vela_config['enable_ospi'] = needs_ospi(model_path, 1.5)
    vela_config['sys_config'] = 'RA8P1'
    vela_config['memory_mode'] = 'Sram_Only'
    vela_config['accel_config'] = 'ethos-u55-256'
    vela_config['optimise'] = 'Performance'
    vela_config['verbose_all'] = False

    \# MCU C code generation options
    mcu_config = {}
    mcu_config['suffix'] = ''
    mcu_config['weight_location'] = 'flash' # other option is: 'iram'

    \# On other scripts we could use False and it will not generate
    \# x86 related source code (python bindings for example),
    mcu_config['use_x86'] = True

    \# generation of reference data from original model format
    \# using the original runtime is only supported for TFLite models
    enable_ref_data = with_ref_data and model_path.suffix == '.tflite'

    deployer.deploy(mera_model,

    mera_platform=platform,
    target=Target.MCU,
    vela_config=vela_config,
    mcu_config=mcu_config,
    enable_ref_data=enable_ref_data)

## 2.6 Full quantization demo

We provide a script that given a model (either with .tflite, .onnx or .pte extension) will:
• calibrate and quantize the model with random data
• deploy the model for the MCU C Codegen platform and generate C source code
• compile the auto-generated Python bindings for the C source code
• execute the C source code through the Python bindings
• compare the MERA Interpreter results and the C source code results

To run this script:

    cd scripts/

    \# deploy for MCU only
    python mcu_quantize.py ../models_fp32 deploy_mcu

    \# deploy for MCU+Ethos-U55
    python mcu_quantize.py -e ../models_fp32_ethos deploy_ethos

## 2.7 Guide to the generated C source code

After processing a model with the MERA compiler you will find several files on your deployment directory. This include some deploying artifacts generated during compilation that are worth to be kept around for debugging purposes.

The most important output that MERA generates is found under the directory <deployment_directory>build/MCU/compilation/src. This directory contains the model converted into a set of C99 source code files.

### 2.7.1 Runtime API - MPU only deployment
When a model is converted into source code with MERA compiler without Ethos-U support, all the operators in the model being deployed will be prepared to be run on CPU/MCU only. In this case, the generated code will refer to a
single subgraph compute_sub_0000<suffix>, by default, when no suffix is provided, the name of the header that need to included on your application entry point is compute_sub_0000.h.
This header provides the declaration of a C function that if called it will run the model with the provided inputs and write the results on the provided output buffers:

    enum BufferSize_sub_0000 {
        kBufferSize_sub_0000 = <intermediate_buffers_size>
    };

    void compute_sub_0000(
        // buffer for intermediate results
        uint8_t* main_storage, // should provide at least <intermediate_buffers_size> bytes of storage

        // inputs
        const int8_t <input_name>[xxx], // 1,224,224,3

        // outputs
        int8_t <output_name>[xxx] // 1,1000
    );

It provides to the user the possibility of providing a buffer to hold intermediate outputs of the model. And this size if provided in compilation time as the value kBufferSize_sub_0000 so the user can use this size to allocate the buffer on
the stack, the heap or a custom data section.

### 2.7.2 Runtime API - MPU + Ethos-U deployment
If Ethos-U support is enabled during conversion into source code with MERA compiler then an arbitrary amount of subgraphs for either CPU or Ethos-U will be generated. Each of these subgraphs will correspond to generated C
functions to run the corresponding section of the model on CPU or Ethos. Each function call will get its inputs from previous outputs of other subgraphs and write its outputs on buffers that are designated to became again inputs to other
functions and so on. To make easier for the user to invoke these models where CPU and NPU are involved, the generated code will automate this process and provide a single function that will orchestrate the calls to the different computation
units named void RunModel(bool clean_outputs) and helpers to access to each of the input and output areas at model level not per subgraph level. The runtime API header when Ethos-U is enabled can be found on a file named model.h
under the same directory <deployment_directory>/build/MCU/compilation/src.
For example, after enabling Ethos-U support for a model with two inputs and three outputs MERA provides the next
runtime API:

    // invoke the whole model
    void RunModel(bool clean_outputs);

    // Model input pointers
    float* GetModelInputPtr_input0();
    float* GetModelInputPtr_input1();

    // Model output pointers
    float* GetModelOutputPtr_out0();
    float* GetModelOutputPtr_out1();
    float* GetModelOutputPtr_out2();

The function GetModelInputPtr_input0 provides access to the buffer where the user can write the first input of the model and GetModelInputPtr_input1 gives us the pointer where the user can copy the second input.
To run the model and all the CPU or NPU units needed to be invoked to do inference with the deployed model, the user should invoke to the RunModel() function. The parameter clean_outputs should be used only for debugging purposes
because it will set to zero all the output buffers used by an NPU unit before invoking it. Recommended value for the parameter clean_outputs is false, as it will not incur into extra time expend on clearing these buffers.

### 2.7.3 Testing helpers for x86
In order to test the generated C99 code without deploying it to the board there is a configuration option that enables the generation of all these helpers. This option can be enabled as below:

With this option enabled we will see some extra C++ files generated:
• CMakeLists.txt CMake project that compiles CMSIS-NN, the generated C99 code and Python bindings into a shared library (Python module).
• cmsis-windows.patch The CMake project will pull dependencies as CMSIS-NN. In order to be able to compile CMSIS-NN on Windows this patch is necessary.
• compare.cpp Small C++ application generated for testing the generated C99 code on x86.
• hal_entry.c Auto-generated example of a possible entry point on Renesas e2 studio project to get the user a starting point on how to run the model. This generated code intended to be used as a reference by the user.
• python_bindings.cpp Contains auto-generated PyBind11 bindings for the C99 generated code.

## 2.8 External Licenses Overview

Table 5: External Licenses

|Copyright|License|
|---|---|
|google/libnop|Apache, Version 2.0|
|uxlfoundation/oneDNN|Apache, Version 2.0|
|GNU OpenMP Linux only|GNU General Public License|
|Microsoft Visual C++ 2015 - 2022 Runtime Windows only |Microsoft Software License|
|vimpunk/mio|MIT|
|nlohmann/json|MIT|
|microsoft/onnxruntime|MIT|
|tensorflow/tensorflow|Apache, Version 2.0|
|gabime/spdlog|MIT|
|jarro2783/cxxopts|MIT|
|pytorch/executorch|BSD|
|GNU C++ Library|GPL3 + Exception to use in proprietary programs|


# INTEGRATION TEST CONDITION AND REPORT
**Out of scope to be public**

# AI MODEL COMPILE API SPECIFICATION

4.1 Module contents

4.1.1 mera module

4.1.2 mera.deploy module

4.1.3 mera.deploy_project module

4.1.4 mera.mera_deployment module

4.1.5 mera.mera_model module

4.1.6 mera.mera_platform module

4.1.7 mera.version module

4.1.8 mera.mera_quantizer module

4.1.9 mera.quantizer module


## MERA ERROR LIST

The following table summarizes common errors encountered during model quantization, conversion, and execution, along with their technical descriptions. Each entry clarifies the root cause and impact of the error to aid in debugging
and resolution.

Table 1: Error List

|Error Name|Module|Error Descroption|
|---|---|---|
|CHECK qparam.IsPerTensor()|Module MERA Inter-preter|The operation expected per-tensor quantization (where a single scale and zero-point are applied to the entire tensor) but encountered an incompatible quantization scheme (such as per-channel quantization). Per-tensor quantization uses uniform scaling across all tensor values, while per-channel quantization applies separate parameters to each channel, typically seen in depthwise convolutional layers. This mismatch prevents the quantization process from proceeding as configured.|
|CHECK qparam.IsPerChannel()|MERA Inter-preter|The operation expected per-channel quantization (where separate scale and zero-point parameters are applied to each channel of the tensor) but encountered an incompatible quantization scheme (such as per-tensor quantization). Per-channel quantization is typically required for depthwise convolutional layers and certain hardware accelerators that optimize for channel-wise scaling, while per-tensor quantization applies uniform parameters across all channels. This mismatch prevents proper quantization or execution of the model.|
|CHECK input.shape.size==output.shape.size|MERA Inter-preter||The operation detected an inconsistency in tensor dimensions between a node’s input and output, where the expected output shape does not match the computed result. This typically occurs when layer operations (such as reshapes, splits, or concatenations) are improperly configured or when the model’s architecture enforces incompatible dimensional transformations between connected layers. The mismatch prevents successful execution of the affected node in the computational graph.|
|CHECK Implementation for node <NODE_TYPE>[<NODE_NAME>] is not defined.|Module MERA Interpreter|The interpreter encountered a node type that is not currently supported for execution, indicating either an incompatible layer operation or an unsupported framework-specific operator. This typically occurs when the model contains custom operations, experimental layers, or framework features that have not been implemented in MERA Interpreter. The operation cannot proceed until the unsupported node is modified or replaced with a compatible alternative.|
|ERROR Deserialization: <MSG>|MERA Interpreter|The deserialization process encountered an error while attempting to load the file, likely due to version incompatibility or file corruption. This typically occurs when trying to read a quantized model file that was created with an older version of the framework or when the serialized data structure has been modified or damaged. The operation cannot proceed without a valid, compatible model file in the current format.|
|CHECK fused_activation ==ir::canonical::TFLiteFusedActType::NONE|MERA Interpreter|The interpreter encountered an operator with unsupported fused activation, indicating that the model uses combined operations (where linear computations and activations are merged into a single optimized node) that aren’t implemented in the current runtime. This limitation occurs when the backend lacks specific handling for these composite operations, requiring either decomposition into separate primitive operations or implementation of the fused operator pattern.|
|CHECK n.axes.shape.size==1|MERA Interpreter|The operation expected a 1-dimensional axes parameter for the TFLite sum operator, but received an invalid or multi-dimensional input.|
|TODO|MERA Interpreter|The operation encountered a missing implementation for a required component or feature, marked as a placeholder (TODO) in the codebase. This indicates unimplemented functionality that was expected to be available during execution, typically arising during development of new features or support for untested use cases. The system cannot proceed until the specified component is properly implemented and integrated.|
|Histogram combination must encompass original histogram’s range:|MERA Quantizer|The histogram-based quantization observer encountered invalid input data during range aggregation, likely due to infinite (inf) or Not-a-Number (NaN) values produced by preceding operators. This occurs when the calibration data or model computations generate numerical instabilities that corrupt the statistical analysis required for determining quantization parameters. The calibration process requires finite input ranges to properly calculate scale and zero-point values.|
|CHECK data.size equals pre_axis times axis times post_axis|MERA Quantizer|The operation encountered an invalid tensor shape durng observer processing, where the input dimensions were incompatible with the expected observation requirements. This typically occurs when statistical observers (used for quantization range calibration) receive malformed tensors that violate shape constraints. The shape mismatch prevents proper collection of activation statistics needed for accurate quantization.|
|CHECK Must have accumulation do-main set.|MERA Quantizer|The quantization process expected tensor operations to use int32 as the accumulation domain (for preserving intermediate calculation precision) but instead encountered operations configured for activation domains (typically int8/uint8).|
|CHECK Unhandled Quantize() con-stant layout: <LAYOUT>|MERA Quantizer|The quantization process failed because the specific memory layout of the constant tensor is not supported. Constants must follow strict layout requirements (such as contiguous memory, specific stride patterns, or dimension ordering) to be properly quantized, but the encountered tensor violates these constraints. This typically occurs when constants are created with unconventional storage formats or optimized layouts that aren’t compatible with the quantization process.|
|CHECK Unhandled axis for layout<LAYOUT>|MERA Quantizer|The specified axis value is invalid for the tensor’s current memory layout, indicating a mismatch between the requested dimensional operation and the actual data organization. This typically occurs when operations (like reductions or broadcasts) reference non-existent dimensions or misinterpret stride patterns, particularly with transposed, sliced, or non-contiguous tensors where logical and physical layouts diverge. The operation cannot proceed until either the axis parameter is corrected or the tensor is reorganized to match the expected layout.|
|Histogram observer can only use PER_TENSOR mode|MERA Quantizer|The histogram observer encountered an unsupported quantization mode, as it only operates with PER_TENSOR quantization (where a single scale/zeropoint is applied to the entire tensor). This limitation occurs because histogram-based range calibration requires uniform statistical analysis across all tensor values, which isn’t compatible with PER_CHANNEL or other granular quantization schemes that maintain separate parameters for different tensor segments. The observer cannot proceed until configured for pure per-tensor operation.|
|No quantized model available. Needs to call QuantizeTransform()|MERA Quantizer|The operation attempted to use an API method designed for quantized models, but was called on a non-quantized input. This occurs when the model has not undergone the necessary quantization transformation process. The system requires explicit quantization via the transform() method to convert the model into the supported quantized representation before this operation can proceed.|
|CHECK Missing quantization transform recipe(s) for modes[<NODE_LIST>]|MERA Quantizer|The operation found a layer type with no quantization implementation, blocking full model conversion. This occurs when the framework lacks quantization logic for the layer’s specific operations. The process requires either implementing support for this layer or replacing it with a quantizable alternative.|
|MERA Core config file not found:<PATH>|Framework Frontend|The operation failed to locate the required configuration file at the specified path.|
|Shape contains an undefined dimension|Framework Frontend|The ONNX parser encountered a tensor shape with undefined dimensions, which occurs when the model contains dynamic shapes or placeholder values that weren’t resolved during export. This prevents proper tensor allocation and validation during model parsing.|
|Input type not supported yet|Framework Frontend|The ONNX parser encountered an input tensor type that is not currently supported by MERA, indicating either a custom data type or an unsupported ONNX feature. This prevents the model from being properly ingested and processed.|
|Symbolic dimension has not been defined for this tensor|Framework Frontend|The ONNX parser encountered a tensor with undefined symbolic dimensions, indicating unresolved dynamic shape variables that must be explicitly specified. To resolve this, provide the missing dimension definitions through the shape_mapping argument when calling from_onnx(), which allows proper shape inference and validation of the computational graph.|
|Only one ONNX operator set is supported at a time|Framework Frontend|The ONNX parser encountered multiple default operator set versions, which violates the specification requiring exactly one global operator set version declaration. This typically occurs when merging models from different ONNX versions or manual editing of the protobuf file, preventing consistent versioned operation handling.|
|Error: constant_segment index is not valid|Framework Frontend|The ExecuTorch parser encountered an invalid constant segment index while processing the model, indicating either corruption in the serialized data or an out-of-bounds access attempt. This prevents proper loading of constant tensor data required for execution.|
|Extended header length <LENGTH> is less than minimum required length <MIN_LENGTH>|Framework Frontend|The ExecuTorch parser rejected the extended header due to insufficient length, indicating the header section is either corrupted or improperly serialized. The actual header size falls below the framework’s minimum required length for valid metadata storage, preventing model initialization.|
|Torch front-end: DataType not supported yet|Framework Frontend|The ExecuTorch parser encountered an unsupported data type during TorchScript model conversion, indicating either a custom type or framework feature not yet implemented in the ExecuTorch frontend. This blocks successful model parsing and deployment.|
|Torch front-end: Unhandled Constant data type|Framework Frontend|The ExecuTorch frontend encountered a constant tensor with an unsupported data type during TorchScript model conversion, indicating either a specialized numeric type or custom constant value that lacks handling in the parser. This prevents complete translation of the model’s static data elements.|
|Torch/EXIR Edge operator not sup-ported yet|Framework Frontend|The ExecuTorch runtime encountered an unsupported edge operator during execution, indicating either a newly introduced PyTorch operation or a specialized kernel that hasn’t been implemented in the edge deployment target. This prevents the model from running on the specified edge device.|
|Torch front-end:non-tensor inputs/outputs are not supporteed|Framework Frontend|The ExecuTorch frontend encountered non-tensor inputs or outputs during TorchScript model conversion, which violates the framework’s requirement that all model boundaries must use tensor types. This typically occurs when passing Python primitives (like integers or lists) directly across the model interface, preventing successful export to the edge runtime.|
|PatternMatchRewrite:the rewrite does not preserve required node|Deploye|The pattern matching rewrite failed because it did not explicitly include a required output node in its replacement outputs, despite this node being consumed by operations outside the rewritten subgraph. This occurs when transformation rules neglect to propagate interface nodes that external graph segments depend on, breaking the model’s dataflow integrity.|
|Found cycles while performing topological sort of subgraphs|Deploye|The operation detected a cyclic dependency during topological sorting of a computational subgraph, indicating circular references between nodes that prevent valid execution ordering. This violates the requirement for directed acyclic graph (DAG) structures in model execution plans, stalling further processing until the cycle is resolved.|
|Vela optimized model to source: expected only one subgraph|Deploye|When Ethos-U target is enabled the MERA compiler will identify subgraphs that can be accelerated with the NPU. It is expected that when MERA invokes the Arm Vela compiler to generate assembly only one subgraph will be present and that this whole subgraph will be merged by Vela into a single Ethos Vela optimized node. This error indicates that one or more nodes have been incorrectly identified as supported by the Ethos-U NPU. This error indicates a bug on MERA software stack that should not be solved by the user but reported to EdgeCortix.|
|No subgraphs found in model|Deploye|Indicates an error processing the Vela optimized model because this model does not contain any subgraph. Can be either an error on either MERA or Arm Vela compiler.|
|No Ethos-U custom operators found in subgraph|Deploye|MERA compiler identified that a subgraph can be accelerated with the Ethos-U NPU but after processing this subgraph with Arm Vela compiler no Arm Vela optimized custom nodes were found on the graph. This typically indicates that there is a bug on MERA compiler and should not be fixed by the user but reported to EdgeCortix.|
|More than one Ethos-U custom operator found in subgraph|Deploye|MERA compiler identified that a subgraph can be accelerated with the Ethos-U NPU but after processing this subgraph with Arm Vela compiler both Arm Vela optimized custom nodes and CPU nodes were found on the graph. This typically indicates that there is a bug on MERA compiler and should not be fixed by the user but reported to EdgeCortix.|
|Error converting runtime plan to source:buffer belongs to several arenas|Deploye|When MERA compiles a model using several targets as for example ARM Cortex-M + Ethos-U55, several subgraphs for each of these targets will be created. The graph that connects these subgraphs for either CPU or Ethos-U is detected as no supported when two subgraphs for the same target share the same input tensor. This situation is not currently supported by MERA because restrictions on how the NPU generally overwrite its inputs tensors as part of the memory plan generated by Arm Vela compiler.|
|Error converting the ONNX model to canonical IR|Deploye|The model conversion from ONNX to canonical intermediate representation failed due to incompatible operators, unsupported attributes, or invalid graph structure that couldn’t be properly translated. This prevents further processing or optimization of the model in the target framework.|
|Error converting the TFLite model to canonical IR|Deploye|The model conversion from TFLite to canonical intermediate representation failed due to incompatible operators, unsupported attributes, or invalid graph structure that couldn’t be properly translated. This prevents further processing or optimization of the model in the target framework.|
|Depthwise transposed conv2d is not supported by tflite|TFLite Export|TFLite doesn’t support depthwise transposed convolutions, preventing conversion or execution of models using this operation.|
|TFLite exporter: Operator code not supported yet|TFLite Export|The TFLite exporter encountered an unsupported operator type, indicating the operation lacks an implementation for conversion to TFLite’s flatbuffer format. This blocks model export until the operator is either implemented or replaced.|
|Operator conversion to tflite not supported yet|TFLite Export|Conversion to TFLite format failed because this operator type isn’t currently supported in the exporter. The operation lacks a translation rule to TFLite’s operator set, preventing model export.|


## CURRENT LIMITATIONS

This section outlines the known constraints and boundaries of the system. While designed to address a wide range of use cases, certain technical, operational, or design limitations may apply. Understanding these limitations ensures optimal deployment and helps guide workarounds or future enhancements.

### 6.1 MERA Quantizer Limitations

Below is a table of different operators and the MERA Quantizer support for each of them. Depending on the target (MCU_CPU or MCU_ETHOS) different types could be available based on the fatures of C-Codegen and/or Vela.
Other operators are not supported for quantization, those are marked with X.


Table 1: MERA Quantizer Operator Support

|Operator Name|MCU_CPU|MCU_ETHOS|
|---|---|---|
|Conv2d|A8W8|A8W8|
|ConvTranspose|A8W8|A8W8|
|Gemm|A8W8|A8W8|
|Add|A8|A8|
|Sub|A8|A8|
|Mul|F32|A8|
|Mul [ONNX]|A8|A8|
|Div|A8|A8|
|ReLU|A8|A8|
|HardSwish|F32|A8|
|HardSigmoid|A8|A8|
|LeakyReLU|A8|A8|
|MaxPool|A8|A8|
|AveragePool|F32|A8|
|Softmax|A8|A8|
|Reshape|A8|A8|
|Squeeze|A8|A8|
|Transpose|A8|A8|
|ConvertLayout|A8|A8|
|Concatenate|A8|A8|
|Slice|A8|A8|
|BatchNorm|A8|A8|
|Clip|A8|A8|
|Tanh|A8|A8|
|Sigmoid|A8|A8|
|Sigmoid [ONNX]|F32|A8|
|Silu (HSwish)|A8|A8|
|Minimum|F32|F32|
|Maximum|X|X|
|ReduceMax|A8|A8|
|ReduceMean|A8|A8|
|ReduceSum|A8|A8|
|Pack|A8|A8|
|Resize2d|F32|A8|
|PReLU|A8|A8|
|Pad|A8|A8|
|MirrorPad|X|X|
|PadV2|X|X|
|Log|F32|F32|
|Neg|F32|F32|
|Exp|F32|A8|
|Abs|X|X|
|Sqrt|X|X|
|FloorDiv|X|X|
|ArgMax|X|X|
|GatherNd|X|X|
|RSqrt|X|X|
|SquaredDifference|X|X|


## 6.2 C-Codegen Limitations

• tfl.concatenation (TFL::ConcatenationOp) Only supports up to 4 dimensional inputs.


