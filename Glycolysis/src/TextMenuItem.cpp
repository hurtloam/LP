/*
 * TextMenuItem.cpp
 *
 *  Created on: Sep 6, 2015
 *      Author: peter
 */

#include "../inc/TextMenuItem.h"

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

TextMenuItem::TextMenuItem(
		int id,
		glm::vec3 scale,
		ObjectType obj1,
		ObjectType obj2,
		GLuint texture,
		glm::vec3 trans,
		LPWatch* watch,
		ResObj& resObj,
		const View& view,
		LPUniform lpUniform) : StaticObj(
				id,
				scale,
				obj1,
				texture,
				trans,
				watch,
				resObj,
				view,
        lpUniform)

{
	counter = 0;
  text_program_id = lpUniform.programID;

//	b_motionState =
//			new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(trans.x, trans.y, trans.z)));
//	b_shape = new btBoxShape(btVector3(1.0f, 0.2f, 0.05f));
//	btScalar mass = 0;
//	btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape);
//	b_rigidBody = new btRigidBody(b_rigidBodyCI);
//	b_rigidBody->setActivationState(DISABLE_DEACTIVATION);



	setColor(resObj.dark_gray);
	texture_local = texture;
	localObj1 = obj1;
	localObj2 = obj2;

	init();

  	setRotationMatrix_X(0);

}

void TextMenuItem::init()
{
	textObjectFirst = new TextObject(++lp_text,
			glm::vec3(1.0f, 1.0f, 1.0f),
			localObj1,
			texture_local,
			glm::vec3(0.0f, 0.0f, 0.0f),
			watch,
			resObj,
			view,
			lpUniform);

	textObjectFirst->setTrans(getTrans() + glm::vec3(0.02f, -0.15f, 0.01f));

	if (localObj2 != undefined_object)
	{
		textObjectSecond = new TextObject(++lp_text,
				glm::vec3(1.0f, 1.0f, 1.0f),
				localObj2,
				texture_local,
				glm::vec3(0.0f, 0.0f, 0.0f),
				watch,
				resObj,
				view,
				lpUniform);
		textObjectSecond->setTrans(getTrans()- glm::vec3(0.2f, 0.2f, 0.0f) + glm::vec3(0.0f, -0.15f, 0.01f));
	}


  b_motionState =
      new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(getTrans().x, getTrans().y -5.5, getTrans().z)));
  b_shape = new btBoxShape(btVector3(textObjectFirst->getTextWidth(), 0.2f, 0.05f));

  btScalar mass = 0;
  btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape);
  b_rigidBody = new btRigidBody(b_rigidBodyCI);
  b_rigidBody->setActivationState(DISABLE_DEACTIVATION);


}


TextMenuItem::~TextMenuItem()
{
	glDisable(GL_BLEND);
	delete textObjectFirst;
	if (localObj2 != undefined_object) {
	  delete textObjectSecond;
	}

}


void TextMenuItem::setTrans(glm::vec3 tr) {
	StaticObj::setTrans(tr);
	textObjectFirst->setTrans(tr);
	if (localObj2 != undefined_object)
	{
		textObjectSecond->setTrans(tr);
	}
}

void TextMenuItem::setMenuColor(GLfloat const _color[4])
{
	setColor(_color);
}

void TextMenuItem::setTextColor(GLfloat const _color[4])
{
	textObjectFirst->setColor(_color);
}

