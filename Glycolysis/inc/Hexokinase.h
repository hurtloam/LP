/*
 * Glucose6Phosphate.h
 *
 *  Created on: Dec 1, 2016
 *      Author: peter
 */

#ifndef HEXOKINASE_H_
#define HEXOKINASE_H_

#include "StaticObj.h"

class Hexokinase: public StaticObj {
public:
  Hexokinase(
			int id,
			glm::vec3 scale,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);

	virtual ~Hexokinase();
	void draw();
	void move(bool flag);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

};

#endif /* HEXOKINASE_H_ */
