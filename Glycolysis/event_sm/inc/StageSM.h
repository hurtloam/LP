/*
 * InitSM.h
 *
 *  Created on: 22 dec. 2018
 *      Author: peter
 */

#ifndef _EVENT_SM_INC_STAGE_SM_H_
#define _EVENT_SM_INC_STAGE_SM_H_

#include "EventSM.h"

class StageSM: public EventSM {
public:
	static EventSM* Instance();
  virtual ~StageSM();
	virtual std::string getName();
  virtual void onF8KeyDown(LearningPlatformIf* lp);
  virtual void onF9KeyDown(LearningPlatformIf* lp, ViewIf* view,
			LPObject* obj);

protected:
  StageSM();
private:
	static EventSM* _instance;
};

#endif // _EVENT_SM_INC_STAGE_SM_H_
