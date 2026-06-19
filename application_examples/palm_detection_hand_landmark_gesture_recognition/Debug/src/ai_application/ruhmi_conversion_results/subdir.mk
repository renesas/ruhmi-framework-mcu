################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ai_application/ruhmi_conversion_results/compute_sub_0001.c \
../src/ai_application/ruhmi_conversion_results/kernel_library_int.c \
../src/ai_application/ruhmi_conversion_results/kernel_library_utils.c \
../src/ai_application/ruhmi_conversion_results/model.c \
../src/ai_application/ruhmi_conversion_results/sub_0000_command_stream.c \
../src/ai_application/ruhmi_conversion_results/sub_0000_invoke.c \
../src/ai_application/ruhmi_conversion_results/sub_0000_model_data.c \
../src/ai_application/ruhmi_conversion_results/sub_0000_tensors.c \
../src/ai_application/ruhmi_conversion_results/sub_0002_command_stream.c \
../src/ai_application/ruhmi_conversion_results/sub_0002_invoke.c \
../src/ai_application/ruhmi_conversion_results/sub_0002_model_data.c \
../src/ai_application/ruhmi_conversion_results/sub_0002_tensors.c 

CREF += \
ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640.cref 

C_DEPS += \
./src/ai_application/ruhmi_conversion_results/compute_sub_0001.d \
./src/ai_application/ruhmi_conversion_results/kernel_library_int.d \
./src/ai_application/ruhmi_conversion_results/kernel_library_utils.d \
./src/ai_application/ruhmi_conversion_results/model.d \
./src/ai_application/ruhmi_conversion_results/sub_0000_command_stream.d \
./src/ai_application/ruhmi_conversion_results/sub_0000_invoke.d \
./src/ai_application/ruhmi_conversion_results/sub_0000_model_data.d \
./src/ai_application/ruhmi_conversion_results/sub_0000_tensors.d \
./src/ai_application/ruhmi_conversion_results/sub_0002_command_stream.d \
./src/ai_application/ruhmi_conversion_results/sub_0002_invoke.d \
./src/ai_application/ruhmi_conversion_results/sub_0002_model_data.d \
./src/ai_application/ruhmi_conversion_results/sub_0002_tensors.d 

OBJS += \
./src/ai_application/ruhmi_conversion_results/compute_sub_0001.o \
./src/ai_application/ruhmi_conversion_results/kernel_library_int.o \
./src/ai_application/ruhmi_conversion_results/kernel_library_utils.o \
./src/ai_application/ruhmi_conversion_results/model.o \
./src/ai_application/ruhmi_conversion_results/sub_0000_command_stream.o \
./src/ai_application/ruhmi_conversion_results/sub_0000_invoke.o \
./src/ai_application/ruhmi_conversion_results/sub_0000_model_data.o \
./src/ai_application/ruhmi_conversion_results/sub_0000_tensors.o \
./src/ai_application/ruhmi_conversion_results/sub_0002_command_stream.o \
./src/ai_application/ruhmi_conversion_results/sub_0002_invoke.o \
./src/ai_application/ruhmi_conversion_results/sub_0002_model_data.o \
./src/ai_application/ruhmi_conversion_results/sub_0002_tensors.o 

MAP += \
ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640.map 


# Each subdirectory must supply rules for building sources it contributes
src/ai_application/ruhmi_conversion_results/%.o: ../src/ai_application/ruhmi_conversion_results/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m85 -mthumb -mlittle-endian -mfloat-abi=hard -Os -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c99 -flax-vector-conversions -fshort-enums -fno-unroll-loops -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/src" -I"." -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/fsp/inc" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/fsp/inc/api" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/fsp/inc/instances" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/fsp/src/rm_freertos_port" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/aws/FreeRTOS/FreeRTOS/Source/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/arm/CMSIS_6/CMSIS/Core/Include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra_gen" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra_cfg/fsp_cfg/bsp" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra_cfg/fsp_cfg" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra_cfg/aws" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/fsp/src/rm_ethosu" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/tes/dave2d/inc" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/arm/CMSIS-NN/Include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/arm/CMSIS-NN" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/npu/flatbuffers/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/arm/CMSIS-DSP/PrivateInclude" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/arm/CMSIS-DSP/Include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/npu/ethos-u-core-software/lib/layer_by_layer_profiler/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/npu/ethos-u-core-software/lib/ethosu_monitor/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/npu/ethos-u-core-software/lib/ethosu_profiler/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/npu/ethos-u-core-driver/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/npu/ruy" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/npu/gemmlowp" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/npu/tflite-micro" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/npu/ethos-u-core-software/lib/crc/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/npu/ethos-u-core-software/lib/arm_profiler/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/arm/CMSIS-View/EventRecorder/Include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/arm/CMSIS-View/EventRecorder/Config" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/src/ai_application" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/src/ai_application/common" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/src/ai_application/ruhmi_conversion_results" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/src/camera_layer" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/src/display_layer" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/src/time_counter" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/src/console_output" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/src/external_memory" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/fsp/src/r_mipi_csi" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/fsp/src/r_vin" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_hand_landmarkmodel_gesture_recognition_camera_LCD_FSP640/ra/fsp/src/r_drw" -D_RENESAS_RA_ -D_RA_CORE=CPU0 -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c "$<" -c -o "$@")
	@clang --target=arm-none-eabi @"$@.in"

