/*
 * Wall.cpp
 *
 *  Created on: Oct 04, 2015
 *      Author: peter
 */

#include "../inc/Wall.h"
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

Wall::Wall(
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
				wall,
				texture,
				trans,
				watch,
				resObj,
				view,
        lpUniform)
{
	b_motionState =
			new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(trans.x, trans.y, trans.z)));
	b_shape = new btBoxShape(btVector3(10,10,1));
	btScalar mass = 0;
	btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape);
	b_rigidBody = new btRigidBody(b_rigidBodyCI);
	setRotationMatrix_X(0);
}

Wall::~Wall() {
	// TODO Auto-generated destructor stub
}

void Wall::draw() {
  StaticObj::draw ();
//  setUseColor(0);
//	StaticObj::draw(wall);
}

void Wall::move(bool flag) {

	/*	btTransform trans;

		getRigidBody()->getMotionState()->getWorldTransform(trans);
		glm::vec3 t;
		t.x = trans.getOrigin().getX();
		t.y = trans.getOrigin().getY();
		t.z = trans.getOrigin().getZ();

		setTrans(t - getTrans());
		*/

  // PETER WAS HEREgiti
  // TWICE
}
