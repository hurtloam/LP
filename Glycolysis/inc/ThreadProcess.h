/*
 * L_Stage.h
 *
 *  Created on: Jan 9, 2018
 *      Author: peter
 *
 *      Interface towards Lua
 */

#ifndef THREAD_PROCESS_H_
#define THREAD_PROCESS_H_

#include <cstdio>
#include <iostream>

#include "../inc/ResObj.h"
#include "../stage/inc/Stage.h"
#include "../inc/SDL_base.h"
#include "../inc/LearningPlatform.h"

class ThreadProcess {
  public:
    static ResObj* resObj_ptr;
    static Stage* stage_ptr;
    static Stage* stage_skyBox_ptr;
    static SDL_base* sdl_ptr;
    static LearningPlatform* lp;
    static int value;

    ThreadProcess() = delete;
    virtual ~ThreadProcess() = delete;

    static void* threadProcess (void*);
    static void setResObj(ResObj* resObj);
    static void setStage(Stage* stage);
    static void setStageBox(Stage* stageBox);
    static void setSdl(SDL_base* sdl);
};

#endif // THREAD_PROCESS_H_
