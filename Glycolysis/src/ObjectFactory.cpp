/*
 * ObjectFactory.cpp
 *
 *  Created on: Mar 20, 2016
 *      Author: peter
 */

#include "../inc/ObjectFactory.h"

//#include <GL/glew.h>
#include <stddef.h>

#include "../inc/WallCube.h"
#include "../inc/SkyBox.h"
#include "../inc/Arrow.h"
#include "../inc/TextObject.h"
#include "../inc/MenuContainer.h"
#include <list>
#include <memory>

using namespace std;


ObjectFactory::ObjectFactory(
    LPWatch* watch,
    ResObj& resObj, const View& view, GLuint programID, GLuint matrixID, GLuint viewMatrixID, GLuint modelMatrixID, GLuint lightID,
                              GLuint textureID) :
    watch (watch), resObj (resObj), view (view), programId (programID), matrixId (matrixID), viewMatrixId (viewMatrixID), modelMatrixId (modelMatrixID), lightId (lightID), textureId (textureID)
{
  // TODO Auto-generated constructor stub

}

ObjectFactory::~ObjectFactory() {
	// TODO Auto-generated destructor stub
}

LPObject* ObjectFactory::createInstance(
		int id,
		glm::vec3 scale,
		ObjectType objType,
		lp_class objClass,
		GLuint texture,
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

	switch (objClass)
	{
	case 99923: // test value remove when done
		cout << "99923, we got the wrongcase" << endl;
    return new WallCube(id,
				scale,
				objType,
				texture,
				pos,
				watch,
				resObj,
				view,
lpUniform);
	case c_skybox:
		cout << "c_skybox, we got the correct case" << endl;
    return new SkyBox(id,
				scale,
				objType,
				texture,
				pos,
				watch,
				resObj,
				view,
				lpUniform);

	case c_arrow:
	{
		cout << "c_arrow, we got the correct case" << endl;
    return new Arrow(id,
				scale,
				objType,
				texture,
				pos,
				watch,
				resObj,
				view,
				lpUniform);
	}
	case c_text:
	  {
	    cout << "c_text, we got the correct case" << endl;
    return new TextObject(id,
	        scale,
	        objType,
	        texture,
	        pos,
	        watch,
	        resObj,
	        view,
	        lpUniform);
	  }
	case c_WallCube: {
    return new WallCube(id, scale, objType, texture, pos, watch, resObj, view,
				lpUniform);

	}
	default:
	{
		cout << "default, we got the wrong case" << endl;
    return new WallCube(id,
				scale,
				objType,
				texture,
				pos,
				watch,
				resObj,
				view,
				lpUniform);
		// default
	}
	}
}


LPObject* ObjectFactory::createInstance(
		int id,
		glm::vec3 scale,
		list<std::pair<ObjectType, FuncPtr>> objList,
		lp_class objClass,
		GLuint texture,
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

	switch (objClass)
	{

	case c_menuContainer:
	{
    MenuContainer* mc = new MenuContainer(id,
				scale,
				objList,
				texture,
				pos,
				watch,
				resObj,
				view,
				lpUniform);
		mc->init();
		return mc;
	}
	default:
	{
		cout << "default, we got the wrong case" << endl;
		return NULL;
	}
	}
}
