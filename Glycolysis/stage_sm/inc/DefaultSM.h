/*
 * DefaultSM.h
 *
 *  Created on: 22 dec. 2018
 *      Author: peter
 */

#ifndef _EVENT_SM_INC_DEFAULT_SM_H_
#define _EVENT_SM_INC_DEFAULT_SM_H_

#include "StageSM.h"

class DefaultSM: public StageSM {
public:
  static StageSM* Instance(Stage* defaultStage, Stage* resourceList, Stage* stageSkyBox);
  virtual ~DefaultSM();
	virtual std::string getName();
  virtual void onF8KeyDown(LearningPlatformIf* lp);
  virtual void onF8KeyUp(LearningPlatformIf* lp);
  virtual void OnKeyDown(LearningPlatformIf* lp, SDL_Keycode sym, Uint16 mod);

protected:
  DefaultSM(Stage* defaultStage, Stage* resourceList, Stage* stageSkyBox);
private:
  static StageSM* _instance;

};

#endif // _EVENT_SM_INC_DEFAULT_SM_H_
