/*
 * LearningPlatformIf.hpp
 *
 *  Created on: Dec 27, 2018
 *      Author: peter
 */

#ifndef _INC_LEARNING_PLATFORM_IF_H_
#define _INC_LEARNING_PLATFORM_IF_H_

#include <BEvent.h>

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_stdinc.h>
#include "../inc/GameLogic2.h"
#include "../inc/Text.h"
#include <btBulletDynamicsCommon.h>

#include "../gui/LPGui.h"
#include <string>

#include "../command/inc/AlterCameraSpeedCmd.h"
#include "../command/inc/AlterGridCmd.h"
#include "../command/inc/PrintCameraPositionCmd.h"
#include "../stage/inc/Stage.h"
//#include "../event_sm/inc/EventSM.h"

#include "LuaIfLPConfig.h"

class ResObj;
class SDL_base;
class View;
class EventSM;

class LearningPlatformIf {
public:
	/**
	 * @brief
	 */
	LearningPlatformIf() = default;
	virtual ~LearningPlatformIf() = default;

	/**
	 * @brief Initialize the openGL context and the window configuration that is created with this call.
	 */
	virtual void changeState(EventSM* eSM) = 0;
	virtual void init() = 0;
	virtual int execute() = 0;
	virtual void action() = 0;
	virtual bool runSplashScreen() = 0;
	virtual void render(double diffTime) = 0;
	virtual void cleanup() = 0;

	virtual void OnExit() = 0;
	virtual void OnKeyDown(SDL_Keycode sym, Uint16 mod) = 0;
	virtual void OnKeyUp(SDL_Keycode sym, Uint16 mod) = 0;
	virtual void OnLButtonDown(int mX, int mY) = 0;
	virtual void OnRButtonDown(int mX, int mY) = 0;
	virtual void OnLButtonUp(int mX, int mY) = 0;
	virtual void OnRButtonUp(int mX, int mY) = 0;
	virtual void OnMButtonUp(int mX, int mY) = 0;
	virtual void OnMButtonDown(int mX, int mY) = 0;
	virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) = 0;
	virtual void OnMouseWheel(Sint32 y) = 0;
	virtual void OnTextInput(char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]) = 0;
	virtual int getScreenWidth() const = 0;
	virtual void setScreenWidth(int screenWidth) = 0;
	virtual int getScreenHeight() const = 0;
	virtual void setScreenHeight(int screenHeight) = 0;
  // Gui
	virtual void OnGuiWindowShowObject(bool* statusOfObjectWindow) = 0;
	virtual void OnGuiWindowShowStatus(bool* statusOfStatusWindow) = 0;
	virtual void OnGuiMainMenuFileQuit() = 0;
  virtual void OnGuiMainMenuShowGrid(bool* statusOfShowGrid) = 0;
	virtual void OnGuiWindowShowChangeLight(bool *statusOfChangeLight) = 0;
	virtual void OnGuiMainMenuRestart() = 0;
  virtual void
  OnGuiMainMenuDebugBullet(bool* statusOfDebugBullet) = 0;

	virtual LPObject* getObj(int mX, int mY, Stage *stage) = 0;
	virtual LPObject* getTextObj(int mX, int mY, Stage *stage) = 0;
};

#endif // _INC_LEARNING_PLATFORM_IF_H_
