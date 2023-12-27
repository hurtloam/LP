/*
 * MenuFactory.cpp
 *
 *  Created on: Mar 20, 2016
 *      Author: peter
 */

#include "../inc/MenuFactory.h"
#include "../inc/MenuContainer.h"

//#include <GL/glew.h>
#include <stddef.h>

#include "../inc/WallCube.h"
#include "../inc/SkyBox.h"

#include "../uniform_location_var/inc/LPUniform.h"



MenuFactory::MenuFactory(
    LPWatch* watch, ResObj& resObj, const View& view, GLuint programID, GLuint matrixID, GLuint viewMatrixID, GLuint modelMatrixID, GLuint lightID, GLuint textureID) :
    watch (watch),
    resObj (resObj), view (view), programId (programID), matrixId (matrixID), viewMatrixId (viewMatrixID), modelMatrixId (modelMatrixID), lightId (lightID), textureId (textureID)
{
  // TODO Auto-generated constructor stub

}

MenuFactory::~MenuFactory() {
	// TODO Auto-generated destructor stub
}


LPObject* MenuFactory::createInstance(
		int id,
		glm::vec3 scale,
		list<std::pair<ObjectType, FuncPtr>> textObjectMap,
		glm::vec3 pos)
{

  LPUniform lpUniform;
  lpUniform.LightID = lightId;
  lpUniform.MatrixID = matrixId;
  lpUniform.ModelMatrixID = modelMatrixId;
  lpUniform.ModelView3x3MatrixID = 0;
  lpUniform.TextureID = textureId;
  lpUniform.ViewMatrixID = viewMatrixId;
  lpUniform.colorID = 0;
  lpUniform.programID = programId;

	new MenuContainer(++lp_text,
			scale,
			textObjectMap,
			0,
			pos,
			watch,
			resObj,
			view,
			lpUniform);
}
