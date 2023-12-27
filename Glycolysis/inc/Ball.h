/*
 * Ball.h
 *
 *  Created on: Oct 30, 2014
 *      Author: peter
 */

#ifndef BALL_H_
#define BALL_H_

#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btDefaultMotionState.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "ResObj.h"
#include "StaticObj.h"

class Ball: public StaticObj {
public:
  Ball(int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, LPUniform lpUniform);
	virtual ~Ball();
	void draw();
	void move(bool flag);
  void move(std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);
  btRigidBody* getRigidBody();

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

  void setColorStatus(ColorStates s) { colorStatus = s; }
private:

  ColorStates colorStatus = ColorStates::S_DEFAULT;

};

#endif /* BALL_H_ */
