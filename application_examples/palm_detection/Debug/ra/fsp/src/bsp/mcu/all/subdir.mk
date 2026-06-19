################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/bsp/mcu/all/bsp_clocks.c \
../ra/fsp/src/bsp/mcu/all/bsp_common.c \
../ra/fsp/src/bsp/mcu/all/bsp_delay.c \
../ra/fsp/src/bsp/mcu/all/bsp_group_irq.c \
../ra/fsp/src/bsp/mcu/all/bsp_guard.c \
../ra/fsp/src/bsp/mcu/all/bsp_io.c \
../ra/fsp/src/bsp/mcu/all/bsp_ipc.c \
../ra/fsp/src/bsp/mcu/all/bsp_irq.c \
../ra/fsp/src/bsp/mcu/all/bsp_macl.c \
../ra/fsp/src/bsp/mcu/all/bsp_ospi_b.c \
../ra/fsp/src/bsp/mcu/all/bsp_register_protection.c \
../ra/fsp/src/bsp/mcu/all/bsp_sbrk.c \
../ra/fsp/src/bsp/mcu/all/bsp_sdram.c \
../ra/fsp/src/bsp/mcu/all/bsp_security.c 

CREF += \
ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640.cref 

C_DEPS += \
./ra/fsp/src/bsp/mcu/all/bsp_clocks.d \
./ra/fsp/src/bsp/mcu/all/bsp_common.d \
./ra/fsp/src/bsp/mcu/all/bsp_delay.d \
./ra/fsp/src/bsp/mcu/all/bsp_group_irq.d \
./ra/fsp/src/bsp/mcu/all/bsp_guard.d \
./ra/fsp/src/bsp/mcu/all/bsp_io.d \
./ra/fsp/src/bsp/mcu/all/bsp_ipc.d \
./ra/fsp/src/bsp/mcu/all/bsp_irq.d \
./ra/fsp/src/bsp/mcu/all/bsp_macl.d \
./ra/fsp/src/bsp/mcu/all/bsp_ospi_b.d \
./ra/fsp/src/bsp/mcu/all/bsp_register_protection.d \
./ra/fsp/src/bsp/mcu/all/bsp_sbrk.d \
./ra/fsp/src/bsp/mcu/all/bsp_sdram.d \
./ra/fsp/src/bsp/mcu/all/bsp_security.d 

OBJS += \
./ra/fsp/src/bsp/mcu/all/bsp_clocks.o \
./ra/fsp/src/bsp/mcu/all/bsp_common.o \
./ra/fsp/src/bsp/mcu/all/bsp_delay.o \
./ra/fsp/src/bsp/mcu/all/bsp_group_irq.o \
./ra/fsp/src/bsp/mcu/all/bsp_guard.o \
./ra/fsp/src/bsp/mcu/all/bsp_io.o \
./ra/fsp/src/bsp/mcu/all/bsp_ipc.o \
./ra/fsp/src/bsp/mcu/all/bsp_irq.o \
./ra/fsp/src/bsp/mcu/all/bsp_macl.o \
./ra/fsp/src/bsp/mcu/all/bsp_ospi_b.o \
./ra/fsp/src/bsp/mcu/all/bsp_register_protection.o \
./ra/fsp/src/bsp/mcu/all/bsp_sbrk.o \
./ra/fsp/src/bsp/mcu/all/bsp_sdram.o \
./ra/fsp/src/bsp/mcu/all/bsp_security.o 

MAP += \
ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/bsp/mcu/all/%.o: ../ra/fsp/src/bsp/mcu/all/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m85 -mthumb -mlittle-endian -mfloat-abi=hard -Os -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c99 -flax-vector-conversions -fshort-enums -fno-unroll-loops -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/src" -I"." -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/fsp/inc" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/fsp/inc/api" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/fsp/inc/instances" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/fsp/src/rm_freertos_port" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/aws/FreeRTOS/FreeRTOS/Source/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/arm/CMSIS_6/CMSIS/Core/Include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra_gen" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra_cfg/fsp_cfg/bsp" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra_cfg/fsp_cfg" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra_cfg/aws" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/fsp/src/rm_ethosu" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/tes/dave2d/inc" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/arm/CMSIS-NN/Include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/arm/CMSIS-NN" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/npu/flatbuffers/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/arm/CMSIS-DSP/PrivateInclude" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/arm/CMSIS-DSP/Include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/npu/ethos-u-core-software/lib/layer_by_layer_profiler/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/npu/ethos-u-core-software/lib/ethosu_monitor/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/npu/ethos-u-core-software/lib/ethosu_profiler/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/npu/ethos-u-core-driver/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/npu/ruy" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/npu/gemmlowp" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/npu/tflite-micro" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/npu/ethos-u-core-software/lib/crc/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/npu/ethos-u-core-software/lib/arm_profiler/include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/arm/CMSIS-View/EventRecorder/Include" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/arm/CMSIS-View/EventRecorder/Config" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/src/ai_application" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/src/ai_application/common" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/src/ai_application/ruhmi_conversion_results" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/src/camera_layer" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/src/display_layer" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/src/time_counter" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/src/console_output" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/src/external_memory" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/fsp/src/r_mipi_csi" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/fsp/src/r_vin" -I"/home/eldorado/e2_studio/workspace_6.4/ek_ra8p1_vision_palm_detection_model_camera_LCD_FSP640/ra/fsp/src/r_drw" -D_RENESAS_RA_ -D_RA_CORE=CPU0 -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c "$<" -c -o "$@")
	@clang --target=arm-none-eabi @"$@.in"

