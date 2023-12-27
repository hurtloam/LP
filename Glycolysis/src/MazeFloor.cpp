/*
 * MazeFloor.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: peter
 */

#include "../inc/MazeFloor.h"

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

#include "../inc/SoundBank.h"

#include <iostream>

MazeFloor::MazeFloor (int id,
                      ObjectType obj,
                      glm::vec3 shape,
                         glm::vec3 scale, GLuint texture,
                          glm::vec3 trans, LPWatch* watch, ResObj& resObj,
                          const View& view, LPUniform lpUniform) : StaticObj(
id, scale, obj, texture, trans, watch, resObj, view, lpUniform)
{
  // physics is added here:

//  b_motionState = new btDefaultMotionState (
//      btTransform (btQuaternion (0, 0, 0, 1),
//                   btVector3 (trans.x, trans.y, trans.z)));

  btTransform startTransform;
  startTransform.setIdentity ();
  startTransform.setOrigin (btVector3 (trans.x, trans.y, trans.z));
  startTransform.setRotation (btQuaternion (0, 0, 0, 1));
  btDefaultMotionState* b_motionState = new btDefaultMotionState (startTransform);



  b_shape = new btBoxShape (btVector3 (shape.x, shape.y, shape.z));

//    btVector3 centerRelation = btVector3 (0, -1, 0);
  //  btTransform center = btTransform (btQuaternion (0, 0, 0, 1), trans.getOrigin ());
//    getRigidBody ()->setCenterOfMassTransform ());




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


//  setRotationMatrix_X (0);
  setMoleculeInfo1 ("MazeFloor");
}

MazeFloor::~MazeFloor () {
  // TODO Auto-generated destructor stub
}

void
MazeFloor::draw () {
  setUseColor(0.0f);
  StaticObj::draw ();
}


void
MazeFloor::setOpenDoor () {
  std::cout << "ENTER MazeFloor::setOpenDoor" << std::endl;
  openDoor = true;
}
void
MazeFloor::move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal) {
//  std::cout << "ENTER MazeFloor::move" << std::endl;
  if (openDoor)
  {
    delay2 = 1;
    std::cout << "MazeFloor::move openDoor is true" << std::endl;
    if (++delay < 190)
    {
      std::cout << "MazeFloor::move delay = " << delay << std::endl;
      setTrans (glm::vec3 (0.02f, 0.f, 0.f));
    }
    else
    {
      std::cout << "MazeFloor::move else branch delay = " << delay << std::endl;
      openDoor = false;
//      delay == 0;
    }
  }
  else
  {
    if (delay2 == 1)
    {
      delay++;
    }
  }

  if (delay > 1000)
  {
    if (delay2 == 1)
    {
      BSoundBank::SoundControl.Play (SoundX);
      delay2 = 0;
    }
    if (++delay < 1180)
    {
      setTrans (glm::vec3 (-0.02f, 0.f, 0.f));
    }
    else
    {
      delay = 0;
    }
  }


  btTransform trans;
  btVector3 bvec;
  getRigidBody ()->getMotionState ()->getWorldTransform (trans);
  bvec = trans.getOrigin ();
  // this made him move push stuff around
  trans.setOrigin (btVector3 (getTrans ().x, getTrans ().y, getTrans ().z));
  getRigidBody ()->getMotionState ()->setWorldTransform (trans);
  getRigidBody ()->setCenterOfMassTransform (trans);


//  btVector3 centerRelation = btVector3 (0, -1, 0);

//  trans.setOrigin(btVector3(getTrans().x, getTrans().y, getTrans().z));
//          getRigidBody()->getMotionState()->setWorldTransform(trans);
//          getRigidBody()->setCenterOfMassTransform (trans);

//  getRigidBody ()->getMotionState ()->getWorldTransform (trans);
//  btTransform center = btTransform (btQuaternion (0, 0, 0, 1), trans.getOrigin ());
//  getRigidBody ()->setCenterOfMassTransform ());

//  glm::vec3 t;
//  t.x = trans.getOrigin ().getX ();
//  t.y = trans.getOrigin ().getY ();
//  t.z = trans.getOrigin ().getZ ();
//
//  if ((t.y - getTrans ().y) > 0.2f || (t.y - getTrans ().y) < -0.2f)
//    {
//      //		BSoundBank::SoundControl.Play(SoundO);
//    }
//  setTrans (t - getTrans ());

//  getRigidBody ()->getMotionState ()->getWorldTransform (trans);
//    bvec = trans.getOrigin();

//  trans.setOrigin (btVector3 (getTrans ().x, getTrans ().y + 2.0f, getTrans ().z));
//  getRigidBody ()->getMotionState ()->setWorldTransform (trans);
//  getRigidBody ()->setCenterOfMassTransform (trans);

  btTransform tr = getRigidBody ()->getWorldTransform ();
  btQuaternion quat = tr.getRotation ();
  btQuaternion quat1 (btVector3 (1, 0, 0), getOrientation ().x);
  btQuaternion quat2 (btVector3 (0, 1, 0), getOrientation ().y);
  btQuaternion quat3 (btVector3 (0, 0, 1), getOrientation ().z);
  tr.setRotation (quat * quat1 * quat2 * quat3);
  getRigidBody ()->setWorldTransform (tr);

}



