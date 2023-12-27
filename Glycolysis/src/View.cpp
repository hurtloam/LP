/*
 * View.cpp
 *
 *  Created on: Jan 1, 2014
 *      Author: peter
 */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <SDL2/SDL.h>
#include "../inc/View.h"
#include <iostream>

using namespace std;

View::View(int w, int h): screenWidth(w), screenHeight(h) {

	keyStates[0] = false;
	keyStates[1] = false;
	keyStates[2] = false;
	keyStates[3] = false;
	keyStates[4] = false;
	keyStates[5] = false;

	movement = keys::still;

  setProjectionMatrix (glm::perspective (FoV, (screenWidth * 1.0f) / (screenHeight * 1.0f), 0.1f, 100.0f));
	glm::vec3 direction(
				cos(getVerticalAngle()) * sin(getHorizontalAngle()),
				sin(getVerticalAngle()),
				cos(getVerticalAngle()) * cos(getHorizontalAngle())
		);
		// Right vector
		glm::vec3 right = glm::vec3(
				sin(getHorizontalAngle() - 3.14159265f/2.0f),
				0,
				cos(getHorizontalAngle() - 3.14159265f/2.0f)
		);

//	position = glm::vec3( -11.0f, 12.0f, 53.0f);
// EPEBROR: latest 	position = glm::vec3( 0.0f, 3.0f, 5.0f);
//		position = glm::vec3( 0.18f, 18.5f, 5.0f);
//		position = glm::vec3(0.0f, 18.5f, 15.0f);
		position = glm::vec3(0.0f, 14.5f, 15.0f);

//		0.180000, 18.500000, 5.000000
//		position = glm::vec3(3.5f, 17.05f, 12.0f); 1280x720

	setViewMatrix(glm::lookAt(getPosition(),           // Camera is here
			getPosition()+direction, // and looks here : at the same position, plus "direction"
			glm::cross( right, direction )                  // Head is up (set to 0,-1,0 to look upside-down)
	));
}


void View::setDefault() {

  setVerticalAngle(getInitialVerticalAngle());
  setHorizontalAngle(getIntitialHorizontalAngle());
  setProjectionMatrix(glm::perspective(getInitialFoV(), (screenWidth * 1.0f) / (screenHeight * 1.0f), 0.1f, 400.0f));
    glm::vec3 direction(
          cos(getInitialVerticalAngle()) * sin(getIntitialHorizontalAngle()),
          sin(getInitialVerticalAngle()),
          cos(getInitialVerticalAngle()) * cos(getIntitialHorizontalAngle())
      );
      // Right vector
      glm::vec3 right = glm::vec3(
          sin(getIntitialHorizontalAngle() - 3.14159265f/2.0f),
          0,
          cos(getIntitialHorizontalAngle() - 3.14159265f/2.0f)
      );

      position = glm::vec3(0.0f, 18.5f, 15.0f);

    setViewMatrix(glm::lookAt(getPosition(),           // Camera is here
        getPosition()+direction, // and looks here : at the same position, plus "direction"
        glm::cross( right, direction )                  // Head is up (set to 0,-1,0 to look upside-down)
    ));
}

bool View::isRotationAllowed() const
{
	return rotationAllowed;
}

void View::setRotationAllowed(bool ra)
{
	rotationAllowed = ra;
}

void View::move(int key)
{
  direction = glm::vec3 (
			cos(getVerticalAngle()) * sin(getHorizontalAngle()),
			sin(getVerticalAngle()),
			cos(getVerticalAngle()) * cos(getHorizontalAngle())
	);
  right = glm::vec3 (
					sin(getHorizontalAngle() - 3.14159265f/2.0f),
					0,
					cos(getHorizontalAngle() - 3.14159265f/2.0f)
			);

	switch (key) {
	case 0: //left
		setPosition(getPosition() - right * getSpeed());
		break;
	case 1: //right
		setPosition(getPosition() + right * getSpeed());
		break;
	case 2: //forward
		setPosition(getPosition() + direction * getSpeed());
		break;
	case 3: //backward
		setPosition(getPosition() - direction * getSpeed());
		break;
	case 4: //up
		setPosition(getPosition() + glm::vec3(0, getSpeed(),0));
		break;
	case 5: //down
		setPosition(getPosition() - glm::vec3(0, getSpeed(),0));
		break;
	case 6: // still, do nothing
		break;
	default:
		break;
	}

	setViewMatrix(glm::lookAt(getPosition(),           // Camera is here
							 getPosition()+direction, // and looks here : at the same position, plus "direction"
							 glm::cross( right, direction )                  // Head is up (set to 0,-1,0 to look upside-down)
						   ));
}

glm::vec3
View::getObjPlacementInFrontOfCamera () {
  glm::vec3 direction = glm::vec3 (cos (getVerticalAngle ()) * sin (getHorizontalAngle ()), sin (getVerticalAngle ()), cos (getVerticalAngle ()) * cos (getHorizontalAngle ()));

  return (getPosition () + direction * 10.0f);
}

