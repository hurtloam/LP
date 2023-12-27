
# Add inputs and outputs from these tool invocations to the build variables

SUB_DIR = $(LP_ROOT)/Glycolysis/command
 
CPP_SRCS += \
$(SUB_DIR)/src/AlterGridCmd.cpp \
$(SUB_DIR)/src/AlterCameraSpeedCmd.cpp \
$(SUB_DIR)/src/PrintCameraPositionCmd.cpp \
$(SUB_DIR)/src/Command.cpp

OBJS += \
$(SUB_DIR)/build/AlterGridCmd.o \
$(SUB_DIR)/build/AlterCameraSpeedCmd.o \
$(SUB_DIR)/build/PrintCameraPositionCmd.o \
$(SUB_DIR)/build/Command.o

CPP_DEPS += \
$(SUB_DIR)/build/AlterGridCmd.d \
$(SUB_DIR)/build/AlterCameraSpeedCmd.d \
$(SUB_DIR)/build/PrintCameraPositionCmd.d \
$(SUB_DIR)/build/Command.d


# Each subdirectory must supply rules for building sources it contributes
$(SUB_DIR)/build/%.o: $(SUB_DIR)/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
#	g++ -D_LINUX -I"$(LP_ROOT)/BEvent" -I"$(LP_ROOT)/BEvent/inc" -I"$(LP_ROOT)/freetype-2.4.12/include" -I"$(LP_ROOT)/bullet-2.82-r2704/src" -I"$(LP_ROOT)/assimp-3.3.1/include" -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -std=c++11 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	g++ -D_LINUX -I"$(LP_ROOT)/BEvent" -I"$(LP_ROOT)/BEvent/inc" -I"$(LP_ROOT)/freetype-2.4.12/include" -I"$(LP_ROOT)/bullet-2.82-r2704/src" -I"$(LP_ROOT)/assimp-3.3.1/include" -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -std=c++11 -fPIC -MMD -MP  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
