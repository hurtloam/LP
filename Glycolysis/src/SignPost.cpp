/*
 * SignPost.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: peter
 */

#include "../inc/SignPost.h"
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

/**
 * @brief When two lines of text needs to be handled as one object.
 *
 * @details When two lines of text needs to be handled as one object we contain them in a SignPost object.
 *
 * @param first_obj
 * @param second_obj
 * @param id
 * @param scale
 * @param objType
 * @param texture
 * @param trans
 * @param resObj
 * @param view
 * @param programID
 * @param MatrixID
 * @param ViewMatrixID
 * @param ModelMatrixID
 * @param LightID
 * @param TextureID
 */
SignPost::SignPost(TextObject *first_obj, TextObject *second_obj, int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj,
                    const View& view, LPUniform lpUniform) : StaticObj(
id, scale, objType, texture, trans, watch, resObj, view, lpUniform), textObjectFirst (first_obj), textObjectSecond (
        second_obj)
{

		textObjectFirst->setTrans(trans - textObjectFirst->getTrans());
		textObjectSecond->setTrans(trans - textObjectSecond->getTrans() - glm::vec3(0.0f, 0.3f, 0.0f));


		b_motionState =
				new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(trans.x, trans.y, trans.z)));

		b_shape = new btBoxShape(btVector3(1.0,0.4,0.5));
		btScalar mass = 0;
		btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape);



		b_rigidBody = new btRigidBody(b_rigidBodyCI);

	//	b_rigidBody->setSleepingThresholds (0.0f, 0.0f);
	//	b_rigidBody->setAngularFactor (0.0f);

	//	b_rigidBody->setCollisionFlags(b_rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		b_rigidBody->setActivationState(DISABLE_DEACTIVATION);
		GLfloat blackish[4] = {0,0,0,1};
		setColor(resObj.black);


counter = 0;
}

void SignPost::setTrans(glm::vec3 tr) {
	StaticObj::setTrans(tr);
	textObjectFirst->setTrans(tr);
	textObjectSecond->setTrans(tr);
}

void SignPost::setColor(GLfloat const _color[4])
{
//	float c[4];
//	c[0] =_color[0];
//	c[1] =_color[1];
//	c[2] =_color[2];
//	c[3] =_color[3];
	std::cout << "SetColor for signPost " << endl;
	textObjectFirst->setColor(_color);
	textObjectSecond->setColor(_color);

}

SignPost::~SignPost() {
	// TODO Auto-generated destructor stub
}

void SignPost::draw() {
//	StaticObj::draw(cube);
	textObjectFirst->draw();
	textObjectSecond->draw();

//	if (counter % 240 == 0) {
//		if (getId() >22100 && getId() < 22110)
//		{
//			std::cout << "****************************************************************************************************" << std::endl;
//			std::cout << "physicscoord: (" << getRigidBody()->getCenterOfMassPosition().getX() << ", " << getRigidBody()->getCenterOfMassPosition().getY() << ", " << getRigidBody()->getCenterOfMassPosition().getZ() << ")" << std::endl;
//			std::cout << "textObj id: " <<  getId() << ", trans: (" << getTrans().x << ", " << getTrans().y << ", " << getTrans().z << ") " << std::endl;
//			std::cout << "textObj id: " <<  getId() << ", physics - center of Mass: (" << getRigidBody()->getCenterOfMassPosition().getX() << ", " << getRigidBody()->getCenterOfMassPosition().getY() << ", " << getRigidBody()->getCenterOfMassPosition().getZ() << ") " << std::endl;
//			std::cout << "textObj id: " <<  getId() << ", physics - center of MassTransform: (" << getRigidBody()->getCenterOfMassTransform().getOrigin().getX() << ", " << getRigidBody()->getCenterOfMassTransform().getOrigin().getY() << ", " << getRigidBody()->getCenterOfMassTransform().getOrigin().getZ() << ") " << std::endl;
//			std::cout << "ActivationState: " << getRigidBody()->getActivationState() << std::endl;
//			std::cout << "****************************************************************************************************" << std::endl;
//		}
//	}
//	counter++;

}

void SignPost::move(bool flag) {

  textObjectFirst->move (flag);
  textObjectSecond->move (flag);

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
