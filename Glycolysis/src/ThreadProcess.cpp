#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../inc/ResObj.h"
#include "../inc/SDL_base.h"
#include "../inc/ThreadProcess.h"
#include "../inc/LearningPlatform.h"
#include <pthread.h>
#include "../stage/inc/Stage.h"

int ThreadProcess::value = 1; // initializer
ResObj* ThreadProcess::resObj_ptr = nullptr; // initializer
Stage* ThreadProcess::stage_ptr = nullptr; // initializer
SDL_base* ThreadProcess::sdl_ptr = nullptr; // initializer
LearningPlatform* ThreadProcess::lp = nullptr; // initializer
Stage* ThreadProcess::stage_skyBox_ptr = nullptr; // initializer

void* ThreadProcess::threadProcess(void* lp_ptr) {
 std::cout << "ENTER ThreadProcess::threadProcess\n";
 pthread_mutex_lock(&sdl_ptr->mymutex);
 lp = reinterpret_cast<LearningPlatform*>(lp_ptr);
 SDL_GL_MakeCurrent(sdl_ptr->getWindow(), sdl_ptr->getThreadContext());
 std::cout << "ThreadProcess::threadProcess before loadObjFilesMultiThreading\n";
  resObj_ptr->loadObjFilesMultiThreading();
// stage_ptr->init2();
// stage_skyBox_ptr->initSkyBox();
 pthread_mutex_unlock(&sdl_ptr->mymutex);
}

void ThreadProcess::setResObj(ResObj* resObj) {
  ThreadProcess::resObj_ptr = resObj;
}

void ThreadProcess::setStage(Stage* stage) {
  ThreadProcess::stage_ptr = stage;
}

void ThreadProcess::setStageBox(Stage* stageBox) {
  ThreadProcess::stage_skyBox_ptr = stageBox;
}

void ThreadProcess::setSdl(SDL_base* sdl) {
  ThreadProcess::sdl_ptr = sdl;
}
