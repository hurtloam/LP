//============================================================================
// Author      : Peter Brorsson
// Name        : LearningPlatform.cpp
// Version     :
// Copyright   : All rights reserved.
// Description : A Simple openGL platform. A simple game exercise.
//============================================================================

#include "../inc/LearningPlatform.h"

//#include <BEvent.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <LinearMath/btVector3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_mixer.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <string>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <future>         // std::async, std::future
#include <functional>

//#include "../inc/logging.h"
#include "../inc/InitError.h"
#include "../inc/ResObj.h"

#include "../inc/Scene.h"
#include "../inc/SDL_base.h"
#include "../inc/SoundBank.h"
#include "../stage/inc/Stage.h"

#include "../inc/texture.hpp"
#include "../inc/View.h"
#include "../inc/shader.hpp"
#include "../inc/GameLogic2.h"
#include "../inc/GameState.h"
#include "../inc/MenuContainer.h"
#include "../command/inc/Command.h"
#include "../command/inc/AlterCameraSpeedCmd.h"
#include "../command/inc/AlterGridCmd.h"
#include "../command/inc/PrintCameraPositionCmd.h"

#include "../inc/MazeFloor.h"

#include "../event_sm/inc/EventSM.h"
#include "../event_sm/inc/InitSM.h"
#include "../event_sm/inc/ObjSelectedSM.h"
#include "../inc/FPerson.h"
#include "../inc/Sniper.h"

//#include "../terminal/inc/LuaInteractive.h"

#include <vector>
#include <utility>
#include "../inc/LuaIfLPConfig.h"

//#include <MyGUI.h>
//#include <MyGUI_OpenGLPlatform.h>
//#include <MyGUI_OpenGLImageLoader.h>
//#include "../inc/MyGUI_OpenGLImageLoader_Devil.h"

//#include <../../imgui/imgui/examples/libs/gl3w/GL/gl3w.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include "../gui/LPGui.h"
#include "../gui/examples/sdl_opengl3_example/imgui_impl_sdl_gl3.h"

#include <unistd.h>


//#include "../inc/BulletDebugDrawer.h"
//#include <btBulletDynamicsCommon.h>

//#include <ft2build.h>
//#include <freetype/freetype.h>
//#include FT_FREETYPE_H

#if SYS_LINUX
//#include <thread>
#include <future>         // std::async, std::future
//#include "../inc/Future.h"
#include <pthread.h>
#include "../inc/ThreadProcess.h"
#include <time.h>
typedef void * (*THREADFUNCPTR)(void *);

#else
#include <pthread.h>
#include "../inc/ThreadProcess.h"
#include <time.h>
typedef void * (*THREADFUNCPTR)(void *);
#endif

using namespace std;
using platformBase::InitError;

static int wall_globalId = 1;
static int falling_globalId = 1;
static int glucose_globalId = 1;
static int plane_globalId = 1;

int screen_width=800, screen_height=600;
GLuint text_program_id;
GLint attribute_coord = -1;
GLint uniform_tex = -1;
GLint uniform_color = -1;
GLint attribute_UV = -1;

const char *fontfilename;
GLuint vbo;

LearningPlatform::LearningPlatform() :
    LPGui(view, stage, resObj), obj(nullptr), text_obj(nullptr)
{
  stage = nullptr;
  resourceList = nullptr;
  stage_skyBox = nullptr;
  stageGui = nullptr;
  resourceList_view = nullptr;
  view = nullptr;
  view_skyBox = nullptr;
  resObj = nullptr;
  obj = nullptr;
  text_obj = nullptr;
  gameLogic = nullptr;

  multiThreadOn = false;
  running = true;
  this->sdl = nullptr;
  lpConfig = new LPConfig ();
  luaIf = new LuaIfLPConfig (lpConfig);
  luaIf->setConfigFile ("config_lp.lua");
  luaIf->configLP ();
  multiThreadOn = lpConfig->multiThreadOn;
  viewPortSelector = 2; // this set the viewport, should have an enum for this
  setScreenWidth (lpConfig->screenWidth);
  setScreenHeight (lpConfig->screenHeight);
  _state = InitSM::Instance ();


  show_test_window = false;
  show_another_window = false;
  show_object_window = true;
  clear_color = ImColor (114, 144, 154);

  io = ImGui::GetIO ();
  io.Fonts->AddFontFromFileTTF (
      "gui/extra_fonts/Roboto-Medium.ttf",
      16.0f, nullptr, io.Fonts->GetGlyphRangesDefault());


  logOutputPtr = new int (1);
  SDL_LogSetPriority(SDL_LOG_CATEGORY_CUSTOM, (SDL_LogPriority)lpConfig->logPriority);
  setLogging (logOutputPtr, lpConfig->logPriority);

  SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "Logging initiated");
  //stage->draw();

}

LearningPlatform::~LearningPlatform()
{
  std::cout << "ENTER ~LearningPlatform()" << std::endl;
  //  stage->deleteActorList ();
  //  stage_skyBox->deleteActorList();
  delete stage;
  std::cout << "stage is deleted" << std::endl;
  if (stage_skyBox != nullptr) {
    delete stage_skyBox;
    std::cout << "stage_skyBox is deleted" << std::endl;
  }
  if (view != nullptr) {
    delete view;
    std::cout << "view is deleted" << std::endl;
  }
  if (view_skyBox != nullptr) {
    delete view_skyBox;
    std::cout << "view_skyBox is deleted" << std::endl;
  }
  if (resObj != nullptr) {
    delete resObj;
    std::cout << "resObj is deleted" << std::endl;
  }
  if (sdl != nullptr) {
    delete sdl;
    std::cout << "sdl is deleted" << std::endl;
  }
  if (logOutputPtr != nullptr) {
    delete logOutputPtr;
    std::cout << "logOutputPtr is deleted" << std::endl;
  }
  if (lpConfig != nullptr) {
    delete lpConfig;
    std::cout << "lpConfig is deleted" << std::endl;
  }
  if (luaIf != nullptr) {
    delete luaIf;
    std::cout << "luaIf is deleted" << std::endl;
  }
  if (gameLogic != nullptr) {
    delete gameLogic;
    std::cout << "gameLogic is deleted" << std::endl;
  }
  if (alterCameraSpeedCmd != nullptr) {
    delete alterCameraSpeedCmd;
    std::cout << "alterCameraSpeedCmd is deleted" << std::endl;
  }
  if (alterGridCmd != nullptr) {
    delete alterGridCmd;
    std::cout << "alterGridCmd is deleted" << std::endl;
  }
  if (printCameraPositionCmd != nullptr) {
    delete printCameraPositionCmd;
    std::cout << "printCameraPositionCmd is deleted" << std::endl;
  }
}

