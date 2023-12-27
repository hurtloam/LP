
# Add inputs and outputs from these tool invocations to the build variables

SUB_DIR = $(LP_ROOT)/Glycolysis/eventstate
 
CPP_SRCS += \
$(SUB_DIR)/src/EventState.cpp

OBJS += \
$(SUB_DIR)/build/EventState.o

CPP_DEPS += \
$(SUB_DIR)/build/EventState.d

# Each subdirectory must supply rules for building sources it contributes
$(SUB_DIR)/build/%.o: $(SUB_DIR)/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_LINUX -I"$(LP_ROOT)/BEvent" -I"$(LP_ROOT)/BEvent/inc" -I"$(LP_ROOT)/freetype-2.4.12/include" -I"$(LP_ROOT)/bullet-2.82-r2704/src" -I"$(LP_ROOT)/assimp-3.3.1/include" -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -std=c++11 -fPIC -MMD -MP  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


