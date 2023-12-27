/**
 * ObjZoomedSM.cpp
 */

#include "../inc/InitSM.h"
#include <glm/glm.hpp>
#include "../../inc/LearningPlatformIf.h"
#include "../inc/ResourceListSM.h"
#include <memory>


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
    std::shared_ptr<LPObject> obj)
{
	// do the stuff needed to make the object rotate
  std::cout << "Changing state ObjZoomedSM->ObjZoomedSM\n";

	obj->setRotationMatrix_X(relY * 0.01);
	obj->setRotationMatrix_Y(relX * 0.01);
}

void ObjZoomedSM::onRightButtonUp(LearningPlatformIf* lp, std::shared_ptr<LPObject> obj)
{
  std::cout << "Changing state ObjZoomedSM->InitSM\n";

	obj->setTrans(obj->getSavedTrans() - obj->getTrans());
	changeState(lp, InitSM::Instance());
}