void LearningPlatform::init()
{
  int static_id = 50;
  int actor_id = 500;
  // Initialize the SDL video subsystem using SDL_Init
  sdl = new SDL_base (SDL_INIT_VIDEO, lpConfig);
   if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
  {
    char msg[128];
    sprintf(msg, "Mix_OpenAudio failure, file: %s:%d", __FILE__, __LINE__);
    std::string errorMsg(msg);
    throw InitError (errorMsg);
  }
  TRACE_INFO("Inside init()");
  sdl->createWindow(lpConfig->title.c_str(), 0, 0, screenWidth, screenHeight,
      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  TRACE_INFO("Before sdl->createOpenGLContext");
  sdl->createOpenGLContext ();
  int major_version = 0;
  int minor_version = 0;
  int sdl_gl_double_buffer = 0;
  int sdl_gl_depth_size = 0;
  int sdl_gl_red_size = 0;
  int sdl_gl_green_size = 0;
  int sdl_gl_blue_size = 0;
  int sdl_gl_alpha_size = 0;
  int sdl_gl_accelerated_visual = 0;
  int sdl_gl_multisamplebuffers = 0;
  int sdl_gl_multisamplesamples = 0;

  SDL_GL_GetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, &major_version);
  SDL_GL_GetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, &minor_version);

  SDL_GL_GetAttribute (SDL_GL_DOUBLEBUFFER, &sdl_gl_double_buffer);
  SDL_GL_GetAttribute (SDL_GL_DEPTH_SIZE, &sdl_gl_depth_size);



  SDL_GL_GetAttribute (SDL_GL_RED_SIZE, &sdl_gl_red_size);
  SDL_GL_GetAttribute (SDL_GL_GREEN_SIZE, &sdl_gl_green_size);
  SDL_GL_GetAttribute (SDL_GL_BLUE_SIZE, &sdl_gl_blue_size);
  SDL_GL_GetAttribute (SDL_GL_ALPHA_SIZE, &sdl_gl_alpha_size);

  //    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

  //    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  //    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

  SDL_GL_GetAttribute (SDL_GL_ACCELERATED_VISUAL, &sdl_gl_accelerated_visual);


  SDL_GL_GetAttribute (SDL_GL_MULTISAMPLEBUFFERS, &sdl_gl_multisamplebuffers);
  // to 1 and SDL_GL_MULTISAMPLESAMPLES to a value greater than 0,
  SDL_GL_GetAttribute (SDL_GL_MULTISAMPLESAMPLES, &sdl_gl_multisamplesamples);




  //  char tmp[128] = "";
  //  strcpy (sdlInfo1, tmp);
  //  sprintf (
  //      sdlInfo1,
  //      "SDL_GL_CONTEXT_MAJOR_VERSION = %d, SDL_GL_CONTEXT_MINOR_VERSION = %d, SDL_GL_DOUBLEBUFFER = %d, SDL_GL_DEPTH_SIZE = %d",
  //      major_version, minor_version, sdl_gl_double_buffer, sdl_gl_depth_size);
  //  strcpy (sdlInfo2, tmp);
  //  sprintf (
  //      sdlInfo2,
  //      "SDL_GL_RED_SIZE = %d, SDL_GL_GREEN_SIZE = %d, SDL_GL_BLUE_SIZE = %d, SDL_GL_ALPHA_SIZE = %d",
  //      sdl_gl_red_size, sdl_gl_green_size, sdl_gl_blue_size, sdl_gl_alpha_size);
  //  strcpy (sdlInfo3, tmp);
  //  sprintf (
  //      sdlInfo3,
  //      "SDL_GL_ACCELERATED_VISUAL = %d, SDL_GL_MULTISAMPLEBUFFERS = %d, SDL_GL_MULTISAMPLESAMPLES = %d",
  //      sdl_gl_accelerated_visual, sdl_gl_multisamplebuffers,
  //      sdl_gl_multisamplesamples);

  printf ("------------------ opengl version: %d.%d --------------------\n",
      major_version, minor_version);

  //  order is
  //  important to
  //  make it
  //  fit with
  //  enum lp_sound in
  //  resObj.h
  //  it is
  //  a list
  //  and id
  //  is the
  //  position in
  //  the list

   if ((BSoundBank::SoundControl.OnLoad ("resources/sound/stonedoor.wav")) == -1)
   {
     throw InitError ("stonedoor.wav");
   }

   if ((BSoundBank::SoundControl.OnLoad ("resources/sound/digging-stone.mp3")) == -1)
   {
     throw InitError ("digging-stone.mp3");
   }

   if ((BSoundBank::SoundControl.OnLoad ("resources/sound/kebn1.mp3")) == -1)
   {
     throw InitError ("kebn1.mp3");
   }

   if ((BSoundBank::SoundControl.OnLoad ("resources/sound/loose.wav")) == -1)
   {
     throw InitError ("loose.wav");
   }

   if ((BSoundBank::SoundControl.OnLoad ("resources/sound/concrete-step.wav")) == -1)
   {
     throw InitError ("concrete-step.wav");
   }

   if ((BSoundBank::SoundControl.OnLoad ("resources/sound/step-tap.wav")) == -1)
   {
     throw InitError ("step-tap.wav");
   }
   if ((BSoundBank::SoundControl.OnLoad ("resources/sound/sonny_step.wav")) == -1)
   {
     throw InitError ("sonny_step.wav");
   }

   if ((BSoundBank::SoundControl.OnLoad ("resources/sound/ellbellekc-step.wav")) == -1)
   {
     throw InitError ("ellbellekc-step.wav");
   }

   if ((BSoundBank::SoundControl.OnLoad ("resources/sound/scary_howling.mp3")) == -1)
   {
     throw InitError ("scary_howling.mp3");
   }



  // EPEBROR: This is normally on
  /* This makes our buffer swap synchronized with the monitor's vertical refresh */
  //	if (SDL_GL_SetSwapInterval(1) == -1) {
  //		throw InitError("Swap interval is not supported.\n");
  //	}

  // Initialize GLEW
  /*
   * GLEW obtains information on the supported extensions from the
   * graphics driver. Experimental or pre-release drivers, however,
   * might not report every available extension through the standard mechanism,
   * in which case GLEW will report it unsupported. To circumvent this
   * situation, the glewExperimental global switch can be turned on by setting
   * it to GL_TRUE before calling glewInit(), which ensures that all extensions
   *  with valid entry points will be exposed.
   */
  glewExperimental = GL_TRUE;
  GLenum err = glewInit ();
  if (err != GLEW_OK)
  {
    char str[256];
    sprintf(str, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
    throw InitError(str);
  }

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //Set the viewport
  //	glViewport( 0.f, 0.f, screenWidth, screenHeight);

  //Initialize Projection Matrix
  //  glMatrixMode ( GL_PROJECTION); // commented this out after looking at tutorial 13

  //Initialize Modelview Matrix
  //  glMatrixMode ( GL_MODELVIEW); // commented this out after looking at tutorial 13

  //	glLoadIdentity();
  //	glOrtho( 0.0, screenWidth, screenHeight, 0.0, 1.0, -1.0 );

  glClearColor (0.0f, 0.0f, 0.4f, 0.0f);

  // Enable depth test
  glEnable (GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc (GL_LESS);
  // Cull triangles which normal is not towards the camera
  //	glEnable(GL_CULL_FACE);

  glEnable (GL_MULTISAMPLE);

  glGenVertexArrays (1, &VertexArrayID);

  glBindVertexArray (VertexArrayID);

  //	ImGui_ImplSdlGL3_NewFrame(sdl->getWindow());

  // Initiate the camera views
  view = new View (screenWidth, screenHeight);
  setView (view); // ImGui
  //	resourceList_view = new View(screenWidth, screenHeight);
  view_skyBox = new View (screenWidth, screenHeight);

  // Initiate all resources
  resObj = new ResObj ();
  stage = new Stage (this, *resObj, *view);
  //  stage_skyBox = new Stage(this, *resObj, *view_skyBox);







  setStage (stage); // ImGui
  setResObj (resObj); // ImGui
  ThreadProcess::setResObj(resObj);
  ThreadProcess::setStage(stage);
  ThreadProcess::setSdl(sdl);

  resObj->loadText("textLines.txt", screenWidth, screenHeight);

  //  #if SYS_LINUX
  //  if (multiThreadOn)
  //    {
  //      // run splash before initiating all
  //      // call function asynchronously:
  //      runSplashScreen ();
  //
  //      std::future<bool> fut = std::async (
  //          std::bind (&ResObj::loadObjFilesMultiThreading, resObj, sdl));
  //
  //      std::chrono::milliseconds span (10);
  //      while (fut.wait_for (span) == std::future_status::timeout)
  //        {
  //          glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //          glClearColor (0, 0, 0, 0);
  //          glClear (GL_COLOR_BUFFER_BIT);
  //          stage->getSplashScreenObject (96003)->setRotationMatrix_Y (0.01);
  //          stage->getSplashScreenObject (96003)->draw ();
  //          stage->getSplashScreenObject_txt (1)->draw ();
  //          stage->getSplashScreenObject_txt (2)->draw ();
  //          sdl->swapWindow ();
  //        }
  //      bool x = fut.get ();
  //
  //      stage->deleteActorListForSplashScreen ();
  //      SDL_GL_MakeCurrent (sdl->getWindow (), sdl->getMainContext ());
  //    }
  //  else
  //    {
  //      resObj->loadObjFiles_maze ();
  //    }
  //#else
  if (multiThreadOn) {
    std::cout << "Start of multithread condition\n";
    // run splash before initiating all
    bool returnCode = runSplashScreen();
    //   pthread_mutex_init(&sdl->mymutex, NULL);
    if (pthread_mutex_init(&sdl->mymutex, NULL) != 0) {
      printf("-------------------------------------mutex_init FAILED\n");
      assert(false);
    }

    pthread_t threadId;
    int rc;

    rc = pthread_create(&threadId, NULL, (THREADFUNCPTR) &ThreadProcess::threadProcess, nullptr);
    printf("RC=%d\n", rc);

    if (rc != 0) {
      printf("ERROR return code from pthread_create() is %d\n", rc);
      assert(false);
    }
    do {
      for (int i = 0; i < 1000; i++) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        if (i % 300 == 0) {
          stage->getSplashScreenObject(96003)->setRotationMatrix_Y(0.01);
          stage->getSplashScreenObject(96003)->draw();
          stage->getSplashScreenObject_txt(1)->draw();
          stage->getSplashScreenObject_txt(2)->draw();
          sdl->swapWindow();
        }
      }
    }
    while (pthread_mutex_trylock(&sdl->mymutex) == EBUSY);
    stage->deleteActorListForSplashScreen();
    SDL_GL_MakeCurrent(sdl->getWindow(), sdl->getMainContext());
  }
  else {
    // resObj->loadObjFiles();
    resObj->loadObjFiles_maze ();
    //EPEBROR 171223      resObj->loadObjFiles_maze ();
  }
  //#endif


  // Initiate all objects
  //	resourceList = new Stage(*resObj, *resourceList_view);
  //	resourceList->initText();

  //EPEBROR 171223  stage->init_maze ();
  stage->init_maze ();
  //stage->init2();
  //	stageGui = new Stage(*resObj, *view);


  //  stage_skyBox->initSkyBox();

  //Initiate the game logic.
  //gameLogic = new GameLogic2(stage, *resObj, *view);

  alterCameraSpeedCmd = new AlterCameraSpeedCmd(*view);
  alterGridCmd = new AlterGridCmd(*stage);
  printCameraPositionCmd = new PrintCameraPositionCmd(*view);
  mydebugdrawer2 = new LPDebugDraw(stage->getScene(), this, view);
  stage->getDynamicsWorld()->setDebugDrawer(mydebugdrawer2);
  stage->getDynamicsWorldText()->setDebugDrawer(mydebugdrawer2);



  m_startTime = GetCurrentTimeMillis();

  //	Logger logger;
}

