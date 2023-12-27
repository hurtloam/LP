/**
 * ObjSelectedSM.cpp
 */

#include "../inc/ObjSelectedSM.h"
#include "../inc/InitSM.h"
#include <glm/glm.hpp>
#include "../../inc/LearningPlatformIf.h"


EventSM* ObjSelectedSM::_instance = 0;

EventSM* ObjSelectedSM::Instance() {
if (_instance == 0) {
	_instance = new ObjSelectedSM;
}
return _instance;
}

std::string ObjSelectedSM::getName() {
	return "ObjSelectedSM";
}

ObjSelectedSM::ObjSelectedSM() {

}

ObjSelectedSM::~ObjSelectedSM() {
	_instance = 0;
}

void ObjSelectedSM::onMouseMove(LearningPlatformIf* lp, int relX, int relY,
		LPObject* obj) {
	// do the stuff needed to make the object move
  std::cout << "Changing state ObjSelectedSM->ObjSelectedSM\n";
	obj->setTrans(glm::vec3(relX * 0.01, -relY * 0.01, 0.f));
}

void ObjSelectedSM::onLeftButtonUp(LearningPlatformIf* lp) {
  std::cout << "Changing state ObjSelectedSM->InitSM\n";
	changeState(lp, InitSM::Instance());
}
