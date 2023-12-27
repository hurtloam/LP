/**
 * InitSM.cpp
 */

#include "../inc/InitSM.h"
#include "../inc/ObjSelectedSM.h"
#include "../inc/ObjZoomedSM.h"
#include "../../inc/LearningPlatformIf.h"

EventSM* InitSM::_instance = 0;

EventSM* InitSM::Instance() {
if (_instance == 0) {
	_instance = new InitSM;
}
return _instance;
}

InitSM::InitSM() {

}

InitSM::~InitSM() {
	_instance = 0;
}

std::string InitSM::getName() {
	return "InitSM";
}

void InitSM::onLeftButtonDown(LearningPlatformIf* lp) {
	// ObjSelected
  std::cout << "Changing state InitSM->ObjSelected\n";
	changeState(lp, ObjSelectedSM::Instance());
}

void InitSM::onRightButtonDown(LearningPlatformIf* lp, ViewIf* view,
		LPObject* obj)
{
// ObjZoomed
  std::cout << "Changing state InitSM->ObjZoomed\n";
	obj->setSavedTrans(obj->getTrans());
	obj->setTrans(
			view->getPosition() + glm::vec3(0.0f, 0.0f, -1.8f)
					- obj->getTrans());
	changeState(lp, ObjZoomedSM::Instance());
}
