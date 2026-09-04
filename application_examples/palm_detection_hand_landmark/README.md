# Introduction
This demo project showcases a two-stage hand tracking pipeline on a Renesas RA8P1 MCU using the RUHMI Framework AI MCU Compiler. A palm detection model finds hands, and a hand landmark model extracts 21 keypoints per hand. Results are displayed on an LCD with bounding boxes and a hand skeleton overlay. Up to 2 hands are tracked simultaneously.

Use the [.zip file](../ek_ra8p1_vision_palm_detection_hand_landmarkmodel_camera_LCD_FSP660.zip) when you import the application project into e² studio.

---

## Overview
The system runs a sequential pipeline: palm detection finds hands, then a rotated crop is fed to the landmark model. Once a hand is tracked, the crop is re-derived from landmarks, so palm detection runs periodically instead of every frame.

| No | Content | Description |
|----|---------|-------------|
| 1 | AI Models | Palm Detection INT8 (192×192) + Hand Landmark INT8 (224×224) |
| 2 | Max Hands | 2 |
| 3 | Keypoints | 21 per hand (x, y + relative z depth) |
| 4 | AI pipeline time | ~30ms (single hand, measured) |
| 5 | Camera frame period | 26ms (38 fps), fixed |

## Architectural Diagram

<div align="center">
<img src="../palm_detection_hand_landmark/docs/palm_detection_hand_landmark_flow_diagram.svg" width="70%">
</div>

---

## Hardware Setup
- **Evaluation Kit**: Renesas **EK-RA8P1**
- **Camera & Display**: Integrated in the EK-RA8P1 kit
- **NPU**: On-board **Arm Ethos-U55** (no external setup required)
- **Connection to PC**: Power on the EK-RA8P1 kit with any of the available USB connectors
- **Important**: Ensure the **SW4 switch (middle of the board)** is set to all **0** (OFF)

## Software Setup

- **e² studio version**: 2026-07
- **Flexible Software Package (FSP)**: 6.6.0
- **Toolchain**: LLVM/Clang (ATfE 22.1.0) is the toolchain this project is configured to build with by default.
- **RTOS**: FreeRTOS (via FSP's `rtos.awsfreertos` module)
- **RUHMI AI MCU Compiler**: Included in this repository

## How to Compile and Flash

1. **Install e² studio**
2. **Connect your EK-RA8P1 board** via USB Type-C
3. **Download this repository and extract**, or extract the project zip linked above
4. **Open e² studio** and import the project: `File` → `Import` → `Existing Projects into Workspace`
5. **Generate drivers**: double-click `configuration.xml` → `Generate Project Content`
6. **Build the project**: right-click the project in the left sidebar → `Build Project`
7. **Flash to the board**: right-click the project → `Debug As` → `Renesas GDB Hardware Debugging`
8. **Run**: click `Resume` a few times

> **Note:** In Release builds, the demo may require one manual board reset after flashing (or power-cycle) before it runs correctly.

---
## Key Source Code

Main AI pipeline logic is in:  
`src/ai_application/palm_detection/MainLoop_obj.cc` (`main_loop_palm_detection()`)

Detection result update/publish is in:  
`src/ai_inference_thread_entry.c` (`update_detection_result()`)

Display/UI rendering is in:  
`src/display_layer/detection_screen_mipi.c` (`do_detection_screen()`)

---
## Code Explanation

```cpp
memcpy((void*)mera_input_ptr(), (const void*)model_buffer_int8, IMAGE_DATA_SIZE);
SCB_CleanDCache_by_Addr((uint32_t*)mera_input_ptr(), (int32_t)IMAGE_DATA_SIZE);
mera_invoke();
```
Copies the palm detector input frame into the tensor buffer, cleans D-cache, and runs palm inference.

```cpp
int8_t* out_scores = mera_output_scores_ptr();
int8_t* out_boxes  = mera_output_boxes_ptr();
int8_t* out_kp0    = mera_output_kp0_ptr();
int8_t* out_kp2    = mera_output_kp2_ptr();
```
Gets pointers to palm model outputs (scores, boxes, and keypoints) for post-processing.

```cpp
const uint32_t elapsed_ms = TimeCounter_CountValueConvertToMs(pipeline_start, TimeCounter_CurrentCountGet());
application_processing_time.ai_inference_time_ms = s_sum / s_count;
```
Computes and reports averaged pipeline processing time.

---

## Results & Performance

| Metric | Typical Value | Notes |
|--------|---------------|-------|
| AI pipeline total (0 hands) | ~38ms | Detector runs every frame while nothing is tracked |
| AI pipeline total (1 hand) | ~30ms | Measured `ai_inference_time_ms` |
| AI pipeline total (2 hands) | ~53ms | Two landmark inferences; detector idle while both slots track |
| Camera frame period | 26ms (38 fps) | Fixed |

> **Note:** `ai_inference_time_ms` measures the AI thread pipeline window: palm tensor copy + palm inference + palm post-processing + per-hand landmark preprocess/inference/post-process. It does **not** include camera capture period, camera post-processing, or LCD refresh time. This project supports up to 2 palms.

## Example output

<div align="center">
<img src="./docs/palm_detection_hand_landmark_demo.png" width="50%">
</div>

## Model Reference

Models are based on [hand-gesture-recognition-using-onnx](https://github.com/PINTO0309/hand-gesture-recognition-using-onnx) by PINTO0309 (Apache-2.0), originally derived from MediaPipe by Google LLC.

- **Palm Detection**: MediaPipe Palm Detection Full
- **Hand Landmark**: MediaPipe Hand Landmark Sparse

Both models have been optimized and quantized (INT8) by Renesas to run efficiently on the EK-RA8P1 Ethos-U55 NPU.

> Note: This example is provided as a demo. The model has not been retrained or fine-tuned for improved accuracy and is provided as-is.
