/*
 * ObjectFactory.h
 *
 *  Created on: Mar 20, 2016
 *      Author: peter
 */

#ifndef INC_OBJECTFACTORY_H_
#define INC_OBJECTFACTORY_H_

#include "LPObject.h"
#include "ResObj.h"
#include "View.h"
#include "LPWatch.h"
#include <memory>

typedef void (*FuncPtr) (void);

class ObjectFactory {
public:
	ObjectFactory(
	    LPWatch* watch,
			ResObj& resObj,
			const View& view,
			GLuint programID,
			GLuint matrixID,
			GLuint viewMatrixID,
			GLuint modelMatrixID,
			GLuint lightID,
			GLuint textureID);

	virtual ~ObjectFactory();

  LPObject* createInstance(
			int id,
			glm::vec3 scale,
			ObjectType objType,
			lp_class objClass,
			GLuint texture,
			glm::vec3 pos);

  LPObject* createInstance(
			int id,
			glm::vec3 scale,
			list<std::pair<ObjectType, FuncPtr>> objList,
			lp_class objClass,
			GLuint texture,
			glm::vec3 pos);
private:
  LPWatch* watch;
  ResObj& resObj;
	const View& view;
	GLuint programId;
	GLuint matrixId;
	GLuint viewMatrixId;
	GLuint modelMatrixId;
	GLuint lightId;
	GLuint textureId;
};

#endif /* INC_OBJECTFACTORY_H_ */
