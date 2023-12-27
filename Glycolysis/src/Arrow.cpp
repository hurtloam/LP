/*
 * Wall.cpp
 *
 *  Created on: Oct 04, 2015
 *      Author: peter
 */

#include "../inc/Arrow.h"
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

Arrow::Arrow(
    int id,
    glm::vec3 scale,
    ObjectType obj,
    GLuint texture,
    glm::vec3 trans,
    LPWatch* watch,
    ResObj& resObj,
    const View& view,
    LPUniform lpUniform) :
    StaticObj(
        id,
        scale,
        obj,
        texture,
        trans,
        watch,
        resObj,
        view,
        lpUniform)
{
  b_motionState =
      new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(trans.x, trans.y, trans.z)));
  b_shape = new btBoxShape(btVector3(0.1f,0.4f,0.1f));
//  b_shape = new btBoxShape(btVector3(0.2f,0.8f,0.1f));
  btScalar mass = 0;
  btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape);
  b_rigidBody = new btRigidBody(b_rigidBodyCI);

  	setRotationMatrix_X(0);

  objType = obj;

  setLightPos(getTrans() + glm::vec3(0.0, 0.0, 60.0));
  cout << "ENTER Arrow Constructor" << endl;
}

Arrow::~Arrow() {
  // TODO Auto-generated destructor stub
}

void Arrow::draw() {
  //	setRotationMatrix(3.1415/4);




  // For movement, temporarily disabled
  static float sign = 1.0;
  static float sign2 = -1.0;
  static int counter = 0;
  static float blue = 1.0;
  static float red = 0.0;



  //    if (objType == arrow_rectangle_down_single1)
  //    {
  //      glUniform1f(useColorID, 1.0);
  //    }
  //    else if (currentObj == plane)
  //    {
  //      glUniform1f(useColorID, 1.0);
  //    }
  //    else if (currentObj == plate)
  //    {
  //      glUniform1f(useColorID, 1.0);
  //    }
  //    else
  //    {
  //      glUniform1f(useColorID, 0.0);
  //    }

  glUniform1f(useColorID, 1.0);


  setObjColor(glm::vec3(1.0, 0.0, 0.0));
//  setObjColor(glm::vec3(red, 0.0, 0.0));
//  if ( counter < 50)
//  {
//    counter++;
//  }
//  else
//  {
//    if (red >= 1.0)
//    {
//      sign2 = -1 * sign2;
//      red -= sign2 * 1.0/60;
//      counter = 0;
//    }
//
//    if (red > 0.0)
//    {
//      red -= sign2 * 1.0/60;
//    }
//
//    if (red <= 0.0)
//    {
//      red += 1.0/2;
//      sign2 = -1 * sign2;
//    }
//  }

  if (colorStatus == ColorStates::S_BLUE) {
    // blue arrow
    setObjColor(glm::vec3(0.0,0.0,blue));
  }
  else {
	  setObjColor(glm::vec3(1.0,0.0,0.0));

    // do nothing
  }
//  if (status != LPObject::MenuStatusE::HIDDEN) {
    StaticObj::draw();
//  }

}

void
Arrow::move (bool flag) {

  // For the physics
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

void
Arrow::move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal) {

  // For the physics
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

