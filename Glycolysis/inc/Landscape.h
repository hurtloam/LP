/*
 * Landscape.h
 *
 *  Created on: Nov 18, 2018
 *      Author: peter
 */

#pragma once

#include "StaticObj.h"

class Landscape: public StaticObj {
public:
  Landscape(int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view,
      LPUniform lpUniform);
	virtual ~Landscape();
	void draw();
	void move(bool flag);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

};
