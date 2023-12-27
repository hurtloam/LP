/*
 * Scene.h
 *
 *  Created on: Dec 8, 2013
 *      Author: peter
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <list>
#include "Actor.h"
#include "StaticObj.h"
#include "LPObject.h"
#include <btBulletDynamicsCommon.h>
#include "shader.hpp"
#include <memory>

using std::list;

//static const uint MAX_BONES = 100;

class Scene {
public:
	Scene(const char * vertexShader, const char * fragmentShader);
  void addActor(LPObject* a);
  void removeActor(LPObject* a);
	void removeActor(int actorId);
	void saveActorList(list<std::string> *objList);
	void loadActorList(list<std::string> *objList);
	void init();
	virtual ~Scene();
	GLuint getLightId() const;
	void setLightId(GLuint lightId);
	GLuint getMatrixId() const;
	void setMatrixId(GLuint matrixId);
	GLuint getModelMatrixId() const;
	void setModelMatrixId(GLuint modelMatrixId);
	GLuint getProgramId() const;
	void setProgramId(GLuint programId);
	GLuint getTextureId() const;
	void setTextureId(GLuint textureId);
	GLuint getViewMatrixId() const;
  LPUniform getLPUniform();
	void setViewMatrixId(GLuint viewMatrixId);
	void draw();
  Actor* getCreature()
  {
    return creature;
  }
	void printCoord(int id);
	void printGameBoard();
  void
  move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);
  LPObject* getObject(int id);

  std::vector<LPObject*> getObjectFromObjType(ObjectType objType);

  list<LPObject*> getActorList()
  {
    return actorList;
  }

	btDiscreteDynamicsWorld* getDynamicsWorld() {
		return dynamicsWorld;
	}
	void clearActorList() {
		actorList.clear();
	}
  bool
  isOccupied (glm::vec3 spot);
  bool
  isSniperColliding (glm::vec3 spot);

private:
  Shader shader;
  list<LPObject*> actorList;
  Actor* creature = nullptr;
  Actor* sniper = nullptr;

  LPUniform lpUniform;


	int tmpCounter;
	glm::vec3 coordinate = glm::vec3(0.0f, 0.0f, 0.0f);

	// Trying out Bullet. These are bullet objects
  btBroadphaseInterface* broadphase = nullptr;
  btDefaultCollisionConfiguration* collisionConfiguration = nullptr;
	btCollisionDispatcher* dispatcher;
  btSequentialImpulseConstraintSolver* solver = nullptr;
  btDiscreteDynamicsWorld* dynamicsWorld = nullptr;

	//temporary for the groundshape:
  btCollisionShape* groundShape = nullptr;
  btDefaultMotionState* groundMotionState = nullptr;
  btRigidBody* groundRigidBody = nullptr;

  int* logOutputPtr;
};

#endif /* SCENE_H_ */
