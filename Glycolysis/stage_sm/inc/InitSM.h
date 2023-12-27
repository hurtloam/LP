/*
 * InitSM.h
 *
 *  Created on: 22 dec. 2018
 *      Author: peter
 */

#ifndef _EVENT_SM_INC_INIT_SM_H_
#define _EVENT_SM_INC_INIT_SM_H_

#include "StageSM.h"

class InitSM : public EventSM {
public:
	static EventSM* Instance();
	virtual ~InitSM();
	virtual std::string getName();
	virtual void onLeftButtonDown(LearningPlatformIf* lp);
	virtual void onRightButtonDown(LearningPlatformIf* lp, ViewIf* view,
			LPObject* obj);

//	class NoKeySSM: public EventSSM {
//	public:
//		static EventSSM* Instance();
//		virtual ~NoKeySSM();
//		virtual std::string getName();
//		virtual void onCtrlButtonDown(LearningPlatformIf* lp);
//		virtual void onShiftButtonDown(LearningPlatformIf* lp);
//	protected:
//		NoKeySSM();
//	private:
//		static EventSSM* _instance;
//	};
//
//	class CtrlKeySSM: public EventSSM {
//	public:
//		static EventSSM* Instance();
//		virtual ~CtrlKeySSM();
//		virtual std::string getName();
//		virtual void onCtrlButtonUp(LearningPlatformIf* lp);
//	protected:
//		CtrlKeySSM();
//	private:
//		static EventSSM* _instance;
//	};
//
//	class ShiftKeySSM: public EventSSM {
//	public:
//		static EventSSM* Instance();
//		virtual ~ShiftKeySSM();
//		virtual std::string getName();
//		virtual void onShiftButtonUp(LearningPlatformIf* lp);
//	protected:
//		ShiftKeySSM();
//	private:
//		static EventSSM* _instance;
//	};


protected:
	InitSM();
private:
	static EventSM* _instance;
};

#endif // _EVENT_SM_INC_INIT_SM_H_
