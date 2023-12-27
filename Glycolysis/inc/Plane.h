/*
 * Plane.h
 *
 *  Created on: Nov 22, 2015
 *      Author: peter
 */

#ifndef PLANE_H_
#define PLANE_H

#include "StaticObj.h"

class Plane: public StaticObj {
public:
	Plane(
			int id,
			glm::vec3 scale,
			ObjectType objType,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);
	virtual ~Plane();
	void draw();
	void move(bool flag);
  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }
};

#endif /* PLANE_H_ */
