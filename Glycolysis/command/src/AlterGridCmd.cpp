/**
 * AlterCameraSpeedCmd.cpp
 */

#include "../inc/AlterGridCmd.h"
#include <glm/glm.hpp>

AlterGridCmd::AlterGridCmd(StageIf& stage) : stage(stage) {

}

AlterGridCmd::~AlterGridCmd() {

}

void AlterGridCmd::execute() {
	stage.createCoordinateLines(glm::vec3(0.0f,0.0f,0.0f), 20000);
}

