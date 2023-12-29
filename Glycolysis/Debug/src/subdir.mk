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
# $(SUB_DIR)/src/Actor.cpp \
# $(SUB_DIR)/src/Arrow.cpp \
# $(SUB_DIR)/src/Ball.cpp \
# $(SUB_DIR)/src/CoordinateLines.cpp \
# $(SUB_DIR)/src/Creature.cpp \
# $(SUB_DIR)/src/FallingCube.cpp \
# $(SUB_DIR)/src/FPerson.cpp \
# $(SUB_DIR)/src/GameLogic.cpp \
# $(SUB_DIR)/src/GameLogic2.cpp \
# $(SUB_DIR)/src/GameState.cpp \
# $(SUB_DIR)/src/Glucose.cpp \
# $(SUB_DIR)/src/Glucose6Phosphate.cpp \
# $(SUB_DIR)/src/Hexokinase.cpp \
# $(SUB_DIR)/src/IceCube.cpp \
# $(SUB_DIR)/src/InitError.cpp \
# $(SUB_DIR)/src/Landscape.cpp \
# $(SUB_DIR)/src/LPDebugDraw.cpp \
# $(SUB_DIR)/src/LPObject.cpp \
# $(SUB_DIR)/src/LearningPlatform.cpp \
# $(SUB_DIR)/src/LightSource.cpp \
# $(SUB_DIR)/src/LineObj.cpp \
# $(SUB_DIR)/src/logging.cpp \
# $(SUB_DIR)/src/MazeFloor.cpp \
# $(SUB_DIR)/src/MazeDoorX.cpp \
# $(SUB_DIR)/src/MazeDoorY.cpp \
# $(SUB_DIR)/src/MenuContainer.cpp \
# $(SUB_DIR)/src/MenuFactory.cpp \
# $(SUB_DIR)/src/MenuItem.cpp \
# $(SUB_DIR)/src/Mitochondria.cpp \
# $(SUB_DIR)/src/Molecule.cpp \
# $(SUB_DIR)/src/NoSign.cpp \
# $(SUB_DIR)/src/ObjectFactory.cpp \
# $(SUB_DIR)/src/Phosphofructokinase.cpp \
# $(SUB_DIR)/src/Plane.cpp \
# $(SUB_DIR)/src/Plate.cpp \
# $(SUB_DIR)/src/ResObj.cpp \
# $(SUB_DIR)/src/SDL_base.cpp \
# $(SUB_DIR)/src/Scene.cpp \
# $(SUB_DIR)/src/SignPost.cpp \
# $(SUB_DIR)/src/SignPost2.cpp \
# $(SUB_DIR)/src/SkyBox.cpp \
# $(SUB_DIR)/src/Sniper.cpp \
# $(SUB_DIR)/src/SoundBank.cpp \
# $(SUB_DIR)/src/StaticObj.cpp \
# $(SUB_DIR)/src/Text.cpp \
# $(SUB_DIR)/src/TextMenuItem.cpp \
# $(SUB_DIR)/src/TextObject.cpp \
# $(SUB_DIR)/src/ThreadProcess.cpp \
# $(SUB_DIR)/src/Two_PhosphoGlycerate.cpp \
# $(SUB_DIR)/src/View.cpp \
# $(SUB_DIR)/src/Wall.cpp \
# $(SUB_DIR)/src/WallCube.cpp \
# $(SUB_DIR)/src/WooddenCube.cpp \
# $(SUB_DIR)/src/WooddenCube2.cpp \
# $(SUB_DIR)/src/WinningArea.cpp \
# $(SUB_DIR)/src/objloader.cpp \
# $(SUB_DIR)/src/shader.cpp \
# $(SUB_DIR)/src/texture.cpp \
# $(SUB_DIR)/src/vboindexer.cpp \
# $(SUB_DIR)/src/L_Stage.cpp \
# $(SUB_DIR)/src/L_ResObj.cpp \
# $(SUB_DIR)/src/LuaIf.cpp \
# $(SUB_DIR)/src/LuaIfLPConfig.cpp \
# $(SUB_DIR)/src/LuaInteractive.cpp \
# $(SUB_DIR)/src/LPConfig.cpp
#$(SUB_DIR)/src/QtTerminal.cpp

