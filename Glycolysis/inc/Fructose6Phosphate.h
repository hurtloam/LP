/*
 * Fructose6Phosphate.h
 *
 *  Created on: Oct 25, 2017
 *      Author: peter
 */

#ifndef FRUCTOSE6_PHOSPHATE_H_
#define FRUCTOSE6_PHOSPHATE_H_

#include "StaticObj.h"

class Fructose6Phosphate: public StaticObj {
public:
  Fructose6Phosphate(
			int id,
			glm::vec3 scale,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);

	virtual ~Fructose6Phosphate();
	void draw();
	void move(bool flag);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }
};

#endif /* FRUCTOSE6_PHOSPHATE_H_ */
