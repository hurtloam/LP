/*
 * WooddenCube2.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: peter
 */

#include "../inc/Glucose.h"
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

Glucose::Glucose(
		int id,
		glm::vec3 scale,
		GLuint texture,
		glm::vec3 trans,
    LPWatch* watch,
		ResObj& resObj,
		const View& view,
		LPUniform lpUniform) : StaticObj(
				id,
				scale,
				alpha_D_glucopyranose,
				texture,
				trans,
				watch,
				resObj,
				view,
				lpUniform)
{

	b_motionState =
			new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(trans.x, trans.y, trans.z)));


	b_shape = new btBoxShape(btVector3(2,2,2));

	btScalar mass = 0;
//		btVector3 fallInertia(0, 0, 0);
//
//		b_shape->calculateLocalInertia(mass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape);

	b_rigidBody = new btRigidBody(b_rigidBodyCI);


/*
	b_motionState =
			new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(trans.x, trans.y, trans.z)));


		b_shape = new btBoxShape(btVector3(1,1,1));

		btScalar mass = 0;
//		btVector3 fallInertia(0, 0, 0);

//		b_shape->calculateLocalInertia(mass, fallInertia);

		btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape);

		b_rigidBody = new btRigidBody(b_rigidBodyCI);

		b_rigidBody->setRestitution(0.3);

		b_rigidBody->setFriction(20);
*/
	setRotationMatrix_X(0);
}

Glucose::~Glucose() {
	// TODO Auto-generated destructor stub
}

void Glucose::draw() {
  printf("ENTER Glucose::draw");
//	StaticObj::drawPhysicsBox();
//  StaticObj::draw (alpha_D_glucopyranose);
  StaticObj::draw ();
}


void Glucose::move(bool flag) {
  printf("ENTER Glucose::move");
	btTransform trans;
	btVector3 bvec;
  setRotationMatrix_Y (3.14159265f / 2.0f);
	getRigidBody()->getMotionState()->getWorldTransform(trans);
	bvec = trans.getOrigin();
	// this made him move push stuff around
	trans.setOrigin(btVector3(getTrans().x, getTrans().y, getTrans().z));
	getRigidBody()->getMotionState()->setWorldTransform(trans);
	getRigidBody()->setCenterOfMassTransform (trans);
  static int timeDelay = 0;


//  if ((timeDelay % 200) == 0)
//    {
//    resObj.getMesh(getObjectType())[5]->trans = glm::vec3(0.01f,0.01f,0.01f);
//    timeDelay = 0;
//  }
//  else {
//    resObj.getMesh(getObjectType())[5]->trans = glm::vec3(0.0f,0.0f,0.0f);
//  }
  timeDelay++;
}