// int LearningPlatform::getSomeValue() {
//   if (resObj->loadTextFile() == true) {
//
//   }
// }

bool LearningPlatform::runSplashScreen()
{
  //	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  double diffTime = 0.0;
  //	(stage->getDynamicsWorld())->stepSimulation(diffTime/(1000.0f), 3);
  //	glViewport( 0.f, 0.f, screenWidth, screenHeight );
  //	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  //	glClear(GL_COLOR_BUFFER_BIT);
  //	stage_skyBox->draw();
  stage->initSplashScreen ();
  stage->draw ();
  sdl->swapWindow ();
}

int LearningPlatform::execute()
{
  SDL_Event Event;
  int nbFrames = 0;
  double diffTime = 0.0;
  double lastTime = SDL_GetTicks () * 1.0;

  try
  {
    TRACE_INFO("Before init()");
    init(); // will throw an InitError exception if it fails.

    // Setup ImGui binding
    TRACE_INFO("Before ImGui_ImplSdlGL3_Init()");
    ImGui_ImplSdlGL3_Init(sdl->getWindow());
    TRACE_INFO("Before while()");
    while (running) {
      while (SDL_PollEvent(&Event)) {
        if (Event.type == SDL_QUIT)
          running = false;
        OnEvent(&Event);
      }
      // Measure speed
      double currentTime = SDL_GetTicks() * 1.0;
      nbFrames++;
      diffTime = currentTime - lastTime;
      //			if (((int)diffTime % (int)(50.0)) == 0) {    // original 50.0
      if (currentTime - lastTime >= 1000) { // If last prinf() was more than 1 sec ago
                                            // printf and reset timer
                                            //					printf("%f ms/frame, %f FPS\n", diffTime/double(nbFrames), (double(nbFrames)*1000)/diffTime );
        nbFrames = 0;
        //					lastTime += 1000.0;
        lastTime = currentTime;
      }
      //			if (((int)diffTime % (int)(45.0)) == 0) {    // original 50.0
      (stage->getDynamicsWorld())->stepSimulation(1 / 60.f, 10);
      (stage->getDynamicsWorldText())->stepSimulation(1 / 60.f, 10);
      //          (stage->getDynamicsWorld ())->stepSimulation (1 / 30.f, 10);
      //          (stage->getDynamicsWorld ())->stepSimulation (diffTime / (1000.0f),
      //                                                        3);
      //        (stage->getDynamicsWorldText ())->stepSimulation (diffTime / (1000.0f), 3);
      //			  (stage->getDynamicsWorldSkyBox())->stepSimulation(diffTime/(1000.0f), 3);


      //			  			stage->getDynamicsWorldText()->debugDrawWorld();

      //			  (resourceList->getDynamicsWorld())->stepSimulation(diffTime/(1000.0f), 3);
      //			resourceList->getDynamicsWorld()->debugDrawWorld();

      //        (stage_skyBox->getDynamicsWorld ())->stepSimulation (diffTime / (1000.0f), 3);
      float distance = 100.0;
      float currAnimTime;
      float RunningTime = (float) ((double) GetCurrentTimeMillis() - (double) m_startTime) / 1000.0f;
      TRACE_INFO("Before action()");
      action();

      TRACE_INFO("Before render()");
      render(diffTime);

    }
    cleanup();
    return 0;

  }
  catch (const InitError& err)
  {
    std::cerr << "Error while initializing SDL:  " << err.what() << std::endl;
  }
  return -1;
}

void LearningPlatform::action()
{
  bool prepareToDelete = false;
  int j;
  int numManifolds = 0;
  std::vector<std::pair<int, int>> collisionDetected;
  btTransform trans;
  btVector3 normalOnB;

  actOnRaytrace ();

  // start text collision
  if (stage->getDynamicsWorldText() != nullptr && stage->getDynamicsWorldText()->getDispatcher() != nullptr) {
    numManifolds = stage->getDynamicsWorldText()->getDispatcher()->getNumManifolds();
//    std::cout << "numManifolds=" << numManifolds << std::endl;
    for (int i = 0; i < numManifolds; i++) {
//      std::cout << "numManifolds=" << numManifolds << std::endl;
      btPersistentManifold* contactManifold = stage->getDynamicsWorldText()->getDispatcher()->getManifoldByIndexInternal(i);
      btCollisionObject* obA = (btCollisionObject*) (contactManifold->getBody0());
      btCollisionObject* obB = (btCollisionObject*) (contactManifold->getBody1());

      int numContacts = contactManifold->getNumContacts();
      for (int j = 0; j < numContacts; j++) {
        btManifoldPoint& pt = contactManifold->getContactPoint(j);
        if (pt.getDistance() < 0.f) {
          if (obA != nullptr && obB != nullptr) {
            LPObject* obAObject = (LPObject*) (obA->getUserPointer());
            LPObject* obBObject = (LPObject*) (obB->getUserPointer());
            if (obAObject != nullptr && obBObject != nullptr) {
              SDL_LogDebug(SDL_LOG_CATEGORY_CUSTOM, "#contacts: %d, normal: (%f,%f), contactPoint distance = %f", pt.m_normalWorldOnB.getX(), pt.m_normalWorldOnB.getZ(), numContacts, contactManifold->getContactPoint(j).getDistance());
              collisionDetected.push_back(std::pair<int, int>(obAObject->getId(), obBObject->getId()));
              normalOnB = pt.m_normalWorldOnB;
            }
          }
        }
      }
    }
  }

  // start object collision
  if (stage->getDynamicsWorld() != nullptr && stage->getDynamicsWorld()->getDispatcher() != nullptr) {
    numManifolds = stage->getDynamicsWorld()->getDispatcher()->getNumManifolds();
//    std::cout << "numManifolds=" << numManifolds << std::endl;
    for (int i = 0; i < numManifolds; i++) {
//      std::cout << "numManifolds=" << numManifolds << std::endl;
      btPersistentManifold* contactManifold = stage->getDynamicsWorld()->getDispatcher()->getManifoldByIndexInternal(i);
      btCollisionObject* obA = (btCollisionObject*) (contactManifold->getBody0());
      btCollisionObject* obB = (btCollisionObject*) (contactManifold->getBody1());

      int numContacts = contactManifold->getNumContacts();
      for (int j = 0; j < numContacts; j++)
      {
        btManifoldPoint& pt = contactManifold->getContactPoint(j);
        if (pt.getDistance() < 0.f)
        {
          if (obA != nullptr && obB != nullptr)
          {
            LPObject* obAObject = (LPObject*) (obA->getUserPointer());
            LPObject* obBObject = (LPObject*) (obB->getUserPointer());
            if (obAObject != nullptr && obBObject != nullptr) {
//              SDL_LogDebug (SDL_LOG_CATEGORY_CUSTOM,"#contacts: %d, normal: (%f,%f), contactPoint distance = %f", pt.m_normalWorldOnB.getX(), pt.m_normalWorldOnB.getZ(), numContacts, contactManifold->getContactPoint(j).getDistance());
              collisionDetected.push_back(std::pair<int, int>(obAObject->getId(), obBObject->getId()));
              normalOnB = pt.m_normalWorldOnB;

              if ((obAObject->getId() == 1000) && (obBObject->getObjType() == alpha_D_glucopyranose))
              {
                prepareForRemovalOfObj = true;
                if (objToRemove->getId() != obBObject->getId()) {
                  objToRemove = obBObject;
                }
              }
            }
          }
        }
      }
    }

    if (prepareForRemovalOfObj) {
      stage->deleteObject(objToRemove);
      prepareForRemovalOfObj = false;
      updateGuiOnCurrentObjData(nullptr);
    }
    //  view_skyBox->move (view_skyBox->getMovement ());
    //  stage_skyBox->move(collisionDetected, normalOnB);
    if (stage->getObject(1000) != nullptr) {
      if (stage->getObject(1000)->isDead()) {
        gameOver = true;
        deactivatingMovements = true;
        //    running = false;
      }
    }
  }    // end collision

  // View movement
  if (attachedToFPS) {
    view->move(stage->getTransCreature() + glm::vec3(0.0f, 1.5f, 0.0f)); // creature = id=1000 ?
    if (stage->getObject(1000) != nullptr) {
      ((LPObject*) stage->getObject(1000))->setOrientation(glm::vec3(0, view->getHorizontalAngle(), 0));
    }
    else {
      TRACE_WARN("Object with id=%d does not exist", 1000);
    }
  }
  else {
    view->move(view->getMovement());
  }

  if (!deactivatingMovements)
  {
    stage->move (collisionDetected, normalOnB);
  }
//  updateGuiOnProcessCompleted(gameLogic->solved());
//  gameLogic->evaluate2();
}

