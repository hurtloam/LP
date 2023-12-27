/*
 * Ball.cpp
 *
 *  Created on: Oct 30, 2014
 *      Author: peter
 */

#include "../inc/Ball.h"

#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <glm/detail/type_vec3.hpp>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>

#include <iostream>

Ball::Ball(int id,
		glm::vec3 scale,
		ObjectType objType,
		GLuint texture,
		glm::vec3 trans,
		LPWatch* watch,
		ResObj& resObj,
		const View& view,
		LPUniform lpUniform) :
    StaticObj(id,
									scale,
									objType,
									texture,
									trans,
									watch,
									resObj,
									view,
									lpUniform)
{
	b_motionState =
			new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(trans.x, trans.y, trans.z)));
  b_shape = new btSphereShape (1.0f);

  btScalar mass = 0;
	btVector3 fallInertia(0, 0, 0);
	b_shape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo b_ballRigidBodyCI(mass, b_motionState, b_shape, fallInertia);
	b_rigidBody = new btRigidBody(b_ballRigidBodyCI);
	b_rigidBody->setRestitution(0.3);
	b_rigidBody->setFriction(50);

	if (texture == 0) {
	  setUseColor(1.0);
	}
	else {
	  setUseColor(0.0);
	}
}

Ball::~Ball() {
	// TODO Auto-generated destructor stub
}

void Ball::draw() {
  glUniform1f(useColorID, 1.0);


   setObjColor(glm::vec3(1.0, 0.0, 0.0));
   if (colorStatus == ColorStates::S_BLUE) {
     // blue arrow
     setObjColor(glm::vec3(0.0,0.0,1.0));
   }
   else {
     setObjColor(glm::vec3(1.0,0.0,0.0));

     // do nothing
   }
	StaticObj::draw();
}

void Ball::move(bool flag) {

  btTransform trans;
  btVector3 bvec;
  getRigidBody ()->getMotionState ()->getWorldTransform (trans);
  bvec = trans.getOrigin ();
  // this made him move push stuff around
  trans.setOrigin (btVector3 (getTrans ().x, getTrans ().y, getTrans ().z));
  getRigidBody ()->getMotionState ()->setWorldTransform (trans);
  getRigidBody ()->setCenterOfMassTransform (trans);

  btTransform tr = getRigidBody ()->getWorldTransform ();
  btQuaternion quat = tr.getRotation ();
  btQuaternion quat1 (btVector3 (1, 0, 0), getOrientation ().x);
  btQuaternion quat2 (btVector3 (0, 1, 0), getOrientation ().y);
  btQuaternion quat3 (btVector3 (0, 0, 1), getOrientation ().z);
  tr.setRotation (quat * quat1 * quat2 * quat3);
  getRigidBody ()->setWorldTransform (tr);
}

void Ball::move(std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal)
{
  btTransform trans;
  btVector3 bvec;
  getRigidBody()->getMotionState()->getWorldTransform(trans);
  bvec = trans.getOrigin();
  // this made him move push stuff around
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


btRigidBody* Ball::getRigidBody()
{
  return b_rigidBody;
}