void TextMenuItem::internalDraw(bool isItemSelected)
{

	counter++;
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	ModelMatrix = glm::translate(ModelMatrix,getTrans()) * getRotationMatrix();
	glm::mat4 MVP = view.getProjectionMatrix() * view.getViewMatrix() * ModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
  glUniformMatrix4fv(lpUniform.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  glUniformMatrix4fv(lpUniform.ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
  glUniformMatrix4fv(lpUniform.ViewMatrixID, 1, GL_FALSE, &(view.getViewMatrix())[0][0]);

	if(text_program_id == 0)
		printf("programID faulty\n");

	attribute_coord = glGetAttribLocation(text_program_id, "coord");
	uniform_tex = glGetUniformLocation(text_program_id, "tex");
	uniform_color = glGetUniformLocation(text_program_id, "color");

	if(attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1)
	{
		fprintf(stderr, "WARNING: Some values not initialized: attribute_coord=%d, uniform_tex=%d, uniform_color=%d\n", attribute_coord, uniform_tex, uniform_color);
		std::cout << "TextMenuItem" << std::endl;
	}

	//		/* Enable blending, necessary for our alpha texture */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glUniform4fv(uniform_color, 1, color);
	glUniform1i(uniform_tex, 0);

//	list<GLuint>::const_iterator texture =  resObj->txtObjArray[getObjType() - 1000].text_tex.begin();
//	for(GLuint l : resObj->getText_vbo(getObjectType()))
//	{
		// texure test
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_local);
//		glUniform1i(uniform_tex, 0);
		// texure test

		/* Set up the VBO for our vertex data */
		glEnableVertexAttribArray(attribute_coord);

//		int x2 = 0;
//		int y2 = 1;
//		int w = 5.0f;
//		int h = 1.5f;

//		point box[4] = {
//				{-2.0f,  1.0f, 0.0f, 0.0f},
//				{ 2.0f,  1.0f, 1.0f, 0.0f},
//				{-2.0f, -1.0f, 0.0f, 1.0f},
//				{ 2.0f, -1.0f, 1.0f, 1.0f},
//		};
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		if (localObj2 != undefined_object)
		{
			point box[4] = {
					{-1.1f, .2f, 0.0f, 0.0f},
					{0.9f, .2f, 1.0f, 0.0f},
					{-1.1f, -.4f, 0.0f, 1.0f},
					{0.9f , -.4f, 1.0f, 1.0f},
			};
			glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		}
		else
		{
//			point box[4] = {
//					{-1.1f, .2f, 0.0f, 0.0f},
//					{0.9f, .2f, 1.0f, 0.0f},
//					{-1.1f, -.2f, 0.0f, 1.0f},
//					{0.9f , -.2f, 1.0f, 1.0f},
//			};

		  float txtWidth = textObjectFirst->getTextWidth();
		  if (!isItemSelected)
		  {
//		    txtWidth = 1.6f;
        txtWidth = getBoxSize();
		  }
      point box[4] = {
          {-txtWidth/2 , .1f, 0.0f, 0.0f},
          {txtWidth/2, .1f, 1.0f, 0.0f},
          {-txtWidth/2, -.1f, 0.0f, 1.0f},
          {txtWidth/2, -.1f, 1.0f, 1.0f},
//			point box[4] = {
//					{-1.0f, .1f, 0.0f, 0.0f},
//					{0.6f, .1f, 1.0f, 0.0f},
//					{-1.0f, -.1f, 0.0f, 1.0f},
//					{0.6f , -.1f, 1.0f, 1.0f},
			};
			glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		}


		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(
				attribute_coord,
				4,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0);
		/* Draw the character on the screen */
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

//	}
	glDisableVertexAttribArray(attribute_coord);
	glDisable(GL_BLEND);
	glDeleteBuffers(1, &vbo);

}
void TextMenuItem::draw()
{
  if (!isItemSelected)
  {
    internalDraw(isItemSelected);
  }
//  textObjectFirst->setTrans((textObjectFirst->getTrans().x * (1-1.6/textObjectFirst->getTextWidth());
	textObjectFirst->draw();
	if (localObj2 != undefined_object)
	{
		textObjectSecond->draw();
	}
}

void TextMenuItem::move(bool flag)
{
	//	 for the physics
	btTransform trans;
	btVector3 bvec;
	getRigidBody()->getMotionState()->getWorldTransform(trans);
	bvec = trans.getOrigin();

	// this made him move push stuff around
	trans.setOrigin(btVector3(getTrans().x, getTrans().y, getTrans().z));
	getRigidBody()->getMotionState()->setWorldTransform(trans);
	getRigidBody()->setCenterOfMassTransform (trans);

  textObjectFirst->move (flag);
		if (localObj2 != undefined_object)
		{
    textObjectSecond->move (flag);
		}
}
