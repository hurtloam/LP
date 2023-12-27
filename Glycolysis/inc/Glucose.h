/*
 * WooddenCube2.h
 *
 *  Created on: Oct 26, 2014
 *      Author: peter
 */

#ifndef GLUCOSE_H_
#define GLUCOSE_H_

#include "StaticObj.h"

class Glucose: public StaticObj {
public:
	Glucose(
			int id,
			glm::vec3 scale,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);

	virtual ~Glucose();
	void draw();
	void move(bool flag);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }
};

#endif /* GLUCOSE_H_ */
