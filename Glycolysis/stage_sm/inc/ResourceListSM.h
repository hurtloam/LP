/*
 * ObjZoomedSM.h
 *
 *  Created on: 9 dec. 2017
 *      Author: peter
 */

#ifndef _EVENT_SM_INC_RESOURCE_LIST_SM_H_
#define _EVENT_SM_INC_RESOURCE_LIST_SM_H_

#include "StageSM.h"


class ResourceListSM: public StageSM {
public:
  static StageSM* Instance();
  virtual ~ResourceListSM();
	virtual std::string getName();

  virtual void OnKeyDown(LearningPlatformIf* lp, SDL_Keycode sym, Uint16 mod);

  virtual void onMouseMove(LearningPlatformIf* lp, int relX, int relY, LPObject* obj);
	virtual void onRightButtonUp(LearningPlatformIf* lp, LPObject* obj);
protected:
  ResourceListSM();
private:
  static StageSM* _instance;
};

#endif // _EVENT_SM_INC_RESOURCE_LIST_SM_H_
