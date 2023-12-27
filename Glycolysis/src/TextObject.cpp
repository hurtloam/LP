/*
 * TextObject.cpp
 *
 *  Created on: Sep 6, 2015
 *      Author: peter
 */

#include "../inc/TextObject.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>

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

#include "../inc/StaticObj.h"
#include "../inc/ResObj.h"
#include <GL/glew.h>
#include <string.h>
#include <iostream>
#include "../inc/shader.hpp"
#include <ft2build.h>
#include <freetype/freetype.h>

#include FT_FREETYPE_H

using namespace std;

TextObject::TextObject(
		int id,

		glm::vec3 scale,
		ObjectType obj,
		GLuint texture,
		glm::vec3 trans,
		LPWatch* watch,
		ResObj& resObj,
		const View& view,
		LPUniform lpUniform) : StaticObj(
				id,
				scale,
				obj,
				texture,
				trans,
				watch,
				resObj,
				view,
        lpUniform)
{

  counter = 0;
  text_width = resObj.txtObjArray[getObjType() - 1000].width;

  btTransform startTransform;
  startTransform.setIdentity();
  startTransform.setOrigin(btVector3(trans.x, trans.y, trans.z));
  startTransform.setRotation(btQuaternion(0, 0, 0, 1));
  b_motionState = new btDefaultMotionState(startTransform);
  b_shape = new btBoxShape(btVector3(text_width*0.6, 0.13, 0.1));

  btScalar mass = 0;
  btVector3 fallInertia(0, 0, 0);
  b_shape->calculateLocalInertia(mass, fallInertia);
  btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape, fallInertia);
  b_rigidBody = new btRigidBody(b_rigidBodyCI);

  b_rigidBody->setRestitution(0.0);
  b_rigidBody->setFriction(90);
  b_rigidBody->setSleepingThresholds(0.0f, 0.0f);
  b_rigidBody->setAngularFactor(0.0f);
  b_rigidBody->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
  b_rigidBody->getCollisionShape()->setMargin(0.01f);
  GLfloat blackish[4] = { 0, 0, 0, 1 };
  setColor(resObj.black);


  	setRotationMatrix_X(0);
}

TextObject::~TextObject()
{
	glDisable(GL_BLEND);
}

void TextObject::draw()
{
  glUseProgram(lpUniform.programID);
	counter++;
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	ModelMatrix = glm::translate(ModelMatrix,getTrans()) * getRotationMatrix();
	glm::mat4 MVP = view.getProjectionMatrix() * view.getViewMatrix() * ModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
  glUniformMatrix4fv(lpUniform.MatrixID, 1, GL_FALSE, &MVP[0][0]);   // MVP see shader
  glUniformMatrix4fv(lpUniform.ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]); // M see shader
  glUniformMatrix4fv(lpUniform.ViewMatrixID, 1, GL_FALSE, &(view.getViewMatrix())[0][0]); // V see shader

  if (lpUniform.programID == 0)
		printf("programID faulty\n");

  attribute_coord = glGetAttribLocation(lpUniform.programID, "coord");
  uniform_tex = glGetUniformLocation(lpUniform.programID, "tex");
  uniform_color = glGetUniformLocation(lpUniform.programID, "color");

	if(attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1)
	{
		fprintf(stderr, "WARNING: Some values not initialized: attribute_coord=%d, uniform_tex=%d, uniform_color=%d\n", attribute_coord, uniform_tex, uniform_color);
		std::cout << "TextObject" << std::endl;
	}

	//		/* Enable blending, necessary for our alpha texture */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUniform4fv(uniform_color, 1, color);
	glUniform1i(uniform_tex, 0);

	list<GLuint>::const_iterator texture =  resObj.txtObjArray[getObjType() - 1000].text_tex.begin();
	for(GLuint l : resObj.getText_vbo(getObjectType()))
	{
		// texure test
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glUniform1i(uniform_tex, 0);
		// texure test

		/* Set up the VBO for our vertex data */
		glEnableVertexAttribArray(attribute_coord);
		glBindBuffer(GL_ARRAY_BUFFER, l);
		glVertexAttribPointer(
		    attribute_coord,
		    4,
		    GL_FLOAT,
		    GL_FALSE,
		    0,
		    0
		 );

		texture++;
		/* Draw the character on the screen */
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		//				glDeleteTextures(1, &tex[i]);
		//				i++;
	}
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(attribute_coord);
}

