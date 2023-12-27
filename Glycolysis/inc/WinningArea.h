/*
 * WinningArea.h
 *
 *  Created on: Nov 15, 2014
 *      Author: peter
 */

#ifndef WINNINGAREA_H_
#define WINNINGAREA_H_

#include "StaticObj.h"

class WinningArea : public StaticObj {
public:
  WinningArea (
      int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, LPUniform lpUniform);

  virtual
  ~WinningArea ();
  void
  draw ();
  void
  move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);
  void
  setOpenDoor ();

private:
  bool openDoor = false;
  int delay = 0;
  int delay2 = 0;
};

#endif /* WINNINGAREA_H_ */
