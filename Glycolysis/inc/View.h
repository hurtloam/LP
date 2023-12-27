/*
 * View.h
 *
 *  Created on: Jan 1, 2014
 *      Author: peter
 */

#ifndef VIEW_H_
#define VIEW_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
#include "ViewIf.h"

enum keys {
	left,
	right,
	forward,
	backward,
	up,
	down,
	still
};


class View : public ViewIf {
public:
  View() = default;
	View(int w, int h);
	void computeMatricesFromInputs(SDL_Window *window, int xpos, int ypos, int relX, int relY, bool Left,bool Right,bool Middle);

	glm::mat4 getViewMatrix() const {
		return ViewMatrix;
	}

	void setViewMatrix(const glm::mat4& viewMatrix) {
		ViewMatrix = viewMatrix;
	}


	void setDefault();

	void ScreenPosToWorldRay(
		int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
		int screenWidth, int screenHeight,  // Window size, in pixels
		glm::mat4 ViewMatrix,               // Camera position and orientation
		glm::mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
		glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
		glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
	) const ;

	bool getKeyStates(int v) const { return keyStates[v];}
	void setFoV(float fov);
	float getFoV() const;
	float getInitialFoV() const;
	void setInitialFoV(float initialFoV = 45.0f);
	void setPosition(const glm::vec3& position);
	void setRelativePosition(const glm::vec3& pos);
	glm::vec3 getPosition() const {return position;}
	float getSpeed() const;
	void setSpeed(float speed);
	float getHorizontalAngle() const;
	void setHorizontalAngle(float horizontalAngle = 3.14f);
	float getVerticalAngle() const;
	void setVerticalAngle(float verticalAngle = 0.0f);

	void move(int key);
	void move(glm::vec3 trans);
	void updateKeyStates(int key);
	glm::mat4 getProjectionMatrix() const {
		return ProjectionMatrix;
	}


	void printPos();



	glm::mat4 getProjectionMatrix2() const {
			return ProjectionMatrix2;
		}

	void setProjectionMatrix(const glm::mat4& projectionMatrix) {
		ProjectionMatrix = projectionMatrix;
	}

	void setAspectRatio(float aspectRatio) {
		setProjectionMatrix(glm::perspective(FoV, aspectRatio, 0.1f, 400.0f));
	}
	void setProjectionMatrix2(const glm::mat4& projectionMatrix) {
			ProjectionMatrix2 = projectionMatrix;
		}

	virtual ~View();

	int getMovement() const {return movement;}


	bool isRotationAllowed() const;
	void setRotationAllowed(bool ra);

	void setScreen(int w, int h)
	{
		screenWidth = w;
		screenHeight = h;
	}

	int getScreenHeight() const
	{
		return screenHeight;
	}

	int getScreenWidth() const
	{
		return screenWidth;
	}

	void warpMouseInWindow(SDL_Window* window, const int x, const int y) const
	{
		SDL_WarpMouseInWindow(window,x, y);
	}

	float getInitialVerticalAngle () const
	{
	  return initialVerticalAngle;
	}

	float getIntitialHorizontalAngle () const
	{
	  return intitialHorizontalAngle;
	}

  glm::vec3
  getObjPlacementInFrontOfCamera ();

  const glm::vec3&
  getDirection () const {
    return direction;
  }

  void
  setDirection (const glm::vec3& direction) {
    this->direction = direction;
  }

  const glm::vec3&
  getRight () const {
    return right;
  }

  void
  setRight (const glm::vec3& right) {
    this->right = right;
  }

	private:
	bool rotationAllowed = true;
	// Initial position : on +Z
	glm::vec3 position;
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.141592f;
	float intitialHorizontalAngle = 3.141592f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	float initialVerticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 45.0f;
//	float initialFoV = 45.0f;

	float FoV = initialFoV;
//	float speed = 0.2f; // 0.2 units / second
	float speed = 0.2f; // 0.2 units / second
//	float speed = 3.0f; // 3 units / second
//	float speed = 3.0f; // 3 units / second
//	float mouseSpeed = 0.002f;
	float mouseSpeed = 0.001f;

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ProjectionMatrix2;

//	glm::vec3 trans = glm::vec3(0,0,0);

	int screenWidth;
	int screenHeight;

	bool keyStates[6];

  int movement = 6;

  glm::vec3 right;
  glm::vec3 direction;

};

#endif /* VIEW_H_ */
