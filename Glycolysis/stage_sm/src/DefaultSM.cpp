/**
 * DefaultSM.cpp
 */

#include "../inc/DefaultSM.h"
#include "../../inc/LearningPlatformIf.h"

StageSM* DefaultSM::_instance = 0;

StageSM* DefaultSM::Instance(Stage* defaultStage, Stage* resourceList, Stage* stageSkyBox)
{
if (_instance == 0) {
    _instance = new DefaultSM(defaultStage, resourceList, stageSkyBox);
}
return _instance;
}

DefaultSM::DefaultSM(Stage* defaultStage, Stage* resourceList, Stage* stageSkyBox) :
    StageSM(defaultStage, resourceList, stageSkyBox)
{

}

DefaultSM::~DefaultSM()
{
	_instance = 0;
}

std::string DefaultSM::getName()
{
  return "DefaultSM";
}

void DefaultSM::onF8KeyDown(LearningPlatformIf* lp)
{
  // change state to ResourceList
}

void DefaultSM::onF8KeyUp(LearningPlatformIf* lp)
{
  // nothing happens?
}

void DefaultSM::OnKeyDown(LearningPlatformIf* lp, SDL_Keycode sym, Uint16 mod)
{
  //OnKeyDown(sym, mod);
  // move all parts of OnKeyDown from LearningPlatform into here

}

