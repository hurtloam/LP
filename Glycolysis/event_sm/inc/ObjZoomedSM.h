/*
 * ObjZoomedSM.h
 *
 *  Created on: 9 dec. 2017
 *      Author: peter
 */

#ifndef _EVENT_SM_INC_OBJ_ZOOMED_SM_H_
#define _EVENT_SM_INC_OBJ_ZOOMED_SM_H_

#include "EventSM.h"


class ObjZoomedSM: public EventSM {
public:
	static EventSM* Instance();
	virtual ~ObjZoomedSM();
	virtual std::string getName();
	virtual void onMouseMove(LearningPlatformIf* lp, int relX, int relY,
			LPObject* obj);
	virtual void onRightButtonUp(LearningPlatformIf* lp, LPObject* obj);
protected:
	ObjZoomedSM();
private:
	static EventSM* _instance;
};

#endif // _EVENT_SM_INC_OBJ_ZOOMED_SM_H_
