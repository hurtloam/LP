/*
 * Molecule.cpp
 *
 *  Created on: Oct 28, 2017
 *      Author: peter
 */

#include "../inc/Molecule.h"
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

#include "../inc/LearningPlatformIf.h"

Molecule::Molecule(
		int id,
		glm::vec3 scale,
		ObjectType objType,
		GLuint texture,
		glm::vec3 trans,
    LPWatch* watch,
		ResObj& resObj,
		const View& view,
		LPUniform lpUniform) : StaticObj(
				id,
				scale,
				objType,
				texture,
				trans,
				watch,
				resObj,
				view,
        lpUniform)
{
 btTransform startTransform;
 startTransform.setIdentity ();
 startTransform.setOrigin (btVector3 (trans.x, trans.y, trans.z));
 startTransform.setRotation (btQuaternion (0, 0, 0, 1));


	b_motionState =
			new btDefaultMotionState(startTransform);
//	b_shape = new btBoxShape(btVector3(2,2,2));
	b_shape = new btBoxShape(btVector3(0.5,0.5,0.1));

//	btVector3 origin;
//	origin.setX(0.0);
//	origin.setY(0.0);
//	origin.setZ(0.0);
//	t.setOrigin(origin);
//	b_shape->getAabb(t, min, max);
	btScalar mass = 0;
  btVector3 fallInertia(0, 0, 0);
  b_shape->calculateLocalInertia(mass, fallInertia);
  btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape, fallInertia);
	b_rigidBody = new btRigidBody(b_rigidBodyCI);

	 b_rigidBody->setRestitution (0.0);
	 b_rigidBody->setFriction (90);
	 b_rigidBody->setSleepingThresholds (0.0f, 0.0f);
	 b_rigidBody->setAngularFactor (0.0f);
  b_rigidBody->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	 b_rigidBody->getCollisionShape ()->setMargin (0.01f);

//setRotationMatrix_X(-3.14/2);
setRotationMatrix_X(0);

//  watch->registerWatch(id - c_glucose + c_molecule_spot, this);

}


Molecule::~Molecule() {
	// TODO Auto-generated destructor stub
}

void Molecule::draw() {
//	StaticObj::drawPhysicsBox();
//	StaticObj::draw(objType);
	StaticObj::draw();
}


void Molecule::move(bool flag) {
  printf("ENTER Molecule::move\n");
	btTransform trans;
	btVector3 bvec;
	getRigidBody()->getMotionState()->getWorldTransform(trans);
	bvec = trans.getOrigin();
	// this made him move push stuff around
	trans.setOrigin(btVector3(getTrans().x, getTrans().y, getTrans().z));
	getRigidBody()->getMotionState()->setWorldTransform(trans);
	getRigidBody()->setCenterOfMassTransform (trans);

//  static int timeDelay = 0;
//
//  if ((timeDelay % 2) == 0) {
//    resObj.getMesh(getObjectType())[5]->trans = glm::vec3(0.01f,0.01f,0.01f);
//    timeDelay = 0;
//  }
//  else {
//    resObj.getMesh(getObjectType())[5]->trans = glm::vec3(0.0f,0.0f,0.0f);
//  }
//  timeDelay++;

// adding to see if physics body comes along...
  btTransform tr = getRigidBody()->getWorldTransform();
  btQuaternion quat = tr.getRotation();
  btQuaternion quat1(btVector3(1, 0, 0), getOrientation().x);
  btQuaternion quat2(btVector3(0, 1, 0), getOrientation().y);
  btQuaternion quat3(btVector3(0, 0, 1), getOrientation().z);
//  tr.setRotation(quat * quat1 * quat2 * quat3);
//  getRigidBody()->setWorldTransform(tr);





}

void Molecule::move(std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal)
{
  printf("ENTER Molecule::move2\n");
  btTransform trans;
  btVector3 bvec;
  getRigidBody()->getMotionState()->getWorldTransform(trans);
  bvec = trans.getOrigin();
  // this made him move push stuff around
  trans.setOrigin(btVector3(getTrans().x, getTrans().y, getTrans().z));
  getRigidBody()->getMotionState()->setWorldTransform(trans);
  getRigidBody()->setCenterOfMassTransform(trans);

//  static int timeDelay = 0;
//
//  if ((timeDelay % 2) == 0) {
//    resObj.getMesh(getObjectType())[5]->trans = glm::vec3(0.01f,0.01f,0.01f);
//    timeDelay = 0;
//  }
//  else {
//    resObj.getMesh(getObjectType())[5]->trans = glm::vec3(0.0f,0.0f,0.0f);
//  }
//  timeDelay++;

// adding to see if physics body comes along...
  btTransform tr = getRigidBody()->getWorldTransform();
  btQuaternion quat = tr.getRotation();
  btQuaternion quat1(btVector3(1, 0, 0), getOrientation().x);
  btQuaternion quat2(btVector3(0, 1, 0), getOrientation().y);
  btQuaternion quat3(btVector3(0, 0, 1), getOrientation().z);
//  tr.setRotation(quat * quat1 * quat2 * quat3);
//  getRigidBody()->setWorldTransform(tr);
  correctPosition = false;
  int objB;
  bool flag;
  for (auto obj : collisionDetected) {
    if (obj.first == getId()) {
      flag = true;
      objB = obj.second;
      if ((objB - 61000) == (getId() - 16000)) {
        correctPosition = true;
      }
    }
  }
}


void Molecule::sawIt(glm::vec3 position, int id)
{
//  std::cout << "Molecule in correct position" << std::endl;
}
