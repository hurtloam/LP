/*
 * TextSpot.cpp
 *
 *  Created on: Oct 20, 2019
 *      Author: peter
 */

#include "../inc/TextSpot.h"
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
#include "../inc/SoundBank.h"
#include <iostream>

TextSpot::TextSpot(int id,
                      ObjectType obj,
                      glm::vec3 shape,
                         glm::vec3 scale, GLuint texture,
                          glm::vec3 trans, LPWatch* watch, ResObj& resObj,
                          const View& view, LPUniform lpUniform) : StaticObj(
id, scale, obj, texture, trans, watch, resObj, view, lpUniform)
{
  btTransform startTransform;
  startTransform.setIdentity ();
  startTransform.setOrigin (btVector3 (trans.x, trans.y, trans.z));
  startTransform.setRotation (btQuaternion (0, 0, 0, 1));
  btDefaultMotionState* b_motionState = new btDefaultMotionState (startTransform);

  b_shape = new btBoxShape(btVector3(shape.x, shape.y, shape.z));

  btScalar mass = 0.0;
  btVector3 fallInertia (0, 0, 0);
  b_shape->calculateLocalInertia (mass, fallInertia);
  btRigidBody::btRigidBodyConstructionInfo b_ballRigidBodyCI (mass,
                                                              b_motionState,
                                                              b_shape,
                                                              fallInertia);
  b_rigidBody = new btRigidBody (b_ballRigidBodyCI);
  b_rigidBody->setRestitution (0.0);
  b_rigidBody->setFriction (90);
  b_rigidBody->setSleepingThresholds (0.0f, 0.0f);
  b_rigidBody->setAngularFactor (0.0f);
  b_rigidBody->getCollisionShape ()->setMargin (0.01f);

  setColor(resObj.dark_gray);
  setMoleculeInfo1("TextSpot");
}

TextSpot::~TextSpot()
{
  // TODO Auto-generated destructor stub
}

void
TextSpot::draw()
{
//  if (!isItemSelected)
//  {
  if (!isCorrectPosition()) {
    internalDraw(true);
  }
//  }
//  StaticObj::draw ();
}


void TextSpot::internalDraw(bool isItemSelected)
{
  glUseProgram(lpUniform.programID);
//    glEnable(GL_BLEND);
  glm::mat4 ModelMatrix = glm::mat4(1.0);
  ModelMatrix = glm::translate(ModelMatrix,getTrans()) * getRotationMatrix();
  glm::mat4 MVP = view.getProjectionMatrix() * view.getViewMatrix() * ModelMatrix;

  // Send our transformation to the currently bound shader,
  // in the "MVP" uniform
  glUniformMatrix4fv(lpUniform.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  glUniformMatrix4fv(lpUniform.ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
  glUniformMatrix4fv(lpUniform.ViewMatrixID, 1, GL_FALSE, &(view.getViewMatrix())[0][0]);

  if(lpUniform.programID == 0)
    printf("programID faulty\n");

  attribute_coord = glGetAttribLocation(lpUniform.programID, "coord");
  uniform_tex = glGetUniformLocation(lpUniform.programID, "tex");
  uniform_color = glGetUniformLocation(lpUniform.programID, "color");
  useColorID = glGetUniformLocation(lpUniform.programID, "useColor");
  glUniform1i(useColorID, 1.0f);
  glUniform4fv(uniform_color, 1, color);

//  std::cout << "attribute_coord=" << attribute_coord << std::endl;
//  std::cout << "uniform_tex=" << uniform_tex << std::endl;
//  std::cout << "uniform_color=" << uniform_color << std::endl;
//  std::cout << "useColorID=" << useColorID << std::endl;
//  if(attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1)
//  {
//    fprintf(stderr, "WARNING: Some values not initialized: attribute_coord=%d, uniform_tex=%d, uniform_color=%d\n", attribute_coord, uniform_tex, uniform_color);
//    std::cout << "TextMenuItem" << std::endl;
//    std::cout << "lpUniform.BoneLocationID" << lpUniform.BoneLocationID << std::endl;
//    std::cout << "lpUniform.LightID" << lpUniform.LightID  << std::endl;
//    std::cout << "lpUniform.MatrixID" << lpUniform.MatrixID << std::endl;
//    std::cout << "lpUniform.ModelMatrixID" << lpUniform.ModelMatrixID << std::endl;
//    std::cout << "lpUniform.ModelView3x3MatrixID" << lpUniform.ModelView3x3MatrixID << std::endl;
//    std::cout << "lpUniform.TextureID" << lpUniform.TextureID << std::endl;
//    std::cout << "lpUniform.ViewMatrixID" << lpUniform.ViewMatrixID << std::endl;
//    std::cout << "lpUniform.colorID" << lpUniform.colorID << std::endl;
//    std::cout << "lpUniform.programID" << lpUniform.programID << std::endl;
//  }

  /* Set up the VBO for our vertex data */
  glEnableVertexAttribArray(attribute_coord);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  float txtWidth = 1.0f;
  point box[4] = {
      {-txtWidth/4 , .1f, 0.0f, 0.0f},
      {txtWidth/4, .1f, 1.0f, 0.0f},
      {-txtWidth/4, -.1f, 1.0f, 1.0f},
      {txtWidth/4, -.1f, 0.0f, 1.0f},

  };
  glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(
      attribute_coord,
      4,
      GL_FLOAT,
      GL_FALSE,
      0,
      (void*)0);
  /* Draw the character on the screen */
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glDisableVertexAttribArray(attribute_coord);
  glDeleteBuffers(1, &vbo);
//    glDisable(GL_BLEND);
}

void
TextSpot::setOpenDoor()
{
}
void
TextSpot::move(std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal)
{
  TRACE_DEBUG("ENTER TextSpot::move()");
  btTransform trans;
  btVector3 bvec;
  getRigidBody()->getMotionState()->getWorldTransform(trans);
  bvec = trans.getOrigin();
  // this made him move push stuff around
  trans.setOrigin(btVector3(getTrans().x, getTrans().y, getTrans().z));
  getRigidBody()->getMotionState()->setWorldTransform(trans);
  getRigidBody()->setCenterOfMassTransform(trans);

  btTransform tr = getRigidBody()->getWorldTransform();
  btQuaternion quat = tr.getRotation();
  btQuaternion quat1(btVector3(1, 0, 0), getOrientation().x);
  btQuaternion quat2(btVector3(0, 1, 0), getOrientation().y);
  btQuaternion quat3(btVector3(0, 0, 1), getOrientation().z);
  tr.setRotation(quat * quat1 * quat2 * quat3);
  getRigidBody()->setWorldTransform(tr);

  correctPosition = false;
  collisionObj = 0;
  if (collisionDetected.size() > 0) {
  TRACE_DEBUG("ENTER TextSpot::move(), collisionDetected[0].first=%d, collisionDetected[0].second=%d", collisionDetected[0].first, collisionDetected[0].second);
  }
  int objB;
  for (auto obj : collisionDetected) {
    if (obj.first == this->getId()) {
      objB = obj.second;
      TRACE_DEBUG("obj.first=%d, obj.second=%d, objB=%d, getId=%d, getObjType=%d", obj.first, obj.second, objB, getId(), getObjType());

              correctPosition = true;
              collisionObj = objB;
    }
    else if (obj.second == this->getId()) {
      objB = obj.first;
      TRACE_DEBUG("obj.first=%d, obj.second=%d, objB=%d, getId=%d, getObjType=%d", obj.first, obj.second, objB, getId(), getObjType());

      correctPosition = true;
      collisionObj = objB;
    }
  }
}
