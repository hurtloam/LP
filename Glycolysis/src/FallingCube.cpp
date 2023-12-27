/*
 * FallingCube.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: peter
 */

#include "../inc/FallingCube.h"

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

FallingCube::FallingCube(int id,
                         glm::vec3 scale, GLuint texture,
                          glm::vec3 trans, LPWatch* watch, ResObj& resObj,
                          const View& view, LPUniform lpUniform) :
    StaticObj (id, scale, cube, texture, trans, watch, resObj, view, lpUniform)
{
  // physics is added here:
  b_motionState = new btDefaultMotionState (
      btTransform (btQuaternion (0, 0, 0, 1),
                   btVector3 (trans.x, trans.y, trans.z)));

  b_shape = new btBoxShape (btVector3 (1.0f, 1.0f, 1.0f));

  btScalar mass = 10.0;
  btVector3 fallInertia (0, 0, 0);

  b_shape->calculateLocalInertia (mass, fallInertia);
  btRigidBody::btRigidBodyConstructionInfo b_ballRigidBodyCI (mass,
                                                              b_motionState,
                                                              b_shape,
                                                              fallInertia);
  b_rigidBody = new btRigidBody (b_ballRigidBodyCI);
  b_rigidBody->setRestitution (0.3);
  b_rigidBody->setFriction (20);
  setRotationMatrix_X (0);
}

FallingCube::~FallingCube() {
  // TODO Auto-generated destructor stub
}

void FallingCube::draw() {
  StaticObj::draw ();
}



void FallingCube::move(bool flag) {

  btTransform trans;

  getRigidBody ()->getMotionState ()->getWorldTransform (trans);
  glm::vec3 t;
  t.x = trans.getOrigin ().getX ();
  t.y = trans.getOrigin ().getY ();
  t.z = trans.getOrigin ().getZ ();

  if ((t.y - getTrans ().y) > 0.2f || (t.y - getTrans ().y) < -0.2f)
    {
      //		BSoundBank::SoundControl.Play(SoundO);
    }
  setTrans (t - getTrans ());
}


