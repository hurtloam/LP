/*
 * Stage.h
 *
 *  Created on: Jul 13, 2014
 *      Author: peter
 */

#pragma once

#include "../../inc/ObjectFactory.h"
#include "../../inc/ResObj.h"
#include "../../inc/View.h"
#include "../../inc/LPWatch.h"
#include "../../inc/Scene.h"
//#include "../gui/examples/sdl_opengl3_example/imgui_impl_sdl_gl3.h"

#include "../../inc/LuaIf.h"
#include "../../terminal/inc/LuaInteractive.h"
#include "../../eventstate/inc/EventState.h"
#include "StageIf.h"

typedef void
(*FuncPtr) (void);

enum stageKeys {
  stage_left, stage_right, stage_forward, stage_backward, stage_up, stage_down, stage_still, stage_north_west, stage_north_east
};


class Stage : public StageIf {
public:
	Stage() = delete;
  Stage (LPWatch* watch, ResObj& resObj, View& view);
	virtual ~Stage();

//  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
	void draw();
  void
  move (std::vector<std::pair<int, int>> collisionDetected, btVector3 normalOnB);
//	void init();
//	void init2();
  void
  init_maze ();
  void init2();
	void initSplashScreen();
	void reloadActorList();
	void deleteActorList();
	void deleteActorListForSplashScreen();
	void initText();
	void initSkyBox();
//	void initGui(bool show_test_window, bool show_another_window,
//	             bool show_object_window, ImVec4 clear_color,
//	             char* objInfo1, char* objInfo2, char* objInfo3,
//	             char* sdlInfo1, char* sdlInfo2, char* sdlInfo3,
//	             char* moleculeInfo1, char* moleculeInfo2, char* moleculeInfo3, ImGuiIO io);

	void moveCreature(glm::vec3 trans);
	glm::vec3 getTransCreature();
	void createNewBall(glm::vec3 startPos);
	void createBall(int id, glm::vec3 startPos, int texture);

	void moveCreatureForward(float l);
	void moveCreatureBack(float l);
	void rotateCreature(float r, float l);

  int
  getProgramId ();

  Scene*
  getScene ();
	void setStandingCreature();

	void createFallingCube(glm::vec3 pos, int id);
	void deleteFallingCube(LPObject *a);

  void
  createMazeFloor (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos);

  void
  createWinningArea (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos);

  void
  createMoleculeSpot(int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos);

  void createTextSpot(int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos);

  void
  createMazeDoorX (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos);
  void
  createMazeDoorY (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos);
	void createWallCube(glm::vec3 pos, int id, GLuint local_texture);
	void deleteWallCube(LPObject *a);

	void deleteObject(LPObject *a);

	void deleteObject(int id);

	void deleteTextObject(LPObject *a);
	void deleteTextObject(int id);

	void createGlucose(glm::vec3 pos, int id, GLuint local_texture);
	void createQuestionCube(glm::vec3 pos, int id, GLuint local_texture);
	void createMolecule(glm::vec3 pos, int id, ObjectType obj,
	                    GLuint local_texture,
	                    string mInfo1, string mInfo2, string mInfo3);

  void createAnimalCell(glm::vec3 scaling, glm::vec3 pos, int id, GLuint local_texture, string mInfo1, string mInfo2, string mInfo3);

  void createArrow(glm::vec3 scaling, glm::vec3 pos, int id, ObjectType objType, GLuint local_texture, string mInfo1, string mInfo2, string mInfo3);

	void createMolecule(glm::vec3 pos,
	                           string mInfo1, string mInfo2, string mInfo3);

	void createGlucose6Phosphate(glm::vec3 pos, int id, GLuint local_texture);

	void createFructosePhosphate(glm::vec3 pos, int id, GLuint local_texture);

	void createHexokinase(glm::vec3 pos, int id, GLuint local_texture);

	void createPhosphofructokinase(glm::vec3 pos, int id, GLuint local_texture);

	void createWall(glm::vec3 pos, int id, GLuint local_texture);

	void createZombie(glm::vec3 pos, int id, GLuint local_texture);

  void
  createSniper (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos);

	void createPlane(glm::vec3 pos, int id, GLuint local_texture);

