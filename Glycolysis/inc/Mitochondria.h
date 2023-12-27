/*
 * WallCube.h
 *
 *  Created on: Dec 31, 2014
 *      Author: peter
 */

#ifndef MITOCHONDRIA_H_
#define MITOCHONDRIA_H_

#include "StaticObj.h"

class Mitochondria: public StaticObj {
public:
  Mitochondria(int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view,
      LPUniform lpUniform);
	virtual ~Mitochondria();
	void draw();
	void move(bool flag);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

};

#endif /* MITOCHONDRIA_H_ */
