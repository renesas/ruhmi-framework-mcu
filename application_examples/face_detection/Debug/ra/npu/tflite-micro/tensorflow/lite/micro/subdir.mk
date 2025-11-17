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
vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest.cref 

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
vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest.map 


# Each subdirectory must supply rules for building sources it contributes
ra/npu/tflite-micro/tensorflow/lite/micro/%.o: ../ra/npu/tflite-micro/tensorflow/lite/micro/%.cc
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m85 -mthumb -mlittle-endian -mfloat-abi=hard -O2 -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c++17 -flax-vector-conversions -fshort-enums -fno-unroll-loops -fno-rtti -fno-exceptions -w -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\src" -I"." -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\fsp\\inc" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\fsp\\inc\\api" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\fsp\\inc\\instances" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\fsp\\src\\rm_freertos_port" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\aws\\FreeRTOS\\FreeRTOS\\Source\\include" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra_gen" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra_cfg\\fsp_cfg\\bsp" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra_cfg\\fsp_cfg" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra_cfg\\aws" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\src\\ai_application" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\src\\ai_application\\common" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\src\\ai_application\\face_detection" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\src\\camera_layer" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\src\\display_layer" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\src\\fsp_custom" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\src\\time_counter" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\src\\console_output" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\src\\external_memory" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\tes\\dave2d\\inc" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\arm\\CMSIS-View\\EventRecorder\\Include" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\arm\\CMSIS-View\\EventRecorder\\Config" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\npu\\ruy" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\npu\\gemmlowp" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\npu\\tflite-micro" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\npu\\ethos-u-core-software\\lib\\crc\\include" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_profiler\\include" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\npu\\ethos-u-core-software\\lib\\layer_by_layer_profiler\\include" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\npu\\ethos-u-core-software\\lib\\arm_profiler\\include" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_monitor\\include" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\npu\\ethos-u-core-driver\\include" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\fsp\\src\\rm_ethosu" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\arm\\CMSIS-DSP\\PrivateInclude" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\arm\\CMSIS-DSP\\Include" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\npu\\flatbuffers\\include" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\arm\\CMSIS-NN\\Include" -I"C:\\Users\\a5125834\\Desktop\\_SolutionTeam\\RUHMI\\test_app_example\\20250925\\ruhmi-framework-mcu\\application_examples\\face_detection\\ra\\arm\\CMSIS-NN" -D_RENESAS_RA_ -D_RA_CORE=CPU0 -DETHOSU55 -DNDEBUG -DTF_LITE_STATIC_MEMORY -DFLATBUFFERS_LOCALE_INDEPENDENT=0 -DCMSIS_NN -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c++ "$<" -c -o "$@")
	@clang++ --target=arm-none-eabi @"$@.in"