	void createPlate(glm::vec3 pos);

//	void createText(glm::vec3 pos, int id, GLuint local_texture);

  void createText(glm::vec3 pos, int id, ObjectType objType, GLuint local_texture);


	void createMenu(int id, list<std::pair<ObjectType, FuncPtr>> objList, glm::vec3 scale, glm::vec3 pos);

	void createCoordinateLines(glm::vec3 pos, int id);

	void moveCoordinateLines(glm::vec3 pos, int id);

	void listText();

	void saveActorList(list<std::string> *objList) {
		return scene->saveActorList(objList);}

	void loadActorList(list<std::string> *objList);

//	void Stage::rotateObject(float r, float l);

	btDiscreteDynamicsWorld* getDynamicsWorld() {
		return scene->getDynamicsWorld();
	}

	btDiscreteDynamicsWorld* getDynamicsWorldText() {
			return scene_txt->getDynamicsWorld();
		}

//	btDiscreteDynamicsWorld* getDynamicsWorldSkyBox() {
//			return scene_skyBox->getDynamicsWorld();
//		}

	LPObject* getObject(int id);
	LPObject* getTextObject(int id);

  bool isAnyInCorrectPosition(ObjectType objType);
  LPObject* getObjInCorrectPosition(ObjectType objType);
  std::vector<LPObject*> getTextObjectFromObjType(ObjectType objType);

	LPObject* getSplashScreenObject(int id);
	LPObject* getSplashScreenObject_txt(int id);

	void addMoleculesOnSide();

	GLuint getPreparedForDelete () const
	{
	  return preparedForDelete;
	}

	void setPreparedForDelete (GLuint preparedForDelete)
	{
	  this->preparedForDelete = preparedForDelete;
	}


  void
  moveFPersonFwd (glm::vec3 direction, glm::vec3 right, bool wasd[7]);
  void
  moveFPersonBack (glm::vec3 direction, glm::vec3 right, bool wasd[7]);
  void
  moveFPersonLeft (glm::vec3 direction, glm::vec3 right, bool wasd[7]);
  void
  moveFPersonRight (glm::vec3 direction, glm::vec3 right, bool wasd[7]);

  void
  moveFPersonJump (glm::vec3 direction, glm::vec3 right);

  void
  stillFPerson ();

//  void SetBoneTransform(uint Index, glm::mat4& Transform);

  std::vector<int> getObjTypeListInUse();
  std::list<LPObject*> getActorList();
  std::list<LPObject*> getActorTextList();



  Scene *scene = nullptr;
  Scene *scene_txt = nullptr;
  Scene *splashScene = nullptr;
  Scene *splashScene_txt = nullptr;
//	Scene *scene_skyBox = NULL;
	ResObj& resObj;
	View& view;
  ObjectFactory* objFactory = nullptr;
  ObjectFactory* objFactory_txt = nullptr;
  ObjectFactory* objFactory_splashTxt = nullptr;

  //textures
	GLuint texture_wood;
	GLuint texture_ice;
	GLuint texture_red_floor;
	GLuint texture_wall;
	GLuint texture_wall_2x32x32;
	GLuint texture_glykolysen;
	GLuint texture_glykolysen_plane;
	GLuint texture_glykolysen_text;
	GLuint texture_arrow_red;
	GLuint texture_plane_skar;
  GLuint texture_dirt;
  GLuint texture_zombie;
  GLuint texture_sniper;

  LuaIf *luaIf = nullptr;
//  LuaInteractive* luaInteractive;

  GLuint texture_sandstone;
	GLuint texture_sandstone4;
	GLuint texture_sandstone3;
	GLuint texture_sandstone5;
  GLuint texture_sandstone5_normal;
  GLuint texture_sandstone5_specular;
	GLuint texture_question2;

	GLuint texture_blue24;



	std::map<TextureName, GLuint> textureList;

	std::map<TextureName, GLuint> getTextureList();
//  bool wasd[7] = { false, false, false, false, false, false, false };
//  EventState eventState;
private:
  LPWatch* watch = nullptr;
	GLuint preparedForDelete = 0;
  int *logOutputPtr = nullptr;
	GLuint texture_skybox;

};

