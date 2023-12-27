/**
 * StageSM.cpp
 */

#include "../inc/StageSM.h"

StageSM::StageSM(Stage* defaultStage, Stage* resourceList, Stage* stageSkyBox) :
    defaultStage(defaultStage), resourceList(resourceList), stageSkyBox(stageSkyBox), stage(defaultStage)
{

}

StageSM::~StageSM()
{
}

std::string StageSM::getName()
{
	return "Parent";
}

void StageSM::onF8KeyDown(LearningPlatformIf* lp)
{
}
void StageSM::onF8KeyUp(LearningPlatformIf* lp)
{
}

void StageSM::onF9KeyDown(LearningPlatformIf* lp)
{
}

void StageSM::onF9KeyUp(LearningPlatformIf* lp)
{
}

void StageSM::changeState(LearningPlatformIf* lp, StageSM* eSM)
{
	lp->changeState(eSM);
}
