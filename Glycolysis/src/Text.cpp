/*
 * Text.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: peter
 */


#include "../inc/Text.h"
#include "../inc/TextObject.h"


using namespace std;

Text::Text (LPWatch* watch, ResObj& resObj, View& view) :
    Stage (watch, resObj, view) {

	// TODO Auto-generated constructor stub

}

Text::~Text() {
	// TODO Auto-generated destructor stub
}

void Text::init() {


	scene = new Scene("shaders/TextShading.vertexshader", "shaders/TextShading.fragmentshader");
//	scene = new Scene("shaders/StandardShading.vertexshader", "shaders/StandardShading.fragmentshader");

//	resObj->attribute_coord = glGetAttrib(program, "coord");
//	resObj->uniform_tex = get_uniform(program, "tex");
//	resObj->uniform_color = get_uniform(program, "color");
	float sx = 2.0/800;
	float sy = 2.0/600;

//	scene->addActor(new TextObject("The Quick Brown Fox Jumps Over The Lazy Dog", -20 + 8 * sx, 1 - 20 * sy, sx, sy,
//			1000,
//			glm::vec3(1.0f,1.0f,1.0f),
//			texture_wood,
//			glm::vec3(50.0f, 10.0f,10.0f),
//			resObj,
//			view,
//			scene->getProgramId(),
//			scene->getMatrixId(),
//			scene->getViewMatrixId(),
//			scene->getModelMatrixId(),
//			scene->getLightId(),
//			scene->getTextureId()
//	));
//
//
//	scene->addActor(new TextObject("The Quick Brown Fox Jumps Over The Lazy Dog", -100 + 8 * sx, 1 - 20 * sy, sx, sy,
//				1000,
//				glm::vec3(1.0f,1.0f,1.0f),
//				texture_wood,
//				glm::vec3(50.0f, 10.0f,10.0f),
//				resObj,
//				view,
//				scene->getProgramId(),
//				scene->getMatrixId(),
//				scene->getViewMatrixId(),
//				scene->getModelMatrixId(),
//				scene->getLightId(),
//				scene->getTextureId()
//		));
//
//
//
//	scene->addActor(new TextObject("The Quick Brown Fox Jumps Over The Lazy Dog", -10 + 8 * sx, 1 - 50 * sy, sx, sy,
//				1000,
//				glm::vec3(1.0f,1.0f,1.0f),
//				texture_wood,
//				glm::vec3(50.0f, 10.0f,10.0f),
//				resObj,
//				view,
//				scene->getProgramId(),
//				scene->getMatrixId(),
//				scene->getViewMatrixId(),
//				scene->getModelMatrixId(),
//				scene->getLightId(),
//				scene->getTextureId()
//		));
//
//
//	scene->addActor(new TextObject("The Quick Brown Fox Jumps Over The Lazy Dog", -1 + 8 * sx, 1 - 50 * sy, sx, sy,
//				1000,
//				glm::vec3(1.0f,1.0f,1.0f),
//				texture_wood,
//				glm::vec3(50.0f, 10.0f,10.0f),
//				resObj,
//				view,
//				scene->getProgramId(),
//				scene->getMatrixId(),
//				scene->getViewMatrixId(),
//				scene->getModelMatrixId(),
//				scene->getLightId(),
//				scene->getTextureId()
//		));

}
