/*
 * EventSSM.h
 *
 *  Created on: 22 dec. 2018
 *      Author: peter
 */

#ifndef _EVENT_SM_INC_EVENT_SM_H_
#define _EVENT_SM_INC_EVENT_SM_H_

#include <string>
#include "../../inc/LPObject.h"
#include "../../inc/ViewIf.h"
#include "../../inc/LearningPlatformIf.h"

class EventSSM {
public:
	EventSSM();
	virtual ~EventSSM();
	virtual void onLeftButtonDown(LearningPlatformIf* lp);
	virtual void onLeftButtonUp(LearningPlatformIf* lp);
	virtual void onRightButtonUp(LearningPlatformIf*, LPObject* obj);

	virtual void onRightButtonDown(LearningPlatformIf* lp, ViewIf* view,
			LPObject* obj);
	virtual void onMouseMove(LearningPlatformIf* lp, int relX, int relY,
			LPObject* obj);
	virtual std::string getName();
protected:
	void changeState(LearningPlatformIf* lp, EventSSM* eSM);
};

#endif // _EVENT_SM_INC_EVENT_SM_H_