void View::move(glm::vec3 trans)
{
  glm::vec3 direction (cos (0) * sin (getHorizontalAngle ()), sin (0), cos (0) * cos (getHorizontalAngle ()));

  glm::vec3 right = glm::vec3 (sin (getHorizontalAngle () - 3.14159265f / 2.0f), 0, cos (getHorizontalAngle () - 3.14159265f / 2.0f));


	setPosition (trans);


	direction = glm::vec3 (
			cos(getVerticalAngle()) * sin(getHorizontalAngle()),
			sin(getVerticalAngle()),
			cos(getVerticalAngle()) * cos(getHorizontalAngle())
	);

	// Right vector
  right = glm::vec3 (
			sin(getHorizontalAngle() - 3.14159265f/2.0f),
			0,
			cos(getHorizontalAngle() - 3.14159265f/2.0f)
	);

//  setPosition (trans);

	setViewMatrix(glm::lookAt(getPosition(),           // Camera is here
			getPosition()+direction, // and looks here : at the same position, plus "direction"
			glm::cross( right, direction )                  // Head is up (set to 0,-1,0 to look upside-down)
	));
}


void View::updateKeyStates(int key) {
	movement = key;
}

void View::computeMatricesFromInputs(SDL_Window *window, int xpos, int ypos, int relX, int relY, bool Left,bool Right,bool Middle){
	// Reset mouse position for next frame
//	int x = 1920/2;
//	int y = 1080/2;
	int x = screenWidth/2;
	int y = screenHeight/2;
//
	if (rotationAllowed) {
	SDL_WarpMouseInWindow(window,x, y); //  1024/2=512, 768/2=384
//	horizontalAngle += mouseSpeed * float(x - xpos );
//	verticalAngle   += mouseSpeed * float( y - ypos );

		horizontalAngle += mouseSpeed * float(x - xpos );
		verticalAngle   += mouseSpeed * float( y - ypos );



//	// Compute new orientation
	float cosVertAngle = cos(verticalAngle);
	float sinVertAngle = sin(verticalAngle);
	float cosHorizAngle = cos(horizontalAngle);
	float sinHorizAngle = sin(horizontalAngle);

	glm::vec3 direction(
			cosVertAngle * sinHorizAngle,
			sinVertAngle,
			cosVertAngle * cosHorizAngle
			);


	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - M_PI/2.0f),
		0,
		cos(horizontalAngle - M_PI/2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross( right, direction );


	// Projection matrix : 45 degrees Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
//	setProjectionMatrix(glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f));
	// Camera matrix

//	setViewMatrix(glm::lookAt(position,           // Camera is here
//							 position+direction, // and looks here : at the same position, plus "direction"
//							 up                  // Head is up (set to 0,-1,0 to look upside-down)
//						   ));
//
	}

}


void View::ScreenPosToWorldRay(
	int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
	int screenWidth, int screenHeight,  // Window size, in pixels
	glm::mat4 ViewMatrix,               // Camera position and orientation
	glm::mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
	glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
	glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
) const {

	// The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
	glm::vec4 lRayStart_NDC(
		((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
		((float)mouseY/(float)screenHeight - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
		-1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
		1.0f
	);
	glm::vec4 lRayEnd_NDC(
		((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f,
		((float)mouseY/(float)screenHeight - 0.5f) * 2.0f,
		0.0,
		1.0f
	);


	// The Projection matrix goes from Camera Space to NDC.
	// So inverse(ProjectionMatrix) goes from NDC to Camera Space.
	glm::mat4 InverseProjectionMatrix = glm::inverse(ProjectionMatrix);

	// The View Matrix goes from World Space to Camera Space.
	// So inverse(ViewMatrix) goes from Camera Space to World Space.
	glm::mat4 InverseViewMatrix = glm::inverse(ViewMatrix);

	glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;    lRayStart_camera/=lRayStart_camera.w;
	glm::vec4 lRayStart_world  = InverseViewMatrix       * lRayStart_camera; lRayStart_world /=lRayStart_world .w;
	glm::vec4 lRayEnd_camera   = InverseProjectionMatrix * lRayEnd_NDC;      lRayEnd_camera  /=lRayEnd_camera  .w;
	glm::vec4 lRayEnd_world    = InverseViewMatrix       * lRayEnd_camera;   lRayEnd_world   /=lRayEnd_world   .w;


	// Faster way (just one inverse)
	//glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
	//glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
	//glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;


	glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
	lRayDir_world = glm::normalize(lRayDir_world);


	out_origin = glm::vec3(lRayStart_world);
	out_direction = glm::normalize(lRayDir_world);
}

void View::printPos() {
   printf("Camera position: (%f, %f, %f)\n", getPosition().x, getPosition().y, getPosition().z);
}



float View::getFoV() const {
	return FoV;
}

void View::setFoV(float fov) {
	this->FoV = fov;
}

float View::getInitialFoV() const {
	return initialFoV;
}

void View::setInitialFoV(float initialFoV) {
	this->initialFoV = initialFoV;
}

void View::setPosition(const glm::vec3& position) {
	this->position = position;
}

void View::setRelativePosition(const glm::vec3& pos) {
  position = position + pos;
}

float View::getSpeed() const {
	return speed;
}

void View::setSpeed(float speed) {
	this->speed = speed;
}

float View::getHorizontalAngle() const {
	return horizontalAngle;
}

void View::setHorizontalAngle(float horizontalAngle) {
	this->horizontalAngle = horizontalAngle;
}

float View::getVerticalAngle() const {
	return verticalAngle;
}

void View::setVerticalAngle(float verticalAngle) {
	this->verticalAngle = verticalAngle;
}

View::~View() {
  std::cout << "ENTER ~View()" << std::endl;

	// TODO Auto-generated destructor stub
}

