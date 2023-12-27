/*
 * LineObj.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: peter
 */


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
#include "../inc/LineObj.h"
#include "../inc/objloader.hpp"
#include "../inc/vboindexer.hpp"
#include "../inc/texture.hpp"
#include "../inc/shader.hpp"
#include "../inc/ResObj.h"

LineObj::LineObj(
    int id,
    glm::vec3 scale,
    GLuint texture,
    glm::vec3 trans,
    LPWatch* watch,
    const View* view,
    GLuint programID, GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID, GLuint LightID, GLuint TextureID) :
    LPObject (id, trans, scale, watch),
    view(view),
    programID(programID), MatrixID(MatrixID), ViewMatrixID(ViewMatrixID), ModelMatrixID(ModelMatrixID), LightID(LightID), TextureID(TextureID)
{
//	Texture = texture;
  glActiveTexture (GL_TEXTURE1);
  ModelMatrix = glm::mat4 (1.0f);
  ModelMatrix = glm::scale (ModelMatrix, scale);
  ModelMatrix = glm::translate (ModelMatrix, trans);
  glm::mat4 MVP;

  setRotationMatrix (0);
}

void LineObj::draw() {
  MVP = view->getProjectionMatrix () * view->getViewMatrix () * ModelMatrix;

  glm::mat4 ModelMatrix = glm::mat4 (1.0);
  ModelMatrix = glm::translate (ModelMatrix, getTrans ()) * getRotationMatrix ();
  glm::mat4 MVP = view->getProjectionMatrix () * view->getViewMatrix () * ModelMatrix;

  // Send our transformation to the currently bound shader,
  // in the "MVP" uniform
  glUniformMatrix4fv (MatrixID, 1, GL_FALSE, &MVP[0][0]);
  glUniformMatrix4fv (ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
  //  glm::mat4 tmpViewMatrix = view.getViewMatrix();
  glUniformMatrix4fv (ViewMatrixID, 1, GL_FALSE, &(view->getViewMatrix ())[0][0]);
	glm::vec3 lightPos = glm::vec3(30.0f,40.0f,30.0f);

	glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

	glm::vec3 tmpgreen = glm::vec3(.9f, 0.8f, 0.9f);

  GLint isAnimationID = glGetUniformLocation(programID, "isAnimation");
  glUniform1i(isAnimationID, 0);

	GLint uniform_color = -1;
	GLint useColorId = -1;
	uniform_color = glGetUniformLocation(programID, "objColor");
	useColorId = glGetUniformLocation(programID, "useColor");

	if (uniform_color == -1) {
	    std::cout << "uniform_color is not set!" << std::endl;
	}
	if (useColorId == -1) {
	    std::cout << "useColor is not set!" << std::endl;
	}
//	std::cout << "uniform_color = " << uniform_color << ", useColorId = " << useColorId << std::endl;
	glUniform1f(useColorId, 1.0f);
  glUniform3f (uniform_color, color.x, color.y, color.z);

	GLuint bufferId;
	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
  glBufferData (GL_ARRAY_BUFFER, lineCoord.size () * sizeof(glm::vec3), &lineCoord[0], GL_STATIC_DRAW);
	// 1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
	    0,                  // attribute
	    3,                  // size
	    GL_FLOAT,           // type
	    GL_FALSE,           // normalized?
	    0,                  // stride
	    (void*)0            // array buffer offset
	);

  glDrawArrays (GL_LINES, 0, lineCoord.size ());
  glDeleteBuffers (1, &bufferId);
}

LineObj::~LineObj() {

}

float LineObj::getHorizontalAngle() const {
	return horizontalAngle;
}

void LineObj::setHorizontalAngle(float horizontalAngle) {
	this->horizontalAngle = horizontalAngle;
}

float LineObj::getVerticalAngle() const {
	return verticalAngle;
}

void LineObj::setVerticalAngle(float verticalAngle) {
	this->verticalAngle = verticalAngle;
}

bool LineObj::isStatic() {
	return true;
}

void LineObj::createId() {

}

void
LineObj::move (bool flag) {

}

void
LineObj::move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal) {
}

