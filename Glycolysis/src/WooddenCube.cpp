/*
 * WooddenCube.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: peter
 */

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

#include "../inc/WooddenCube.h"


WooddenCube::WooddenCube(int id,
		glm::vec3 scale,
		ObjectType objType,
		GLuint texture,
		glm::vec3 trans,
		LPWatch* watch,
		ResObj& resObj,
		const View& view,
		LPUniform lpUniform) : StaticObj(id,
		scale,
		objType,
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
//
//		b_shape->calculateLocalInertia(mass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape);

	b_rigidBody = new btRigidBody(b_rigidBodyCI);
  setRotationMatrix_X (0);


}

WooddenCube::~WooddenCube() {
	// TODO Auto-generated destructor stub
}

void WooddenCube::draw() {
  StaticObj::draw ();
}

void WooddenCube::move(bool flag) {
	setTrans(glm::vec3(0.1f*sin(getOrientation().y), 0.0f, 0.1f*sin(3.14159265f/2.0f - getOrientation().y)));
	setRotationMatrix_Y(0.06);

	//	 for the physics
	btTransform trans;
	btVector3 bvec;
	getRigidBody()->getMotionState()->getWorldTransform(trans);
	bvec = trans.getOrigin();

	// this made him move push stuff around
	trans.setOrigin(btVector3(getTrans().x, getTrans().y, getTrans().z));
	getRigidBody()->getMotionState()->setWorldTransform(trans);
	getRigidBody()->setCenterOfMassTransform (trans);

}
