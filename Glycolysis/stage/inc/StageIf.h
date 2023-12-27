/*
 * Stage.h
 *
 *  Created on: Jul 13, 2014
 *      Author: peter
 */

#pragma once
#include "../../inc/ResObj.h"
#include "../../inc/LPObject.h"
#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <vector>
#include <utility>
#include <memory>

	typedef void (*FuncPtr)(void);

class StageIf {
public:
	    StageIf() {};
	    virtual ~StageIf(){};

	virtual void draw() = 0;
  virtual void
  move (std::vector<std::pair<int, int>> collisionDetected, btVector3 normalOnB) = 0;
//	virtual void init() = 0;
//	virtual void init2() = 0;
	virtual void initText() = 0;
	virtual void initSkyBox() = 0;

	// TODO: Put all strings in a struct of its own
//	virtual void initGui(bool show_test_window, bool show_another_window,
//	             bool show_object_window, ImVec4 clear_color,
//	             char* objInfo1, char* objInfo2, char* objInfo3,
//	             char* sdlInfo1, char* sdlInfo2, char* sdlInfo3,
//	             char* moleculeInfo1, char* moleculeInfo2, char* moleculeInfo3, ImGuiIO io) = 0;

	virtual void moveCreature(glm::vec3 trans) = 0;
	virtual glm::vec3 getTransCreature() = 0;
	virtual void createNewBall(glm::vec3 startPos) = 0;
	virtual void moveCreatureForward(float l) = 0;
	virtual void moveCreatureBack(float l) = 0;
	virtual void rotateCreature(float r, float l) = 0;
	virtual void setStandingCreature() = 0;
	virtual void createFallingCube(glm::vec3 pos, int id) = 0;
	virtual void deleteFallingCube(LPObject *a) = 0;
	virtual void createWallCube(glm::vec3 pos, int id, GLuint local_texture) = 0;

  virtual void
  createWinningArea (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos) = 0;
  virtual void
  createMoleculeSpot(int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos) = 0;
  virtual void
  createSniper (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos) = 0;
  virtual void
  createMazeFloor (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos) = 0;
  virtual void
  createMazeDoorX (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos) = 0;
  virtual void
  createMazeDoorY (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos) = 0;
	virtual void deleteWallCube(LPObject *a) = 0;
	virtual void deleteObject(LPObject *a) = 0;
	virtual void deleteObject(int id) = 0;
	virtual void deleteTextObject(int id) = 0;
	virtual void deleteTextObject(LPObject *a) = 0;
	virtual void createGlucose(glm::vec3 pos, int id, GLuint local_texture) = 0;
	virtual void createQuestionCube(glm::vec3 pos, int id, GLuint local_texture) = 0;
	virtual void createMolecule(glm::vec3 pos, int id, ObjectType obj,
	                    GLuint local_texture,
	                    string mInfo1, string mInfo2, string mInfo3) = 0;
	virtual void createMolecule(glm::vec3 pos,
	                           string mInfo1, string mInfo2, string mInfo3) = 0;
	virtual void createGlucose6Phosphate(glm::vec3 pos, int id, GLuint local_texture) = 0;
	virtual void createFructosePhosphate(glm::vec3 pos, int id, GLuint local_texture) = 0;
	virtual void createHexokinase(glm::vec3 pos, int id, GLuint local_texture) = 0;
	virtual void createPhosphofructokinase(glm::vec3 pos, int id, GLuint local_texture) = 0;
	virtual void createWall(glm::vec3 pos, int id, GLuint local_texture) = 0;
	virtual void createZombie(glm::vec3 pos, int id, GLuint local_texture) = 0;
	virtual void createPlane(glm::vec3 pos, int id, GLuint local_texture) = 0;
	virtual void createPlate(glm::vec3 pos) = 0;
//	virtual void createText(glm::vec3 pos, int id, GLuint local_texture) = 0;
  virtual void createText(glm::vec3 pos, int id, ObjectType objType, GLuint local_texture) = 0;
	virtual void createMenu(int id, list<std::pair<ObjectType, FuncPtr>> objList, glm::vec3 scale, glm::vec3 pos) = 0;
	virtual void createCoordinateLines(glm::vec3 pos, int id) = 0;
	virtual void moveCoordinateLines(glm::vec3 pos, int id) = 0;
	virtual void listText() = 0;
	virtual void saveActorList(list<std::string> *objList) = 0;
	virtual void loadActorList(list<std::string> *objList) = 0;
	virtual btDiscreteDynamicsWorld* getDynamicsWorld() = 0;
	virtual btDiscreteDynamicsWorld* getDynamicsWorldText() = 0;

	virtual LPObject * getObject(int id) = 0;
	virtual LPObject * getTextObject(int id) = 0;
	virtual void addMoleculesOnSide() = 0;
	virtual GLuint getPreparedForDelete () const = 0;
	virtual void setPreparedForDelete (GLuint preparedForDelete) = 0;

	virtual std::map<TextureName, GLuint> getTextureList() = 0;

//  virtual void SetBoneTransform(uint Index, glm::mat4& Transform) = 0;
  virtual std::vector<int> getObjTypeListInUse() = 0;

  virtual std::list<LPObject*> getActorList() = 0;
  virtual std::list<LPObject*> getActorTextList() = 0;
};
