/*
 * Plate.h
 *
 *  Created on: May 11, 2016
 *      Author: peter
 */

#ifndef PLATE_H_
#define PLATE_H

#include "StaticObj.h"

class Plate: public StaticObj {
public:
  Plate(int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view,
      LPUniform lpUniform);
	virtual ~Plate();
	void draw();
//	void move(bool flag);
  void
  move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

};

#endif /* PLATE_H_ */