void TextObject::draw(ObjectType obj) {
  setObjectType(obj);
  counter++;
  glm::mat4 ModelMatrix = glm::mat4(1.0);
  ModelMatrix = glm::translate(ModelMatrix, getTrans()) * getRotationMatrix();
  glm::mat4 MVP = view.getProjectionMatrix() * view.getViewMatrix() * ModelMatrix;

  // Send our transformation to the currently bound shader,
  // in the "MVP" uniform
  glUniformMatrix4fv(lpUniform.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  glUniformMatrix4fv(lpUniform.ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
  glUniformMatrix4fv(lpUniform.ViewMatrixID, 1, GL_FALSE, &(view.getViewMatrix())[0][0]);

  if (lpUniform.programID == 0)
    printf("programID faulty\n");

  attribute_coord = glGetAttribLocation(lpUniform.programID, "coord");
  uniform_tex = glGetUniformLocation(lpUniform.programID, "tex");
  uniform_color = glGetUniformLocation(lpUniform.programID, "color");

  GLint useColorID = glGetUniformLocation(lpUniform.programID, "useColor");
  glUniform1f(useColorID, 0.0); // don't use color, use texture and color  instead

  if (attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1) {
    fprintf(stderr, "WARNING: Some values not initialized: attribute_coord=%d, uniform_tex=%d, uniform_color=%d\n", attribute_coord, uniform_tex, uniform_color);
    std::cout << "TextObject" << std::endl;
  }

  //		/* Enable blending, necessary for our alpha texture */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glUniform4fv(uniform_color, 1, color);
  glUniform1i(uniform_tex, 0);
  list<GLuint>::const_iterator texture = resObj.txtObjArray[getObjType() - 1000].text_tex.begin();
  for (GLuint l : resObj.getText_vbo(getObjectType())) {
    // texure test
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glUniform1i(uniform_tex, 0);
    // texture test

    /* Set up the VBO for our vertex data */
    glEnableVertexAttribArray(attribute_coord);
    glBindBuffer(GL_ARRAY_BUFFER, l);
    glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
    texture++;
    /* Draw the character on the screen */
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  }
  glDisable(GL_BLEND);
  glDisableVertexAttribArray(attribute_coord);
}

void TextObject::move(std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal)
{
  btTransform trans;
  btVector3 bvec;
  getRigidBody()->getMotionState()->getWorldTransform(trans);
  bvec = trans.getOrigin();

  trans.setOrigin(btVector3(getTrans().x, getTrans().y, getTrans().z));
  getRigidBody()->getMotionState()->setWorldTransform(trans);
  getRigidBody()->setCenterOfMassTransform(trans);

  btTransform tr = getRigidBody()->getWorldTransform();
  btQuaternion quat = tr.getRotation();
  btQuaternion quat1(btVector3(1, 0, 0), getOrientation().x);
  btQuaternion quat2(btVector3(0, 1, 0), getOrientation().y);
  btQuaternion quat3(btVector3(0, 0, 1), getOrientation().z);
  tr.setRotation(quat * quat1 * quat2 * quat3);
  getRigidBody()->setWorldTransform(tr);

  correctPosition = false;
  collisionObj = 0;

  int objB;
  for (auto obj : collisionDetected) {
    if (obj.first == this->getId()) {
      objB = obj.second;
      TRACE_DEBUG("obj.first=%d, objB=%d, getId=%d", obj.first, objB, getId());
      TRACE_DEBUG("objB=%d, getId=%d", objB, getId());
      if ((objB - 61000) == getObjType()) {
        correctPosition = true;
        collisionObj = objB;
      }
      else if ((objB - 61000 - 100) == getObjType()) {
        correctPosition = true;
        collisionObj = objB;
      }
      else if ((objB - 61000 - 200) == getObjType()) {
        correctPosition = true;
        collisionObj = objB;
      }
      else if ((objB - 61000 - 300) == getObjType()) {
        correctPosition = true;
        collisionObj = objB;
      }
      else if ((objB - 61000 - 400) == getObjType()) {
        correctPosition = true;
        collisionObj = objB;
      }
      else if ((objB - 61000 - 500) == getObjType()) {
        correctPosition = true;
        collisionObj = objB;
      }
    }
    else if (obj.second == getId()) {
      objB = obj.first;
      TRACE_DEBUG("obj.first=%d, obj.second=%d, objB=%d, getId=%d, getObjType=%d", obj.first, obj.second, objB, getId(), getObjType());
      if ((objB - 62000) == (getObjType() - 1000)) {
        correctPosition = true;
        collisionObj = objB;
        TRACE_DEBUG("collisionObj=%d", collisionObj);
      }
      else if ((objB - 62000 - 100) == (getObjType() - 1000)) {
        correctPosition = true;
        collisionObj = objB;
        TRACE_DEBUG("collisionObj=%d", collisionObj);
      }
      else if ((objB - 62000 - 200) == (getObjType() - 1000)) {
        correctPosition = true;
        collisionObj = objB;
        TRACE_DEBUG("collisionObj=%d", collisionObj);
      }
      else if ((objB - 62000 - 300) == (getObjType() - 1000)) {
        correctPosition = true;
        collisionObj = objB;
        TRACE_DEBUG("collisionObj=%d", collisionObj);
      }
      else if ((objB - 62000 - 400) == (getObjType() - 1000)) {
        correctPosition = true;
        collisionObj = objB;
        TRACE_DEBUG("collisionObj=%d", collisionObj);
      }
      else if ((objB - 62000 - 500) == (getObjType() - 1000)) {
        correctPosition = true;
        collisionObj = objB;
        TRACE_DEBUG("collisionObj=%d", collisionObj);
      }
    }
  }
}

void TextObject::move(bool flag)
{
  btTransform trans;
  btVector3 bvec;
  getRigidBody()->getMotionState()->getWorldTransform(trans);
  bvec = trans.getOrigin();

  trans.setOrigin(btVector3(getTrans().x, getTrans().y, getTrans().z));
  getRigidBody()->getMotionState()->setWorldTransform(trans);
  getRigidBody()->setCenterOfMassTransform(trans);

  btTransform tr = getRigidBody()->getWorldTransform();
  btQuaternion quat = tr.getRotation();
  btQuaternion quat1(btVector3(1, 0, 0), getOrientation().x);
  btQuaternion quat2(btVector3(0, 1, 0), getOrientation().y);
  btQuaternion quat3(btVector3(0, 0, 1), getOrientation().z);
  tr.setRotation(quat * quat1 * quat2 * quat3);
  getRigidBody()->setWorldTransform(tr);
}
