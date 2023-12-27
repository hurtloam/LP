/*
 * StageSM.h
 *
 *  Created on: 22 dec. 2018
 *      Author: peter
 */

#ifndef _EVENT_SM_INC_STAGE_SM_H_
#define _EVENT_SM_INC_STAGE_SM_H_

#include <string>
#include "../../inc/LPObject.h"
#include "../../inc/LearningPlatformIf.h"
#include "../../stage/inc/StageIf.h"


class StageSM {
public:
  StageSM(Stage* defaultStage, Stage* resourceList, Stage* stageSkyBox, View* view, View* resView, View* skyBoxView);
  virtual ~StageSM();
  virtual void onF8KeyDown(LearningPlatformIf* lp);
  virtual void onF9KeyDown(LearningPlatformIf* lp);
  virtual void onF8KeyUp(LearningPlatformIf* lp);
  virtual void onF9KeyUp(LearningPlatformIf* lp);

  virtual void OnKeyDown(SDL_Keycode sym, Uint16 mod);

	virtual std::string getName();
protected:
  void changeState(LearningPlatformIf* lp, StageSM* eSM);

  Stage* defaultStage;
  Stage* resourceList;
  Stage* stageSkyBox;
  Stage* stage;
};

#endif // _EVENT_SM_INC_STAGE_SM_H_