void LearningPlatform::render(double diffTime)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // two viewports, one left and one right
  if (viewPortSelector == 1)
  {
    glClearColor(1, 1, 1, 1);
    //    resourceList_view->setAspectRatio((screenWidth * 1.f / 5.f) / screenHeight );
    //    resourceList_view->setScreen(screenWidth * 1.f / 5.f, screenHeight);
    glViewport(screenWidth * 3.f / 4.f, 0.f, screenWidth, screenHeight);
    //    resourceList->draw();
    //    mPlatform->getRenderManagerPtr()->setViewSize(screenWidth, screenHeight);
    //    //    mPlatform->getRenderManagerPtr()->doRender(vBuffer, myTexture, 100);
    //    mPlatform->getRenderManagerPtr()->drawOneFrame();

    //    glClearColor(1, 1, 1, 1);
    view->setAspectRatio((screenWidth * 3.f / 4.f) / (screenHeight));
    glViewport(0.f, 0.f, screenWidth * 3.f / 4.f, screenHeight);
    view->setScreen(screenWidth, screenHeight);
    stage->draw();
    //    view_skyBox->setScreen(screenWidth, screenHeight);
    //    stage_skyBox->draw();
  }
  // one viewport
  else if (viewPortSelector == 2)
  {
    glViewport(0.f, 0.f, screenWidth, screenHeight);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    // DISABLE for a while
    if (debugBullet) {
      mydebugdrawer2->SetMatrices(view->getViewMatrix(), view->getProjectionMatrix(), stage->getProgramId());
      stage->getDynamicsWorld()->debugDrawWorld();
      stage->getDynamicsWorldText()->debugDrawWorld();
    }


    stage->draw ();
    //    stage_skyBox->draw ();
    //    SDL_Log("After stage->draw() in render()");
    ImGui_ImplSdlGL3_NewFrame(sdl->getWindow(), g_MouseWheel);
    runGui(show_test_window, show_another_window, show_object_window, clear_color, io);
    //    SDL_Log("After runGui(---) in render()");

    // EPEBROR Comment out temporarily
    //    glClearColor(1, 1, 1, 1);
    //
    //    view->setAspectRatio((screenWidth*1.0f) / (screenHeight*1.0f));
    //    view->setScreen(screenWidth, screenHeight);
    //    view_skyBox->setAspectRatio((screenWidth*1.0f) / (screenHeight*1.0f));
    //    view_skyBox->setScreen(screenWidth, screenHeight);

  }
  // With a radar view
  else if (viewPortSelector == 3)
  {
    glClearColor(1, 1, 1, 1);
    //    resourceList_view->setAspectRatio((screenWidth * 1.f / 5.f) / screenHeight );
    //    resourceList_view->setScreen(screenWidth * 1.f / 5.f, screenHeight);
    glViewport(0.f, 0.f, screenWidth, screenHeight);
    view->setScreen(screenWidth, screenHeight);
    view->setAspectRatio((screenWidth * 1.0f) / (screenHeight * 1.0f));
    //TMP    glViewport(0.f, 0.f, screenWidth * 1.f / 5.f, screenHeight);
    //    resourceList->draw();
    stage->draw();

    //Radar quad
    //TMP    view_skyBox->setAspectRatio((screenWidth * 1.f - (screenWidth * 1.f / 5.f)) / screenHeight);
    glViewport(screenWidth - (screenWidth / 8.f), screenHeight - (screenHeight / 8.f), screenWidth / 8.f, screenHeight / 8.f);
    view->setAspectRatio((screenWidth - (screenWidth / 8.f) - (screenWidth / 8.f)) / ((screenHeight - (screenHeight / 8.f)) - (screenHeight / 8.f)));
    view->setScreen((int) (1.f * screenWidth - (1.f * screenWidth / 8.f) - (1.f * screenWidth / 8.f)), (int) ((1.f * screenHeight - (1.f * screenHeight / 8.f)) - (1.f * screenHeight / 8.f)));

    //TMP    glViewport(screenWidth * 1.f / 5.f, 0.f, screenWidth * 1.f, screenHeight * 1.f);

    //TMP    view->setAspectRatio((screenWidth * 1.f - (screenWidth * 1.f / 5.f)) / screenHeight);
    //TMP    view->setScreen(4 * screenWidth * 1.f / 5.f, screenHeight);

    //TMP    view_skyBox->setScreen(4 * screenWidth * 1.f / 5.f, screenHeight);
    //TMP    stage_skyBox->draw();
    stage->draw();
  }
  sdl->swapWindow ();
}

void LearningPlatform::cleanup()
{
  // to be implemented
  SDL_LogInfo (SDL_LOG_CATEGORY_CUSTOM, "Inside cleanup function");
}

void LearningPlatform::OnExit()
{
  running = false;
}