OBJS += \
$(SUB_DIR)/Debug/src/Actor.o \
$(SUB_DIR)/Debug/src/Arrow.o \
$(SUB_DIR)/Debug/src/Ball.o \
$(SUB_DIR)/Debug/src/CoordinateLines.o \
$(SUB_DIR)/Debug/src/Creature.o \
$(SUB_DIR)/Debug/src/FallingCube.o \
$(SUB_DIR)/Debug/src/FPerson.o \
$(SUB_DIR)/Debug/src/Fructose6Phosphate.o \
$(SUB_DIR)/Debug/src/GameLogic.o \
$(SUB_DIR)/Debug/src/GameLogic2.o \
$(SUB_DIR)/Debug/src/GameState.o \
$(SUB_DIR)/Debug/src/Glucose.o \
$(SUB_DIR)/Debug/src/Glucose6Phosphate.o \
$(SUB_DIR)/Debug/src/Hexokinase.o \
$(SUB_DIR)/Debug/src/IceCube.o \
$(SUB_DIR)/Debug/src/InitError.o \
$(SUB_DIR)/Debug/src/Landscape.o \
$(SUB_DIR)/Debug/src/LPDebugDraw.o \
$(SUB_DIR)/Debug/src/LPObject.o \
$(SUB_DIR)/Debug/src/LearningPlatform.o \
$(SUB_DIR)/Debug/src/LightSource.o \
$(SUB_DIR)/Debug/src/LineObj.o \
$(SUB_DIR)/Debug/src/logging.o \
$(SUB_DIR)/Debug/src/MazeFloor.o \
$(SUB_DIR)/Debug/src/MazeDoorX.o \
$(SUB_DIR)/Debug/src/MazeDoorY.o \
$(SUB_DIR)/Debug/src/MenuContainer.o \
$(SUB_DIR)/Debug/src/MenuFactory.o \
$(SUB_DIR)/Debug/src/MenuItem.o \
$(SUB_DIR)/Debug/src/Mitochondria.o \
$(SUB_DIR)/Debug/src/Molecule.o \
$(SUB_DIR)/Debug/src/MoleculeSpot.o \
$(SUB_DIR)/Debug/src/NoSign.o \
$(SUB_DIR)/Debug/src/ObjectFactory.o \
$(SUB_DIR)/Debug/src/Phosphofructokinase.o \
$(SUB_DIR)/Debug/src/Plane.o \
$(SUB_DIR)/Debug/src/Plate.o \
$(SUB_DIR)/Debug/src/ResObj.o \
$(SUB_DIR)/Debug/src/SDL_base.o \
$(SUB_DIR)/Debug/src/Scene.o \
$(SUB_DIR)/Debug/src/SignPost.o \
$(SUB_DIR)/Debug/src/SignPost2.o \
$(SUB_DIR)/Debug/src/SkyBox.o \
$(SUB_DIR)/Debug/src/Sniper.o \
$(SUB_DIR)/Debug/src/SoundBank.o \
$(SUB_DIR)/Debug/src/StaticObj.o \
$(SUB_DIR)/Debug/src/Text.o \
$(SUB_DIR)/Debug/src/TextMenuItem.o \
$(SUB_DIR)/Debug/src/TextSpot.o \
$(SUB_DIR)/Debug/src/TextObject.o \
$(SUB_DIR)/Debug/src/ThreadProcess.o \
$(SUB_DIR)/Debug/src/Two_PhosphoGlycerate.o \
$(SUB_DIR)/Debug/src/View.o \
$(SUB_DIR)/Debug/src/Wall.o \
$(SUB_DIR)/Debug/src/WallCube.o \
$(SUB_DIR)/Debug/src/WooddenCube.o \
$(SUB_DIR)/Debug/src/WooddenCube2.o \
$(SUB_DIR)/Debug/src/WinningArea.o \
$(SUB_DIR)/Debug/src/objloader.o \
$(SUB_DIR)/Debug/src/shader.o \
$(SUB_DIR)/Debug/src/texture.o \
$(SUB_DIR)/Debug/src/vboindexer.o \
$(SUB_DIR)/Debug/src/L_Stage.o \
$(SUB_DIR)/Debug/src/L_ResObj.o \
$(SUB_DIR)/Debug/src/LuaIf.o \
$(SUB_DIR)/Debug/src/LuaIfLPConfig.o \
$(SUB_DIR)/Debug/src/LuaInteractive.o \
$(SUB_DIR)/Debug/src/LPConfig.o
#./src/QtTerminal.o

