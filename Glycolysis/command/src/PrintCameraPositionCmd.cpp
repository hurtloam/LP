/**
 * PrintCameraPositionCmd.cpp
 */

#include "../inc/PrintCameraPositionCmd.h"
#include <glm/glm.hpp>
#include <stdio.h>

PrintCameraPositionCmd::PrintCameraPositionCmd(ViewIf& view) : view(view) {

}

PrintCameraPositionCmd::~PrintCameraPositionCmd() {

}

void PrintCameraPositionCmd::execute() {
	printf("ViewMatrix [%f,%f,%f] (view position)\n", view.getViewMatrix()[0].x,view.getViewMatrix()[0].y,view.getViewMatrix()[0].z);
	printf("ViewMatrix [%f,%f,%f] (view position)\n", view.getViewMatrix()[1].x,view.getViewMatrix()[1].y,view.getViewMatrix()[1].z);
	printf("ViewMatrix [%f,%f,%f] (view position)\n", view.getViewMatrix()[2].x,view.getViewMatrix()[2].y,view.getViewMatrix()[2].z);
	printf("ViewMatrix [%f,%f,%f,%f,%f] (view position)\n", view.getViewMatrix()[3].x,view.getViewMatrix()[3].y,view.getViewMatrix()[3].z, view.getViewMatrix()[3].w, view.getViewMatrix()[3].t);

}

