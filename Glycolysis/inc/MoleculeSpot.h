/*
 * MoleculeSpot.h
 *
 *  Created on: Oct 13, 2019
 *      Author: peter
 */

#ifndef MOLECULE_SPOT_H_
#define MOLECULE_SPOT_H_

#include "StaticObj.h"

class MoleculeSpot: public StaticObj {
public:
  MoleculeSpot(
      int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, LPUniform lpUniform);

  virtual
  ~MoleculeSpot();
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

#endif /* MOLECULE_SPOT_H_ */