void LearningPlatform::OnKeyDown(SDL_Keycode sym, Uint16 mod)
{
  //  stageSM->OnKeyDown(this, SDL_Keycode sym, Uint16 mod);

  list<std::string> objL;
  list<std::string> loadObjL;

  //imgui
  int key = sym & ~SDLK_SCANCODE_MASK;
  io.KeysDown[key] = true;
  io.KeyShift = ((SDL_GetModState () & KMOD_SHIFT) != 0);
  io.KeyCtrl = ((SDL_GetModState () & KMOD_CTRL) != 0);
  io.KeyAlt = ((SDL_GetModState () & KMOD_ALT) != 0);
  io.KeySuper = ((SDL_GetModState () & KMOD_GUI) != 0);

  glm::vec3 direction(cos(view->getVerticalAngle()) * sin(view->getHorizontalAngle()), sin(view->getVerticalAngle()), cos(view->getVerticalAngle()) * cos(view->getHorizontalAngle()));
  // changing to lock the FP Shooter at horizontal level at all times
  //  glm::vec3 direction (cos (0) * sin (view->getHorizontalAngle ()), sin (0), cos (0) * cos (view->getHorizontalAngle ()));

  // Right vector
  glm::vec3 right = glm::vec3 (
      sin (view->getHorizontalAngle () - M_PI / 2.0f), 0,
      cos (view->getHorizontalAngle () - 3.14159265f / 2.0f));

  switch (sym)
  {
  case SDLK_ESCAPE:
    running = false;
    break;
  case SDLK_HOME:
    lightHome = true;
    break;
  case SDLK_END:
    lightEnd = true;
    break;
  case SDLK_DELETE:
    lightDelete = true;
    break;
  case SDLK_PAGEDOWN:
    lightPageDown = true;
    break;
  case SDLK_INSERT:
    lightInsert = true;
    break;
  case SDLK_PAGEUP:
    lightPageUp = true;
    break;
  case SDLK_w: // move creature forward  (original 0.25)
    //      stage->moveCreatureForward (0.25);
    wasd[keys::forward] = true;
    stage->moveFPersonFwd(direction, right, wasd);
    break;
  case SDLK_s: // move creature backward   (original 0.25)
    //      stage->moveCreatureBack (0.25);
    wasd[keys::backward] = true;
    stage->moveFPersonBack(direction, right, wasd);
    break;
  case SDLK_a: // rotate creature left
    //      stage->rotateCreature (3.14159265f / 25.0f, 0.01);
    wasd[keys::left] = true;
    stage->moveFPersonLeft(direction, right, wasd);
    break;
  case SDLK_d: // rotate creature right
    //      stage->rotateCreature (-3.14159265f / 25.0f, 0.01);
    wasd[keys::right] = true;
    stage->moveFPersonRight(direction, right, wasd);
    break;
  case SDLK_SPACE: // rotate creature right
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ENTER OnKeyDown, key SDLK_SPACE has been pressed down");
    //      stage->rotateCreature (-3.14159265f / 25.0f, 0.01);
    stage->moveFPersonJump(direction, right);
    break;
  case SDLK_c: // create wall
    c_button = true;
    break;
  case SDLK_p: // create Plate
    p_button = true;
    break;
  case SDLK_g: // create glucose
    g_button = true;
    break;
  case SDLK_i: // create MenuContainer
    i_button = true;
    break;
  case SDLK_b: // create Text
    b_button = true;
    break;
  case SDLK_r: // rotate object
    r_button = true;
    break;
  case SDLK_u: // move the camera forward
    view->updateKeyStates(keys::forward);
    break;
  case SDLK_j: // move the camera backward
    view->updateKeyStates(keys::backward);
    break;
  case SDLK_h: // move the camera left
    view->updateKeyStates(keys::left);
    break;
  case SDLK_k: // move the camera right
    view->updateKeyStates(keys::right);
    break;
  case SDLK_m: // rotate view allowed
    m_button = true;
    view->setRotationAllowed(true);
    view_skyBox->setRotationAllowed(true);
    break;
  case SDLK_n: // create plane
    n_button = true;
    break;
  case SDLK_q:
//    gameLogic->reset();
//    gameLogic->easyGamePlayInit();
    break;
  case SDLK_t: // delete cube
    t_button = true;
    break;
  case SDLK_x: // activate resource window
    x_button = true;
    break;
  case SDLK_z: // delete text
    z_button = true;
    break;
  case SDLK_v:
    v_button = true;
    break;
  case SDLK_1: // switch to two viewports
    viewPortSelector = 1;
    break;
  case SDLK_2: // switch to one viewports
    viewPortSelector = 2;
    break;
  case SDLK_3: // switch to one viewport and a radar view
    viewPortSelector = 3;
    break;
  case SDLK_4: // print viewMatrix info
    printCameraPositionCmd->execute();
    break;
  case SDLK_9: // save the world
    stage->saveActorList(&objL);
    resObj->saveScene("worldSave.lps", &objL);
    objL.clear();
    break;
  case SDLK_8: // load the world
    resObj->loadScene("worldSave.lps", &loadObjL);
    stage->loadActorList(&loadObjL);
    loadObjL.clear();
    BSoundBank::SoundControl.Stop();
    BSoundBank::SoundControl.FadeInChannel(horror, 1000);
    BSoundBank::SoundControl.Repeat(horror);
    BSoundBank::SoundControl.FadeInChannel(Soundwin, 1000);
    BSoundBank::SoundControl.Repeat(Soundwin);
    updateGuiOnFPersonData(stage->getScene()->getCreature());
    break;
  case SDLK_LCTRL:
    ctrl_button = true;
    break;
  case SDLK_UP:
  {
    if (ctrl_button) {
      //		  view->setPosition(view->getPosition() + glm::vec3(0,view->getSpeed(),0));
      view->setPosition(glm::vec3(1.18f, 18.5f, 5.0f));
    }
    else {
//      view->move(keys::up);
      view->updateKeyStates(keys::up);
      // view->setPosition(glm::vec3(3.5f, 17.05f, 12.0f)); 1280x720
    }
    break;
  }
  case SDLK_DOWN:
  {
    if (ctrl_button) {
      //		  view->setPosition(view->getPosition() - glm::vec3(0,view->getSpeed(),0));
      view->setPosition(glm::vec3(1.180000, 14.330000, 5.000000));
      break;
    }
    else {
      //view->setPosition(glm::vec3(3.5f, 6.80f, 12.0f)); 1280x720
      view->updateKeyStates(keys::down);
//      view->move(keys::down);
      break;
    }
  }
  case SDLK_LEFT:
  {
    //		view->setPosition(view->getPosition() + glm::vec3(0,view->getSpeed(),0));
    view->move(keys::left);
    break;
  }
  case SDLK_RIGHT:
  {
    //					view->setPosition(view->getPosition() - glm::vec3(0,view->getSpeed(),0));
    view->move(keys::right);
    break;
  }
  case SDLK_F1:
  {
    view->printPos();
    break;
  }
  case SDLK_F2:
  {
    if ((key == 3) && (x_button == true)) {
      resourceList->createCoordinateLines(glm::vec3(0.0f, 0.0f, 0.0f), c_line);
    }
    else {
      alterGridCmd->execute();
      if (statusOfShowGrid == true) {
        statusOfShowGrid = false;
      }
      else {
        statusOfShowGrid = true;
      }
    }
    break;
  }
  case SDLK_F3:
  {
    if (l_shift_button) {
      if ((key == 3) && (x_button == true)) {
        resourceList->moveCoordinateLines(glm::vec3(0.0f, 0.0f, -1.0f), 20000);
      }
      else {
        // moveOutGridCmd->execute();
        stage->moveCoordinateLines(glm::vec3(0.0f, 0.0f, -1.0f), 20000);
      }
    }
    else
    {
      if ((key == 3) && (x_button == true))
      {
        resourceList->moveCoordinateLines(glm::vec3(0.0f, 0.0f, 1.0f), 20000);
      }
      else
      {
        // moveInGridCmd->execute();
        stage->moveCoordinateLines(glm::vec3(0.0f, 0.0f, 1.0f), 20000);
      }
    }
    break;
  }
  case SDLK_F4:
  {
    if (l_shift_button)
    {
      if ((key == 3) && (x_button == true))
      {
        resourceList->moveCoordinateLines(glm::vec3(-1.0f, 0.0f, 0.0f), 20000);
      }
      else
      {
        // moveOutGridCmd->execute();
        stage->moveCoordinateLines(glm::vec3(-1.0f, 0.0f, 0.0f), 20000);
      }
    }
    else {
      if ((key == 3) && (x_button == true))
      {
        resourceList->moveCoordinateLines(glm::vec3(1.0f, 0.0f, 0.0f), 20000);
      }
      else
      {
        // moveInGridCmd->execute();
        stage->moveCoordinateLines(glm::vec3(1.0f, 0.0f, 0.0f), 20000);
      }
    }
    break;
  }
  case SDLK_LSHIFT:
  {
    l_shift_button = true;
    break;
  }
  case SDLK_F5:
  {
    stage->listText();
    break;
  }
  case SDLK_F8:
    if (F8_button)
      F8_button = false;
    else
      F8_button = true;
    break;
  case SDLK_F9:
    if (F9_button)
      F9_button = false;
    else
      F9_button = true;
    break;
  case SDLK_F10:
    alterCameraSpeedCmd->execute();
    break;
  case SDLK_F12:
    if (F12_button) {
      F12_button = false;
      //      view->setDefault();
      //      view_skyBox->setDefault();
      view->setRotationAllowed(false);
      view_skyBox->setRotationAllowed(false);
    }
    else {
      F12_button = true;
      view->setRotationAllowed(true);
      view_skyBox->setRotationAllowed(true);
    }
    break;
  default:
    break;
  }
  view->setViewMatrix (glm::lookAt (view->getPosition (),      // Camera is here
      view->getPosition () + direction, // and looks here : at the same position, plus "direction"
      glm::cross (right, direction) // Head is up (set to 0,-1,0 to look upside-down)
          ));
}

