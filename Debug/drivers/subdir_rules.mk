################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
drivers/LCD\ 8bit.obj: ../drivers/LCD\ 8bit.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="E:/STUDY/192_semester/Embedded_System_Programming/Exercise/FreeRTOS_Ex2" --include_path="E:/STUDY/192_semester/Embedded_System_Programming/Exercise/FreeRTOS_Ex2/Application" --include_path="E:/STUDY/192_semester/Embedded_System_Programming/Exercise/FreeRTOS_Ex2" --include_path="E:/STUDY/192_semester/Embedded_System_Programming/Exercise/FreeRTOS_Ex2/drivers" --include_path="E:/STUDY/192_semester/Embedded_System_Programming/Exercise/FreeRTOS_Ex2/FreeRTOS" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="drivers/LCD 8bit.d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

drivers/%.obj: ../drivers/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="E:/STUDY/192_semester/Embedded_System_Programming/Exercise/FreeRTOS_Ex2" --include_path="E:/STUDY/192_semester/Embedded_System_Programming/Exercise/FreeRTOS_Ex2/Application" --include_path="E:/STUDY/192_semester/Embedded_System_Programming/Exercise/FreeRTOS_Ex2" --include_path="E:/STUDY/192_semester/Embedded_System_Programming/Exercise/FreeRTOS_Ex2/drivers" --include_path="E:/STUDY/192_semester/Embedded_System_Programming/Exercise/FreeRTOS_Ex2/FreeRTOS" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="drivers/$(basename $(<F)).d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


