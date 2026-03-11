################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../ra/npu/tflite-micro/tensorflow/lite/micro/flatbuffer_utils.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/memory_helpers.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/micro_allocation_info.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/micro_allocator.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/micro_context.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/micro_interpreter.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/micro_interpreter_context.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/micro_interpreter_graph.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/micro_log.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/micro_op_resolver.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/micro_profiler.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/micro_resource_variable.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/micro_utils.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/recording_micro_allocator.cc 

CREF += \
ek_ra8p1_vision_face_detection_yolo_fastest.cref 

CC_DEPS += \
./ra/npu/tflite-micro/tensorflow/lite/micro/flatbuffer_utils.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/memory_helpers.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_allocation_info.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_allocator.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_context.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_interpreter.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_interpreter_context.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_interpreter_graph.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_log.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_op_resolver.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_profiler.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_resource_variable.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_utils.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/recording_micro_allocator.d 

OBJS += \
./ra/npu/tflite-micro/tensorflow/lite/micro/flatbuffer_utils.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/memory_helpers.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_allocation_info.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_allocator.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_context.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_interpreter.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_interpreter_context.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_interpreter_graph.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_log.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_op_resolver.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_profiler.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_resource_variable.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/micro_utils.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/recording_micro_allocator.o 

MAP += \
ek_ra8p1_vision_face_detection_yolo_fastest.map 


# Each subdirectory must supply rules for building sources it contributes
ra/npu/tflite-micro/tensorflow/lite/micro/%.o: ../ra/npu/tflite-micro/tensorflow/lite/micro/%.cc
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m85 -mthumb -mlittle-endian -mfloat-abi=hard -Os -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c++17 -flax-vector-conversions -fshort-enums -fno-unroll-loops -fno-rtti -fno-exceptions -w -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\src" -I"." -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\fsp\\inc" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\fsp\\inc\\api" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\fsp\\inc\\instances" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\fsp\\src\\rm_freertos_port" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\aws\\FreeRTOS\\FreeRTOS\\Source\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra_gen" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra_cfg\\fsp_cfg\\bsp" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra_cfg\\fsp_cfg" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra_cfg\\aws" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\fsp\\src\\rm_ethosu" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\tes\\dave2d\\inc" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\arm\\CMSIS-NN\\Include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\arm\\CMSIS-NN" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\npu\\flatbuffers\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\arm\\CMSIS-DSP\\PrivateInclude" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\arm\\CMSIS-DSP\\Include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\npu\\ethos-u-core-software\\lib\\layer_by_layer_profiler\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_monitor\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_profiler\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\npu\\ethos-u-core-driver\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\npu\\ruy" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\npu\\gemmlowp" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\npu\\tflite-micro" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\npu\\ethos-u-core-software\\lib\\crc\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\npu\\ethos-u-core-software\\lib\\arm_profiler\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\arm\\CMSIS-View\\EventRecorder\\Include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\arm\\CMSIS-View\\EventRecorder\\Config" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\src\\ai_application" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\src\\ai_application\\common" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\src\\ai_application\\face_detection" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\src\\ai_application\\ruhmi_conversion_results" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\src\\camera_layer" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\src\\display_layer" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\src\\time_counter" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\src\\console_output" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\src\\external_memory" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\fsp\\src\\r_mipi_csi" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\fsp\\src\\r_vin" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_face_detection_yolo_fastest\\ra\\fsp\\src\\r_drw" -D_RENESAS_RA_ -D_RA_CORE=CPU0 -DTF_LITE_STATIC_MEMORY -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c++ "$<" -c -o "$@")
	@clang++ --target=arm-none-eabi @"$@.in"

