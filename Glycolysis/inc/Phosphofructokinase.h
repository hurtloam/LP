/*
 * Glucose6Phosphate.h
 *
 *  Created on: Dec 1, 2016
 *      Author: peter
 */

#ifndef PHOSPHOFRUCTOKINASE_H_
#define PHOSPHOFRUCTOKINASE_H_

#include "StaticObj.h"

class Phosphofructokinase: public StaticObj {
public:
  Phosphofructokinase(
			int id,
			glm::vec3 scale,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);

	virtual ~Phosphofructokinase();
	void draw();
	void move(bool flag);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

};

#endif /* PHOSPHOFRUCTOKINASE_H_ */
