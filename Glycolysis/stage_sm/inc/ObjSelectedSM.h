/*
 * ObjSelectedSM.h
 *
 *  Created on: 9 dec. 2017
 *      Author: peter
 */

#ifndef _EVENT_SM_INC_OBJ_SELECTED_SM_H_
#define _EVENT_SM_INC_OBJ_SELECTED_SM_H_

#include "StageSM.h"


class ObjSelectedSM : public EventSM {
public:
	static EventSM* Instance();
	virtual ~ObjSelectedSM();
	virtual std::string getName();
	virtual void onMouseMove(LearningPlatformIf* lp, int relX, int relY,
	    std::shared_ptr<LPObject> obj);
	virtual void onLeftButtonUp(LearningPlatformIf* lp);
protected:
	ObjSelectedSM();
private:
	static EventSM* _instance;
};

#endif // _EVENT_SM_INC_OBJ_SELECTED_SM_H_
