/*
 * FPerson.h
 *
 *  Created on: Jul 9, 2014
 *      Author: peter
 */

#ifndef FPERSON_H_
#define FPERSON_H_

//#include "StaticObj.h"
#include "Actor.h"

class FPerson : public Actor {
public:
  FPerson(int id, glm::vec3 scale, ObjectType objType, int objArray_length, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, GLuint programID, GLuint MatrixID,
           GLuint ViewMatrixID, GLuint ModelMatrixID, GLuint LightID, GLuint TextureID);
  virtual ~FPerson();
  void draw();
  void move(std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);

  const glm::vec3& getDirection() const
  {
    return direction;
  }

  void setDirection(const glm::vec3& direction)
  {
    this->direction = direction;
  }

  const glm::vec3& getRight() const
  {
    return right;
  }

  void setRight(const glm::vec3& right)
  {
    this->right = right;
  }



  const bool* getWasd() const
  {
    return wasd;
  }

  void setWasd(bool* wasd)
  {
    this->wasd[0] = wasd[0];
    this->wasd[1] = wasd[1];
    this->wasd[2] = wasd[2];
    this->wasd[3] = wasd[3];
    this->wasd[4] = wasd[4];
    this->wasd[5] = wasd[5];
    this->wasd[6] = wasd[6];

    SDL_Log ("ENTER setWasd wasd = (%d,%d,%d,%d,%d,%d,%d,)", wasd[0], wasd[1], wasd[2], wasd[3], wasd[4], wasd[5], wasd[6]);
  }

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

private:
  int key = 6;
  int secondKey = 6;
  bool wasd[7] =
  { false, false, false, false, false, false, false };
  LPObject* lastDetectedCollisionObj = nullptr;
  glm::vec3 direction;
  glm::vec3 right;
  int collisionDirection = 6; // default is "still"
  glm::vec3 collisiondirectionVec;
  int sndCnt = 0;
//  int *logOutputPtr = nullptr;

  glm::vec3 useThisNormal;
  bool oldFlag;

  int timer;
  int timerThreshold;
};

#endif /* FPERSON_H_ */
