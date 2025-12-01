################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/tes/dave2d/src/dave_64bitoperation.c \
../ra/tes/dave2d/src/dave_base.c \
../ra/tes/dave2d/src/dave_blit.c \
../ra/tes/dave2d/src/dave_box.c \
../ra/tes/dave2d/src/dave_circle.c \
../ra/tes/dave2d/src/dave_context.c \
../ra/tes/dave2d/src/dave_curve.c \
../ra/tes/dave2d/src/dave_dlist.c \
../ra/tes/dave2d/src/dave_driver.c \
../ra/tes/dave2d/src/dave_edge.c \
../ra/tes/dave2d/src/dave_errorcodes.c \
../ra/tes/dave2d/src/dave_gradient.c \
../ra/tes/dave2d/src/dave_hardware.c \
../ra/tes/dave2d/src/dave_line.c \
../ra/tes/dave2d/src/dave_math.c \
../ra/tes/dave2d/src/dave_memory.c \
../ra/tes/dave2d/src/dave_pattern.c \
../ra/tes/dave2d/src/dave_perfcount.c \
../ra/tes/dave2d/src/dave_polyline.c \
../ra/tes/dave2d/src/dave_quad.c \
../ra/tes/dave2d/src/dave_rbuffer.c \
../ra/tes/dave2d/src/dave_render.c \
../ra/tes/dave2d/src/dave_texture.c \
../ra/tes/dave2d/src/dave_triangle.c \
../ra/tes/dave2d/src/dave_utility.c \
../ra/tes/dave2d/src/dave_viewport.c \
../ra/tes/dave2d/src/dave_wedge.c 

CREF += \
vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_mobilenet_v1.cref 

C_DEPS += \
./ra/tes/dave2d/src/dave_64bitoperation.d \
./ra/tes/dave2d/src/dave_base.d \
./ra/tes/dave2d/src/dave_blit.d \
./ra/tes/dave2d/src/dave_box.d \
./ra/tes/dave2d/src/dave_circle.d \
./ra/tes/dave2d/src/dave_context.d \
./ra/tes/dave2d/src/dave_curve.d \
./ra/tes/dave2d/src/dave_dlist.d \
./ra/tes/dave2d/src/dave_driver.d \
./ra/tes/dave2d/src/dave_edge.d \
./ra/tes/dave2d/src/dave_errorcodes.d \
./ra/tes/dave2d/src/dave_gradient.d \
./ra/tes/dave2d/src/dave_hardware.d \
./ra/tes/dave2d/src/dave_line.d \
./ra/tes/dave2d/src/dave_math.d \
./ra/tes/dave2d/src/dave_memory.d \
./ra/tes/dave2d/src/dave_pattern.d \
./ra/tes/dave2d/src/dave_perfcount.d \
./ra/tes/dave2d/src/dave_polyline.d \
./ra/tes/dave2d/src/dave_quad.d \
./ra/tes/dave2d/src/dave_rbuffer.d \
./ra/tes/dave2d/src/dave_render.d \
./ra/tes/dave2d/src/dave_texture.d \
./ra/tes/dave2d/src/dave_triangle.d \
./ra/tes/dave2d/src/dave_utility.d \
./ra/tes/dave2d/src/dave_viewport.d \
./ra/tes/dave2d/src/dave_wedge.d 

OBJS += \
./ra/tes/dave2d/src/dave_64bitoperation.o \
./ra/tes/dave2d/src/dave_base.o \
./ra/tes/dave2d/src/dave_blit.o \
./ra/tes/dave2d/src/dave_box.o \
./ra/tes/dave2d/src/dave_circle.o \
./ra/tes/dave2d/src/dave_context.o \
./ra/tes/dave2d/src/dave_curve.o \
./ra/tes/dave2d/src/dave_dlist.o \
./ra/tes/dave2d/src/dave_driver.o \
./ra/tes/dave2d/src/dave_edge.o \
./ra/tes/dave2d/src/dave_errorcodes.o \
./ra/tes/dave2d/src/dave_gradient.o \
./ra/tes/dave2d/src/dave_hardware.o \
./ra/tes/dave2d/src/dave_line.o \
./ra/tes/dave2d/src/dave_math.o \
./ra/tes/dave2d/src/dave_memory.o \
./ra/tes/dave2d/src/dave_pattern.o \
./ra/tes/dave2d/src/dave_perfcount.o \
./ra/tes/dave2d/src/dave_polyline.o \
./ra/tes/dave2d/src/dave_quad.o \
./ra/tes/dave2d/src/dave_rbuffer.o \
./ra/tes/dave2d/src/dave_render.o \
./ra/tes/dave2d/src/dave_texture.o \
./ra/tes/dave2d/src/dave_triangle.o \
./ra/tes/dave2d/src/dave_utility.o \
./ra/tes/dave2d/src/dave_viewport.o \
./ra/tes/dave2d/src/dave_wedge.o 

MAP += \
vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_mobilenet_v1.map 


# Each subdirectory must supply rules for building sources it contributes
ra/tes/dave2d/src/%.o: ../ra/tes/dave2d/src/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m85 -mthumb -mlittle-endian -mfloat-abi=hard -O2 -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c99 -flax-vector-conversions -fshort-enums -fno-unroll-loops -w -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\src" -I"." -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\fsp\\inc" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\fsp\\inc\\api" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\fsp\\inc\\instances" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\fsp\\src\\rm_freertos_port" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\aws\\FreeRTOS\\FreeRTOS\\Source\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra_gen" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra_cfg\\fsp_cfg\\bsp" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra_cfg\\fsp_cfg" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra_cfg\\aws" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\src\\ai_application" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\src\\ai_application\\common" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\src\\camera_layer" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\src\\display_layer" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\src\\fsp_custom" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\src\\time_counter" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\src\\console_output" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\src\\external_memory" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\tes\\dave2d\\inc" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\arm\\CMSIS-View\\EventRecorder\\Include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\arm\\CMSIS-View\\EventRecorder\\Config" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\npu\\ruy" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\npu\\gemmlowp" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\npu\\tflite-micro" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\npu\\ethos-u-core-software\\lib\\crc\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_profiler\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\npu\\ethos-u-core-software\\lib\\layer_by_layer_profiler\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\npu\\ethos-u-core-software\\lib\\arm_profiler\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_monitor\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\npu\\ethos-u-core-driver\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\fsp\\src\\rm_ethosu" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\arm\\CMSIS-DSP\\PrivateInclude" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\arm\\CMSIS-DSP\\Include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\npu\\flatbuffers\\include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\arm\\CMSIS-NN\\Include" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\ra\\arm\\CMSIS-NN" -I"C:\\Users\\a5033228\\e2_studio\\workspace_20251201\\image_classification.zip_expanded\\image_classification\\src\\ai_application\\image_classification" -D_RENESAS_RA_ -D_RA_CORE=CPU0 -DETHOSU55 -DETHOSU_ARCH=u55 -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c "$<" -c -o "$@")
	@clang --target=arm-none-eabi @"$@.in"

