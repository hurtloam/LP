/*
 * Glucose6Phosphate.h
 *
 *  Created on: Dec 1, 2016
 *      Author: peter
 */

#ifndef GLUCOSE6_PHOSPHATE_H_
#define GLUCOSE6_PHOSPHATE_H_

#include "StaticObj.h"

class Glucose6Phosphate: public StaticObj {
public:
  Glucose6Phosphate(
			int id,
			glm::vec3 scale,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);

	virtual ~Glucose6Phosphate();
	void draw();
	void move(bool flag);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

};

#endif /* GLUCOSE6_PHOSPHATE_H_ */
