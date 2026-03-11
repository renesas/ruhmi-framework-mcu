################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/add.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/batch_matmul.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/conv.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/depthwise_conv.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/fully_connected.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/maximum_minimum.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/mul.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/pooling.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/softmax.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/svdf.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/transpose_conv.cc \
../ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/unidirectional_sequence_lstm.cc 

CREF += \
ek_ra8p1_vision_image_classification_mobilenet_v1.cref 

CC_DEPS += \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/add.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/batch_matmul.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/conv.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/depthwise_conv.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/fully_connected.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/maximum_minimum.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/mul.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/pooling.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/softmax.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/svdf.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/transpose_conv.d \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/unidirectional_sequence_lstm.d 

OBJS += \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/add.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/batch_matmul.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/conv.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/depthwise_conv.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/fully_connected.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/maximum_minimum.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/mul.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/pooling.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/softmax.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/svdf.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/transpose_conv.o \
./ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/unidirectional_sequence_lstm.o 

MAP += \
ek_ra8p1_vision_image_classification_mobilenet_v1.map 


# Each subdirectory must supply rules for building sources it contributes
ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/%.o: ../ra/npu/tflite-micro/tensorflow/lite/micro/kernels/cmsis_nn/%.cc
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m85 -mthumb -mlittle-endian -mfloat-abi=hard -O2 -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c++17 -flax-vector-conversions -fshort-enums -fno-unroll-loops -fno-rtti -fno-exceptions -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\src" -I"." -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\fsp\\inc" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\fsp\\inc\\api" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\fsp\\inc\\instances" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\fsp\\src\\rm_freertos_port" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\aws\\FreeRTOS\\FreeRTOS\\Source\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra_gen" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra_cfg\\fsp_cfg\\bsp" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra_cfg\\fsp_cfg" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra_cfg\\aws" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\fsp\\src\\rm_ethosu" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\tes\\dave2d\\inc" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\arm\\CMSIS-NN\\Include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\arm\\CMSIS-NN" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\npu\\flatbuffers\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\arm\\CMSIS-DSP\\PrivateInclude" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\arm\\CMSIS-DSP\\Include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\npu\\ethos-u-core-software\\lib\\layer_by_layer_profiler\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_monitor\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_profiler\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\npu\\ethos-u-core-driver\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\npu\\ruy" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\npu\\gemmlowp" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\npu\\tflite-micro" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\npu\\ethos-u-core-software\\lib\\crc\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\npu\\ethos-u-core-software\\lib\\arm_profiler\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\arm\\CMSIS-View\\EventRecorder\\Include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\arm\\CMSIS-View\\EventRecorder\\Config" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\src\\ai_application" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\src\\ai_application\\common" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\src\\ai_application\\image_classification" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\src\\ai_application\\ruhmi_conversion_results" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\src\\camera_layer" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\src\\display_layer" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\src\\time_counter" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\src\\console_output" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\src\\external_memory" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\fsp\\src\\r_mipi_csi" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\fsp\\src\\r_vin" -I"C:\\Users\\a5033228\\e2_studio\\workspace_app_test\\ek_ra8p1_vision_image_classification_mobilenet_v1\\ra\\fsp\\src\\r_drw" -D_RENESAS_RA_ -D_RA_CORE=CPU0 -DTF_LITE_STATIC_MEMORY -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c++ "$<" -c -o "$@")
	@clang++ --target=arm-none-eabi @"$@.in"