void LearningPlatform::OnKeyUp(SDL_Keycode sym, Uint16 mod)
{
  //	printf("LearningPlatform:OnKeyUp\n");
  int key = sym & ~SDLK_SCANCODE_MASK;
  io.KeysDown[key] = false;
  io.KeyShift = ((SDL_GetModState () & KMOD_SHIFT) != 0);
  io.KeyCtrl = ((SDL_GetModState () & KMOD_CTRL) != 0);
  io.KeyAlt = ((SDL_GetModState () & KMOD_ALT) != 0);
  io.KeySuper = ((SDL_GetModState () & KMOD_GUI) != 0);

  switch (sym)
  {
  case SDLK_HOME:
    lightHome = false;
    break;
  case SDLK_END:
    lightEnd = false;
    break;
  case SDLK_DELETE:
    lightDelete = false;
    break;
  case SDLK_PAGEDOWN:
    lightPageDown = false;
    break;
  case SDLK_PAGEUP:
    lightPageUp = false;
    break;
  case SDLK_INSERT:
    lightInsert = false;
    break;

  case SDLK_w:
    wasd[keys::forward] = false;
    SDL_Log("OnSDLKeyUp noted that forward key: w is UP");
    ((FPerson*) stage->getScene()->getCreature())->setWasd(wasd);
    break;
  case SDLK_a:
    wasd[keys::left] = false;
    SDL_Log("OnSDLKeyUp noted that left key: a is UP");
    ((FPerson*) stage->getScene()->getCreature())->setWasd(wasd);
    break;
  case SDLK_s:
    wasd[keys::backward] = false;
    SDL_Log("OnSDLKeyUp noted that backward key: s is UP");
    ((FPerson*) stage->getScene()->getCreature())->setWasd(wasd);
    break;
  case SDLK_d:
    wasd[keys::right] = false;
    SDL_Log("OnSDLKeyUp noted that right key: d is UP");
    ((FPerson*) stage->getScene()->getCreature())->setWasd(wasd);
    break;
  case SDLK_SPACE:
    // add resetting jump bool in scene...
    break;
  case SDLK_c: // create wall
    c_button = false;
    break;
  case SDLK_p: // create Plate
    p_button = false;
    break;
  case SDLK_g: // create glucose
    g_button = false;
    break;
  case SDLK_i: // create MenuContainer
    i_button = false;
    break;
  case SDLK_b: // create Text
    b_button = false;
    break;
  case SDLK_r: // rotate object
    r_button = false;
    break;
  case SDLK_u:
    view->updateKeyStates(keys::still);
    break;
  case SDLK_j:
    view->updateKeyStates(keys::still);
    break;
  case SDLK_h: // move the camera left
    view->updateKeyStates(keys::still);
    break;
  case SDLK_k: // move the camera right
    view->updateKeyStates(keys::still);
    break;
  case SDLK_UP: // move the camera right
    view->updateKeyStates(keys::still);
    break;
  case SDLK_DOWN: // move the camera right
      view->updateKeyStates(keys::still);
      break;
  case SDLK_m: // rotate view
    m_button = false;
    view->setDefault();
    view_skyBox->setDefault();
    view->setRotationAllowed(false);
    view_skyBox->setRotationAllowed(false);
    break;
  case SDLK_n: // create plane
    n_button = false;
    break;
  case SDLK_t: // delete cube
    t_button = false;
    break;
  case SDLK_x: // Coordinate lines in resource window
    x_button = false;
    break;
  case SDLK_LSHIFT:
    l_shift_button = false;
    break;
  case SDLK_LCTRL:
    ctrl_button = false;
    break;
  default:
    break;
  }
}

void LearningPlatform::OnRButtonDown(int mX, int mY)
{
  rightButtonDown = true;
  move_obj = true;
  Stage *st;

  if (F8_button)
    st = resourceList;
  else
    st = stage;

  if ((obj = getObj (mX, getScreenHeight () - mY, st)) != nullptr)
  {
    if (t_button)
    {
      st->deleteFallingCube(obj);
      t_button = false;
    }
    else if (x_button) {
      move_obj_depth = true;
    }
    else if (l_shift_button) {
      st->createFallingCube(obj->getTrans() + glm::vec3(0.0f, 2.0f, 0.0f), c_FallingCube + falling_globalId++);
    }
    else {
      _state->onRightButtonDown(this, view, obj);
      //			obj->setSavedTrans(obj->getTrans());
      //			obj->setTrans(view->getPosition() + glm::vec3(0.0f,0.0f,-1.8f) - obj->getTrans());
      //			std::cout << "Saved Trans: [" << obj->getSavedTrans().x << ", " << obj->getSavedTrans().y << ", " << obj->getSavedTrans().z << "]" << std::endl;
    }
  }

  // Same for text objects:
  if ((text_obj = getTextObj(mX, getScreenHeight() - mY, st)) != nullptr) {
    if (t_button) {
      st->deleteFallingCube(text_obj);
      t_button = false;
    }
    else if (x_button) {
      move_obj_depth = true;
    }
    else {
      _state->onRightButtonDown(this, view, text_obj);
      //      obj->setSavedTrans(obj->getTrans());
      //      obj->setTrans(view->getPosition() + glm::vec3(0.0f,0.0f,-1.8f) - obj->getTrans());
      //      std::cout << "Saved Trans: [" << obj->getSavedTrans().x << ", " << obj->getSavedTrans().y << ", " << obj->getSavedTrans().z << "]" << std::endl;
    }
  }

}

void LearningPlatform::OnLButtonDown(int mX, int mY)
{
  SDL_Window* window = sdl->getWindow ();
  Stage *st;
  leftButtonDown = true;
  if (ImGui::IsMouseHoveringAnyWindow ()) // If user is interacting with window gui, then do nothing.
  {
    return;
  }

  if (F8_button)
  {
    st = resourceList;
  }
  else if (F9_button)
  {
    st = stage_skyBox;
  }
  else
  {
    st = stage;
  }

  if (menu_select)
  {
    cout << "menu_select = true" << std::endl;
    menu_select = static_cast<MenuContainer*>(text_obj)->selectMenuItem(window,
        mX, mY);
    startmY = false;
    return;
  }

  if ((obj = getObj (mX, st->view.getScreenHeight () - mY, st)) != nullptr)
  {
    cout << "Checking id of NON-TEXT object, id = " << obj->getId() << endl;
    std::cout << "Obj id: " << obj->getId() << ", trans: (" << obj->getTrans().x << ", " << obj->getTrans().y << ", " << obj->getTrans().z << ") " << std::endl;

    updateGuiOnCurrentObjData(obj);

    move_obj = true;
    _state->onLeftButtonDown(this);

    if (obj->getId () > 56050 && obj->getId () < 59000)
    {
      if (true)
      {
        //      BSoundBank::SoundControl.Play (SoundX);
        ((MazeFloor*) obj)->setOpenDoor();
      }
    }
    if (t_button) {
      //      BSoundBank::SoundControl.Play (SoundX);
      st->deleteObject(obj);
      t_button = false;
    }
    else if (v_button) {
      //			BSoundBank::SoundControl.Play(SoundO);
      st->createWallCube(obj->getTrans() + glm::vec3(0.0f, 2.0f, 0.0f), ++lp_wall_cube, 2);
      v_button = false;
    }
    else if (g_button) {
      if (ctrl_button) {
        st->createGlucose6Phosphate(obj->getTrans() + glm::vec3(0.0f, 0.0f, 2.0f), ++lp_glucose, 2);
      }
      else {
        //			BSoundBank::SoundControl.Play(SoundO);
        st->createWallCube(obj->getTrans() + glm::vec3(0.0f, 0.0f, 2.0f), ++lp_wall_cube, 2);
        g_button = false;
      }
    }
    else if (c_button) {
      st->createWall(obj->getTrans() + glm::vec3(0.0f, 0.0f, 4.0f), ++lp_wall, 2);
    }
    else if (p_button) {
      st->createPlate(obj->getTrans() + glm::vec3(0.0f, 0.0f, .2f));
    }
    else if (b_button) {
      //			BSoundBank::SoundControl.Play(SoundO);
//      st->createText(obj->getTrans() + glm::vec3(0.0f, 0.0f, 1.0f), ++lp_text, 2);
    }
    else if (n_button) {
      //			BSoundBank::SoundControl.Play(SoundO);
      st->createPlane(obj->getTrans() + glm::vec3(0.0f, 14.0f, 0.0f), ++lp_plane, 2);
    }
    else if (r_button) {
      double r = 3.14159265f / 4.0f;
      if (l_shift_button) {
        obj->setRotationMatrix_X(r);
      }
      else {
        obj->setRotationMatrix_Y(r);
      }
    }
    else if (lightHome) {
      obj->setLightPos(obj->getLightPos() + glm::vec3(0.0f, 10.0f, 0.0f));
      std::cout << "lightposition: (" << obj->getLightPos().x << ", " << obj->getLightPos().y << ", " << obj->getLightPos().z << ")" << std::endl;
    }
    else if (lightEnd) {
      obj->setLightPos(obj->getLightPos() + glm::vec3(0.0f, -10.0f, 0.0f));
      std::cout << "lightposition: (" << obj->getLightPos().x << ", " << obj->getLightPos().y << ", " << obj->getLightPos().z << ")" << std::endl;
    }
    else if (lightDelete) {
      obj->setLightPos(obj->getLightPos() + glm::vec3(-10.0f, 0.0f, 0.0f));
      std::cout << "lightposition: (" << obj->getLightPos().x << ", " << obj->getLightPos().y << ", " << obj->getLightPos().z << ")" << std::endl;
    }
    else if (lightPageDown) {
      obj->setLightPos(obj->getLightPos() + glm::vec3(10.0f, 0.0f, 0.0f));
      std::cout << "lightposition: (" << obj->getLightPos().x << ", " << obj->getLightPos().y << ", " << obj->getLightPos().z << ")" << std::endl;
    }
    else if (lightPageUp) {
      obj->setLightPos(obj->getLightPos() + glm::vec3(0.0f, 0.0f, 10.0f));
      std::cout << "lightposition: (" << obj->getLightPos().x << ", " << obj->getLightPos().y << ", " << obj->getLightPos().z << ")" << std::endl;
    }
    else if (lightInsert) {
      obj->setLightPos(obj->getLightPos() + glm::vec3(0.0f, 0.0f, -10.0f));
      std::cout << "lightposition: (" << obj->getLightPos().x << ", " << obj->getLightPos().y << ", " << obj->getLightPos().z << ")" << std::endl;
    }
  }
  if ((text_obj = getTextObj(mX, st->view.getScreenHeight() - mY, st)) != nullptr) {
    cout << "Checking id of TEXT object, id = " << text_obj->getId() << endl;
    std::cout << "Obj id: " << text_obj->getId() << ", trans: (" << text_obj->getTrans().x << ", " << text_obj->getTrans().y << ", " << text_obj->getTrans().z << ") " << std::endl;

    updateGuiOnCurrentObjData(text_obj);

    move_text = true;
    _state->onLeftButtonDown(this);
  }
}

