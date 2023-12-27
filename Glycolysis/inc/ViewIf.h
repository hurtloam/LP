/*
 * View.h
 *
 *  Created on: Jan 1, 2014
 *      Author: peter
 */

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>

class ViewIf {
public:
  ViewIf() = default;
  virtual ~ViewIf() = default;


	virtual void computeMatricesFromInputs(SDL_Window *window, int xpos, int ypos, int relX, int relY, bool Left,bool Right,bool Middle) = 0;
	virtual glm::mat4 getViewMatrix() const = 0;
	virtual void setViewMatrix(const glm::mat4& viewMatrix) = 0;
	virtual void setDefault() = 0;

	virtual void ScreenPosToWorldRay(
		int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
		int screenWidth, int screenHeight,  // Window size, in pixels
		glm::mat4 ViewMatrix,               // Camera position and orientation
		glm::mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
		glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
		glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
	) const = 0;

	virtual bool getKeyStates(const int v) const = 0;
	virtual void setFoV(float fov) = 0;
	virtual float getFoV() const = 0;
	virtual float getInitialFoV() const = 0;
	virtual void setInitialFoV(float initialFoV = 45.0f) = 0;
	virtual void setPosition(const glm::vec3& position) = 0;
	virtual glm::vec3 getPosition() const = 0;

	virtual float getSpeed() const = 0;
	virtual void setSpeed(float speed) = 0;

	virtual float getHorizontalAngle() const = 0;
	virtual void setHorizontalAngle(float horizontalAngle = 3.14f) = 0;
	virtual float getVerticalAngle() const = 0;
	virtual void setVerticalAngle(float verticalAngle = 0.0f) = 0;

	virtual void move(int key) = 0;
	virtual void move(glm::vec3 trans) = 0;
	virtual void updateKeyStates(int key) = 0;
	virtual glm::mat4 getProjectionMatrix() const = 0;
	virtual void printPos() = 0;

	virtual void setProjectionMatrix(const glm::mat4& projectionMatrix) = 0;
	virtual void setAspectRatio(float aspectRatio) = 0;
	virtual void setProjectionMatrix2(const glm::mat4& projectionMatrix) = 0;
	virtual int getMovement() const = 0;
	virtual bool isRotationAllowed() const = 0;
	virtual void setRotationAllowed(bool ra) = 0;
	virtual void setScreen(int w, int h) = 0;
	virtual int getScreenHeight() const = 0;
	virtual int getScreenWidth() const = 0;
	virtual void warpMouseInWindow(SDL_Window* window, const int x, const int y) const = 0;
  virtual float getInitialVerticalAngle () const = 0;
  virtual float getIntitialHorizontalAngle () const = 0;
  virtual glm::vec3
  getObjPlacementInFrontOfCamera () = 0;

  virtual const glm::vec3&
  getDirection () const = 0;

  virtual const glm::vec3&
  getRight () const = 0;

};

