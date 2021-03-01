################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ex_main.c 

OBJS += \
./src/ex_main.o 

C_DEPS += \
./src/ex_main.d 


# Each subdirectory must supply rules for building sources it contributes
src/ex_main.o: ../src/ex_main.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32PG12B500F1024GL125=1' -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//platform/service/sleeptimer/config" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//platform/service/sleeptimer/inc" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//platform/service/sleeptimer/src" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//platform/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//platform/micrium_os" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//app/mcu_example/SLSTK3402A_EFM32PG12/micriumos_blink/cfg" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//app/mcu_example/SLSTK3402A_EFM32PG12/micriumos_blink" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//util/third_party/segger/systemview/SEGGER" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//util/third_party/segger/systemview/Config" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//util/third_party/segger/systemview/Sample/MicriumOSKernel" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/SLSTK3402A_EFM32PG12/config" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//platform/Device/SiliconLabs/EFM32PG12B/Include" -I"C:/SiliconLabs/SimplicityStudio/v4_2/developer/sdks/gecko_sdk_suite/v2.7//platform/micrium_os/bsp/siliconlabs/generic/include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/ex_main.d" -MT"src/ex_main.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


