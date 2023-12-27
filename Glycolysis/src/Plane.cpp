/*
 * WallCube.cpp
 *
 *  Created on: Dec 31, 2014
 *      Author: peter
 */

#include "../inc/Plane.h"
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

glm::vec3 const blue = glm::vec3(0.0, 0.0, 1.0);
glm::vec3 const light_blue = glm::vec3(0.5, 0.5, 1.0);


Plane::Plane(int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view,
		LPUniform lpUniform) : StaticObj(id, scale, objType, texture, trans, watch, resObj, view, lpUniform)
{

//		b_motionState =
//				new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(trans.x, trans.y, trans.z)));
//
//
//		b_shape = new btBoxShape (btVector3 (6, 0.01, 11.0f));

  btScalar mass = 0;
//		btVector3 fallInertia(0, 0, 0);
//
//		b_shape->calculateLocalInertia(mass, fallInertia);

//		btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape);
//
//		b_rigidBody = new btRigidBody(b_rigidBodyCI);
//
//		b_rigidBody->setSleepingThresholds (0.0f, 0.0f);
//			b_rigidBody->setAngularFactor (0.0f);

//		setRotationMatrix_X(3.14159265);
  setRotationMatrix_Z (3.14159265 / 2);


}

Plane::~Plane() {
	// TODO Auto-generated destructor stub
}

void Plane::draw() {
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
  // change below if you want it to be a certain color
//  glUniform1f(useColorID, 1.0);
//  setObjColor(light_blue);
//  glUniform3f(colorID, getObjColor().x, getObjColor().y, getObjColor().z);

  StaticObj::draw();

  glUniform1f(useColorID, 0.0);
}

void Plane::move(bool flag) {

//		btTransform trans;
//
//		getRigidBody()->getMotionState()->getWorldTransform(trans);
//		glm::vec3 t;
//		t.x = trans.getOrigin().getX();
//		t.y = trans.getOrigin().getY();
//		t.z = trans.getOrigin().getZ();
//
//		setTrans(t - getTrans());

	//	 for the physics
	btTransform trans;
	btVector3 bvec;
//	getRigidBody()->getMotionState()->getWorldTransform(trans);
//	bvec = trans.getOrigin();
//
//	// this made him move push stuff around
//	trans.setOrigin(btVector3(getTrans().x, getTrans().y, getTrans().z));
//	getRigidBody()->getMotionState()->setWorldTransform(trans);
//	getRigidBody()->setCenterOfMassTransform (trans);
}
