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
../ra/fsp/src/bsp/mcu/all/bsp_register_protection.c \
../ra/fsp/src/bsp/mcu/all/bsp_sbrk.c \
../ra/fsp/src/bsp/mcu/all/bsp_sdram.c \
../ra/fsp/src/bsp/mcu/all/bsp_security.c 

CREF += \
vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest.cref 

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
./ra/fsp/src/bsp/mcu/all/bsp_register_protection.o \
./ra/fsp/src/bsp/mcu/all/bsp_sbrk.o \
./ra/fsp/src/bsp/mcu/all/bsp_sdram.o \
./ra/fsp/src/bsp/mcu/all/bsp_security.o 

MAP += \
vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/bsp/mcu/all/%.o: ../ra/fsp/src/bsp/mcu/all/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m85 -mthumb -mlittle-endian -mfloat-abi=hard -O2 -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c99 -flax-vector-conversions -fshort-enums -fno-unroll-loops -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\src" -I"." -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\fsp\\inc" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\fsp\\inc\\api" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\fsp\\inc\\instances" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\fsp\\src\\rm_freertos_port" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\aws\\FreeRTOS\\FreeRTOS\\Source\\include" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra_gen" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra_cfg\\fsp_cfg\\bsp" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra_cfg\\fsp_cfg" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra_cfg\\aws" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\src\\ai_application" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\src\\ai_application\\common" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\src\\ai_application\\face_detection" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\src\\camera_layer" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\src\\display_layer" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\src\\fsp_custom" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\src\\time_counter" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\src\\console_output" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\src\\external_memory" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\tes\\dave2d\\inc" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\arm\\CMSIS-View\\EventRecorder\\Include" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\arm\\CMSIS-View\\EventRecorder\\Config" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\npu\\ruy" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\npu\\gemmlowp" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\npu\\tflite-micro" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\npu\\ethos-u-core-software\\lib\\crc\\include" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_profiler\\include" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\npu\\ethos-u-core-software\\lib\\layer_by_layer_profiler\\include" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\npu\\ethos-u-core-software\\lib\\arm_profiler\\include" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\npu\\ethos-u-core-software\\lib\\ethosu_monitor\\include" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\npu\\ethos-u-core-driver\\include" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\fsp\\src\\rm_ethosu" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\arm\\CMSIS-DSP\\PrivateInclude" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\arm\\CMSIS-DSP\\Include" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\npu\\flatbuffers\\include" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\arm\\CMSIS-NN\\Include" -I"C:\\Users\\a5139312\\Downloads\\AI_app_fsp6.0.0\\vision_ai_ethosu_mipicsi_glcd_ek_ra8p1_llvm_mera_yolo_fastest\\ra\\arm\\CMSIS-NN" -D_RENESAS_RA_ -D_RA_CORE=CPU0 -DETHOSU55 -DETHOSU_ARCH=u55 -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c "$<" -c -o "$@")
	@clang --target=arm-none-eabi @"$@.in"

