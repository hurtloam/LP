/*
scene-> * Stage.cpp
 *
 *  Created on: Jul 13, 2014
 *      Author: peter
 */

#include "../../eventstate/inc/EventState.h"
#include "../../inc/Actor.h"
#include "../../inc/Arrow.h"
#include "../../inc/Ball.h"
#include "../../inc/CoordinateLines.h"
#include "../../inc/Creature.h"
#include "../../inc/FPerson.h"
#include "../../inc/FPerson.h"
#include "../../inc/FallingCube.h"
#include "../../inc/Fructose6Phosphate.h"
#include "../../inc/Glucose.h"
#include "../../inc/Glucose6Phosphate.h"
#include "../../inc/Hexokinase.h"
#include "../../inc/LPDebugDraw.h"
#include "../../inc/LPWatch.h"
#include "../../inc/Landscape.h"
#include "../../inc/LightSource.h"
#include "../../inc/MazeDoorX.h"
#include "../../inc/MazeDoorY.h"
#include "../../inc/MazeFloor.h"
#include "../../inc/MenuContainer.h"
#include "../../inc/MenuItem.h"
#include "../../inc/Mitochondria.h"
#include "../../inc/Molecule.h"
#include "../../inc/NoSign.h"
#include "../../inc/ObjectFactory.h"
#include "../../inc/Phosphofructokinase.h"
#include "../../inc/Plane.h"
#include "../../inc/Plate.h"
#include "../../inc/SignPost.h"
#include "../../inc/SignPost2.h"
#include "../../inc/Sniper.h"
#include "../../inc/TextMenuItem.h"
#include "../../inc/TextObject.h"
#include "../../inc/TextSpot.h"
#include "../../inc/Two_PhosphoGlycerate.h"
#include "../../inc/Wall.h"
#include "../../inc/WallCube.h"
#include "../../inc/WooddenCube.h"
#include "../../inc/WooddenCube2.h"
#include "../../inc/logging.h"
#include "../../inc/texture.hpp"
#include "../inc/Stage.h"
#include "../../inc/MoleculeSpot.h"
#include "LinearMath/btIDebugDraw.h"
#include <cmath>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <utility>
#include <vector>

using namespace std;
//using namespace platformBase;


Stage::Stage (LPWatch* watch, ResObj& resObj, View& view) :
    watch (watch), resObj (resObj), view (view) {
	logOutputPtr = new int(1);
	setLogging(logOutputPtr, 1);

  luaIf = new LuaIf(this, nullptr);

  // A Separate scene for all text objects. It will have different shaders apart from the other objects.
  scene_txt = new Scene("shaders/text.v.glsl", "shaders/text.f.glsl");
  scene = new Scene("shaders/StandardShading.vertexshader", "shaders/StandardShading.fragmentshader");

  objFactory = new ObjectFactory(watch, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(), scene->getLightId(), scene->getTextureId());
  objFactory_txt = new ObjectFactory(watch, resObj, view, scene_txt->getProgramId(), scene_txt->getMatrixId(), scene_txt->getViewMatrixId(), scene_txt->getModelMatrixId(), scene_txt->getLightId(), scene_txt->getTextureId());
}

Stage::~Stage() {
  std::cout << "ENTER ~Stage()" << std::endl;
  if (splashScene != nullptr) {
    delete splashScene;
    std::cout << "splashScene is deleted" << std::endl;
  }
  std::cout << "1";
  if (splashScene_txt != nullptr) {
    delete splashScene_txt;
    std::cout << "splashScene_txt is deleted" << std::endl;
  }
  std::cout << "2";
  if (objFactory_splashTxt != nullptr) {
    delete objFactory_splashTxt;
    std::cout << "objFactory_splashTxt is deleted" << std::endl;
  }
  std::cout << "3";
  if (objFactory != nullptr) {
    delete objFactory;
    std::cout << "objFactory is deleted" << std::endl;
  }
  std::cout << "4";
  if (objFactory_txt != nullptr) {
    delete objFactory_txt;
    std::cout << "objFactory_txt is deleted" << std::endl;
  }
  std::cout << "5";
  if (luaIf != nullptr) {
    delete luaIf;
    std::cout << "luaIf is deleted" << std::endl;
  }
  std::cout << "6";
  if (scene_txt != nullptr) {
    delete scene_txt;
    std::cout << "scene_txt is deleted" << std::endl;
  }
  std::cout << "7";
  if (scene != nullptr) {
    delete scene;
    std::cout << "scene is deleted" << std::endl;
  }
  std::cout << "8";
  if (logOutputPtr != nullptr) {
    delete logOutputPtr;
    std::cout << "logOutputPtr is deleted" << std::endl;
  }
  std::cout << "9";
  std::cout << "END ~Stage()" << std::endl;
}

void Stage::initSplashScreen() {
	splashScene = new Scene("shaders/StandardShading.vertexshader", "shaders/StandardShading.fragmentshader");
	splashScene_txt = new Scene("shaders/text.v.glsl", "shaders/text.f.glsl");
	texture_sandstone3 = loadBMP_custom("resources/obj/stone_brick/stonen_50_COLOR.bmp");
//  resObj.loadStaticObjFiles("resources/obj/plate/plate_round_4x8.blend", plate, "plate");
  resObj.loadStaticObjFiles("resources/obj/glucose/alpha_D_glucopyranose.obj", alpha_D_glucopyranose, "alpha_D_glucopyranose", "alpha_D_glucopyranose");
	  splashScene->addActor(new Plate(96003,
	      glm::vec3(1.0f,1.0f,1.0f),
//		  plate,
	      alpha_D_glucopyranose,
	      texture_sandstone3,
		  glm::vec3(-1.0,15.0,0.0),
		  watch,
	      resObj,
	      view,
          splashScene->getLPUniform()));


	  objFactory_splashTxt = new ObjectFactory(
	      watch,
	        resObj,
	        view,
			splashScene_txt->getProgramId(), splashScene_txt->getMatrixId(), splashScene_txt->getViewMatrixId(), splashScene_txt->getModelMatrixId(), splashScene_txt->getLightId(),
      splashScene_txt->getTextureId());

	  splashScene_txt->addActor(objFactory_splashTxt->createInstance(1,
	      glm::vec3(1.0f, 1.0f, 1.0f),
	      txt_BIOMOLCRAFT,
	      lp_class::c_text,
	      texture_plane_skar,
	      glm::vec3(0.0f, 15.0, 13.0)));

	  const GLfloat color[4] = {0.5, 0.5, 0.5, 1.0};
	  	  getSplashScreenObject_txt(1)->setColor(color);
	  splashScene_txt->addActor(objFactory_splashTxt->createInstance(2,
	      glm::vec3(1.0f, 1.0f, 1.0f),
	      txt_TITLE,
	      lp_class::c_text,
	      texture_plane_skar,
	      glm::vec3(0.0f, 13.8, 13.0)));
	  getSplashScreenObject_txt(2)->setColor(color);

}


