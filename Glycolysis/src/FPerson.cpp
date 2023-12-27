/*
 * FPerson.cpp
 *
 *  Created on: Jul 9, 2014
 *      Author: peter
 */

#include "../inc/FPerson.h"

#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
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

//FPerson::FPerson (int id, glm::vec3 scale, GLuint texture, glm::vec3 trans, LPWatch* watch, const ResObj& resObj, const View& view, GLuint programID, GLuint MatrixID, GLuint ViewMatrixID,
//                  GLuint ModelMatrixID,
//                  GLuint LightID, GLuint TextureID) :
FPerson::FPerson(int id, glm::vec3 scale, ObjectType objType, int objArray_length, GLuint texture,
    glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, GLuint programID,
    GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID, GLuint LightID, GLuint TextureID) :
    Actor (id, scale, objType, objArray_length, texture, trans, watch, resObj, view, programID, MatrixID, ViewMatrixID, ModelMatrixID, LightID, TextureID) {
  oldFlag = false;
  logOutputPtr = new int (1);
  setLogging (logOutputPtr, SDL_LOG_PRIORITY_DEBUG);
//    StaticObj (id, scale, cube, texture, trans, watch, resObj, view, programID, MatrixID, ViewMatrixID, ModelMatrixID, LightID, TextureID) {

  // physics is added here: (OLD)
//  b_motionState = new btDefaultMotionState (btTransform (btQuaternion (0, 0, 0, 1), btVector3 (trans.x, trans.y, trans.z)));
//
//  b_shape = new btBoxShape (btVector3 (0.5f, 3.0f, 0.5f));
//
//  btScalar mass = 100.0;
//  btVector3 fallInertia (0, 0, 0);
//
//  b_shape->calculateLocalInertia (mass, fallInertia);
//  btRigidBody::btRigidBodyConstructionInfo b_ballRigidBodyCI (mass, b_motionState, b_shape, fallInertia);
//  b_rigidBody = new btRigidBody (b_ballRigidBodyCI);
//  b_rigidBody->setRestitution (0.3);
//  b_rigidBody->setFriction (20);
//
//  b_rigidBody->setSleepingThresholds (0.0f, 0.0f);
//  b_rigidBody->setAngularFactor (0.0f);

// NEW copied from sniper:
  btTransform startTransform;
  startTransform.setIdentity ();
  startTransform.setOrigin (btVector3 (trans.x, trans.y, trans.z));
  startTransform.setRotation (btQuaternion (0, 0, 0, 1));
  btDefaultMotionState* b_motionState = new btDefaultMotionState (startTransform);

  b_shape = new btBoxShape (btVector3 (0.5f, 1.0f, 0.5f));


  btScalar mass = 0.0f;
  btVector3 fallInertia (0, 0, 0);
  b_shape->calculateLocalInertia (mass, fallInertia);

//  b_rigidBody->setFriction (90);
  btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI (mass, b_motionState, b_shape);
//  btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI (mass, b_motionState, b_shape);
  b_rigidBody = new btRigidBody (b_rigidBodyCI);
  b_rigidBody->setSleepingThresholds (0.0f, 0.0f);
//  b_rigidBody->setActivationState (DISABLE_DEACTIVATION);
  b_rigidBody->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);
  b_rigidBody->setAngularFactor (0.0f);
  b_rigidBody->getCollisionShape ()->setMargin (0.01f);

  direction = glm::vec3 (0.0f, 0.0f, 1.01f);
  key = 6;
//  setRotationMatrix_X (0);
  setMoleculeInfo1 ("FPerson");

  timer = 0;
  timerThreshold = 60;
}

FPerson::~FPerson () {
  // TODO Auto-generated destructor stub
  delete logOutputPtr;
}

void
FPerson::draw () {
//  StaticObj::draw ();
}

