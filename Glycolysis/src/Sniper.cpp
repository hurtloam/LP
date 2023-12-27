/*
 * Sniper.cpp
 *
 *  Created on: Jul 8, 2014
 *      Author: peter
 */

#include "../inc/Sniper.h"
#include <glm/gtc/random.hpp>

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
#include "../inc/LearningPlatform.h"
#include <vector>
#include "../inc/LineObj.h"

#include <iostream>
using namespace std;

//Sniper::Sniper(int id, glm::vec3 scale, ObjectType objType, int objArray_length, GLuint texture,
//               glm::vec3 trans, LPWatch* watch, const ResObj& resObj, const View& view, GLuint programID,
//                GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID, GLuint LightID, GLuint TextureID) :
//    Actor (id, scale, objType, objArray_length, texture, trans, watch, resObj, view, programID, MatrixID, ViewMatrixID, ModelMatrixID, LightID, TextureID), wasCollisionDetecedLastFrame (
//        false), movingStraightLength (0), counter (0), _sign (1.0f)
//
//
//
//{
//
Sniper::Sniper(int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, LPUniform lpUniform) :
    StaticObj(id, scale, objType, texture, trans, watch, resObj, view, lpUniform), wasCollisionDetecedLastFrame(false), movingStraightLength(0), counter(0), _sign(1.0f)



  {

  // physics is added here:

  btTransform startTransform;
  startTransform.setIdentity ();
  startTransform.setOrigin (btVector3 (trans.x, trans.y, trans.z));
  startTransform.setRotation (btQuaternion (0, 0, 0, 1));
  btDefaultMotionState* b_motionState = new btDefaultMotionState (startTransform);


  b_shape = new btBoxShape(btVector3(0.1f, 1.0f, 0.1f));

  btScalar mass = 100.0f;

  btVector3 fallInertia (0, 0, 0);

  b_shape->calculateLocalInertia (mass, fallInertia);

  btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI (mass, b_motionState, b_shape);

  b_rigidBody = new btRigidBody (b_rigidBodyCI);

  b_rigidBody->setSleepingThresholds (0.0f, 0.0f);
  b_rigidBody->setAngularFactor (0.0f);
  b_rigidBody->getCollisionShape ()->setMargin (0.01f);

  watch->registerWatch (1000, this);

  line = new LineObj(997, glm::vec3(1.0f, 1.0f, 1.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f), watch, &view, lpUniform.programID, lpUniform.MatrixID, lpUniform.ViewMatrixID, lpUniform.ModelMatrixID, lpUniform.LightID, lpUniform.TextureID);
//  emptyLineCoord.push_back (getTrans ());
//  emptyLineCoord.push_back (getTrans () + glm::vec3 (0.0f, 2.0f, 0.0f));

  setMoleculeInfo1 ("Sniper");
  currentObject = objType;
}

Sniper::~Sniper() {
	// TODO Auto-generated destructor stub
}

void Sniper::draw() {
  StaticObj::draw(currentObject);
  line->draw ();
//  line->setLineCoord (emptyLineCoord);
}

void
Sniper::move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal) {


  float speed = 4.0;
  bool flag = false;


  counter++; // what is this used for? Check if this one can be removed


  for (auto obj : collisionDetected) {
    if (obj.first == getId()) {
      flag = true;
    }
  }
  if (flag == false) {
    setTrans(glm::vec3(speed * 0.025f * sin(getOrientation().y), 0.0f, speed * 0.025f * sin(3.14159265f / 2.0f - getOrientation().y)));
  }
  else {
    setRotationMatrix_Y(3.14159265f / 2.0f);
    setTrans(glm::vec3(speed * 0.685f * sin(getOrientation().y), 0.0f, speed * 0.685f * sin(3.14159265f / 2.0f - getOrientation().y)));
  }

  StaticObj::move(collisionDetected, normal);

  //	 for the physics
  btTransform trans;

//  btTransform trans;
  getRigidBody ()->getMotionState ()->getWorldTransform (trans);

  // this made him move push stuff around
  trans.setOrigin (btVector3 (getTrans ().x, getTrans ().y + 2.4f, getTrans ().z));
  getRigidBody ()->getMotionState ()->setWorldTransform (trans);
  getRigidBody ()->setCenterOfMassTransform (trans);
}

void
Sniper::sawIt (glm::vec3 position, int id) {
//  std::cout << "Sniper saw FPerson, id = " << id << std::endl;
  static bool delayStarted;
  static int delay;

  if (delayStarted && delay > 0)
  {
    delay--;
  }
  else if (delayStarted && delay <= 0)
  {
  std::vector<glm::vec3> lineCoord;
  lineCoord.push_back (position);
  lineCoord.push_back (getTrans ());
  line->setLineCoord (lineCoord);
  float z = position.z - getTrans ().z;
  float x = position.x - getTrans ().x;

  float v = atan (abs (z) / abs (x));
  float y = atan (abs (x) / abs (z));

  setZ (z);
  setX (x);
  setV (v);
  setY (y);

  if (x < 0 && z > 0)
  {
    setRotationMatrix_Y (-getOrientation ().y + 3 * 3.14159265 / 2 + v);
//    std::cout << "111setRotationMatrix_Y angle = " << 3.14159265 - v << "(" << v << ")" << std::endl;
  }
  else if (x > 0 && z < 0)
  {
    setRotationMatrix_Y (-getOrientation ().y + 3.14159265 / 2 + v);
//    std::cout << "222setRotationMatrix_Y angle = " << 3.14159265 + 3.14159265 / 2 - v << "(" << v << ")" << std::endl;
  }
  else if (x < 0 && z < 0)
  {
    setRotationMatrix_Y (-getOrientation ().y + (3 * 3.14159265 / 2) - v);
//    std::cout << "333setRotationMatrix_Y angle = " << 3.14159265 + 3 * 3.14159265 / 2 + v << "(" << v << ")" << std::endl;

  }
  else
  if (x > 0 && z > 0)
  {
    setRotationMatrix_Y (-getOrientation ().y + (3.14159265 / 2) - v);
//    std::cout << "444setRotationMatrix_Y angle = " << 3.14159265 + 3 * 3.14159265 / 2 - v << "(" << v << ")" << std::endl;

  }
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
//  btQuaternion quat1 (btVector3 (1, 0, 0), getOrientation ().x);
  btQuaternion quat2 (btVector3 (0, 1, 0), getOrientation ().y);
//  btQuaternion quat3 (btVector3 (0, 0, 1), getOrientation ().z);
  tr.setRotation (quat2);
  getRigidBody ()->setWorldTransform (tr);

    //reset flags for delay
    delayStarted = false;
    delay = 100;
  }
  else if (!delayStarted)
  {
    delayStarted = true;
    delay = 100;
  }


}
