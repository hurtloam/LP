/*
 * LearningPlatform.hpp
 *
 *  Created on: Dec 27, 2013
 *      Author: peter
 */

#pragma once

#include <BEvent.h>
#include "LearningPlatformIf.h"

//#include <GPUPerfAPI.h>
//#include <GPUPerfAPIFunctionTypes.h>
//#include <GPUPerfAPITypes.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_stdinc.h>
#include "../stage/inc/Stage.h"
#include "../inc/GameLogic2.h"
#include "../inc/Text.h"
#include <btBulletDynamicsCommon.h>

#include "../gui/LPGui.h"
#include "../inc/LPWatch.h"
#include <string>

#include "../command/inc/AlterCameraSpeedCmd.h"
#include "../command/inc/AlterGridCmd.h"
#include "../command/inc/PrintCameraPositionCmd.h"

#include "../inc/BulletDebugDrawer.h"
#include "../inc/LPDebugDraw.h"

#include "LuaIfLPConfig.h"
#include <sys/time.h>

class ResObj;
class SDL_base;
class View;
class EventSM;
class LPObject;

//#ifdef WIN32
//static long long GetCurrentTimeMillis()
//{
//  return GetTickCount();
//}
//#else
//static long long GetCurrentTimeMillis()
//{
//  timeval t;
//  gettimeofday(&t, NULL);
//
//  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
//
//  return ret;
//}
//#endif





class LearningPlatform : public LearningPlatformIf, BEvent, LPGui, LPWatch {
public:
	/**
	 * @brief
	 */
	LearningPlatform();
	virtual ~LearningPlatform();

	/**
	 * @brief Initialize the openGL context and the window configuration that is created with this call.
	 */
	void init();
	int execute();
	void action();
	bool runSplashScreen();
	void render(double diffTime);
	void cleanup();

	void OnExit();
	void OnKeyDown(SDL_Keycode sym, Uint16 mod);
	void OnKeyUp(SDL_Keycode sym, Uint16 mod);
	void OnLButtonDown(int mX, int mY);
	void OnRButtonDown(int mX, int mY);
	void OnLButtonUp(int mX, int mY);
	void OnRButtonUp(int mX, int mY);
	void OnMButtonUp(int mX, int mY);
	void OnMButtonDown(int mX, int mY);
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
	void OnMouseWheel(Sint32 y);
	void OnTextInput(char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]);

//	void MyLoggingFunction( GPA_Logging_Type messageType, const char* message );

	int getScreenWidth() const {
		return screenWidth;
	}

	void setScreenWidth(int screenWidth) {
		this->screenWidth = screenWidth;
	}

	int getScreenHeight() const {
		return screenHeight;
	}

	void setScreenHeight(int screenHeight) {
		this->screenHeight = screenHeight;
	}


  // Gui
  void OnGuiWindowShowObject(bool* statusOfObjectWindow);
  void OnGuiWindowShowStatus(bool* statusOfStatusWindow);
	void OnGuiWindowCreateObjectsWindow(bool* statusOfCreateWindow);
  void OnGuiMainMenuFileQuit() {
    running = false;
  }

  void OnGuiMainMenuShowGrid(bool* statusOfShowGrid)
  {
    alterGridCmd->execute();
    if (*statusOfShowGrid == true) {
      *statusOfShowGrid = false;
    }
    else {
      *statusOfShowGrid = true;
    }
  }

  void
  OnGuiMainMenuMoveObjEnabled(bool* statusOfMoveObjEnabled)
  {
    if (*statusOfMoveObjEnabled == true)
    {
      *statusOfMoveObjEnabled = false;
      moveObjEnabled = false;
    }
    else
    {
      *statusOfMoveObjEnabled = true;
      moveObjEnabled = true;
    }
  }

  void OnGuigetRegulationQuestionState(bool isRegulationQuestionStateActive) {
    RegulationQuestionStateIsActive = isRegulationQuestionStateActive;
    if (RegulationQuestionStateIsActive) {
      view->setPosition(glm::vec3(0.0f, 14.5f, 15.0f));
      view_skyBox->setPosition(glm::vec3(0.0f, 14.5f, 15.0f));
      view->setRotationAllowed(false);
      view_skyBox->setRotationAllowed(false);
    } else {
      obj = nullptr;
      text_obj = nullptr;
      updateGuiOnCurrentObjData(nullptr);
    }
  }

  bool OnGuigetRegulationQuestion1Active();
  bool OnGuigetRegulationQuestion1ActiveAndSuccessful();

  bool OnGuigetRegulationQuestion2Active();
  bool OnGuigetRegulationQuestion2ActiveAndSuccessful();

  bool OnGuigetRegulationQuestion3Active();
  bool OnGuigetRegulationQuestion3ActiveAndSuccessful();


  void
  OnGuiMainMenuAdjustToGridEnabled(bool* statusOfAdjustToGridEnabled)
  {
    if (*statusOfAdjustToGridEnabled == true)
    {
      *statusOfAdjustToGridEnabled = false;
      adjustToGridEnabled = false;
    }
    else
    {
      *statusOfAdjustToGridEnabled = true;
      adjustToGridEnabled = true;
    }
  }

  void
  OnGuiMainMenuDebugBullet(bool* statusOfDebugBullet)
  {
    if (*statusOfDebugBullet == true)
    {
      *statusOfDebugBullet = false;
      debugBullet = false;
    }
    else
    {
      *statusOfDebugBullet = true;
      debugBullet = true;
    }
  }

  void
  OnGuiMainMenuDetachFromFPS(bool* statusOfDetachFromFPS);

  void OnGuiWindowShowChangeLight(bool *statusOfChangeLight);
  void OnGuiMainMenuRestart();

  void
  OnGuiMainMenuDeactivatingMovements(bool* statusOfDeactivatingMovements);
  void
  OnGuiWindowMenuConfigRayTrace (bool* statusOfConfigRayTrace);

  void
  registerWatch (int id, LPObject* requester);

  void
  actOnRaytrace ();



