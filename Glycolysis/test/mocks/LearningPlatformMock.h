/*
 * StageMock.h
 *
 *  Created on: Apr 1, 2018
 *      Author: peter
 */

#pragma once

#include <gmock/gmock.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../event_sm/inc/EventSM.h"
#include "../../inc/LearningPlatformIf.h"

class LearningPlatformMock : public LearningPlatformIf {
  public:
	MOCK_METHOD1(changeState, void(EventSM* eSM));
	MOCK_METHOD0(init, void ());
	MOCK_METHOD0(execute, int());
	MOCK_METHOD0(action, void());
	MOCK_METHOD0(runSplashScreen, bool());
	MOCK_METHOD1(render, void(double diffTime));
	MOCK_METHOD0(cleanup, void());
	MOCK_METHOD0(OnExit, void());
	MOCK_METHOD2(OnKeyDown, void(SDL_Keycode sym, Uint16 mod));
	MOCK_METHOD2(OnKeyUp, void(SDL_Keycode sym, Uint16 mod));
	MOCK_METHOD2(OnLButtonDown, void(int mX, int mY));
	MOCK_METHOD2(OnRButtonDown, void(int mX, int mY));
	MOCK_METHOD2(OnLButtonUp, void(int mX, int mY));
	MOCK_METHOD2(OnRButtonUp, void(int mX, int mY));
	MOCK_METHOD2(OnMButtonUp, void(int mX, int mY));
	MOCK_METHOD2(OnMButtonDown, void(int mX, int mY));
	MOCK_METHOD7(OnMouseMove, void(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle));
	MOCK_METHOD1(OnMouseWheel, void(Sint32 y));
	MOCK_METHOD1(OnTextInput, void (char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]));
	MOCK_CONST_METHOD0(getScreenWidth, int());
	MOCK_METHOD1(setScreenWidth, void(int screenWidth));
	MOCK_CONST_METHOD0(getScreenHeight, int());
	MOCK_METHOD1(setScreenHeight, void(int screenHeight));

	// Gui
	MOCK_METHOD1(OnGuiWindowShowObject, void(bool* statusOfObjectWindow));
	MOCK_METHOD1(OnGuiWindowShowStatus, void(bool* statusOfStatusWindow));
	MOCK_METHOD0(OnGuiMainMenuFileQuit, void());
	MOCK_METHOD0(OnGuiMainMenuShowGrid, void());
	MOCK_METHOD1(OnGuiWindowShowChangeLight, void(bool *statusOfChangeLight));
	MOCK_METHOD0(OnGuiMainMenuRestart, void());
  MOCK_METHOD1(OnGuiMainMenuShowGrid, void(bool* statusOfShowGrid));
  MOCK_METHOD1(OnGuiMainMenuDebugBullet, void (bool*));

	MOCK_METHOD3(getObj, LPObject* (int mX, int mY, Stage *stage));
	MOCK_METHOD3(getTextObj, LPObject* (int mX, int mY, Stage *stage));
};
