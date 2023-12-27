/*
 * Wall.h
 *
 *  Created on: Oct 04, 2015
 *      Author: peter
 */

#ifndef WALL_H_
#define WALL_H_

#include "StaticObj.h"

class Wall: public StaticObj {
public:
	Wall(
			int id,
			glm::vec3 scale,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);

	virtual ~Wall();
	void draw();
	void move(bool flag);
};

#endif /* WALL_H_ */
