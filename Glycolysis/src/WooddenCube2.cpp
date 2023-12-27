/*
 * WooddenCube2.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: peter
 */

#include "../inc/WooddenCube2.h"
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

WooddenCube2::WooddenCube2(
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
				cube,
				texture,
				trans,
				watch,
				resObj,
				view,
        lpUniform)
{

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

  setRotationMatrix_X (0);
}

WooddenCube2::~WooddenCube2() {
	// TODO Auto-generated destructor stub
}

void WooddenCube2::draw() {
  StaticObj::draw ();
}

void WooddenCube2::move(bool flag) {

//		btTransform trans;
//
//		getRigidBody()->getMotionState()->getWorldTransform(trans);
//		glm::vec3 t;
//		t.x = trans.getOrigin().getX();
//		t.y = trans.getOrigin().getY();
//		t.z = trans.getOrigin().getZ();
//
//		setTrans(t - getTrans());
}