CPP_DEPS += \
$(SUB_DIR)/Debug/src/Actor.d \
$(SUB_DIR)/Debug/src/Arrow.d \
$(SUB_DIR)/Debug/src/Ball.d \
$(SUB_DIR)/Debug/src/CoordinateLines.d \
$(SUB_DIR)/Debug/src/Creature.d \
$(SUB_DIR)/Debug/src/FallingCube.d \
$(SUB_DIR)/Debug/src/FPerson.d \
$(SUB_DIR)/Debug/src/Fructose6Phosphate.d \
$(SUB_DIR)/Debug/src/GameLogic.d \
$(SUB_DIR)/Debug/src/GameLogic2.d \
$(SUB_DIR)/Debug/src/GameState.d \
$(SUB_DIR)/Debug/src/Glucose.d \
$(SUB_DIR)/Debug/src/Glucose6Phosphate.d \
$(SUB_DIR)/Debug/src/Hexokinase.d \
$(SUB_DIR)/Debug/src/IceCube.d \
$(SUB_DIR)/Debug/src/InitError.d \
$(SUB_DIR)/Debug/src/Landscape.d \
$(SUB_DIR)/Debug/src/LPDebugDraw.d \
$(SUB_DIR)/Debug/src/LPObject.d \
$(SUB_DIR)/Debug/src/LearningPlatform.d \
$(SUB_DIR)/Debug/src/LightSource.d \
$(SUB_DIR)/Debug/src/LineObj.d \
$(SUB_DIR)/Debug/src/logging.d \
$(SUB_DIR)/Debug/src/MazeFloor.d \
$(SUB_DIR)/Debug/src/MazeDoorX.d \
$(SUB_DIR)/Debug/src/MazeDoorY.d \
$(SUB_DIR)/Debug/src/MenuContainer.d \
$(SUB_DIR)/Debug/src/MenuFactory.d \
$(SUB_DIR)/Debug/src/MenuItem.d \
$(SUB_DIR)/Debug/src/Mitochondria.d \
$(SUB_DIR)/Debug/src/Molecule.d \
$(SUB_DIR)/Debug/src/MoleculeSpot.d \
$(SUB_DIR)/Debug/src/NoSign.d \
$(SUB_DIR)/Debug/src/ObjectFactory.d \
$(SUB_DIR)/Debug/src/Phosphofructokinase.d \
$(SUB_DIR)/Debug/src/Plane.d \
$(SUB_DIR)/Debug/src/Plate.d \
$(SUB_DIR)/Debug/src/ResObj.d \
$(SUB_DIR)/Debug/src/SDL_base.d \
$(SUB_DIR)/Debug/src/Scene.d \
$(SUB_DIR)/Debug/src/SignPost.d \
$(SUB_DIR)/Debug/src/SignPost2.d \
$(SUB_DIR)/Debug/src/SkyBox.d \
$(SUB_DIR)/Debug/src/Sniper.d \
$(SUB_DIR)/Debug/src/SoundBank.d \
$(SUB_DIR)/Debug/src/StaticObj.d \
$(SUB_DIR)/Debug/src/Text.d \
$(SUB_DIR)/Debug/src/TextMenuItem.d \
$(SUB_DIR)/Debug/src/TextObject.d \
$(SUB_DIR)/Debug/src/TextSpot.d \
$(SUB_DIR)/Debug/src/ThreadProcess.d \
$(SUB_DIR)/Debug/src/Two_PhosphoGlycerate.d \
$(SUB_DIR)/Debug/src/View.d \
$(SUB_DIR)/Debug/src/Wall.d \
$(SUB_DIR)/Debug/src/WallCube.d \
$(SUB_DIR)/Debug/src/WooddenCube.d \
$(SUB_DIR)/Debug/src/WooddenCube2.d \
$(SUB_DIR)/Debug/src/WinningArea.d \
$(SUB_DIR)/Debug/src/objloader.d \
$(SUB_DIR)/Debug/src/shader.d \
$(SUB_DIR)/Debug/src/texture.d \
$(SUB_DIR)/Debug/src/vboindexer.d \
$(SUB_DIR)/Debug/src/L_Stage.d \
$(SUB_DIR)/Debug/src/L_ResObj.d \
$(SUB_DIR)/Debug/src/LuaIf.d \
$(SUB_DIR)/Debug/src/LuaIfLPConfig.d \
$(SUB_DIR)/Debug/src/LuaInteractive.d \
$(SUB_DIR)/Debug/src/LPConfig.d
#./src/QtTerminal.d


#INC = -I$(SUB_DIR)/LP/lua-5.1/src
#LIB = -L$(SUB_DIR)/LP/lua-5.1/src


# Each subdirectory must supply rules for building sources it contributes
$(SUB_DIR)/Debug/src/%.o: $(SUB_DIR)/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	@echo 'Operating System = $(OPER_SYS)'
	@echo 'MY_FLAGS =  $(MY_FLAGS)'
	@echo 'LP_ROOT =  $(LP_ROOT)'	
	g++ -D_LINUX $(MY_FLAGS) -I"$(LP_ROOT)/BEvent" -I"$(LP_ROOT)/BEvent/inc" -I"$(LP_ROOT)/Glycolysis/command/inc"  -I"$(LP_ROOT)/bullet-2.82-r2704/src"  -I"$(LP_ROOT)/assimp-3.3.1/include" -I"$(LP_ROOT)/lua-5.1/src" -I"$(LP_ROOT)/freetype-2.4.12/include" -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -Wno-unused-variable  -std=c++11 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/LearningPlatform.o: $(SUB_DIR)/src/LearningPlatform.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_LINUX $(MY_FLAGS) -I"$(LP_ROOT)/BEvent" -I"$(LP_ROOT)/BEvent/inc" -I"$(LP_ROOT)/bullet-2.82-r2704/src"   -I/usr/local/include/MYGUI -I"$(LP_ROOT)/assimp-3.3.1/include" -I"$(LP_ROOT)/lua-5.1/src" -I"$(LP_ROOT)/freetype-2.4.12/include"   -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -Wno-unused-variable  -std=c++11 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/LearningPlatform.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