void Stage::init2() {

//  luaIf = new LuaIf(this, nullptr);
//
//  // A Separate scene for all text objects. It will have different shaders apart from the other objects.
//  scene_txt = new Scene("shaders/text.v.glsl", "shaders/text.f.glsl");
//  scene = new Scene("shaders/StandardShading.vertexshader", "shaders/StandardShading.fragmentshader");
//
//  objFactory = new ObjectFactory(watch, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(), scene->getLightId(), scene->getTextureId());
//  objFactory_txt = new ObjectFactory(watch, resObj, view, scene_txt->getProgramId(), scene_txt->getMatrixId(), scene_txt->getViewMatrixId(), scene_txt->getModelMatrixId(), scene_txt->getLightId(), scene_txt->getTextureId());

  texture_plane_skar = loadBMP_custom("resources/textures/uvlayout_grisskar.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_plane_skar, texture_plane_skar));

  texture_sandstone = loadBMP_custom("resources/textures/sand_stone.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_sandstone, texture_sandstone));

  texture_blue24 = loadBMP_custom("resources/textures/blue-24.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_blue24, texture_blue24));

  texture_skybox  = loadBMP_custom("resources/obj/skybox/SkyBox-Clouds-Wispy-Dawn.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_skybox, texture_skybox));

  texture_sandstone3 = loadBMP_custom("resources/obj/stone_brick/stonen_50_COLOR.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_sandstone3, texture_sandstone3));

//  texture_red_floor = loadBMP_custom("resources/textures/uvlayout_pattern1.bmp");  // the color red
  texture_red_floor = loadBMP_custom("resources/textures/blue-24.bmp");  // the color red
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_red_floor, texture_red_floor));

  texture_sandstone5 = loadBMP_custom("resources/textures/Cliff.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_sandstone5, texture_sandstone5));

//    string mInfo1 = "Glucose";
//    string mInfo2 = "";
//    string mInfo3 = "";
//
////  createHexokinase(glm::vec3(-5.0f, -10.0f, 3.0f), lp_glucose++, 0);
//  mInfo1 = "Hexokinase";
//  mInfo2 = " ";
//  mInfo3 = " ";
//  createMolecule(glm::vec3(-5.0f, 10.0f, 3.0f), ++lp_glucose, hexokinase, 0, mInfo1, mInfo2, mInfo3);
//
//  mInfo1 = "phosphoglucoseisomerase";
//  mInfo2 = " ";
//  mInfo3 = " ";
//  createMolecule(glm::vec3(-5.0f, 15.0f, 1.0f), ++lp_glucose, phosphoglucoseisomerase, 0, mInfo1, mInfo2, mInfo3);
//
//  mInfo1 = "enolase";
//  mInfo2 = " ";
//  mInfo3 = " ";
//  createMolecule(glm::vec3(-5.0f, 20.0f, 1.0f), ++lp_glucose, enolase, 0, mInfo1, mInfo2, mInfo3);

  float zCoord = 0.0f;
  SDL_Log("Inside Stage::init2  at beginning of STAGE 1");

  luaIf->config("Debug/Glycolysis_config.lua");

//  createMoleculeSpot(c_molecule_spot + 1, molecule_spot, glm::vec3(2.0f, 0.2f, 0.01f), glm::vec3(1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3(-1.0f, 10.0, 0.1f));
//  createMoleculeSpot(c_molecule_spot + 2, molecule_spot, glm::vec3(2.0f, 0.2f, 0.01f), glm::vec3(1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3(-1.0f, 11.0, 0.1f));
//  createMoleculeSpot(c_molecule_spot + 3, molecule_spot, glm::vec3(2.0f, 0.2f, 0.01f), glm::vec3(1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3(-1.0f, 11.0, 0.1f));
//  createMoleculeSpot(c_molecule_spot + 4, molecule_spot, glm::vec3(2.0f, 0.2f, 0.01f), glm::vec3(1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3(-1.0f, 11.0, 0.1f));
//  createMoleculeSpot(c_molecule_spot + 5, molecule_spot, glm::vec3(2.0f, 0.2f, 0.01f), glm::vec3(1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3(-1.0f, 11.0, 0.1f));
//  createMoleculeSpot(c_molecule_spot + 6, molecule_spot, glm::vec3(2.0f, 0.2f, 0.01f), glm::vec3(1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3(-1.0f, 11.0, 0.1f));
//  createMoleculeSpot(c_molecule_spot + 7, molecule_spot, glm::vec3(2.0f, 0.2f, 0.01f), glm::vec3(1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3(-1.0f, 11.0, 0.1f));
//  createMoleculeSpot(c_molecule_spot + 8, molecule_spot, glm::vec3(2.0f, 0.2f, 0.01f), glm::vec3(1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3(-1.0f, 11.0, 0.1f));
//  createMoleculeSpot(c_molecule_spot + 9, molecule_spot, glm::vec3(2.0f, 0.2f, 0.01f), glm::vec3(1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3(-1.0f, 11.0, 0.1f));
//  createMoleculeSpot(c_molecule_spot + 10, molecule_spot, glm::vec3(2.0f, 0.2f, 0.01f), glm::vec3(1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3(-1.0f, 11.0, 0.1f));
//  createMoleculeSpot(c_molecule_spot + 11, molecule_spot, glm::vec3(2.0f, 0.2f, 0.01f), glm::vec3(1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3(-1.0f, 11.0, 0.1f));

//  addMoleculesOnSide();



//   scene_txt->addActor(objFactory_txt->createInstance(36120,
//      glm::vec3(1.0f, 1.0f, 1.0f),
//      objList,
//      lp_class::c_menuContainer,
//      texture_plane_skar,
//      glm::vec3(0.0, 0.0, 0.0)));
//
//  scene_txt->addActor(objFactory_txt->createInstance(36002,
//      glm::vec3(1.0f, 1.0f, 1.0f),
//      objList,
//      lp_class::c_menuContainer,
//      texture_plane_skar,
//      glm::vec3(-1.202, 20.14, 0.0)));
//
//  scene_txt->addActor(objFactory_txt->createInstance(36016,
//        glm::vec3(1.0f, 1.0f, 1.0f),
//        objList,
//        lp_class::c_menuContainer,
//        texture_plane_skar,
//        glm::vec3(1.0, 20.5, 0.0)));
//
//  scene_txt->addActor(objFactory_txt->createInstance(36017,
//          glm::vec3(1.0f, 1.0f, 1.0f),
//          objList,
//          lp_class::c_menuContainer,
//          texture_plane_skar,
//          glm::vec3(1.0, 20.25, 0.0)));

//  scene->addActor(objFactory->createInstance(c_arrow + 1, glm::vec3(0.25f, 0.25f, 0.25f), arrow_rectangle_down_single1, lp_class::c_arrow, texture_blue24, glm::vec3(0.02, 20.3f, zCoord)));

  // ----------------------------- NEXT

//  scene_txt->addActor(objFactory_txt->createInstance(36004,
//        glm::vec3(1.0f, 1.0f, 1.0f),
//        objList,
//        lp_class::c_menuContainer,
//        texture_plane_skar,
//        glm::vec3(-1.1, 18.7, 0.0)));

//    scene->addActor(objFactory->createInstance(c_arrow + 2,
//        glm::vec3(0.25f, 0.25f, 0.25f),
//          arrow_rectangle_down_up,
//          lp_class::c_arrow,
//          texture_blue24,
//          glm::vec3(0.0f, 18.7f,zCoord)));


    // ----------------------------- NEXT

//    scene_txt->addActor(objFactory_txt->createInstance(36007,
//          glm::vec3(1.0f, 1.0f, 1.0f),
//          objList,
//          lp_class::c_menuContainer,
//          texture_plane_skar,
//          glm::vec3(-1.1, 17.4, 0.0)));
//
//    scene_txt->addActor(objFactory_txt->createInstance(36116,
//          glm::vec3(1.0f, 1.0f, 1.0f),
//          objList,
//          lp_class::c_menuContainer,
//          texture_plane_skar,
//          glm::vec3(1.095, 17.5, 0.0)));
//
//    scene_txt->addActor(objFactory_txt->createInstance(36117,
//            glm::vec3(1.0f, 1.0f, 1.0f),
//            objList,
//            lp_class::c_menuContainer,
//            texture_plane_skar,
//            glm::vec3(1.102, 17.25, 0.0)));


//      scene->addActor(objFactory->createInstance(c_arrow + 3,
//          glm::vec3(0.25f, 0.25f, 0.25f),
//            arrow_rectangle_down_single1,
//            lp_class::c_arrow,
//            texture_sandstone,
//            glm::vec3(0.0f, 17.3f,zCoord)));


//      scene_txt->addActor(objFactory_txt->createInstance(36009,
//              glm::vec3(1.0f, 1.0f, 1.0f),
//              objList,
//              lp_class::c_menuContainer,
//              texture_plane_skar,
//              glm::vec3(0.85, 15.7, 0.0)));

//      scene->addActor(objFactory->createInstance(c_arrow + 4,
//          glm::vec3(0.25f, 0.25f, 0.25f),
//                  arrow_rectangle_down_side_long,
//                  lp_class::c_arrow,
//                  texture_sandstone,
//                  glm::vec3(0.0f, 15.7f,zCoord)));


//      scene_txt->addActor(objFactory_txt->createInstance(36012,
//                glm::vec3(1.0f, 1.0f, 1.0f),
//                objList,
//                lp_class::c_menuContainer,
//                texture_plane_skar,
//                glm::vec3(-1.1, 15.25, 0.0)));


//      scene->addActor(objFactory->createInstance(c_arrow + 5,
//          glm::vec3(0.25f, 0.25f, 0.25f),
//                      arrow_rectangle_down_up_45_1,
//                      lp_class::c_arrow,
//                      texture_sandstone,
//                      glm::vec3(-0.51f, 15.5f,zCoord)));


//--- STAGE 2 -------
//      cout << "Inside Stage::init2  at STAGE 2" << endl;
//      scene_txt->addActor(objFactory_txt->createInstance(36021,
//                         glm::vec3(1.0f, 1.0f, 1.0f),
//                         objList,
//                         lp_class::c_menuContainer,
//                         texture_plane_skar,
//                         glm::vec3(-1.51f, 13.5f,0.0f)));
//
//
//      scene_txt->addActor(objFactory_txt->createInstance(36018,
//                         glm::vec3(1.0f, 1.0f, 1.0f),
//                         objList,
//                         lp_class::c_menuContainer,
//                         texture_plane_skar,
//                         glm::vec3(1.1, 13.7, 0.0)));
//
//
//      scene_txt->addActor(objFactory_txt->createInstance(36019,
//                         glm::vec3(1.0f, 1.0f, 1.0f),
//                         objList,
//                         lp_class::c_menuContainer,
//                         texture_plane_skar,
//                         glm::vec3(1.1, 13.4, 0.0)));


//      scene->addActor(objFactory->createInstance(c_arrow + 6,
//           glm::vec3(0.25f, 0.25f, 0.25f),
//                       arrow_rectangle_down_up_bent_long,
//                       lp_class::c_arrow,
//                       texture_sandstone,
//                       glm::vec3(0.0f, 13.5f,zCoord)));


//      scene_txt->addActor(objFactory_txt->createInstance(36025,
//                          glm::vec3(1.0f, 1.0f, 1.0f),
//                          objList,
//                          lp_class::c_menuContainer,
//                          texture_plane_skar,
//                          glm::vec3(-1.33f, 12.20f,0.0f)));
//
//
//       scene_txt->addActor(objFactory_txt->createInstance(36217,
//                          glm::vec3(1.0f, 1.0f, 1.0f),
//                          objList,
//                          lp_class::c_menuContainer,
//                          texture_plane_skar,
//                          glm::vec3(1.1, 12.55, 0.0)));
//
//
//       scene_txt->addActor(objFactory_txt->createInstance(36216,
//                          glm::vec3(1.0f, 1.0f, 1.0f),
//                          objList,
//                          lp_class::c_menuContainer,
//                          texture_plane_skar,
//                          glm::vec3(1.1, 12.2, 0.0)));


//      scene->addActor(objFactory->createInstance(c_arrow + 7,
//           glm::vec3(0.25f, 0.25f, 0.25f),
//                       arrow_rectangle_down_up_bent,
//                       lp_class::c_arrow,
//                       texture_sandstone,
//                       glm::vec3(0.0f, 12.3f,zCoord)));


//      scene_txt->addActor(objFactory_txt->createInstance(36028,
//                         glm::vec3(1.0f, 1.0f, 1.0f),
//                         objList,
//                         lp_class::c_menuContainer,
//                         texture_plane_skar,
//                         glm::vec3(-1.3, 11.2, 0.0)));

//      scene->addActor(objFactory->createInstance(c_arrow + 8,
//           glm::vec3(0.25f, 0.25f, 0.25f),
//                       arrow_rectangle_down_up,
//                       lp_class::c_arrow,
//                       texture_sandstone,
//                       glm::vec3(0.0f, 11.2f,zCoord)));

//      scene_txt->addActor(objFactory_txt->createInstance(36031,
//                         glm::vec3(1.0f, 1.0f, 1.0f),
//                         objList,
//                         lp_class::c_menuContainer,
//                         texture_plane_skar,
//                         glm::vec3(-1.3, 9.9, 0.0)));
//
//
//      scene_txt->addActor(objFactory_txt->createInstance(36020,
//                         glm::vec3(1.0f, 1.0f, 1.0f),
//                         objList,
//                         lp_class::c_menuContainer,
//                         texture_plane_skar,
//                         glm::vec3(1.1, 9.8, 0.0)));

//      scene->addActor(objFactory->createInstance(c_arrow + 9,
//           glm::vec3(0.25f, 0.25f, 0.25f),
//                       arrow_rectangle_down_up_halfside_bent,
//                       lp_class::c_arrow,
//                       texture_sandstone,
//                       glm::vec3(0.0f, 9.9f,zCoord)));

//      scene_txt->addActor(objFactory_txt->createInstance(36033,
//                          glm::vec3(1.0f, 1.0f, 1.0f),
//                          objList,
//                          lp_class::c_menuContainer,
//                          texture_plane_skar,
//                          glm::vec3(-1.3, 8.8, 0.0)));
//
//      scene_txt->addActor(objFactory_txt->createInstance(36317,
//                          glm::vec3(1.0f, 1.0f, 1.0f),
//                          objList,
//                          lp_class::c_menuContainer,
//                          texture_plane_skar,
//                          glm::vec3(1.1, 8.95, 0.0)));
//
//
//       scene_txt->addActor(objFactory_txt->createInstance(36316,
//                          glm::vec3(1.0f, 1.0f, 1.0f),
//                          objList,
//                          lp_class::c_menuContainer,
//                          texture_plane_skar,
//                          glm::vec3(1.1, 8.65, 0.0)));


//       scene->addActor(objFactory->createInstance(c_arrow + 10,
//            glm::vec3(0.25f, 0.25f, 0.25f),
//                        arrow_rectangle_down_single1,
//                        lp_class::c_arrow,
//                        texture_sandstone,
//                        glm::vec3(0.0f, 8.7f,zCoord)));




////   Create Title
//  scene_txt->addActor(new TextObject(++lp_text,
//            glm::vec3(1.0f, 1.0f, 1.0f),
//            txt_TITLE,
//            texture_red_floor,
//            glm::vec3(-2.29, 20.63, 0.5),
//            resObj,
//            view,
//            scene_txt->getProgramId(),
//            scene_txt->getMatrixId(),
//            scene_txt->getViewMatrixId(),
//            scene_txt->getModelMatrixId(),
//            scene_txt->getLightId(),
//            scene_txt->getTextureId()));



//  createMolecule(glm::vec3(-3.25f, -170.0f, -88.0f), ++lp_glucose, animal_cell, 0, animalInfo1, animalInfo2, animalInfo3);



//    scene->addActor(new Mitochondria(++lp_glucose, glm::vec3(2.5f, 2.5f, 2.5f), animal_cell, texture_sandstone,
//                                     glm::vec3(-23.25f, -94.5f, -68.0f),
//      glm::vec3(-3.25f, -170.0f, -88.0f), resObj, view, scene->getLPUniform());


// Date: 3/7 -19
// temporarily commenting out these to make it quicker to start application during testing
//  string animalInfo1 = "Animal Cell";
//  string animalInfo2 = "";
//  string animalInfo3 = "";
//  createMolecule(glm::vec3(-2.5f, 2.5f, 2.5f), ++lp_glucose, animal_cell, 0, animalInfo1, animalInfo2, animalInfo3);
//    scene->addActor(new Landscape(++lp_menuContainer,
//    								 glm::vec3(100.0f, 25.0f, 100.0f),
////                                     glm::vec3(2.5f, 2.5f, 2.5f),
//                                     landscape,
//                                     texture_sandstone,
//									 glm::vec3(0.0f, -100.0f,0.0f),
//									                   watch,
//                                     resObj,
//                                     view,
//                                     scene->getLPUniform()));

}


void
Stage::init_maze ()
{



  // A Separate scene for all text objects. It will have different shaders apart from the other objects.
//  scene_txt = new Scene ("shaders/text.v.glsl", "shaders/text.f.glsl");
//  scene = new Scene ("shaders/StandardShading.vertexshader",
//                     "shaders/StandardShading.fragmentshader");
//
  scene = new Scene("shaders/StandardShading.vertexshader",
                     "shaders/StandardShading.fragmentshader");


  objFactory = new ObjectFactory (watch, resObj, view, scene->getProgramId (),
                                  scene->getMatrixId (),
                                  scene->getViewMatrixId (),
                                  scene->getModelMatrixId (),
                                  scene->getLightId (), scene->getTextureId ());

//  objFactory_txt = new ObjectFactory (resObj, view, scene_txt->getProgramId (),
//                                      scene_txt->getMatrixId (),
//                                      scene_txt->getViewMatrixId (),
//                                      scene_txt->getModelMatrixId (),
//                                      scene_txt->getLightId (),
//                                      scene_txt->getTextureId ());

  texture_plane_skar = loadBMP_custom ("resources/textures/uvlayout_grisskar.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_plane_skar, texture_plane_skar));
  texture_sandstone = loadBMP_custom ("resources/textures/sand_stone.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_sandstone, texture_sandstone));

  texture_blue24 = loadBMP_custom ("resources/textures/blue-24.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_blue24, texture_blue24));

  texture_skybox = loadBMP_custom ("resources/obj/skybox/SkyBox-Clouds-Wispy-Dawn.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_skybox, texture_skybox));

  texture_sandstone3 = loadBMP_custom ("resources/obj/stone_brick/stonen_50_COLOR.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_sandstone3, texture_sandstone3));

  texture_wood = loadBMP_custom ("resources/textures/uvlayout_pattern1_TEST.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_wood, texture_wood ));

  //texture_sandstone5 = loadBMP_custom ("resources/textures/Cliff.bmp");
//  texture_sandstone5 = loadBMP_custom ("resources/obj/medieval/labyrinth/wall.bmp");
  texture_sandstone5 = loadBMP_custom ("resources/textures/wall2.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_sandstone5, texture_sandstone5));

  texture_sandstone5_normal = loadBMP_custom ("resources/textures/CliffJagged004_NRM_3K.jpg.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_sandstone5_normal, texture_sandstone5_normal));

  texture_sandstone5_specular = loadBMP_custom ("resources/textures/CliffJagged004_GLOSS_3K.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_sandstone5_specular, texture_sandstone5_specular));



  texture_sniper = loadBMP_custom ("resources/obj/sniper/diffuse_packed2.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_sniper, texture_sniper));

  texture_red_floor = loadBMP_custom ("resources/textures/uvlayout_pattern1.bmp");  // the color red
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_red_floor, texture_red_floor));

  texture_dirt = loadBMP_custom ("resources/textures/dirt_tracks/GroundTireTracks001/3K/GroundTireTracks001_REFL_3K.bmp");  // dirt tracks
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_dirt, texture_dirt));

  texture_zombie = loadBMP_custom("resources/obj/zombie/zombie2_1/textures/zombie2_packed0_diffuse.bmp");
  textureList.insert(std::pair<TextureName, GLuint>(TextureName::tx_zombie, texture_zombie));




  float zCoord = 0.0f;
//  SDL_Log ("Inside Stage::init_maze  at beginning of STAGE 1");
  TRACE_INFO("Inside Stage::init_maze  at beginning of STAGE 1");
  string mInfo1 = "Glucose";
  string mInfo2 = "";
  string mInfo3 = "";


//  createPlane (glm::vec3 (0, 0, 0), 24001, texture_sandstone5); // ground floor
//
//  scene->addActor(
//      new Sniper(++lp_sniper, glm::vec3(1.0f, 1.0f, 1.0f), sniper1, 29, texture_sniper, glm::vec3(-5, -1.4, 7), resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(), scene->getLightId(),
//          scene->getTextureId()));


// Adding FPerson object
  scene->addActor(
      new FPerson(1000, glm::vec3(1.0f, 1.0f, 1.0f), cube, 1, texture_red_floor, glm::vec3(8.0, 1.0, 4.0), watch, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(), scene->getLightId(),
          scene->getTextureId()));


//      int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, const ResObj& resObj, const View& view, GLuint programID, GLuint MatrixID,
//                  GLuint ViewMatrixID, GLuint ModelMatrixID, GLuint LightID, GLuint TextureID
//

//  LPObject* tmpZombie = new WallCube(++lp_sniper, glm::vec3(0.1f, 0.1f, 0.1f), zombie, texture_zombie, glm::vec3(8.0, 1.0, -4.0), nullptr, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(),
//      scene->getLightId(), scene->getTextureId());
//  scene->addActor(tmpZombie);
//
//  tmpZombie = new WallCube(++lp_sniper, glm::vec3(0.1f, 0.1f, 0.1f), zombie, texture_zombie, glm::vec3(8.0, 1.0, -4.0), nullptr, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(),
//      scene->getLightId(), scene->getTextureId());
//  scene->addActor(tmpZombie);
//  tmpZombie = new WallCube(++lp_sniper, glm::vec3(0.1f, 0.1f, 0.1f), zombie, texture_zombie, glm::vec3(8.0, 1.0, -4.0), nullptr, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(),
//      scene->getLightId(), scene->getTextureId());
//  scene->addActor(tmpZombie);
//
//  tmpZombie = new WallCube(++lp_sniper, glm::vec3(0.1f, 0.1f, 0.1f), zombie, texture_zombie, glm::vec3(8.0, 1.0, -4.0), nullptr, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(),
//      scene->getLightId(), scene->getTextureId());
//  scene->addActor(tmpZombie);
//  tmpZombie = new WallCube(++lp_sniper, glm::vec3(0.1f, 0.1f, 0.1f), zombie, texture_zombie, glm::vec3(8.0, 1.0, -4.0), nullptr, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(),
//      scene->getLightId(), scene->getTextureId());
//  scene->addActor(tmpZombie);
//  tmpZombie = new WallCube(++lp_sniper, glm::vec3(0.1f, 0.1f, 0.1f), zombie, texture_zombie, glm::vec3(8.0, 1.0, -4.0), nullptr, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(),
//      scene->getLightId(), scene->getTextureId());
//  scene->addActor(tmpZombie);
//  tmpZombie = new WallCube(++lp_sniper, glm::vec3(0.1f, 0.1f, 0.1f), zombie, texture_zombie, glm::vec3(8.0, 1.0, -4.0), nullptr, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(),
//      scene->getLightId(), scene->getTextureId());
//  scene->addActor(tmpZombie);
//  tmpZombie = new WallCube(++lp_sniper, glm::vec3(0.1f, 0.1f, 0.1f), zombie, texture_zombie, glm::vec3(8.0, 1.0, -4.0), nullptr, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(),
//      scene->getLightId(), scene->getTextureId());
//  scene->addActor(tmpZombie);
//  tmpZombie = new WallCube(++lp_sniper, glm::vec3(0.1f, 0.1f, 0.1f), zombie, texture_zombie, glm::vec3(8.0, 1.0, -4.0), nullptr, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(),
//      scene->getLightId(), scene->getTextureId());
//  scene->addActor(tmpZombie);
//  tmpZombie = new WallCube(++lp_sniper, glm::vec3(0.1f, 0.1f, 0.1f), zombie, texture_zombie, glm::vec3(8.0, 1.0, -4.0), nullptr, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(),
//      scene->getLightId(), scene->getTextureId());
//  scene->addActor(tmpZombie);



// temoporarily testing this
//  tmpZombie->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
//  tmpZombie->setRotationMatrix(glm::vec3(0.0f, 0.0f, 0.0f));
//  btTransform tr = tmpZombie->getRigidBody()->getWorldTransform();
//  btQuaternion quat = tr.getRotation();
//  btQuaternion quat1(btVector3(1, 0, 0), 0.0f);
//  btQuaternion quat2(btVector3(0, 1, 0), 0.0f);
//  btQuaternion quat3(btVector3(0, 0, 1), 0.0f);
//  tr.setRotation(quat * quat1 * quat2 * quat3);
//  tmpZombie->getRigidBody()->setWorldTransform(tr);
// temoporarily testing this





//  (int id, glm::vec3 scale, ObjectType objType, int objArray_length, GLuint texture, glm::vec3 trans, LPWatch* watch, const ResObj& resObj, const View& view, GLuint programID, GLuint MatrixID,
//      GLuint ViewMatrixID, GLuint ModelMatrixID, GLuint LightID, GLuint TextureID);


  TRACE_INFO("Inside Stage::init_maze  Finished");
}


void Stage::initText() {

  scene = new Scene("shaders/StandardShading.vertexshader", "shaders/StandardShading.fragmentshader");
  scene_txt = new Scene("shaders/text.v.glsl", "shaders/text.f.glsl");

//  texture_wall = loadBMP_custom("resources/obj/wall/wall_04.bmp");
//  texture_wall_2x32x32 = loadBMP_custom("resources/obj/wall/wall_2x32x32.bmp");
//  texture_ice = loadBMP_custom("resources/textures/CartoonIce.bmp");
//  GLuint texture_creature = loadBMP_custom("resources/textures/uvlayout.bmp");
//  GLuint texture_sandstone = loadBMP_custom("resources/textures/sand_stone.bmp");
//  texture_sandstone3 = loadBMP_custom("resources/textures/sand_stone3.bmp");
//  GLuint texture_gray = loadBMP_custom("resources/textures/gray.bmp");
//  texture_sandstone4 = loadBMP_custom("resources/textures/sand_stone4.bmp");
//  texture_sandstone5 = loadBMP_custom("resources/textures/sand_stone5.bmp");
//  GLuint texture2 = loadBMP_custom("resources/textures/uvlayout_pattern2.bmp");  // beans, could look like dirt
//  texture_wood = loadBMP_custom("resources/textures/uvlayout_pattern1_TEST.bmp");
//  texture_red_floor = loadBMP_custom("resources/textures/uvlayout_pattern1.bmp");  // the color red

  scene_txt->addActor(new TextObject(++lp_text,
        glm::vec3(1.0f, 1.0f, 1.0f),
        txt_5,
        texture_red_floor,
        glm::vec3(-1.0f, 2.0f,2.0f),
        watch,
        resObj,
        view,
        scene_txt->getLPUniform()));



  scene_txt->addActor(new TextObject(++lp_text,
          glm::vec3(1.0f, 1.0f, 1.0f),
          txt_4,
          texture_red_floor,
          glm::vec3(-1.0f,4.0f,2.0f),
          watch,
          resObj,
          view,
          scene_txt->getLPUniform()));



  scene_txt->addActor(new TextObject(++lp_text,
          glm::vec3(1.0f, 1.0f, 1.0f),
          txt_3,
          texture_red_floor,
          glm::vec3(-1.0f, 6.0f,2.0f),
          watch,
          resObj,
          view,
          scene_txt->getLPUniform()));




  scene_txt->addActor(new TextObject(++lp_text,
          glm::vec3(1.0f, 1.0f, 0.0f),
          txt_2,
          texture_red_floor,
          glm::vec3(-1.0f, 8.0f,2.0f),
          watch,
          resObj,
          view,
          scene_txt->getLPUniform()));


  // Adding wall
//  for (int i = -10; i < 10; i++) {
//
//    for (int j = -2; j < 30; j++) {
//      scene->addActor(new WooddenCube2(++lp_woodden_cube2,
//          glm::vec3(1.0f,1.0f,1.0f),
////          texture_red_floor,
//          texture_gray,
//          glm::vec3(2.0f * i,2.0f*j,0.0f),
//          resObj,
//          view,
//          scene->getProgramId(),
//          scene->getMatrixId(),
//          scene->getViewMatrixId(),
//          scene->getModelMatrixId(),
//          scene->getLightId(),
//          scene->getTextureId()
//      ));

//    }
//  }
view.setPosition(glm::vec3( 0.0f, 11.0f, 30.0f));
}

void Stage::initSkyBox()
{
  scene = new Scene("shaders/SkyBoxShading.vertexshader", "shaders/SkyBoxShading.fragmentshader");
  texture_skybox = loadBMP_custom("resources/obj/skybox/SkyBox-Clouds-Wispy-Dawn.bmp");

  objFactory = new ObjectFactory(watch, resObj, view, scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(), scene->getLightId(), scene->getTextureId());

  // skybox
//  scene->addActor(objFactory->createInstance(++lp_skybox, glm::vec3(250.0f, 250.0f, 250.0f), skybox, lp_class::c_skybox, texture_skybox, glm::vec3(0.0f, -100.0f, 0.0f)));
}

void Stage::draw() {
  if (scene != nullptr)
  {
    scene->draw();
  }
  if (scene_txt != nullptr)
  {
    scene_txt->draw();
  }
  if (splashScene != nullptr)
  {
	  splashScene->draw();
  }
}

void
Stage::move (std::vector<std::pair<int, int>> collisionDetected, btVector3 normalOnB) {
// std::cout << "Stage::move" << std::endl;
  if (scene != nullptr)
  {
    glm::vec3 normal = glm::vec3 (normalOnB.x (), normalOnB.y (), normalOnB.z ());

    // raytrace to find normal

    //send collisionDetected and the normal to each object
    if (scene->getCreature () != nullptr)
    {
      glm::vec3 direction (cos (0) * sin (view.getHorizontalAngle ()), sin (0), cos (0) * cos (view.getHorizontalAngle ()));
      glm::vec3 right = glm::vec3 (sin (view.getHorizontalAngle () - M_PI / 2.0f), 0, cos (view.getHorizontalAngle () - 3.14159265f / 2.0f));

      ((FPerson*) (scene->getCreature ()))->setDirection (direction);
      ((FPerson*) (scene->getCreature ()))->setRight (right);
    }
    scene->move (collisionDetected, normal);
  }
  if (scene_txt != nullptr)
  {
    glm::vec3 normal = glm::vec3(normalOnB.x(), normalOnB.y(), normalOnB.z());
//    glm::vec3 normal = glm::vec3 (0.f, 0.f, 0.f);
    scene_txt->move (collisionDetected, normal);
  }
}

void Stage::createNewBall(glm::vec3 startPos) {
  scene->addActor (
      new Ball (++lp_ball, glm::vec3 (1.0f, 1.0f, 1.0f), ball, 9,
        startPos,
        watch,
        resObj,
        view,
        scene->getLPUniform()
    ));
}

void Stage::createBall(int id, glm::vec3 startPos, int texture) {
  scene->addActor (
      new Ball (id, glm::vec3 (.5f, .5f, .5f), ball, texture,
        startPos,
        watch,
        resObj,
        view,
        scene->getLPUniform()
    ));
}

void Stage::moveCreature(glm::vec3 trans) {
  (scene->getCreature())->setTrans(trans);
}

glm::vec3 Stage::getTransCreature() {
  return (scene->getCreature())->getTrans();
}

void Stage::moveCreatureForward(float l) {
  (scene->getCreature())->setTrans(glm::vec3(l*sin((scene->getCreature())->getOrientation().y), 0.0f, l*sin(3.14159265f/2.0f - (scene->getCreature())->getOrientation().y)));
}

void Stage::moveCreatureBack(float l) {
  (scene->getCreature())->setTrans(glm::vec3(-0.65f*sin((scene->getCreature())->getOrientation().y  ), 0.0f, -0.65f*sin(3.14159265f/2.0f - (scene->getCreature())->getOrientation().y)));
}

void Stage::rotateCreature(float r, float l) {
  (scene->getCreature())->setRotationMatrix_Y(r);
  (scene->getCreature())->setTrans(glm::vec3(l*sin((scene->getCreature())->getOrientation().y), 0.0f, l*sin(3.14159265f/2.0f - (scene->getCreature())->getOrientation().y)));
}

void Stage::setStandingCreature() {
  (scene->getCreature())->setStanding();
}

void Stage::createFallingCube(glm::vec3 pos, int id) {
scene->addActor(new FallingCube(++lp_falling_cube,
    glm::vec3(1.0f,1.0f,1.0f),
    texture_wood,
    pos,
    watch,
    resObj,
    view,
    scene->getLPUniform()));
}

void
Stage::createMazeFloor (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos) {
scene->addActor(new MazeFloor(id,
        obj, shape, scale, texture,
        pos,
        watch,
        resObj,
        view,
        scene->getLPUniform()));
}

void
Stage::createSniper (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos) {
  //      new Sniper (++lp_sniper, glm::vec3 (1.0f, 1.0f, 1.0f), sniper1, 29, texture_sniper, glm::vec3 (-5, -1.4, 7), resObj, view, scene->getProgramId (), scene->getMatrixId (),
  //                  scene->getViewMatrixId (), scene->getModelMatrixId (), scene->getLightId (), scene->getTextureId ()));
  lp_sniper = id;
  scene->addActor (
      new Sniper(id, glm::vec3(1.0f, 1.0f, 1.0f), sniper1, texture_sniper, scale, watch, resObj, view, scene->getLPUniform()));

}

void
Stage::createWinningArea (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos) {
  scene->addActor (
      new MazeFloor(id, obj, shape, scale, texture, pos, watch, resObj, view, scene->getLPUniform()));
}

void
Stage::createMoleculeSpot(int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos)
{
  scene->addActor(new MoleculeSpot(id, obj, shape, scale, texture, pos, watch, resObj, view, scene->getLPUniform()));

}

void
Stage::createTextSpot(int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos)
{
  scene_txt->addActor(new TextSpot(id, obj, shape, scale, texture, pos, watch, resObj, view, scene_txt->getLPUniform()));

}

void
Stage::createMazeDoorX (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos) {
  scene->addActor (
      new MazeDoorX(id, maze_door_x_3x3, shape, scale, texture, pos, watch, resObj, view, scene->getLPUniform()));
}

void
Stage::createMazeDoorY (int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, int texture, glm::vec3 pos) {
  scene->addActor (
      new MazeDoorY(id, maze_door_y_3x3, shape, scale, texture, pos, watch, resObj, view, scene->getLPUniform()));
}

void Stage::createCoordinateLines(glm::vec3 pos, int id) {
  LPObject *tmp = scene->getObject(id);
  if (tmp != nullptr)
  {
    deleteObject(tmp);
  }
  else
  {
  scene->addActor(new CoordinateLines(id,
        glm::vec3(1.0f,1.0f,1.0f),
        pos,
        watch,
        resObj,
        view,
        scene->getProgramId(),
        scene->getMatrixId(),
        scene->getViewMatrixId(),
        scene->getModelMatrixId(),
        scene->getLightId(),
        scene->getTextureId()
    ));
  }
}

void Stage::moveCoordinateLines(glm::vec3 pos, int id) {
  LPObject * tmp;
  tmp = scene->getObject(id);
  if (tmp) {
    tmp->setTrans(pos);
  }
}

void Stage::deleteFallingCube(LPObject *a) {
  scene->removeActor(a);
}

void Stage::deleteObject(LPObject *a) {
  scene->removeActor(a);
}

void Stage::deleteTextObject(LPObject *a) {
  scene_txt->removeActor(a);
}

void Stage::deleteTextObject(int id)
{
  scene_txt->removeActor(scene_txt->getObject(id));
}

void Stage::deleteObject(int id) {
	LPObject* obj = scene->getObject(id);
	if (obj != nullptr)
	{
		cout << "Deleting the object with id=" << id << endl;
		SDL_Log("Deleting the object with id=%d", id);
		scene->removeActor(obj);
	} else {
		cout << "ERROR: Could not find the object!" << endl;
	}
}

LPObject * Stage::getObject(int id)
{
  return scene->getObject(id);
}

LPObject * Stage::getSplashScreenObject(int id)
{
  return splashScene->getObject(id);
}

LPObject * Stage::getSplashScreenObject_txt(int id)
{
  return splashScene_txt->getObject(id);
}

LPObject * Stage::getTextObject(int id)
{
  return scene_txt->getObject(id);
}

std::vector<LPObject*> Stage::getTextObjectFromObjType(ObjectType objType)
{
  return scene_txt->getObjectFromObjType(objType);
}

bool Stage::isAnyInCorrectPosition(ObjectType objType)
{
  bool foundInCorrectPosistion = false;
  for (LPObject* obj : getTextObjectFromObjType(objType)) {
    if (obj->isCorrectPosition()) {
      foundInCorrectPosistion = true;
    }
  }
  return foundInCorrectPosistion;
}

LPObject* Stage::getObjInCorrectPosition(ObjectType objType)
{
  for (LPObject* obj : getTextObjectFromObjType(objType)) {
    if (obj->isCorrectPosition()) {
      return obj;
    }
  }
  return nullptr;
}



void Stage::createWallCube(glm::vec3 pos, int id, GLuint local_texture) {
GLuint txt = 0;
  if (local_texture ==1) {
    txt = texture_wood;
  } else if (local_texture == 2) {
		txt = texture_sandstone3;
  }
	std::cout << "createWallCube - texture = " << txt << std::endl;
	std::cout << "createWallCube - id = " << id << std::endl;
	std::cout << "createWallCube - objType = " << cube << std::endl;
//  scene->addActor(objFactory->createInstance(++lp_wall_cube,
//      glm::vec3(1.0f, 1.0f, 1.0f),
//        cube,
//        lp_class::c_WallCube,
//        txt,
//        pos));

  return scene->addActor (
      new WallCube (id, glm::vec3 (1.0, 1.0, 1.0), cube, texture_sandstone3,
                    pos, watch, resObj, view,
                    scene->getLPUniform()));

}

void Stage::createText(glm::vec3 pos, int id, ObjectType objType, GLuint local_texture)
{
  scene_txt->addActor(new TextObject(id, glm::vec3(1.0f, 1.0f, 1.0f), objType, texture_red_floor, pos, watch, resObj, view, scene_txt->getLPUniform()));
}

void Stage::createMenu(int id, list<std::pair<ObjectType, FuncPtr>> objList, glm::vec3 scale, glm::vec3 pos) {

  scene_txt->addActor(
      objFactory_txt->createInstance(id,
          scale,
          objList,
          lp_class::c_menuContainer,
          texture_plane_skar,
          pos));
}

void Stage::listText()
{
  for (LPObject *a : scene_txt->getActorList()) {
      cout << "textObject: " << a->getId() << endl;
    }
}

void Stage::createGlucose(glm::vec3 pos, int id, GLuint local_texture) {
GLuint txt = 0;
// Adding a wall cube, this one cannot be moved
  if (local_texture ==1) {
    txt = texture_wood;
  } else if (local_texture == 2) {
    txt = texture_sandstone5;
  }
  scene->addActor(new Glucose(++lp_glucose,
      glm::vec3(0.4f, 0.4f, 0.4f),
      texture_red_floor,
      pos,
      watch,
      resObj,
      view,
      scene->getLPUniform()));
}

void Stage::createQuestionCube(glm::vec3 pos, int id, GLuint local_texture) {
GLuint txt = 0;
// Adding a wall cube, this one cannot be moved
  if (local_texture ==1) {
    txt = texture_wood;
  } else if (local_texture == 2) {
    txt = texture_sandstone5;
  }
  scene->addActor(new WallCube(id,
      glm::vec3(0.2f, 0.2f, 0.2f),
      cube,
      texture_question2,
      pos,
      watch,
      resObj,
      view,
      scene->getLPUniform()));
}


void Stage::createMolecule(glm::vec3 pos, int id, ObjectType obj,
                           GLuint local_texture,
                           string mInfo1, string mInfo2, string mInfo3) {
  scene->addActor(new Molecule(id,
      glm::vec3(0.1f, 0.1f, 0.1f),
      obj,
      texture_red_floor,
      pos,
      watch,
      resObj,
      view,
      scene->getLPUniform()));

  getObject(id)->setMoleculeInfo1(mInfo1);
  getObject(id)->setMoleculeInfo2(mInfo2);
  getObject(id)->setMoleculeInfo3(mInfo3);
}

void Stage::createAnimalCell(glm::vec3 scaling, glm::vec3 pos, int id, GLuint local_texture, string mInfo1, string mInfo2, string mInfo3)
{
//  scene->addActor(new Molecule(id, scaling, animal_cell, texture_red_floor, pos, watch, resObj, view, scene->getLPUniform()));

  scene->addActor(new Mitochondria(id, scaling, animal_cell, texture_red_floor, pos, watch, resObj, view, scene->getLPUniform()));


  getObject(id)->setMoleculeInfo1(mInfo1);
  getObject(id)->setMoleculeInfo2(mInfo2);
  getObject(id)->setMoleculeInfo3(mInfo3);
}

void Stage::createArrow(glm::vec3 scaling, glm::vec3 pos, int id, ObjectType objType, GLuint local_texture, string mInfo1, string mInfo2, string mInfo3)
{
  scene->addActor(objFactory->createInstance(id, scaling, objType, lp_class::c_arrow, local_texture, pos));

  getObject(id)->setMoleculeInfo1(mInfo1);
  getObject(id)->setMoleculeInfo2(mInfo2);
  getObject(id)->setMoleculeInfo3(mInfo3);

}

void Stage::createMolecule(glm::vec3 pos,
                           string mInfo1, string mInfo2, string mInfo3) {

    scene->addActor(new Molecule(990000,
      glm::vec3(0.1f, 0.1f, 0.1f),
      alpha_D_glucopyranose,
      texture_red_floor,
      pos,
      watch,
      resObj,
      view,
      scene->getLPUniform()));

  getObject(lp_glucose)->setMoleculeInfo1(mInfo1);
  getObject(lp_glucose)->setMoleculeInfo2(mInfo2);
  getObject(lp_glucose)->setMoleculeInfo3(mInfo3);
}

void Stage::createGlucose6Phosphate(glm::vec3 pos, int id, GLuint local_texture) {

  scene->addActor(new Glucose6Phosphate(++lp_glucose,
      glm::vec3(1.40f, 1.40f, 1.40f),
      local_texture,
      pos,
      watch,
      resObj,
      view,
      scene->getLPUniform()));
}

void Stage::createFructosePhosphate(glm::vec3 pos, int id, GLuint local_texture) {
  scene->addActor(new Fructose6Phosphate(++lp_glucose,
      glm::vec3(0.40f, 0.40f, 0.40f),
      texture_sandstone3,
      pos,
      watch,
      resObj,
      view,
      scene->getLPUniform()));
}

void Stage::createHexokinase(glm::vec3 pos, int id, GLuint local_texture) {
  scene->addActor(new Hexokinase(id,
      glm::vec3(0.04f, 0.04f, 0.04f),
      texture_sandstone3,
      pos,
      watch,
      resObj,
      view,
      scene->getLPUniform()));
}

void Stage::createPhosphofructokinase(glm::vec3 pos, int id, GLuint local_texture) {
  scene->addActor(new Phosphofructokinase(id,
      glm::vec3(0.04f, 0.04f, 0.04f),
      texture_sandstone3,
      pos,
      watch,
      resObj,
      view,
      scene->getLPUniform()));
}

void Stage::createZombie(glm::vec3 pos, int id, GLuint local_texture) {
//  scene->addActor(new Wall(++lp_wall,
//      glm::vec3(0.015f, 0.015f, 0.015f),
//      local_texture,
//      pos,
//      watch,
//      resObj,
//      view,
//      scene->getProgramId(),
//      scene->getMatrixId(),
//      scene->getViewMatrixId(),
//      scene->getModelMatrixId(),
//      scene->getLightId(),
//      scene->getTextureId()));

  scene->addActor(
      new WallCube(id, glm::vec3(2.5f, 2.5f, 2.5f), zombie, texture_zombie, pos, nullptr, resObj, view, scene->getLPUniform()));



}

void Stage::createWall(glm::vec3 pos, int id, GLuint local_texture) {
GLuint txt = 0;
  if (local_texture ==1) {
    txt = texture_wood;
  } else if (local_texture == 2) {
    txt = texture_sandstone5;
  }
  scene->addActor(new Wall(++lp_wall,
      glm::vec3(1.0f, 1.0f, 1.0f),
      texture_sandstone3,
      pos,
      watch,
      resObj,
      view,
      scene->getLPUniform()));
}

void Stage::createPlane(glm::vec3 pos, int id, GLuint local_texture) {
GLuint txt = 0;
  scene->addActor (
      new Plane (id,
      glm::vec3 (1.0f, 1.0f, 1.0f),
      plane,
      local_texture,
      pos,
      watch,
      resObj,
      view,
      scene->getLPUniform()
      ));
}

void Stage::createPlate(glm::vec3 pos) {
GLuint txt = 0;
  scene->addActor(new Plate(++lp_plate,
      glm::vec3(2.0f,2.0f,2.0f),
      plate,
      texture_sandstone3,
      pos,
      watch,
      resObj,
      view,
      scene->getLPUniform()
      ));
}

void Stage::deleteWallCube(LPObject *a) {
  scene->removeActor(a);
}

void Stage::reloadActorList() {
	for (LPObject *a : scene->getActorList()) {
		cout << "Removing object id=" << a->getId() << endl;
		scene->removeActor(a);
	}

  for (LPObject *a : scene_txt->getActorList()) {
    cout << "Removing object id=" << a->getId() << endl;
    scene_txt->removeActor(a);
  }

  cout << "Finished Removing actors" << endl;
//  init_maze ();
  init2();
}

void Stage::deleteActorList() {
	for (LPObject *a : scene->getActorList()) {
		cout << "Removing object id=" << a->getId() << endl;
		scene->removeActor(a);
	}
}

void Stage::deleteActorListForSplashScreen() {
	for (LPObject *a : splashScene->getActorList()) {
		cout << "Removing object id=" << a->getId() << endl;
		splashScene->removeActor(a);
	}
}

void Stage::loadActorList(list<std::string> *objList) {
  int id, objType, texture;
  float x,y,z;
  float rotationX, rotationY, rotationZ;
  float scaleX, scaleY, scaleZ;
  bool missingOBj = false;
  cout << "Enter method loadActorList" << endl;

  for (LPObject *a : scene->getActorList()) {
    cout << "Removing object id=" << a->getId() << endl;
    scene->removeActor(a);
  }

  for (std::list<std::string>::iterator it = objList->begin(); it != objList->end(); it++)
  {
    //    actorList.push_back(it._Node);
    std::cout << it->c_str() << std::endl;
    int fieldsCount = 0;
    fieldsCount = sscanf(it->c_str(), "id:%d,objType:%d,position:(%f,%f,%f),rotation:(%f,%f,%f),scale:(%f,%f,%f),texture:%d\n", &id, &objType, &x, &y, &z, &rotationX, &rotationY, &rotationZ, &scaleX, &scaleY, &scaleZ, &texture);

    if (fieldsCount < 12) {
      SDL_Log("ERROR: sscanf returned %d fields scanned positive. This differs from 12", fieldsCount);
    }
    SDL_Log("sscanf returned %d fields scanned positive.", fieldsCount);
    if (id < 1000)
    {
      lp_falling_cube = id;
      // Adding a falling cube
      scene->addActor(new FallingCube(id,
          glm::vec3(1.0f,1.0f,1.0f),
          texture,
          glm::vec3(x, y, z),
          watch,
          resObj,
          view,
          scene->getLPUniform()
      ));
    }
    else if (id < 1500)
    {
      //      // FP Shooter
      scene->addActor (
//          new FPerson (1000, glm::vec3 (1.0f, 1.0f, 1.0f), texture_red_floor, glm::vec3 (6.0f, 1.0f, 0.0f), watch, resObj, view, scene->getProgramId (), scene->getMatrixId (),
//                       scene->getViewMatrixId (),
//                       scene->getModelMatrixId (), scene->getLightId (), scene->getTextureId ()));

          new FPerson (1000, glm::vec3 (1.0f, 1.0f, 1.0f), cube, 1, texture_red_floor, glm::vec3 (6.0, 1.0, 0.0), watch, resObj, view, scene->getProgramId (), scene->getMatrixId (),
                       scene->getViewMatrixId (), scene->getModelMatrixId (), scene->getLightId (), scene->getTextureId ()));

    }else if (id < 4000) {
      // Ball
      lp_ball = id;
      scene->addActor (
          new Ball (id, glm::vec3 (scaleX, scaleY, scaleZ), ball, texture,
              glm::vec3(x, y, z),
              watch,
              resObj,
              view,
              scene->getLPUniform()
          ));
    } else if (id < 6000) {
      std::cout << "Creature, id<6000, texture=" << texture << std::endl;
      // Creature
      lp_creature = id;
      scene->addActor(new Creature(id, glm::vec3(1.0f,1.0f,1.0f), creature0, 23, texture,
          glm::vec3(x,y,z),
          watch,
          resObj,
          view,
          scene->getProgramId(), scene->getMatrixId(), scene->getViewMatrixId(), scene->getModelMatrixId(), scene->getLightId(),
              scene->getTextureId()));
    } else if (id < 6000) {


    }else if (id < 10000) {
      lp_sniper = id;
      scene->addActor(
          new Sniper(id, glm::vec3(1.0f, 1.0f, 1.0f), sniper1, texture,
          glm::vec3(x,y,z),
          watch,
          resObj,
          view,
          scene->getLPUniform()
      ));
    } else if (id < 12000) {
          std::cout << "WallCube2, id<12000, texture=" << texture << std::endl;
      lp_wall_cube = id;
      scene->addActor(objFactory->createInstance(id,
          glm::vec3(1.0f, 1.0f, 1.0f),
          cube,
          lp_class::c_WallCube,
          texture,
          glm::vec3(x,y,z)));


    } else if (id < 14000) {
      lp_woodden_cube = id;
      scene->addActor(new WooddenCube(id,
          glm::vec3(1.0f,1.0f,1.0f),
          cube,
          texture,
          glm::vec3(x,y,z),
          watch,
          resObj,
          view,
          scene->getLPUniform()
      ));
    } else if (id < 16000) {
          std::cout << "WoodenCube2, id<16000, texture=" << texture << std::endl;
      lp_woodden_cube2 = id;
      scene->addActor(new WooddenCube2(id,
          glm::vec3(1.0f,1.0f,1.0f),
          texture,
          glm::vec3(x,y,z),
          watch,
          resObj,
          view,
          scene->getLPUniform()
      ));
    } else if (id < 18000) {
      lp_glucose = id;
      scene->addActor(
          new Molecule(id,
          glm::vec3(1.0f,1.0f,1.0f),
          alpha_D_glucopyranose,
          texture,
          glm::vec3(x,y,z),
          watch,
          resObj,
          view,
          scene->getLPUniform()
      ));

    }
    else if (id < 20000) {
      lp_wall = id;
      scene->addActor(new Wall(id,
          glm::vec3(1.0f,1.0f,1.0f),
          texture,
          glm::vec3(x,y,z),
          watch,
          resObj,
          view,
          scene->getLPUniform()));
    }

    else if (id < (c_plane + 2000))
        {
      lp_plane = id;
      scene->addActor(new Plane(id,
          glm::vec3(1.0f,1.0f,1.0f),
          plane,
          texture_dirt,
          glm::vec3(x, y, z),
          watch,
          resObj,
          view,
          scene->getLPUniform()
          ));
        }
    else if (id < (c_plate + 2000))
            {
      lp_plate = id;
          scene->addActor(new Plate(id,
              glm::vec3(1.0f,1.0f,1.0f),
              plate,
              texture,
              glm::vec3(x, y, z),
              watch,
              resObj,
              view,
              scene->getLPUniform()
              ));
            }
    else if (id < (c_lightSource + 2000))
                {
      ++lp_lightSource;
              scene->addActor(new LightSource(id,
                  glm::vec3(1.0f,1.0f,1.0f),
                  ball,
                  texture,
                  glm::vec3(x, y, z),
                  watch,
                  resObj,
                  view,
                  scene->getLPUniform()
                  ));
                }
    else if (id < (c_maze_floor_3x1 + 1000))
    {
      ++lp_maze_floor_3x1;
      createMazeFloor (id, maze_floor_3x1, glm::vec3 (1.0f, 3.0f, 1.0f), glm::vec3 (1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3 (x, y, z));
    }
    else if (id < (c_maze_floor_3x5 + 1000))
    {
      if (id > lp_maze_floor_3x5)
      {
        lp_maze_floor_3x5 = id;
      }
      createMazeFloor (id, maze_floor_3x5, glm::vec3 (5.0f, 3.0f, 1.0f), glm::vec3 (1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3 (x, y, z));
      std::cout << "Loading Maze Wall 3x5: id= " << id << std::endl;
    }
    else if (id < (c_maze_floor_3x10 + 1000))
    {
      if (id > lp_maze_floor_3x10)
      {
        lp_maze_floor_3x10 = id;
      }
//      ++lp_maze_floor_3x10;
      createMazeFloor (id, maze_floor_3x10, glm::vec3 (10.0f, 3.0f, 1.0f), glm::vec3 (1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3 (x, y, z));
      std::cout << "Loading Maze Wall 3x10: id= " << id << std::endl;
    }
    else if (id < (c_maze_floor_3x3 + 1000))
    {
      ++lp_maze_floor_3x3;
      createMazeFloor (id, maze_floor_3x3, glm::vec3 (3.0f, 3.0f, 1.0f), glm::vec3 (1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3 (x, y, z));
    }
    else if (id < (c_maze_floor_5x5 + 1000))
    {
      ++lp_maze_floor_5x5;
      createMazeFloor (id, maze_floor_5x5, glm::vec3 (5.0f, 5.0f, 1.0f), glm::vec3 (1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3 (x, y, z));
    }
    else if (id < (c_maze_floor_3x20 + 1000))
    {
      ++lp_maze_floor_3x20;
      createMazeFloor (id, maze_floor_3x20, glm::vec3 (20.0f, 3.0f, 1.0f), glm::vec3 (1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3 (x, y, z));
    }
    else if (id < (c_maze_door_3x2 + 1000))
    {
      ++lp_maze_door_3x2;
      createMazeFloor (id, maze_door_3x2, glm::vec3 (2.0f, 3.0f, 1.0f), glm::vec3 (1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3 (x, y, z));
    }
    else if (id < (c_maze_door_x_3x3 + 1000))
    {
      ++lp_maze_door_x_3x3;
      createMazeDoorX (id, maze_door_x_3x3, glm::vec3 (3.0f, 3.0f, 1.0f), glm::vec3 (1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3 (x, y, z));
    }
    else if (id < (c_maze_door_y_3x3 + 1000))
    {
      ++lp_maze_door_y_3x3;
      createMazeDoorY (id, maze_door_y_3x3, glm::vec3 (1.0f, 3.0f, 3.0f), glm::vec3 (1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3 (x, y, z));
    }
    else if (id < (c_winning_area + 1000))
    {
      ++lp_winning_area;
      createWinningArea (id, winning_area, glm::vec3 (8.0f, 2.0f, 4.0f), glm::vec3 (1.0f, 1.0f, 1.0f), texture_sandstone5, glm::vec3 (x, y, z));
    }
    else if (id < (c_zombie + 1000)) {
      ++lp_zombie;
      createZombie(glm::vec3(x, y, z), id, texture_sandstone5);
    }
    else
    {
      cout << "Error, could not find any object matching id=" << id << endl;
      missingOBj = true;
    }

    if (!missingOBj)
    {
      getObject(id)->setScale(glm::vec3(scaleX, scaleY, scaleZ));
      // Load rotationInformation in the object:
      cout << "Loading rotationInformation for the object id=" << id << endl;
      getObject(id)->setRotationMatrix(glm::vec3(rotationX, rotationY, rotationZ));

      if (getObject (id)->getRigidBody () != NULL)
      {
        btTransform tr = getObject (id)->getRigidBody ()->getWorldTransform ();
//      tr.setIdentity ();
        btQuaternion quat = tr.getRotation ();
        btQuaternion quat1 (btVector3 (1, 0, 0), rotationX);
//        tr.setRotation (quat1);
        btQuaternion quat2 (btVector3 (0, 1, 0), rotationY);
//        tr.setRotation (quat2);
        btQuaternion quat3 (btVector3 (0, 0, 1), rotationZ);
        tr.setRotation (quat * quat1 * quat2 * quat3);
        getObject (id)->getRigidBody ()->setWorldTransform (tr);
      }
    }
    missingOBj = false;
  }
  TRACE_INFO("Finished loading all objects into memory (loadActorList)");
}

void Stage::addMoleculesOnSide() {

  // ----------------------------- NEXT

  scene_txt->addActor(objFactory_txt->createInstance(36507,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_7,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 20.4, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36616,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_16,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 20.2, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36510,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_10,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 20.0, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36512,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_12,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 19.8, 0.5)));


  scene_txt->addActor(objFactory_txt->createInstance(36514,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_14,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 19.6, 0.5)));



  scene_txt->addActor(objFactory_txt->createInstance(36617,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_17,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 19.4, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36508,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_8,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 19.2, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36509,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_9,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 19.0, 0.5)));



  // ----------------------------- NEXT

  scene_txt->addActor(objFactory_txt->createInstance(36504,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_4,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 18.8, 0.5)));


  scene_txt->addActor(objFactory_txt->createInstance(36506,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_6,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 18.6, 0.5)));

  // ----------------------------- NEXT





  scene_txt->addActor(objFactory_txt->createInstance(36517,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_17,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 18.4, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36502,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_2,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 18.2, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36503,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_3,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 18.0, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36501,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_1,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 17.8, 0.5)));



  scene_txt->addActor(objFactory_txt->createInstance(36516,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_16,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 17.6, 0.5)));

  //--- STAGE 2 -------

  scene_txt->addActor(objFactory_txt->createInstance(36717,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_17,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 15.6, 0.5)));


  scene_txt->addActor(objFactory_txt->createInstance(36716,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_16,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 15.4, 0.5)));



  scene_txt->addActor(objFactory_txt->createInstance(36525,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_25,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 15.2f,0.5f)));




  // ----------------------------- NEXT

  scene_txt->addActor(objFactory_txt->createInstance(36532,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_32,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 15.0, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36533,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_33,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 14.8, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36817,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_17,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 14.6, 0.5)));


  scene_txt->addActor(objFactory_txt->createInstance(36816,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_16,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 14.4, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36534,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_34,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 14.2, 0.5)));



  // --------------------------------------------------------- //

  scene_txt->addActor(objFactory_txt->createInstance(36527,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_27,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4, 14.0, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36528,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_28,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 13.8, 0.5)));


  scene_txt->addActor(objFactory_txt->createInstance(36530,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_30,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 13.6, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36531,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_31,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 13.4, 0.5)));


  scene_txt->addActor(objFactory_txt->createInstance(36520,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_20,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 13.2, 0.5)));

  // ----------------------------- NEXT

  scene_txt->addActor(objFactory_txt->createInstance(36521,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_21,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 13.0f,0.5f)));

  scene_txt->addActor(objFactory_txt->createInstance(36519,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_19,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 12.8, 0.5)));


  scene_txt->addActor(objFactory_txt->createInstance(36524,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_24,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 12.6, 0.5)));

  scene_txt->addActor(objFactory_txt->createInstance(36518,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_18,
      lp_class::c_text,
      texture_plane_skar,
      glm::vec3(4.4f, 12.4, 0.5)));
}

//void Stage::printCreaturePos()
//{
//         printf("Cube position: (%f, %f, %f)\n", getTransCreature().x, getTransCreature().y, getTransCreature().z);
//}

void
Stage::moveFPersonFwd (glm::vec3 direction, glm::vec3 right, bool wasd[7]) {
  SDL_Log ("ENTER Stage::moveFPersonFwd");
  ((FPerson*) (scene->getCreature ()))->setWasd (&wasd[0]);
  ((FPerson*) (scene->getCreature ()))->setDirection (direction);
  ((FPerson*) (scene->getCreature ()))->setRight (right);
}

void
Stage::moveFPersonBack (glm::vec3 direction, glm::vec3 right, bool wasd[7]) {
  SDL_Log ("ENTER Stage::moveFPersonBack");
  ((FPerson*) (scene->getCreature ()))->setWasd (&wasd[0]);
  ((FPerson*) (scene->getCreature ()))->setDirection (direction);
  ((FPerson*) (scene->getCreature ()))->setRight (right);
}

void
Stage::moveFPersonLeft (glm::vec3 direction, glm::vec3 right, bool wasd[7]) {
  SDL_Log ("ENTER Stage::moveFPersonLeft");
  ((FPerson*) (scene->getCreature ()))->setWasd (&wasd[0]);
  ((FPerson*) (scene->getCreature ()))->setDirection (direction);
  ((FPerson*) (scene->getCreature ()))->setRight (right);
}

void
Stage::moveFPersonRight (glm::vec3 direction, glm::vec3 right, bool wasd[7]) {
  SDL_Log ("ENTER Stage::moveFPersonRight");

  ((FPerson*) (scene->getCreature ()))->setWasd (&wasd[0]);
  ((FPerson*) (scene->getCreature ()))->setDirection (direction);
  ((FPerson*) (scene->getCreature ()))->setRight (right);
}

void
Stage::moveFPersonJump (glm::vec3 direction, glm::vec3 right) {
  cout << "ENTER moveFPersonJump" << endl;
  SDL_Log ("ENTER Stage::moveFPersonJump");
//  (scene->getCreature ())->getRigidBody ()->activate ();
//  int tmpFr = (scene->getCreature ())->getRigidBody ()->getFriction ();
//  (scene->getCreature ())->getRigidBody ()->setFriction (0.0f);
//  if (!scene->isOccupied ((scene->getCreature ())->getTrans () + glm::vec3 (0, 2, 0)))
//  {
//
//    (scene->getCreature ())->getRigidBody ()->applyForce (btVector3 (0.0f, 0.0, 2.0f), btVector3 (0.0f, 0.0f, 0.0f));
//
////    (scene->getCreature ())->setTrans (glm::vec3 (0, 1, 0));
//  }
//  else
//  {
//    (scene->getCreature ())->setTrans (glm::vec3 (0, 0.1, 0));
//  }
//  (scene->getCreature ())->getRigidBody ()->setFriction (tmpFr);
//  //       for the physics
//  btTransform trans;
//  btVector3 bvec;
//  (scene->getCreature ())->getRigidBody ()->getMotionState ()->getWorldTransform (trans);
//  bvec = trans.getOrigin ();
//  // this made him move push stuff around
//  trans.setOrigin (btVector3 ((scene->getCreature ())->getTrans ().x, (scene->getCreature ())->getTrans ().y, (scene->getCreature ())->getTrans ().z));
//  (scene->getCreature ())->getRigidBody ()->getMotionState ()->setWorldTransform (trans);
//  (scene->getCreature ())->getRigidBody ()->setCenterOfMassTransform (trans);
  if ((scene->getCreature ())->getFPSJumping () == false)
  {
  btTransform trans;
  btVector3 bvec;
  (scene->getCreature ())->getRigidBody ()->getMotionState ()->getWorldTransform (trans);
  bvec = trans.getOrigin ();
  (scene->getCreature ())->getRigidBody ()->activate ();
  int tmpFr = (scene->getCreature ())->getRigidBody ()->getFriction ();
  (scene->getCreature ())->getRigidBody ()->setFriction (0.0f);
//    if (glm::abs(relY) != 0) {
  (scene->getCreature ())->getRigidBody ()->applyForce (btVector3 (0.0f, 800.0f, 0.0f), btVector3 (0.0f, 0.0f, 0.0f));
  (scene->getCreature ())->getRigidBody ()->applyForce (btVector3 (0.0f, 800.0f, 0.0f), btVector3 (0.0f, 0.0f, 0.0f));
  (scene->getCreature ())->getRigidBody ()->applyForce (btVector3 (0.0f, 800.0f, 0.0f), btVector3 (0.0f, 0.0f, 0.0f));
  (scene->getCreature ())->getRigidBody ()->applyForce (btVector3 (0.0f, 800.0f, 0.0f), btVector3 (0.0f, 0.0f, 0.0f));
  (scene->getCreature ())->getRigidBody ()->applyForce (btVector3 (0.0f, 800.0f, 0.0f), btVector3 (0.0f, 0.0f, 0.0f));
  (scene->getCreature ())->getRigidBody ()->applyForce (btVector3 (0.0f, 800.0f, 0.0f), btVector3 (0.0f, 0.0f, 0.0f));
//}
//    else
//{
//      (scene->getCreature ())->getRigidBody()->applyForce(btVector3(0.0f, 0.0f, mY/8.0f),btVector3(0.0f,0.0f,0.0f));
//}
(scene->getCreature ())->getRigidBody()->setFriction(tmpFr);

  }




}

void
Stage::stillFPerson () {
  bool wasd[7] =
  { false, false, false, false, false, false, false };
  ((FPerson*) (scene->getCreature ()))->setWasd (&wasd[0]);
}

int
Stage::getProgramId () {
  return scene->getProgramId ();
}

Scene*
Stage::getScene () {
  return scene;
}


std::vector<int> Stage::getObjTypeListInUse()
{
  std::vector<int> list;
  for (LPObject* o : scene->getActorList()) {
    list.push_back(o->getObjType());
  }
  return list;
}

std::list<LPObject*> Stage::getActorList() {
 return scene->getActorList();
}

std::list<LPObject*> Stage::getActorTextList()
{
  return scene_txt->getActorList();
}

std::map<TextureName, GLuint> Stage::getTextureList() {
 return textureList;
}