LPObject* LearningPlatform::getObj(int mX, int mY, Stage* stage)
{
  glm::vec3 out_origin;
  glm::vec3 out_direction;
  stage->view.ScreenPosToWorldRay (mX, mY, stage->view.getScreenWidth (),
      stage->view.getScreenHeight(), stage->view.getViewMatrix(), stage->view.getProjectionMatrix(), out_origin, out_direction);
  out_direction = out_direction * 1000.0f;
  TRACE_DEBUG("out_origin=(%f, %f, %f)", out_origin.x, out_origin.y, out_origin.z);
  TRACE_DEBUG("out_direction=(%f, %f, %f)", out_direction.x, out_direction.y, out_direction.z);

  btCollisionWorld::ClosestRayResultCallback RayCallback (
      btVector3 (out_origin.x, out_origin.y, out_origin.z),
      btVector3 (out_direction.x, out_direction.y, out_direction.z));
  stage->getDynamicsWorld ()->rayTest (
      btVector3 (out_origin.x, out_origin.y, out_origin.z),
      btVector3 (out_direction.x, out_direction.y, out_direction.z),
      RayCallback);
  if (RayCallback.hasHit ())
  {
    obj = (LPObject*) RayCallback.m_collisionObject->getUserPointer();
    std::cout << "Found Object!\n";
  }
  else
  {
    obj = nullptr;
    std::cout << "No Object!\n";
  }
  return obj;
}

LPObject* LearningPlatform::getTextObj(int mX, int mY, Stage * stage)
{
  glm::vec3 out_origin;
  glm::vec3 out_direction;
  stage->view.ScreenPosToWorldRay (mX, mY, stage->view.getScreenWidth (),
      stage->view.getScreenHeight(), stage->view.getViewMatrix(), stage->view.getProjectionMatrix(), out_origin, out_direction);
  out_direction = out_direction * 1000.0f;
  TRACE_DEBUG("out_origin=(%f, %f, %f)", out_origin.x, out_origin.y, out_origin.z);
  TRACE_DEBUG("out_direction=(%f, %f, %f)", out_direction.x, out_direction.y, out_direction.z);

  btCollisionWorld::ClosestRayResultCallback RayCallback (
      btVector3 (out_origin.x, out_origin.y, out_origin.z),
      btVector3 (out_direction.x, out_direction.y, out_direction.z));
  stage->getDynamicsWorldText ()->rayTest (
      btVector3 (out_origin.x, out_origin.y, out_origin.z),
      btVector3 (out_direction.x, out_direction.y, out_direction.z),
      RayCallback);
  if (RayCallback.hasHit ())
  {
    text_obj = (LPObject*) RayCallback.m_collisionObject->getUserPointer();
  }
  else
  {
    text_obj = nullptr;
    std::cout << "No Text Object!\n";
  }
  return text_obj;
}

void LearningPlatform::OnLButtonUp(int mX, int mY)
{
  cout << "ENTER OnLButtonUp" << endl;
  leftButtonDown = false;
  move_text = false;
  move_obj = false;

  view->updateKeyStates(keys::still); // stop moving the camera
  _state->onLeftButtonUp (this);
  //	std::cout << "OnLButtonUp: getPreparedForDelete has value w="
  //			<< stage->getPreparedForDelete() << endl;

  if (adjustToGridEnabled)
  {
    if (obj != nullptr)
    {
      obj->adjustToGrid (); // make it fit in grid
    }
    if (text_obj != nullptr)
    {
      text_obj->adjustToGrid (); // make it fit in grid
    }
  }

  SDL_SetRelativeMouseMode (SDL_bool::SDL_FALSE);
  // TODO: EPEBROR Commented out since restart was not working when it was active.
  if (obj != nullptr) {
    obj->getRigidBody()->activate();
  }
  else if (text_obj != nullptr) {
    text_obj->getRigidBody()->activate();
  }
}

void LearningPlatform::OnRButtonUp(int mX, int mY)
{
  rightButtonDown = false;
  move_obj = false;
  move_obj_depth = false;
  if (obj != nullptr)
  {
    if (x_button == true) {
      x_button = false;
    }
    else
    {
      _state->onRightButtonUp(this, obj);
    }
    if (adjustToGridEnabled) {
      obj->adjustToGrid(); // make it fit in grid
    }
  }
  SDL_SetRelativeMouseMode (SDL_bool::SDL_FALSE);
}

void LearningPlatform::OnMButtonUp(int mX, int mY)
{
  middleButtonDown = false;
  //	obj->getRigidBody()->activate();
}

void LearningPlatform::OnMButtonDown(int mX, int mY)
{
  middleButtonDown = true;
  //	obj->getRigidBody()->activate();
}

void LearningPlatform::OnMouseWheel(Sint32 y)
{
  if (ImGui::IsMouseHoveringAnyWindow()) // If user is interacting with window gui, then do nothing.
  {
    //    if (y > 0) {
    //      g_MouseWheel = 1;
    //    }
    //    else if (y < 0) {
    //      g_MouseWheel = -1;
    //    }
    return;
  }

  //imgui
  if (y > 0)
  {
    //      g_MouseWheel = 1;
    //    view->updateKeyStates(keys::forward);
    view->move(keys::forward);
    view->move(keys::forward);
    view->move(keys::forward);
    view->move(keys::forward);
    view->move(keys::forward);
    view->move(keys::forward);
    view->move(keys::forward);
    view->move(keys::forward);
    view->move(keys::forward);

  }
  else if (y < 0)
  {
    //      g_MouseWheel = -1;
    view->move(keys::backward);
    view->move(keys::backward);
    view->move(keys::backward);
    view->move(keys::backward);
    view->move(keys::backward);
    view->move(keys::backward);
    view->move(keys::backward);
    view->move(keys::backward);
    view->move(keys::backward);
  }

  //	view->setFoV(view->getFoV() - 2 * y);
  //	view->setProjectionMatrix(glm::perspective(view->getFoV(), screenWidth * 1.0f / (screenHeight * 1.0f), 0.1f, 200.0f));
}

void LearningPlatform::OnTextInput(char text[SDL_TEXTINPUTEVENT_TEXT_SIZE])
{
  io.AddInputCharactersUTF8 (text);
}

