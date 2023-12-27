/*
 * MoleculeSpot.h
 *
 *  Created on: Oct 13, 2019
 *      Author: peter
 */

#ifndef TEXT_SPOT_H_
#define TEXT_SPOT_H_

#include "StaticObj.h"

class TextSpot: public StaticObj {
public:
  TextSpot(
      int id, ObjectType obj, glm::vec3 shape, glm::vec3 scale, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, LPUniform lpUniform);

  virtual
  ~TextSpot();
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
  void internalDraw(bool isItemSelected);

  struct point {
    GLfloat x;
    GLfloat y;
    GLfloat s;
    GLfloat t;
  };
  glm::vec3 pos;

  bool openDoor = false;
  int delay = 0;
  int delay2 = 0;
};

#endif /* TEXT_SPOT_H_ */
