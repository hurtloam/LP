################################################################################
# Automatically-generated file. Do not edit!
################################################################################

USER_OBJS :=
#LIBS := -lSDL2 -lglew -lGLEW -llibGLEW -lGL
ifeq ($(OPER_SYS), WINNT)
CPPFLAGS := -mwin32

LIBPATHS := \
-L"$(LP_ROOT)/BEvent/Debug" \
-L/MinGW/mingw64/lib \
-L"$(LP_ROOT)/lua-5.1/src" \
-L"$(LP_ROOT)/bullet-2.82-r2704/src/BulletDynamics" \
-L"$(LP_ROOT)/bullet-2.82-r2704/src/BulletCollision" \
-L"$(LP_ROOT)/bullet-2.82-r2704/src/LinearMath" \
-L"$(LP_ROOT)/Glycolysis/Debug" \
-L"$(LP_ROOT)/assimp-3.3.1/lib"

LIBS := -lassimp -lBEvent -lSDL2 -lSDL2_mixer -lopengl32 -lglew32 -lBulletDynamics -lBulletCollision -lLinearMath -lfreetype -llua51 -lm -lz -pthread
endif

ifeq ($(OPER_SYS),LINUX)
CPPFLAGS :=

LIBPATHS := \
-L"$(LP_ROOT)/BEvent/Debug" \
-L"$(LP_ROOT)/lua-5.1/src" \
-L"$(LP_ROOT)/bullet-2.82-r2704/src/BulletDynamics" \
-L"$(LP_ROOT)/bullet-2.82-r2704/src/BulletCollision" \
-L"$(LP_ROOT)/bullet-2.82-r2704/src/LinearMath" \
-L"$(LP_ROOT)/Glycolysis/Debug" \
-L"$(LP_ROOT)/assimp-3.3.1/lib" \
-L"$(LP_ROOT)/lib"

# -L/MinGW/mingw64/lib \

LIBS := -lassimp -lBEvent -lSDL2 -lSDL2_mixer-2.0 -lGL -lGLEW -lBulletDynamics -lBulletCollision -lLinearMath -lfreetype -llua -ldl -lm -pthread
endif


