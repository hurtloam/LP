
RM := rm -rf

OPER_SYS = UNDEFINED_WIN
ifeq ($(OS),Windows_NT)
  OPER_SYS = WINNT
  LP_ROOT = C:/Users/peter/projects/LP
  MY_FLAGS = -DSYS_WINNT -DMY_DEBUG
else
  ifeq ($(shell uname),Linux)
     LP_ROOT = $(HOME)/projects/LP
     OPER_SYS = LINUX
     MY_FLAGS = -DSYS_LINUX -DMY_DEBUG
  endif
endif

# All of the sources participating in the build are defined here

#-include ../Debug/src/subdir.mk
#-include ../Debug/objects.mk

-include test/subdir.mk
-include subdir.mk

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

# All Target
all: EventSM


#dependents:
#	-cd $(LP_ROOT)/BEvent/Debug && $(MAKE) all

# Tool invocations
#EventSM: $(OBJS) $(USER_OBJS) $(LP_ROOT)/BEvent/Debug/libBEvent.a
EventSM: $(OBJS) $(USER_OBJS)
	@echo 'Operating System =  $(OPER_SYS)'
	@echo 'Operating System =  $(MY_FLAGS)'
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
#	g++ -fpermissive -L"$(LP_ROOT)/BEvent/Debug" -L"$(LP_ROOT)/bullet-2.82-r2704/src/BulletDynamics" -L"$(LP_ROOT)/bullet-2.82-r2704/src/BulletCollision" -L"$(LP_ROOT)/bullet-2.82-r2704/src/LinearMath" -L"$(LP_ROOT)/assimp-3.3.1/lib" -L"$(LP_ROOT)/lua-5.1/src" -L/usr/local/lib/ -L/usr/src/gtest -L/usr/src/gmock -L/usr/local/lib/ -L/lib/x86_64-linux-gnu -p -o "EventSM" $(OBJS) $(USER_OBJS) $(LIBS) -lgtest -lgtest_main -pthread -lpthread -lgmock -lgmock_main
	g++ -fpermissive -L"$(LP_ROOT)/lib" -L"$(LP_ROOT)/bullet-2.82-r2704/src/BulletDynamics" -L"$(LP_ROOT)/bullet-2.82-r2704/src/BulletCollision" -L"$(LP_ROOT)/bullet-2.82-r2704/src/.libs" -L"$(LP_ROOT)/bullet-2.82-r2704/src/LinearMath" -L/usr/local/lib/ -L/usr/src/gtest -L/usr/src/gmock -L/usr/local/lib/ -L/lib/x86_64-linux-gnu -p -o "EventSM" $(OBJS) $(USER_OBJS) $(LIBS) -lBulletDynamics -lBulletCollision -lLinearMath -lgtest -lgtest_main -pthread -lpthread -lgmock -lgmock_main
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) EventSM
	-@echo ' '

.PHONY: all clean dependents test

