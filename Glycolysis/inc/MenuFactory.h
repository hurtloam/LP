/*
 * MenuFactory.h
 *
 *  Created on: Mar 20, 2016
 *      Author: peter
 */

#ifndef INC_MENUFACTORY_H_
#define INC_MENUFACTORY_H_

#include "LPObject.h"
#include "ResObj.h"
#include "View.h"
#include "LPWatch.h"
#include <map>

typedef void (*FuncPtr)(void);

class MenuFactory {
public:
	MenuFactory(
	    LPWatch* watch,
			ResObj& resObj,
			const View& view,
			GLuint programID,
			GLuint matrixID,
			GLuint viewMatrixID,
			GLuint modelMatrixID,
			GLuint lightID,
			GLuint textureID);

	virtual ~MenuFactory();

	LPObject* createInstance(
			int id,
			glm::vec3 scale,
			list<std::pair<ObjectType, FuncPtr>> textObjectMap,
			glm::vec3 pos);
private:
  ResObj& resObj;
	const View& view;
  LPWatch* watch;
	GLuint programId;
	GLuint matrixId;
	GLuint viewMatrixId;
	GLuint modelMatrixId;
	GLuint lightId;
	GLuint textureId;
};

#endif /* INC_MENUFACTORY_H_ */
