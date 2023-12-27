/**
 * EventSM.cpp
 */

#include "../inc/EventSM.h"

EventSM::EventSM() {

}

EventSM::~EventSM() {

}

std::string EventSM::getName() {
	return "Parent";
}

void EventSM::onLeftButtonDown(LearningPlatformIf* lp) {}
void EventSM::onLeftButtonUp(LearningPlatformIf* lp) {}

void EventSM::onRightButtonDown(LearningPlatformIf* lp, ViewIf* view,
		LPObject* obj) {
}

void EventSM::onRightButtonUp(LearningPlatformIf*, LPObject* obj) {

}

void EventSM::onMouseMove(LearningPlatformIf* lp, int relX, int relY,
		LPObject* obj) {
}
void EventSM::changeState(LearningPlatformIf* lp, EventSM* eSM) {
	lp->changeState(eSM);
}
