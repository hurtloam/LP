/**
 * ObjZoomedSM.cpp
 */

#include "../inc/ObjZoomedSM.h"
#include "../inc/InitSM.h"
#include <glm/glm.hpp>
#include "../../inc/LearningPlatformIf.h"


EventSM* ObjZoomedSM::_instance = 0;

EventSM* ObjZoomedSM::Instance() {
if (_instance == 0) {
		_instance = new ObjZoomedSM;
}
return _instance;
}

std::string ObjZoomedSM::getName() {
	return "ObjZoomedSM";
}

ObjZoomedSM::ObjZoomedSM() {

}

ObjZoomedSM::~ObjZoomedSM() {
	_instance = 0;
}

void ObjZoomedSM::onMouseMove(LearningPlatformIf* lp, int relX, int relY,
		LPObject* obj) {
	// do the stuff needed to make the object rotate
  std::cout << "Changing state ObjZoomedSM->ObjZoomedSM\n";

	obj->setRotationMatrix_X(relY * 0.01);
	obj->setRotationMatrix_Y(relX * 0.01);
}

void ObjZoomedSM::onRightButtonUp(LearningPlatformIf* lp, LPObject* obj) {
  std::cout << "Changing state ObjZoomedSM->InitSM\n";

	obj->setTrans(obj->getSavedTrans() - obj->getTrans());
	changeState(lp, InitSM::Instance());
}
