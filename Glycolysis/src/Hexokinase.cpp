/*
 * Glucose6Phosphate.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: peter
 */

#include "../inc/Hexokinase.h"
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

Hexokinase::Hexokinase(
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
				hexokinase,
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
	btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape);

	b_rigidBody = new btRigidBody(b_rigidBodyCI);

}

Hexokinase::~Hexokinase() {
	// TODO Auto-generated destructor stub
}

void Hexokinase::draw() {
//  setObjColor(glm::vec3(0,0,1));
//  StaticObj::drawPhysicsBox();
  StaticObj::draw();
}


void Hexokinase::move(bool flag) {
	btTransform trans;
	btVector3 bvec;
	getRigidBody()->getMotionState()->getWorldTransform(trans);
	bvec = trans.getOrigin();
	// this made him move push stuff around
	trans.setOrigin(btVector3(getTrans().x, getTrans().y, getTrans().z));
	getRigidBody()->getMotionState()->setWorldTransform(trans);
	getRigidBody()->setCenterOfMassTransform (trans);
}
