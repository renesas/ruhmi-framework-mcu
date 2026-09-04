Date: 2026-09-04

# 5 application examples (FSP v6.6.0 release update).  

### Software requirements
  - e² studio 2026-07  
  - FSP 6.6.0  
  - LLVM 22.1.0  

## Overall
** Unified all five demo branches to the FSP v6.6.0 baseline for consistent build/import behavior in the latest e² studio environment.  
** Improved runtime stability and visual consistency across demos, especially for overlay behavior, tracking continuity, and frame-to-frame smoothness.
** Resolved reliability issues in inference input/output handling and display update flow to reduce intermittent mis-detections or UI artifacts.  

### 1) Face Detection  
- Updated project baseline to FSP v6.6.0 for release alignment.  
- Improved bounding-box stability so stationary faces show significantly less box flicker while moving faces remain responsive.  
- Stabilized per-frame processing cost by limiting pre-NMS candidate volume to the app display capacity.  
- Fixed output quantization handling to prevent rare cases where inference results could become inconsistent across builds/toolchains.  

### 2) Image Classification  
- Updated project baseline to FSP v6.6.0 for release alignment.  
- Improved Top-N result stability so near-tie classes are less likely to swap rapidly between adjacent frames.  
- Improved sidebar label/probability rendering consistency to avoid occasional truncation or stale text artifacts.  
- Fixed output/result handling robustness to keep classification output behavior stable under continuous real-time operation.  

### 3) Palm Detection
- Updated project baseline to FSP v6.6.0 for release alignment.  
- Fixed a display update race that could intermittently clear overlays mid-cycle, seen as brief box blinking.  
- Improved box stability during hand motion and still-hand scenarios by adding temporal smoothing with slot-aware matching.  

### 4) Palm Detection + Hand Landmark  
- Updated project baseline to FSP v6.6.0 for release alignment.  
- Improved overlay consistency by using landmark-derived hand geometry and by correcting edge-of-screen clipping behavior.  
- Reduced AI pipeline time by switching to tracking-first operation (detector runs periodically instead of every frame when tracking is stable).  
- Improved visual smoothness and interaction stability by applying temporal filtering to both hand ROI updates and landmark point rendering, reducing frame-to-frame jitter while keeping hand motion responsive.

## Performance Summary (high level)  
- Hand pipelines improved from ~63 ms to ~30 ms in the typical single-hand case.
- Two-hand typical case improved from ~84 ms to ~53 ms, mainly by reducing detector frequency while tracking is active.  	
