/*
 * Creature.cpp
 *
 *  Created on: Aug 10, 2014
 *      Author: peter
 */

#include "../inc/Creature.h"
using  namespace std;

Creature::Creature(int id,glm::vec3 scale, ObjectType objType, int objArray_length, GLuint texture,
		glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, GLuint programID,
                    GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID, GLuint LightID, GLuint TextureID) :
				Actor(id, scale, objType, objArray_length, texture,
				   trans, watch, resObj, view, programID, MatrixID, ViewMatrixID, ModelMatrixID, LightID, TextureID)
{
  setRotationMatrix_X (0);
}
Creature::~Creature() {
	// TODO Auto-generated destructor stub
}



void Creature::draw() {
	Actor::draw();
	if (!isWalking()) {
		setCurrentObj(creature0);
	}

}
