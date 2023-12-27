################################################################################
# Automatically-generated file. Do not edit!
################################################################################

RM := rm -rf

OPER_SYS = UNDEFINED_WIN
ifeq ($(OS),Windows_NT)
  OPER_SYS = WINNT
  LP_ROOT = C:/Users/peter/git/LP
  MY_FLAGS = -DSYS_WINNT -DMY_DEBUG
else
  ifeq ($(shell uname),Linux)
     LP_ROOT = $(HOME)/projects/LP
     OPER_SYS = LINUX
     MY_FLAGS = -DSYS_LINUX -DMY_DEBUG
  endif
endif

# All of the sources participating in the build are defined here
include $(LP_ROOT)/Glycolysis/Debug/src/subdir.mk

include $(LP_ROOT)/Glycolysis/Debug/gui/extra_fonts/subdir.mk
include $(LP_ROOT)/Glycolysis/Debug/gui/examples/sdl_opengl3_example/subdir.mk
include $(LP_ROOT)/Glycolysis/Debug/gui/subdir.mk
include $(LP_ROOT)/Glycolysis/command/subdir.mk
include $(LP_ROOT)/Glycolysis/event_sm/subdir.mk
include $(LP_ROOT)/Glycolysis/eventstate/subdir.mk

include subdir.mk
include test/subdir.mk
include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif
-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# -L"C:/MinGW/mingw64/x86_64-w64-mingw32/lib"



# All Target
all: dependents Glycolysis

dependents:
	-cd $(LP_ROOT)/BEvent/Debug && $(MAKE) all

# Tool invocations
Glycolysis: $(OBJS) $(USER_OBJS) $(LP_ROOT)/BEvent/Debug/libBEvent.a
	@echo 'Operating System = $(MY_FLAGS)'
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++   -o "Glycolysis" $(OBJS) $(USER_OBJS) $(LIBPATHS) $(LIBS) $(CPPFLAGS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) $(LP_ROOT)/BEvent/Debug/libBEvent.a Glycolysis
	-@echo ' '

.PHONY: all clean dependents test
.SECONDARY:
$(LP_ROOT)/BEvent/Debug/libBEvent.a:

-include ../makefile.targets