void
FPerson::move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal) {
  bool flag = false;
  int objB;
  int countKeys = 0;
  timer++;

  if (timer % timerThreshold == 0)
  {
    setHp (getHp () - 1);
  }

  bool HPFlagSet = false;
  for (auto obj : collisionDetected)
  {
    if (obj.first == getId ())
    {
      flag = true;
      objB = obj.second;
//      std::cout << "Collision1 detected with id=" << objB->getId () << std::endl;
      if ((objB > 8000) && (objB < 9000))
      {
        setHp (getHp () - 1);
//        std::cout << "Collision1 setting HP = " << getHp () << std::endl;
        if (getHp () < 1)
        {
          setDead (true);
          return;
        }
      }

      if ((objB > 16000) && (objB < 17000))
      {
        if (!HPFlagSet) {
          setHp(getHp() + 20);
          HPFlagSet = true;
        }
        std::cout << "Collision with Glucose setting HP = " << getHp() << std::endl;
        if (getHp () < 1)
        {
          setDead (true);
          return;
        }
      }

      if ((objB > 59000) && (objB < 60000))
      {
        setHp (getHp () + 20);
        std::cout << "Collision with winningBlock setting HP = " << getHp() << std::endl;
        if (getHp () > 1)
        {
          setWinning (true);
          return;
        }
      }

    }
    else if (obj.second == getId ())
    {

      flag = true;
      objB = obj.first;
//      std::cout << "Collision2 detected with id=" << objB->getId () << std::endl;
      if ((objB > 8000) && (objB < 9000))
      {
        setHp (getHp () - 1);
//        std::cout << "Collision2 setting HP = " << getHp () << std::endl;
        if (getHp () < 1)
        {
          setDead (true);
          return;
        }
      }
//      return;
    }
  }

  if (getHp () < 1)
  {
    setDead (true);
    return;
  }

  if (flag == true && oldFlag == false)
  {
    useThisNormal = normal;
    oldFlag = true;
  }
  else if (flag == true && oldFlag == true)
  {
    // don't change the normal
  }
  else
  {
    oldFlag = false;
  }

  if (!flag)
  {
//    collisionDirection = key;
//    int countKeys = 0;
    key = 6;
    secondKey = 6;
    countKeys = 0;
    for (int i = 0; i < 6; i++)
    {
      if (wasd[i] == true)
      {
        countKeys += 1;
        if (countKeys == 1)
        {
          key = i;
        }
        else
        {
          secondKey = i;
        }
      }
    }

    switch (key)
    {
      case 0: //left
        if (sndCnt % 30 == 0)
        {
          SDL_Log ("Play left - key = %d", key);
          SDL_Log ("Play left - wasd = (%d,%d,%d,%d,%d,%d,%d,)", wasd[0], wasd[1], wasd[2], wasd[3], wasd[4], wasd[5], wasd[6]);
          BSoundBank::SoundControl.Play (StepTap);
        }
        if (sndCnt == 10000)
        {
          sndCnt = 0;
        }
        sndCnt++;
        if (countKeys == 2)
        {
          if (secondKey == 2)
          {
            setTrans (direction * 0.07f);
            setTrans (-1.0f * right * 0.07f);
          }
        }
          else
          {
        setTrans (-1.0f * right * 0.1f);
          }
        break;
      case 1: //right
        if (sndCnt % 25 == 0)
        {
          SDL_Log ("Play right");
          BSoundBank::SoundControl.Play (StepTap);
        }
        if (sndCnt == 10000)
        {
          sndCnt = 0;
        }
        sndCnt++;
        if (countKeys == 2)
        {
          if (secondKey == 2)
          {
            setTrans (direction * 0.07f);
            setTrans (1.0f * right * 0.07f);
          }
        }
        else
        {
          setTrans (1.0f * right * 0.1f);
        }
        break;
      case 2: //forward
        if (sndCnt % 35 == 0)
        {
          SDL_Log ("Play forward");
          BSoundBank::SoundControl.Play (StepTap);
        }
        if (sndCnt == 10000)
        {
          sndCnt = 0;
        }
        sndCnt++;

//        if (countKeys == 2)
//        {
//          if (secondKey == 2)
//          {
//            setTrans (direction * 0.05f);
//            setTrans (1.0f * right * 0.05f);
//          }
//          else
//          {
//            setTrans (1.0f * right * 0.1f);
//          }
//        }
        setTrans (direction * 0.1f);
        break;
      case 3: //backward
        if (sndCnt % 30 == 0)
        {
          SDL_Log ("Play backward");
          BSoundBank::SoundControl.Play (StepTap);
        }
        if (sndCnt == 10000)
        {
          sndCnt = 0;
        }
        sndCnt++;

        setTrans (-1.0f * direction * 0.1f);
        break;
//      case 7: //north_west
//        if (sndCnt % 30 == 0)
//        {
//          BSoundBank::SoundControl.Play (StepTap);
//        }
//        if (sndCnt == 10000)
//        {
//          sndCnt = 0;
//        }
//        sndCnt++;
//
//        setTrans (direction * 0.1f);
//        setTrans (-1.0f * right * 0.1f);
//        break;
//      case 8: //north_east
//        if (sndCnt % 30 == 0)
//        {
//          BSoundBank::SoundControl.Play (StepTap);
//        }
//        if (sndCnt == 10000)
//        {
//          sndCnt = 0;
//        }
//        sndCnt++;
//
//        setTrans (direction * 0.1f);
//        setTrans (right * 0.1f);
//        break;

        break;
      default:
        break;
    }  // end switch
    countKeys = 0;
  }
  else
  {

    key = 6;
    secondKey = 6;
    countKeys = 0;
    for (int i = 0; i < 6; i++)
    {
      if (wasd[i] == true)
      {
        countKeys += 1;
        if (countKeys == 1)
        {
          key = i;
        }
        else
        {
          secondKey = i;
        }
      }
    }
//    std::cout << "direction=(" << direction.x << "," << direction.y << "," << direction.z << ")" << std::endl;
//    std::cout << "right=(" << right.x << "," << right.y << "," << right.z << ")" << std::endl;
//    std::cout << "normal=(" << normal.x << "," << normal.y << "," << normal.z << ")" << std::endl;
    collisiondirectionVec = direction;
    switch (key)
    {
      case 0: //left
//        if (right.x > 0)
//        {
//          setTrans (-1.0f * right * 0.1f);
//        }
//        else
//        {
//          setTrans (-1.0f * glm::vec3 (0.0f, 1.0f, 1.0f) * right * 0.1f);
//        }
//        break;

        if ((useThisNormal.z > 0.9999f && right.z > 0.f))
        {
          SDL_Log ("Left:North - useThisNormal:(%f,%f), right:(%f,%f)", useThisNormal.x, useThisNormal.z, right.x, right.z);
          SDL_LogInfo (SDL_LOG_CATEGORY_CUSTOM, "Left:North - useThisNormal:(%f,%f), right:(%f,%f)", useThisNormal.x, useThisNormal.z, right.x, right.z);
          setTrans (-1.f * glm::vec3 (1.0f, 1.0f, 0.0f) * right * 0.1f);
        }
        else if ((useThisNormal.z > 0.9999f && right.z < 0.f))
        {
          setTrans (-1.f * right * 0.1f);
        }

        //west
        else if ((useThisNormal.x > 0.9999f && right.x > 0.f))
        {
          setTrans (-1.f * glm::vec3 (0.0f, 1.0f, 1.f) * right * 0.1f);
        }
        else if ((useThisNormal.x > 0.9999f && right.x < 0.f))
        {
          setTrans (-1.f * right * 0.1f);
        }

        // south
        if ((useThisNormal.z < -0.9999f && right.z < 0.f))
        {
          setTrans (-1.f * glm::vec3 (1.0f, 1.0f, 0.0f) * right * 0.1f);
        }
        else if ((useThisNormal.z < -0.9999f && right.z > 0.f))
        {
          setTrans (-1.f * right * 0.1f);
        }

        //east
        else if ((useThisNormal.x < -0.9999f && right.x < 0.f))
        {
          setTrans (-1.f * glm::vec3 (0.0f, 1.0f, 1.f) * right * 0.1f);
        }
        else if (useThisNormal.x < -0.9999f && right.x > 0.f)
        {
          setTrans (-1.f * right * 0.1f);
        }

        break;

      case 1: //right
//        if (right.x < 0)
//        {
//          setTrans (right * 0.1f);
//        }
//        else
//        {
//          setTrans (glm::vec3 (1.0f, 1.0f, 0.0f) * right * 0.1f);
//        }

        //north
        if ((useThisNormal.z > 0.9999f && right.z < 0.f))
        {
          setTrans (glm::vec3 (1.0f, 1.0f, 0.0f) * right * 0.1f);
        }
        else if ((useThisNormal.z > 0.9999f && right.z > 0.f))
        {
          setTrans (right * 0.1f);
        }

        //west
        else if ((useThisNormal.x > 0.9999f && right.x < 0.f))
        {
          setTrans (glm::vec3 (0.0f, 1.0f, 1.f) * right * 0.1f);
        }
        else if ((useThisNormal.x > 0.9999f && right.x > 0.f))
        {
          setTrans (right * 0.1f);
        }

        // south
        if ((useThisNormal.z < -0.9999f && right.z > 0.f))
        {
          setTrans (glm::vec3 (1.0f, 1.0f, 0.0f) * right * 0.1f);
        }
        else if ((useThisNormal.z < -0.9999f && right.z < 0.f))
        {
          setTrans (right * 0.1f);
        }

        //east
        else if ((useThisNormal.x < -0.9999f && right.x > 0.f))
        {
          setTrans (glm::vec3 (0.0f, 1.0f, 1.f) * right * 0.1f);
        }
        else if (useThisNormal.x < -0.9999f && right.x < 0.f)
        {
          setTrans (right * 0.1f);
        }
        break;
      case 2: //forward
        //north
//        if ((useThisNormal.z > 0.9999f && direction.z < 0.f))
        if ((useThisNormal.z > 0.9999f && direction.z < 0.f))
        {
          SDL_Log ("Forward:North - useThisNormal:(%f,%f), direction< :(%f,%f)", useThisNormal.x, useThisNormal.z, direction.x, direction.z);
          setTrans (glm::vec3 (1.0f, 1.0f, 0.0f) * direction * 0.1f);
        }
        else if ((useThisNormal.z > 0.9999f && direction.z >= 0.f))
        {
          SDL_Log ("Forward:North - useThisNormal:(%f,%f), direction>=:(%f,%f)", useThisNormal.x, useThisNormal.z, direction.x, direction.z);
          setTrans (direction * 0.1f);
        }

        //west
        else if ((useThisNormal.x > 0.9999f && direction.x < 0.f))
        {
          SDL_Log ("Forward:West  - useThisNormal:(%f,%f), direction< :(%f,%f)", useThisNormal.x, useThisNormal.z, direction.x, direction.z);
          setTrans (glm::vec3 (0.0f, 1.0f, 1.f) * direction * 0.1f);
        }
        else if ((useThisNormal.x > 0.9999f && direction.x >= 0.f))
        {
          SDL_Log ("Forward:West  - useThisNormal:(%f,%f), direction>=:(%f,%f)", useThisNormal.x, useThisNormal.z, direction.x, direction.z);
          setTrans (direction * 0.1f);
        }

        // south
        if ((useThisNormal.z < -0.9999f && direction.z >= 0.f))
        {
          SDL_Log ("Forward:South - useThisNormal:(%f,%f), direction>=:(%f,%f)", useThisNormal.x, useThisNormal.z, direction.x, direction.z);
          setTrans (glm::vec3 (1.0f, 1.0f, 0.0f) * direction * 0.1f);
        }
        else if ((useThisNormal.z < -0.9999f && direction.z < 0.f))
        {
          SDL_Log ("Forward:South - useThisNormal:(%f,%f), direction< :(%f,%f)", useThisNormal.x, useThisNormal.z, direction.x, direction.z);
          setTrans (direction * 0.1f);
        }

        //east
        else if ((useThisNormal.x < -0.9999f && direction.x >= 0.f))
        {
          SDL_Log ("Forward:East  - useThisNormal:(%f,%f), direction>=:(%f,%f)", useThisNormal.x, useThisNormal.z, direction.x, direction.z);
          setTrans (glm::vec3 (0.0f, 1.0f, 1.f) * direction * 0.1f);
        }
        else if (useThisNormal.x < -0.9999f && direction.x < 0.f)
        {
          SDL_Log ("Forward:East  - useThisNormal:(%f,%f), direction< :(%f,%f)", useThisNormal.x, useThisNormal.z, direction.x, direction.z);
          setTrans (direction * 0.1f);
        }

        break;
      case 3: //backward
        //north
        if ((useThisNormal.z > 0.9999f && direction.z > 0.f))
        {
          setTrans (-1.f * glm::vec3 (1.0f, 1.0f, 0.0f) * direction * 0.1f);
        }
        else if ((useThisNormal.z > 0.9999f && direction.z < 0.f))
        {
          setTrans (-1.f * direction * 0.1f);
        }

        //west
        else if ((useThisNormal.x > 0.9999f && direction.x > 0.f))
        {
          setTrans (-1.f * glm::vec3 (0.0f, 1.0f, 1.f) * direction * 0.1f);
        }
        else if ((useThisNormal.x > 0.9999f && direction.x < 0.f))
        {
          setTrans (-1.f * direction * 0.1f);
        }

        // south
        if ((useThisNormal.z < -0.9999f && direction.z < 0.f))
        {
          setTrans (-1.f * glm::vec3 (1.0f, 1.0f, 0.0f) * direction * 0.1f);
        }
        else if ((useThisNormal.z < -0.9999f && direction.z > 0.f))
        {
          setTrans (-1.f * direction * 0.1f);
        }

        //east
        else if ((useThisNormal.x < -0.9999f && direction.x < 0.f))
        {
          setTrans (-1.f * glm::vec3 (0.0f, 1.0f, 1.f) * direction * 0.1f);
        }
        else if (useThisNormal.x < -0.9999f && direction.x > 0.f)
        {
          setTrans (-1.f * direction * 0.1f);
        }
        break;
      default:
        break;
    }
  }
  // temporarily commented out (date:tor3/1)
//  btTransform trans;
//
//  getRigidBody ()->getMotionState ()->getWorldTransform (trans);
//  glm::vec3 t;
//  t.x = trans.getOrigin ().getX ();
//  t.y = trans.getOrigin ().getY ();
//  t.z = trans.getOrigin ().getZ ();
//
//  if ((t.y - getTrans ().y) > 0.2f || (t.y - getTrans ().y) < -0.2f)
//  {
//    //                BSoundBank::SoundControl.Play(SoundO);
//  }
//  setTrans (t - getTrans ());


//trans.setOrigin (btVector3 (getTrans ().x, getTrans ().y + 2.0f, getTrans ().z));
//getRigidBody ()->getMotionState ()->setWorldTransform (trans);
//getRigidBody ()->setCenterOfMassTransform (trans);

  //       for the physics
//  btTransform trans;
//  btVector3 bvec;
//  getRigidBody ()->getMotionState ()->getWorldTransform (trans);
//  bvec = trans.getOrigin ();
//  // this made him move push stuff around
//  trans.setOrigin (btVector3 (getTrans ().x, getTrans ().y, getTrans ().z));
//  getRigidBody ()->getMotionState ()->setWorldTransform (trans);
//  getRigidBody ()->setCenterOfMassTransform (trans);
//
//  btTransform tr = getRigidBody ()->getWorldTransform ();
//  btQuaternion quat = tr.getRotation ();
//  btQuaternion quat1 (btVector3 (1, 0, 0), getOrientation ().x);
//  btQuaternion quat2 (btVector3 (0, 1, 0), getOrientation ().y);
//  btQuaternion quat3 (btVector3 (0, 0, 1), getOrientation ().z);
//  tr.setRotation (quat * quat1 * quat2 * quat3);
//  getRigidBody ()->setWorldTransform (tr);
//  getRigidBody ()->getMotionState ()->setWorldTransform (tr);



// OLD Version: (17/1)
//  btTransform trans;
//
////  btTransform trans;
//  getRigidBody ()->getMotionState ()->getWorldTransform (trans);
//
//  // this made him move push stuff around
//  trans.setOrigin (btVector3 (getTrans ().x, getTrans ().y, getTrans ().z));
//  getRigidBody ()->getMotionState ()->setWorldTransform (trans);
//  getRigidBody ()->setCenterOfMassTransform (trans);

  // NEW Version: (17/1)
  btTransform trans;

  //  btTransform trans;
  getRigidBody ()->getMotionState ()->getWorldTransform (trans);

  // this made him move push stuff around
  trans.setOrigin (btVector3 (getTrans ().x, getTrans ().y, getTrans ().z));
//  getRigidBody ()->getMotionState ()->getWorldTransform (trans);
  getRigidBody ()->getMotionState ()->setWorldTransform (trans);
  getRigidBody ()->setCenterOfMassTransform (trans);

// From Sniper:
//  btTransform tr = getRigidBody ()->getWorldTransform ();
//  btQuaternion quat = tr.getRotation ();
////  btQuaternion quat1 (btVector3 (1, 0, 0), getOrientation ().x);
//  btQuaternion quat2 (btVector3 (0, 1, 0), getOrientation ().y);
////  btQuaternion quat3 (btVector3 (0, 0, 1), getOrientation ().z);
//  tr.setRotation (quat2);
//  getRigidBody ()->setWorldTransform (tr);
//
//  getRigidBody ()->forceActivationState (ISLAND_SLEEPING);
////  lastDetectedCollisionObj = objB;
//  std::cout << "End of Move in FPerson" << std::endl;
}


