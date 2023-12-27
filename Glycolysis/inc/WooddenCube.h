/*
 * WooddenCube.h
 *
 *  Created on: Oct 26, 2014
 *      Author: peter
 */

#ifndef WOODDENCUBE_H_
#define WOODDENCUBE_H_

#include "StaticObj.h"

class WooddenCube: public StaticObj {
public:
	WooddenCube(
			int id,
			glm::vec3 scale,
			ObjectType objType,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);
	virtual ~WooddenCube();
	void draw();
	void move(bool flag);
};

#endif /* WOODDENCUBE_H_ */
