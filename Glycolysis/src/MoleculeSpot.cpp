/*
 * MoleculeSpot.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: peter
 */

#include "../inc/MoleculeSpot.h"
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
#include "../inc/SoundBank.h"
#include <iostream>

MoleculeSpot::MoleculeSpot(int id,
                      ObjectType obj,
                      glm::vec3 shape,
                         glm::vec3 scale, GLuint texture,
                          glm::vec3 trans, LPWatch* watch, ResObj& resObj,
                          const View& view, LPUniform lpUniform) : StaticObj(
id, scale, obj, texture, trans, watch, resObj, view, lpUniform)
{
  btTransform startTransform;
  startTransform.setIdentity ();
  startTransform.setOrigin (btVector3 (trans.x, trans.y, trans.z));
  startTransform.setRotation (btQuaternion (0, 0, 0, 1));
  btDefaultMotionState* b_motionState = new btDefaultMotionState (startTransform);

  b_shape = new btBoxShape(btVector3(shape.x, shape.y, shape.z));

  btScalar mass = 0.0;
  btVector3 fallInertia (0, 0, 0);
  b_shape->calculateLocalInertia (mass, fallInertia);
  btRigidBody::btRigidBodyConstructionInfo b_ballRigidBodyCI (mass,
                                                              b_motionState,
                                                              b_shape,
                                                              fallInertia);
  b_rigidBody = new btRigidBody (b_ballRigidBodyCI);
  b_rigidBody->setRestitution (0.0);
  b_rigidBody->setFriction (90);
  b_rigidBody->setSleepingThresholds (0.0f, 0.0f);
  b_rigidBody->setAngularFactor (0.0f);
  b_rigidBody->getCollisionShape ()->setMargin (0.01f);

  setMoleculeInfo1("MoleculeSpot");
}

MoleculeSpot::~MoleculeSpot()
{
  // TODO Auto-generated destructor stub
}

void
MoleculeSpot::draw()
{
  StaticObj::draw ();
}

void
MoleculeSpot::setOpenDoor()
{
}
void
MoleculeSpot::move(std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal)
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
