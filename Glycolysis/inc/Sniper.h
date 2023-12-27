/*
 * Sniper.h
 *
 *  Created on: Jul 8, 2014
 *      Author: peter
 */

#ifndef SNIPER_H_
#define SNIPER_H_

#include "StaticObj.h"

#include "View.h"
#include "ResObj.h"
#include "LineObj.h"

class Sniper: public StaticObj {
public:
  Sniper(int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, LPUniform lpUniform);

  virtual
  ~Sniper ();
  void
  draw ();
  void
  move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);

  void
  sawIt (glm::vec3 position, int id);

private:
  bool wasCollisionDetecedLastFrame = false;
  int movingStraightLength = 0;
  int counter;
  float _sign;
  LineObj *line;
  ObjectType currentObject;
};

#endif /* SNIPER_H_ */
