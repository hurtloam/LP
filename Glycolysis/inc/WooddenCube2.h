/*
 * WooddenCube2.h
 *
 *  Created on: Oct 26, 2014
 *      Author: peter
 */

#ifndef WOODDENCUBE2_H_
#define WOODDENCUBE2_H_

#include "StaticObj.h"

class WooddenCube2: public StaticObj {
public:
	WooddenCube2(
			int id,
			glm::vec3 scale,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);

	virtual ~WooddenCube2();
	void draw();
	void move(bool flag);
};

#endif /* WOODDENCUBE2_H_ */
