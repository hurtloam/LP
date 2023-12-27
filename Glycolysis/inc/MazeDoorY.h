/*
 * MazeDoorY.h
 *
 *  Created on: Nov 15, 2014
 *      Author: peter
 */

#ifndef MAZEDOORY_H_
#define MAZEDOORY_H_

#include "StaticObj.h"

class MazeDoorY : public StaticObj {
public:
  MazeDoorY (
      int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view,
      LPUniform lpUniform);

  virtual
  ~MazeDoorY ();
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

#endif /* MAZEDOORY_H_ */
