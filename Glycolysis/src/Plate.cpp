/*
 * Plate.cpp
 *
 *  Created on: Dec 31, 2014
 *      Author: peter
 */

#include "../inc/Plate.h"
#include <BulletCollision/CollisionShapes/btBoxShape.h>
//#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <GL/glew.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>


glm::vec3 magenta = glm::vec3(0.5,0.5,0.8);
glm::vec3 dark_magenta = glm::vec3(0.5,0.5,0.2);
glm::vec3 light_gray = glm::vec3(0.5,0.5,0.5);
glm::vec3 lime_green = glm::vec3(0.5,0.8,0.5);
glm::vec3 pig_pink = glm::vec3(0.8,0.5,0.5);
glm::vec3 dark_gray = glm::vec3(0.3,0.3,0.3);


Plate::Plate(int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, LPUniform lpUniform) : StaticObj(
id, scale, objType, texture, trans, watch, resObj, view, lpUniform)
{

  b_motionState = new btDefaultMotionState (btTransform (btQuaternion (0, 0, 0, 1), btVector3 (trans.x, trans.y, trans.z)));
  b_shape = new btBoxShape (btVector3 (4.0f, 2.0f, 0.4f));

  btScalar mass = 0;
  btVector3 fallInertia (0, 0, 0);
  b_shape->calculateLocalInertia (mass, fallInertia);

  btRigidBody::btRigidBodyConstructionInfo b_ballRigidBodyCI (mass, b_motionState, b_shape, fallInertia);

  b_rigidBody = new btRigidBody (b_ballRigidBodyCI);
  b_rigidBody->setRestitution (0.0);
  b_rigidBody->setFriction (90);
  b_rigidBody->setSleepingThresholds (0.0f, 0.0f);
  b_rigidBody->setAngularFactor (0.0f);
  b_rigidBody->getCollisionShape ()->setMargin (0.01);
}

Plate::~Plate() {
	// TODO Auto-generated destructor stub
}

void Plate::draw() {
  colorID = glGetUniformLocation(lpUniform.programID, "objColor");
  useColorID = glGetUniformLocation(lpUniform.programID, "useColor");
  if (useColorID == 999)
  {
    fprintf(stderr, "Error: useColorID was never retrieved");
  }

  if (colorID == 999)
  {
    fprintf(stderr, "Error: colorID was never retrieved");
  }
  glUniform1f(useColorID, 1.0);
  setObjColor(dark_magenta);
  glUniform3f(colorID, getObjColor().x, getObjColor().y, getObjColor().z);

  StaticObj::draw();

//  glUniform1f(useColorID, 0.0);
}

void
Plate::move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal)
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

  btTransform tr = getRigidBody ()->getWorldTransform ();
  btQuaternion quat = tr.getRotation ();
  btQuaternion quat1 (btVector3 (1, 0, 0), getOrientation ().x);
  btQuaternion quat2 (btVector3 (0, 1, 0), getOrientation ().y);
  btQuaternion quat3 (btVector3 (0, 0, 1), getOrientation ().z);
  tr.setRotation (quat * quat1 * quat2 * quat3);
  getRigidBody ()->setWorldTransform (tr);

}
