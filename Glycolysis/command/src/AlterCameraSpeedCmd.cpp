/**
 * AlterCameraSpeedCmd.cpp
 */

#include "../inc/AlterCameraSpeedCmd.h"
//#include <glm/glm.hpp>

AlterCameraSpeedCmd::AlterCameraSpeedCmd(ViewIf& view) : view(view) {

}

AlterCameraSpeedCmd::~AlterCameraSpeedCmd() {

}

void AlterCameraSpeedCmd::execute() {
	if ((view.getSpeed()) < 0.02)
	{
		view.setSpeed(0.2);
	}
	else
	{
		view.setSpeed(0.01);
	}
}

