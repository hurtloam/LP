/*
 * IceCube.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: peter
 */

#include "../inc/IceCube.h"

IceCube::IceCube (int id,
		glm::vec3 scale,
		ObjectType objType,
		int objArray_length,
		GLuint texture,
		glm::vec3 trans,
		LPWatch* watch,
		ResObj& resObj,
		const View& view,
		GLuint programID,
		GLuint MatrixID,
		GLuint ViewMatrixID,
		GLuint ModelMatrixID,
		GLuint LightID,
		GLuint TextureID):
		Actor(id, scale, objType, objArray_length, texture,
		   trans, watch, resObj, view, programID, MatrixID, ViewMatrixID, ModelMatrixID, LightID, TextureID)
{
}

IceCube::~IceCube() {
	// TODO Auto-generated destructor stub
}

void IceCube::draw() {
	Actor::draw();
}

void
IceCube::move (bool flag) {
	setRotationMatrix_Z(0.08);
  Actor::move (flag);
}
