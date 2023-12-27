/*
 * WallCube.cpp
 *
 *  Created on: Dec 31, 2014
 *      Author: peter
 */

#include "../inc/WallCube.h"
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

WallCube::WallCube(int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, 
		LPUniform lpUniform) : StaticObj( id, scale, objType, texture, trans, watch, resObj, view, lpUniform)
{
  /* TEMPORARILY COMMENTING OUT THIS
  // physics is added here:
  b_motionState = new btDefaultMotionState (
      btTransform (btQuaternion (0, 0, 0, 1),
                   btVector3 (trans.x, trans.y, trans.z)));
  b_shape = new btBoxShape (btVector3 (1.0f, 1.0f, 1.0f));
  btScalar mass = 0.0;
//  btVector3 fallInertia (0, 0, 0);
//  b_shape->calculateLocalInertia (mass, fallInertia);
  btRigidBody::btRigidBodyConstructionInfo b_ballRigidBodyCI (mass,
                                                              b_motionState,
                                                              b_shape);
  b_rigidBody = new btRigidBody (b_ballRigidBodyCI);
  b_rigidBody->setRestitution (0.3);
  b_rigidBody->setFriction (20);


   */

  // COPIED FROM MAZEFLOOR: physics is added here:
//  b_motionState = new btDefaultMotionState (
//      btTransform (btQuaternion (0, 0, 0, 1),
//                   btVector3 (trans.x, trans.y, trans.z)));
  btTransform startTransform;
  startTransform.setIdentity();
  startTransform.setOrigin(btVector3(trans.x, trans.y, trans.z));
  startTransform.setRotation(btQuaternion(0, 0, 0, 1));
  btDefaultMotionState* b_motionState = new btDefaultMotionState(startTransform);

  b_shape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));

//    btVector3 centerRelation = btVector3 (0, -1, 0);
  //  btTransform center = btTransform (btQuaternion (0, 0, 0, 1), trans.getOrigin ());
//    getRigidBody ()->setCenterOfMassTransform ());

  btScalar mass = 0.0;
  btVector3 fallInertia(0, 0, 0);
  b_shape->calculateLocalInertia(mass, fallInertia);
  btRigidBody::btRigidBodyConstructionInfo b_ballRigidBodyCI(mass, b_motionState, b_shape, fallInertia);
  b_rigidBody = new btRigidBody(b_ballRigidBodyCI);
  b_rigidBody->setRestitution(0.0);
  b_rigidBody->setFriction(90);
  b_rigidBody->setSleepingThresholds(0.0f, 0.0f);
  b_rigidBody->setAngularFactor(0.0f);
  b_rigidBody->getCollisionShape()->setMargin(0.01f);

  setMoleculeInfo1("Bob");
}

WallCube::~WallCube() {
  // TODO Auto-generated destructor stub
}

void WallCube::draw() {
  //  if (isIsHidden() == false) {
  //	setUseColor(0.0);
  //	std::cout << "draw WallCube!" << std::endl;
  StaticObj::draw(zombie);
  //  }
}

void WallCube::move(bool flag) {

  //  static int timeDelay = 0;
  //  setRotationMatrix_Y(0.05);
  //  timeDelay = 1;
  //  timeDelay++;

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

  // Temporarily comment out:
  /*
  btTransform trans;
  btVector3 bvec;
  getRigidBody ()->getMotionState ()->getWorldTransform (trans);
  bvec = trans.getOrigin ();
  // this made him move push stuff around
  trans.setOrigin (btVector3 (getTrans ().x, getTrans ().y, getTrans ().z));
  getRigidBody ()->getMotionState ()->setWorldTransform (trans);
  getRigidBody ()->setCenterOfMassTransform (trans);
   */

  btTransform trans;
  btVector3 bvec;
  getRigidBody ()->getMotionState ()->getWorldTransform (trans);
  bvec = trans.getOrigin ();
  // this made him move push stuff around
  trans.setOrigin (btVector3 (getTrans ().x, getTrans ().y, getTrans ().z));
  getRigidBody ()->getMotionState ()->setWorldTransform (trans);
  getRigidBody ()->setCenterOfMassTransform (trans);

}