void LearningPlatform::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
  // EventSM->onMouseMove(mX, mY, relX, relY, Left, Right, Middle);
  //    logger << "ENTER LearningPlatform::OnMouseMove\n";
  // std::cout << "ENTER LearningPlatform::OnMouseMove" << std::endl;
  TRACE_INFO("ENTER LearningPlatform::OnMouseMove");
  SDL_Window* window = sdl->getWindow ();

  Stage *st;
  View *v;
  if (F8_button)
  {
    st = resourceList;
    v = resourceList_view;
  }
  else
  {
    st = stage;
    v = view;
  }
  if (menu_select)
  {
    disableMouseCursor(text_obj, mX, mY);
    if (startmY == false)
    {
      static_cast<MenuContainer*>(text_obj)->markInitMenuItem(window, mX, mY);
      startmY = true;
    }
    else
    {
      static_cast<MenuContainer*>(text_obj)->markMenuItem(mY);
    }
  }
  else
  {
    // Below is to calculate the view angle when moving the mouse
    v->computeMatricesFromInputs(window, mX, mY, relX, relY, Left, Right, Middle);
    view_skyBox->computeMatricesFromInputs(window, mX, mY, relX, relY, Left, Right, Middle);
    if (obj != nullptr || text_obj != nullptr)
    {
      if (move_text && moveObjEnabled) {
        if ((text_obj->getId() < 62000) || (text_obj->getId() > 63000)) {
          disableMouseCursor(text_obj, mX, mY);
          _state->onMouseMove(this, relX, relY, text_obj); // move (leftbutton) or rotate (rightButton)
        }
      }
      if (move_obj && moveObjEnabled) {
        if ((obj->getId () != 20000) && ( (obj->getId () < 24000) ||(obj->getId () > 27000)) && ((obj->getId() < 61000) || (obj->getId() > 63000))  && ((obj->getId() > 31000) || (obj->getId() < 30000))) {
          disableMouseCursor(obj, mX, mY);
          _state->onMouseMove(this, relX, relY, obj); // move (leftbutton) or rotate (rightButton)
        }
      }
      if (move_obj && move_obj_depth) {
        if ((obj->getId() < 61000) || (obj->getId() > 62000 ) ) {
          TRACE_INFO("obj->getId()=%d", obj->getId());
          std::cout << "obj->getId()=" << obj->getId() << std::endl;
          SDL_ShowCursor(SDL_DISABLE);
          obj->setTrans(glm::vec3(0.f, 0.f, -relY * 0.01));
        }
      }
      if (move_text && move_obj_depth) {
        if ((text_obj->getId() < 62000) || (text_obj->getId() > 63000)) {
          TRACE_INFO("text_obj->getId()=%d", text_obj->getId());
          std::cout << "text_obj->getId()=" << text_obj->getId() << std::endl;
          SDL_ShowCursor(SDL_DISABLE);
          text_obj->setTrans(glm::vec3(0.f, 0.f, -relY * 0.01));
        }
      }
    }
    else {
      // Move the view instead

        if (leftButtonDown && !ImGui::IsMouseHoveringAnyWindow () && !RegulationQuestionStateIsActive) {
          view->setRelativePosition(-glm::vec3(relX * 0.01, -relY * 0.01, 0.f));
        }
    }
  }
}

void LearningPlatform::disableMouseCursor(LPObject* obj, int mX, int mY)
{
  if (SDL_ShowCursor (-1) == 1)
  {
    SDL_SetRelativeMouseMode(SDL_bool::SDL_TRUE);
    SDL_ShowCursor(SDL_DISABLE);
    //	std::cout << "SDL_ShowCursor = 1 now DISABLING" << std::endl;
    if (obj != nullptr) {
      obj->setMouseCoord(glm::vec2((float) mX, (float) mY));
    }
    if (text_obj != nullptr) {
      text_obj->setMouseCoord(glm::vec2((float) mX, (float) mY));
    }
  }
}

void LearningPlatform::OnGuiMainMenuRestart()
{
//  gameLogic->reset();
  obj = nullptr;
  text_obj = nullptr;
  updateGuiOnCurrentObjData(nullptr);
}

void LearningPlatform::OnGuiWindowShowObject(bool *statusOfObjectWindow)
{
  if (*statusOfObjectWindow == false)
  {
    *statusOfObjectWindow = true;
  }
  else
  {
    *statusOfObjectWindow = false;
  }
}

void LearningPlatform::OnGuiWindowShowStatus(bool *statusOfStatusWindow)
{
  if (*statusOfStatusWindow == false)
  {
    *statusOfStatusWindow = true;
  }
  else
  {
    *statusOfStatusWindow = false;
  }
}

void LearningPlatform::OnGuiWindowShowChangeLight(bool *statusOfChangeLight)
{
  if (*statusOfChangeLight == false)
  {
    *statusOfChangeLight = true;
  }
  else
  {
    *statusOfChangeLight = false;
  }
}

void LearningPlatform::OnGuiMainMenuDeactivatingMovements( bool* statusOfDeactivatingMovements)
{
  if (*statusOfDeactivatingMovements == true)
  {
    *statusOfDeactivatingMovements = false;
    deactivatingMovements = false;
  }
  else
  {
    *statusOfDeactivatingMovements = true;
    deactivatingMovements = true;
  }
}

void LearningPlatform::OnGuiWindowMenuConfigRayTrace (bool* statusOfConfigRayTrace)
{
  {
    if (*statusOfConfigRayTrace == false)
    {
      *statusOfConfigRayTrace = true;
    }
    else
    {
      *statusOfConfigRayTrace = false;
    }
  }
}

void LearningPlatform::OnGuiWindowCreateObjectsWindow( bool* statusOfCreateWindow)
{
  if (*statusOfCreateWindow == false)
  {
    *statusOfCreateWindow = true;
  }
  else
  {
    *statusOfCreateWindow = false;
  }
}

void LearningPlatform::changeState(EventSM* eSM)
{
  _state = eSM;
}

void LearningPlatform::OnGuiMainMenuDetachFromFPS(bool* statusOfDetachFromFPS)
{
  if (*statusOfDetachFromFPS == true) {
    *statusOfDetachFromFPS = false;
    attachedToFPS = true;
  }
  else {
    *statusOfDetachFromFPS = true;
    attachedToFPS = false;
  }
}

void LearningPlatform::registerWatch(int id, LPObject* requester)
{
  std::cout << "adding watch for id=" << id << std::endl;
  watchList.push_back (std::pair<int, LPObject*> (id, requester));
}

void LearningPlatform::actOnRaytrace ()
{
  // raytrace start
  //  std::cout << "Size of WatchList size=" << watchList.size () << std::endl;
  for (auto watched : watchList)
  {
    LPObject* theWatched = stage->getObject(watched.first);
    LPObject* theWatcher = watched.second;
    if (theWatched != nullptr) {
      btTransform transform;
      watched.second->getRigidBody()->getMotionState()->getWorldTransform(transform);
      btVector3 my_direction = btVector3(theWatched->getTrans().x, theWatched->getTrans().y, theWatched->getTrans().z);

      btVector3 my_origin;
      my_origin.setX(watched.second->getTrans().x);
      my_origin.setY(watched.second->getTrans().y + 2);
      my_origin.setZ(watched.second->getTrans().z);
      btCollisionWorld::ClosestRayResultCallback RayCallback(my_origin, my_direction);
      stage->getDynamicsWorld()->rayTest(my_origin, my_direction, RayCallback);
      if (RayCallback.hasHit())
      {
        if (((LPObject*) RayCallback.m_collisionObject->getUserPointer()) == theWatched) {
          theWatcher->sawIt(theWatched->getTrans(), watched.first);
          std::cout << "FPerson is busted!!! Got a hit on an object: id=" << ((LPObject*) RayCallback.m_collisionObject->getUserPointer())->getId() << std::endl;
        }
      }
    }
    else {
      SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "WARNING: the watched could not be found: id=%d", watched.first);
    }
  }
  // End of raytrace
}

bool LearningPlatform::OnGuigetRegulationQuestion1Active() {
//  if (gameLogic->gameState.getAssessment(0) == Assessment::SUCCESS) {
//    return true;
//  }
  return false;
}

bool LearningPlatform::OnGuigetRegulationQuestion1ActiveAndSuccessful() {
//  if (gameLogic->gameState.getAssessment(10) == Assessment::SUCCESS) {
//    return true;
//  }
  return false;
}

bool LearningPlatform::OnGuigetRegulationQuestion2Active() {
//  if (gameLogic->gameState.getAssessment(2) == Assessment::SUCCESS) {
//    return true;
//  }
  return false;
}

bool LearningPlatform::OnGuigetRegulationQuestion2ActiveAndSuccessful() {
//  if (gameLogic->gameState.getAssessment(11) == Assessment::SUCCESS) {
//    return true;
//  }
  return false;
}

bool LearningPlatform::OnGuigetRegulationQuestion3Active() {
//  if (gameLogic->gameState.getAssessment(9) == Assessment::SUCCESS) {
//     return true;
//   }
   return false;
}

bool LearningPlatform::OnGuigetRegulationQuestion3ActiveAndSuccessful() {
//  if (gameLogic->gameState.getAssessment(12) == Assessment::SUCCESS) {
//    return true;
//  }
  return false;
}


//void LearningPlatform::OnGuiMainMenuCameraShowPosition(bool *statusOfStatusWindow)
//{
//  if (*statusOfStatusWindow == false)
//  {
//    *statusOfStatusWindow = true;
//  }
//  else
//  {
//      *statusOfStatusWindow = false;
//  }
//}

#ifdef SYS_LINUX
int main(int argc, char **argv)
#else
#ifdef SYS_WINNT
int WinMain(int argc, char **argv)
#endif
#endif
{
  LearningPlatform learningPlatform;
  return learningPlatform.execute ();
}

