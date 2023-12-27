/*
 * LineObj.h
 *
 *  Created on: Apr 5, 2015
 *      Author: peter
 */

#ifndef LINEOBJ_H_
#define LINEOBJ_H_

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/euler_angles.hpp>
#include "LPObject.h"
#include "View.h"
#include "ResObj.h"

#include "../uniform_location_var/inc/LPUniform.h"

class LineObj: public LPObject {
public:
	LineObj(
	    int id,
			glm::vec3 scale,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			const View* view,
			GLuint programID, GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID, GLuint LightID, GLuint TextureID);

	virtual ~LineObj();

//	void draw(ObjectType obj);
	void draw();
	float getHorizontalAngle() const;
	void setHorizontalAngle(float horizontalAngle = 3.14f);
	float getVerticalAngle() const;
	void setVerticalAngle(float verticalAngle = 0.0f);

	bool isStatic();

	GLuint getNormalbuffer() const;

	void setNormalbuffer(GLuint normalbuffer);

	bool isDrawnOnce() {return drawnOnce;}

	void createId();

  GLuint getTexture()
  {
    return Texture;
  }
  ;

	glm::vec3 getOrientation() {return gOrientation;}
	void setOrientation(float o) {
		gOrientation.y = gOrientation.y + o;
	}

//	void setRotationMatrix(float r) {
//		setOrientation(r);
//		RotationMatrix =
//		    glm::eulerAngleYXZ(
//		        gOrientation.y+r,
//		        gOrientation.x,
//		        gOrientation.z);
//	}

	glm::mat4 getRotationMatrix() {return RotationMatrix;}

  void
  move (bool flag);

  void
  move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);

  glm::vec4 getColor() const {
    return color;
  }

  int getObjType() { return objType;}

  void setColor(glm::vec4 color) {
    this->color = color;
  }

  void
  setRotationMatrix (float r) {
    setOrientation (r);
    RotationMatrix = glm::eulerAngleYXZ (gOrientation.y + r, gOrientation.x, gOrientation.z);
  }

  const std::vector<glm::vec3>& getLineCoord() const {
    return lineCoord;
  }

  void setLineCoord(const std::vector<glm::vec3>& lineCoord) {
    this->lineCoord = lineCoord;
    glm::vec3 center = glm::vec3 (abs (lineCoord[0].x - lineCoord[0].x), abs (lineCoord[0].y - lineCoord[0].y), abs (lineCoord[0].z - lineCoord[0].z));
//    setTrans (center);
  }

  void
  sawIt (glm::vec3 position, int id) {
  }


private:

  const View* view;
	GLuint programID;
	GLuint MatrixID; GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint LightID;
	GLuint TextureID;

	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;

	// As an example, rotate arount the vertical axis at 180 degrees/sec
	glm::vec3 gOrientation = glm::vec3(0.0f, 0.0f, 0.0f);

	// Build the model matrix
	glm::mat4 RotationMatrix;

	bool walking = true;
	GLuint Texture;
	glm::mat4 MVP;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ModelMatrix;

	bool drawnOnce = false;
	int objType = line;
  std::vector<glm::vec3> lineCoord;
  glm::vec4 color;
};


#endif /* LINEOBJ_H_ */