bool leftButtonDown = false;
bool rightButtonDown = false;
bool middleButtonDown = false;
bool i_button = false;
bool t_button = false;
bool z_button = false;
bool c_button = false;
bool g_button = false;
bool b_button = false;
bool v_button = false;
bool m_button = false;
bool n_button = false;
bool r_button = false;
bool l_shift_button = false;
bool p_button = false;
bool x_button = false; // activate resource window
bool F8_button = false; // activate resource window
bool F9_button = false; // activate skybox stage making it possible to affect the skybox
bool F10_button = false; // activate slower motion to camera
bool F12_button = false; // activate first person movement via mouse (as m_button)
bool ctrl_button = false; // move single step up or down

bool move_text = false; // L Mouse button down we are moving the text
bool move_obj = false;
bool move_obj_depth = false;

bool lightHome = false;
bool lightEnd = false;
bool lightDelete = false;
bool lightPageDown = false;
bool lightPageUp = false;
bool lightInsert = false;
bool menu_select = false;
bool startmY = false;

bool RegulationQuestionStateIsActive = false;

// imgui settings
ImGuiIO io;
bool g_MousePressed[3] = { false, false, false };
float g_MouseWheel = 0.0f;


	void changeState(EventSM* eSM);
  int getSomeValue();
private:
//	friend class EventSM;
	EventSM* _state;
	LPObject* getObj(int mX, int mY, Stage *stage);
	LPObject* getTextObj(int mX, int mY, Stage *stage);
	void disableMouseCursor(LPObject* obj, int mX, int mY);
	bool running;
	SDL_base *sdl;
	Stage *stage;
	Stage *resourceList;
	Stage* stage_skyBox;
	Stage* stageGui;
	View *resourceList_view;
	View *view;
	View* view_skyBox;
	ResObj *resObj;
	GLuint VertexArrayID;
	LPObject *obj;
	LPObject *text_obj;
	GameLogic2 *gameLogic;

	AlterCameraSpeedCmd* alterCameraSpeedCmd;
	AlterGridCmd* alterGridCmd;
	PrintCameraPositionCmd* printCameraPositionCmd;

	int key;
  int viewPortSelector;
	int screenWidth;
	int screenHeight;


//	char objInfo1[128];
//	char objInfo2[128];
//	char objInfo3[128];
//	char moleculeInfo1[128];
//	char moleculeInfo2[128];
//	char moleculeInfo3[128];
//
//	char sdlInfo1[128];
//	char sdlInfo2[128];
//	char sdlInfo3[128];
//	char sdlInfo4[128];

  long long m_startTime;
//  vector<glm::mat4> Transforms;


  bool show_test_window;
  bool show_another_window;
  bool show_object_window;
  ImVec4 clear_color;

	LuaIfLPConfig* luaIf;
  LPConfig* lpConfig;
  bool multiThreadOn;
  int *logOutputPtr;

  bool attachedToFPS = true;
  bool deactivatingMovements = false;
  BulletDebugDrawer mydebugdrawer;
  LPDebugDraw* mydebugdrawer2;
  std::vector<std::pair<int, LPObject*>> watchList;

  bool gameOver = false;
  bool debugBullet = false;
  bool moveObjEnabled = false;
  bool adjustToGridEnabled = false;

  bool prepareForRemovalOfObj = false;
  LPObject* objToRemove;

  bool wasd[7] =
  { false, false, false, false, false, false, false };

  float animTime = 0.0;
  int cnt = 0;
};
