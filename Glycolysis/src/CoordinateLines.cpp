/*
 * CoordinateLines.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: peter
 */

#include "../inc/CoordinateLines.h"
#include "../inc/objloader.hpp"
#include "../inc/vboindexer.hpp"
#include "../inc/texture.hpp"
#include "../inc/shader.hpp"
#include "../inc/ResObj.h"
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <GL/glew.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>
#include <vector>
#include "../uniform_location_var/inc/LPUniform.h"

CoordinateLines::CoordinateLines(int id,
		glm::vec3 scale,
		glm::vec3 trans,
		LPWatch* watch,
		ResObj& resObj,
		const View& view,
    GLuint programID,
    GLuint MatrixID,
    GLuint ViewMatrixID,
    GLuint ModelMatrixID,
    GLuint LightID,
    GLuint TextureID) :
    LPObject (id, trans, scale, watch),
		resObj(resObj),
		view(view),
programID(programID),
MatrixID(MatrixID),
ViewMatrixID(ViewMatrixID),
ModelMatrixID(ModelMatrixID),
LightID(LightID),
TextureID(TextureID)
{

//    Texture = texture;

    glActiveTexture(GL_TEXTURE1);

    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix = glm::scale(ModelMatrix,scale);
    ModelMatrix = glm::translate(ModelMatrix,trans);

    glm::mat4 MVP;

	b_motionState =
			new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(trans.x, trans.y, trans.z)));
	b_shape = new btBoxShape(btVector3(10,10,1));
	btScalar mass = 0;
	btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape);
	b_rigidBody = new btRigidBody(b_rigidBodyCI);

	setRotationMatrix(0);

}

CoordinateLines::~CoordinateLines() {
	// TODO Auto-generated destructor stub
}

void CoordinateLines::draw(ObjectType obj) {
  MVP = view.getProjectionMatrix() * view.getViewMatrix() * ModelMatrix;

  glm::mat4 ModelMatrix = glm::mat4(1.0);
  ModelMatrix = glm::translate(ModelMatrix,getTrans()) * getRotationMatrix();
  glm::mat4 MVP = view.getProjectionMatrix() * view.getViewMatrix() * ModelMatrix;

  // Send our transformation to the currently bound shader,
  // in the "MVP" uniform
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
  glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
  //  glm::mat4 tmpViewMatrix = view.getViewMatrix();
  glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &(view.getViewMatrix())[0][0]);
  glm::vec3 lightPos = glm::vec3(30.0f,40.0f,30.0f);

  glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
  GLint isAnimationID = glGetUniformLocation(programID, "isAnimation");
  glUniform1i(isAnimationID, 0);

  glBindTexture(GL_TEXTURE_2D, 0);

  std::vector<glm::vec3> tmp2;
  std::vector<glm::vec4> color;

  for (int i = -50; i < 50; i++ )
  {
    tmp2.push_back(glm::vec3(i * 1.0f, 0.0f, 0.0f));
    tmp2.push_back(glm::vec3(i * 1.0f, 50.0f, 0.0f));
  }

  for (int i = 50; i > 0; i-- )
  {
    tmp2.push_back(glm::vec3(-50.0f, i * 1.0f, 0.0f));
    tmp2.push_back(glm::vec3(50.0f, i * 1.0f, 0.0f));
  }

  for (int i = -50; i < 50; i++ )
  {
    tmp2.push_back(glm::vec3(0.0f, 0.0f, i * 1.0f));
    tmp2.push_back(glm::vec3(0.0f, 50.0f,i * 1.0f));
  }

  for (int i = 50; i > 0; i-- )
  {
    tmp2.push_back(glm::vec3(0.0f, i * 1.0f, -50.0f));
    tmp2.push_back(glm::vec3(0.0f, i * 1.0f, 50.0f));
  }

//  GLuint colorId;
//  glGenBuffers(1, &colorId);
//  glBindBuffer(GL_ARRAY_BUFFER, colorId);
//  glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(glm::vec4), &color, GL_STATIC_DRAW);
//  glPointSize( 30.0f );
//  glColor4f(0.9f, 0.25f, 0.15f, 1.0f);

  GLuint bufferId;
  glGenBuffers(1, &bufferId);
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
  glBufferData(GL_ARRAY_BUFFER, tmp2.size() * sizeof(glm::vec3), &tmp2[0], GL_STATIC_DRAW);
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

  glDrawArrays(GL_LINES, 0, tmp2.size());

  glDeleteBuffers(1, &bufferId);
}


void CoordinateLines::draw() {
  draw(cube);
}


float CoordinateLines::getHorizontalAngle() const {
  return horizontalAngle;
}

void CoordinateLines::setHorizontalAngle(float horizontalAngle) {
  this->horizontalAngle = horizontalAngle;
}

float CoordinateLines::getVerticalAngle() const {
  return verticalAngle;
}

void CoordinateLines::setVerticalAngle(float verticalAngle) {
  this->verticalAngle = verticalAngle;
}

bool CoordinateLines::isStatic() {
  return true;
}

void CoordinateLines::createId() {

}


void
CoordinateLines::move (bool flag) {


}

void
CoordinateLines::move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal) {

}
