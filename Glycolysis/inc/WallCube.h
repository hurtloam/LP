/*
 * WallCube.h
 *
 *  Created on: Dec 31, 2014
 *      Author: peter
 */

#ifndef WALLCUBE_H_
#define WALLCUBE_H

#include "StaticObj.h"
#include <glm/detail/type_vec3.hpp>

class WallCube: public StaticObj {
public:
  WallCube(int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, LPUniform lpUniform);
	virtual ~WallCube();
	void draw();
	void move(bool flag);
};

#endif /* WALLCUBE_H_ */
