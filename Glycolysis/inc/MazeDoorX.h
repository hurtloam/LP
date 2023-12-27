/*
 * MazeDoorX.h
 *
 *  Created on: Nov 15, 2014
 *      Author: peter
 */

#ifndef MAZEDOORX_H_
#define MAZEDOORX_H_

#include "StaticObj.h"

class MazeDoorX : public StaticObj {
public:
  MazeDoorX (
      int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view,
      LPUniform lpUniform);

  virtual
  ~MazeDoorX ();
  void
  draw ();
  void
  move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);
  void
  setOpenDoor ();

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

private:
  bool openDoor = false;
  int delay = 0;
  int delay2 = 0;
};

#endif /* MAZEDOORX_H_ */
