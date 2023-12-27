/*
 * MazeFloor.h
 *
 *  Created on: Nov 15, 2014
 *      Author: peter
 */

#ifndef MAZEFLOOR_H_
#define MAZEFLOOR_H_

#include "StaticObj.h"

class MazeFloor : public StaticObj {
public:
  MazeFloor (
      int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view,
      LPUniform lpUniform);

  virtual
  ~MazeFloor ();
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

#endif /* MAZEFLOOR_H_ */
