/*
 * StageMock.h
 *
 *  Created on: Apr 1, 2018
 *      Author: peter
 */

#ifndef STAGE_TEST_MOCKS_STAGEMOCK_H_
#define STAGE_TEST_MOCKS_STAGEMOCK_H_

#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <cmath>
#include <cstdio>
#include <gmock/gmock.h>
#include "../../inc/StageIf.h"
#include "../../../inc/ResObj.h"


class StageMock : public StageIf{
  public:
    MOCK_METHOD0(draw, void());
    MOCK_METHOD0(move, void());
    MOCK_METHOD0(init, void());
    MOCK_METHOD0(init2, void());
    MOCK_METHOD0(initText, void());
    MOCK_METHOD0(initSkyBox, void());

//    MOCK_METHOD14(initGui, void (bool , bool ,
//                 bool , ImVec4 ,
//                 char* , char* , char* ,
//                 char* , char* , char* ,
//                 char* , char* , char* , ImGuiIO ));

    MOCK_METHOD1(moveCreature, void(glm::vec3 trans));
    MOCK_METHOD0(getTransCreature, glm::vec3());
    MOCK_METHOD1(createNewBall, void(glm::vec3 startPos));

//    virtual void initGui(bool show_test_window, bool show_another_window,
//                   bool show_object_window, ImVec4 clear_color,
//                   char* objInfo1, char* objInfo2, char* objInfo3,
//                   char* sdlInfo1, char* sdlInfo2, char* sdlInfo3,
//                   char* moleculeInfo1, char* moleculeInfo2, char* moleculeInfo3, ImGuiIO io);

    MOCK_METHOD1(moveCreatureForward, void(float l));
    MOCK_METHOD1(moveCreatureBack, void(float l));
    MOCK_METHOD2(rotateCreature, void(float r, float l));
    MOCK_METHOD0(setStandingCreature, void());
    MOCK_METHOD2(createFallingCube, void(glm::vec3 pos, int id));
    MOCK_METHOD1(deleteFallingCube, void(LPObject *a));
    MOCK_METHOD3(createWallCube, void(glm::vec3 pos, int id, GLuint local_texture));
    MOCK_METHOD1(deleteWallCube, void(LPObject *a));
    MOCK_METHOD1(deleteObject, void(LPObject *a));
    MOCK_METHOD1(deleteObject, void(int id));
    MOCK_METHOD1(deleteTextObject, void (int id));
    MOCK_METHOD1(deleteTextObject, void(LPObject *a));
    MOCK_METHOD3(createGlucose, void(glm::vec3 pos, int id, GLuint local_texture));
    MOCK_METHOD3(createQuestionCube, void(glm::vec3 pos, int id, GLuint local_texture));
    MOCK_METHOD7(createMolecule, void(glm::vec3 pos, int id, ObjectType obj,
                          GLuint local_texture,
                          string mInfo1, string mInfo2, string mInfo3));

    MOCK_METHOD4(createMolecule, void(glm::vec3 pos,
                                 string mInfo1, string mInfo2, string mInfo3));
    MOCK_METHOD3(createGlucose6Phosphate, void(glm::vec3 pos, int id, GLuint local_texture));
    MOCK_METHOD3(createFructosePhosphate, void(glm::vec3 pos, int id, GLuint local_texture));
    MOCK_METHOD3(createHexokinase, void(glm::vec3 pos, int id, GLuint local_texture));
    MOCK_METHOD3(createPhosphofructokinase, void(glm::vec3 pos, int id, GLuint local_texture));
    MOCK_METHOD3(createWall, void(glm::vec3 pos, int id, GLuint local_texture));
    MOCK_METHOD3(createZombie, void(glm::vec3 pos, int id, GLuint local_texture));
    MOCK_METHOD3(createPlane, void(glm::vec3 pos, int id, GLuint local_texture));
    MOCK_METHOD1(createPlate, void(glm::vec3 pos));
    MOCK_METHOD3(createText, void(glm::vec3 pos, int id, GLuint local_texture));
  MOCK_METHOD4(createText, void(glm::vec3 pos, int id, ObjectType objType, GLuint local_texture));
    MOCK_METHOD4(createMenu, void(int id, list<std::pair<ObjectType, FuncPtr>> objList, glm::vec3 scale, glm::vec3 pos));
    MOCK_METHOD2(createCoordinateLines, void(glm::vec3, int));

    MOCK_METHOD2(moveCoordinateLines, void(glm::vec3 pos, int id));
    MOCK_METHOD0(listText, void());
    MOCK_METHOD1(saveActorList, void(list<std::string> *objList));
    MOCK_METHOD1(loadActorList, void(list<std::string> *objList));
    MOCK_METHOD0(getDynamicsWorld, btDiscreteDynamicsWorld*());
    MOCK_METHOD0(getDynamicsWorldText, btDiscreteDynamicsWorld*());
    MOCK_METHOD1(getObject, LPObject *(int id));
    MOCK_METHOD1(getTextObject, LPObject * (int id));
    MOCK_METHOD0(addMoleculesOnSide, void());
    MOCK_CONST_METHOD0(getPreparedForDelete, GLuint());
    MOCK_METHOD1(setPreparedForDelete, void(GLuint preparedForDelete));
  MOCK_METHOD6(createWinningArea ,void(int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos));

  MOCK_METHOD2(move, void(std::vector<std::pair<int, int> >, btVector3));
  MOCK_METHOD6(createSniper, void(int, ObjectType, glm::vec3, glm::vec3, int, glm::vec3));
  MOCK_METHOD6(createMazeFloor, void(int, ObjectType, glm::vec3, glm::vec3, int, glm::vec3));
  MOCK_METHOD6(createMazeDoorX, void(int, ObjectType, glm::vec3, glm::vec3, int, glm::vec3));
  MOCK_METHOD6(createMazeDoorY, void(int, ObjectType, glm::vec3, glm::vec3, int, glm::vec3));
  MOCK_METHOD0(getTextureList, std::map<TextureName, unsigned int> ());
  MOCK_METHOD0(getObjTypeListInUse, std::vector<int>());
  MOCK_METHOD0(getActorList, list<LPObject*>());
  MOCK_METHOD0(getActorTextList, list<LPObject*>());



};



#endif /* STAGE_TEST_MOCKS_STAGEMOCK_H_ */
