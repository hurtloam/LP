################################################################################
# Automatically-generated file. Do not edit!
################################################################################
  ifeq ($(shell uname),Linux)
     LP_ROOT = $(HOME)/projects/LP
     OPER_SYS = LINUX
     MY_FLAGS = -DSYS_LINUX -DMY_DEBUG
  endif


SUB_DIR := $(LP_ROOT)/Glycolysis
# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
$(SUB_DIR)/gui/examples/sdl_opengl3_example/imgui_impl_sdl_gl3.cpp 

OBJS += \
$(SUB_DIR)/Debug/gui/examples/sdl_opengl3_example/imgui_impl_sdl_gl3.o 

CPP_DEPS += \
$(SUB_DIR)/Debug/gui/examples/sdl_opengl3_example/imgui_impl_sdl_gl3.d 


# Each subdirectory must supply rules for building sources it contributes
$(SUB_DIR)/Debug/gui/examples/sdl_opengl3_example/%.o: $(SUB_DIR)/gui/examples/sdl_opengl3_example/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_LINUX -I"/home/peter/projects/workspace-cpp2_git/BEvent" -I"/home/peter/projects/workspace-cpp2_git/BEvent/inc" -I"$(LP_ROOT)/freetype-2.4.12/include" -I"/home/peter/projects/workspace-cpp2_git/../bullet-2.82-r2704/src" -I"/home/peter/projects/workspace-cpp2_git/../assimp-3.3.1/include" -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


