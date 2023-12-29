################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 

  ifeq ($(shell uname),Linux)
     LP_ROOT = $(HOME)/projects/LP
     OPER_SYS = LINUX
     MY_FLAGS = -DSYS_LINUX -DMY_DEBUG
  endif


SUB_DIR := $(LP_ROOT)/Glycolysis

CPP_SRCS += \
$(SUB_DIR)/gui/imgui.cpp \
$(SUB_DIR)/gui/imgui_draw.cpp \
$(SUB_DIR)/gui/LPGui.cpp

OBJS += \
$(SUB_DIR)/Debug/gui/imgui.o \
$(SUB_DIR)/Debug/gui/imgui_draw.o \
$(SUB_DIR)/Debug/gui/LPGui.o

CPP_DEPS += \
$(SUB_DIR)/Debug/gui/imgui.d \
$(SUB_DIR)/Debug/gui/imgui_draw.d \
$(SUB_DIR)/Debug/gui/LPGui.d 



# Each subdirectory must supply rules for building sources it contributes
$(SUB_DIR)/Debug/gui/%.o: $(SUB_DIR)/gui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_LINUX -I"$(LP_ROOT)/BEvent" -I"$(LP_ROOT)/BEvent/inc" -I"$(LP_ROOT)/freetype-2.4.12/include" -I"$(LP_ROOT)/bullet-2.82-r2704/src" -I"$(LP_ROOT)/assimp-3.3.1/include" -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


