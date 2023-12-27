/*
 * Creature.h
 *
 *  Created on: Aug 10, 2014
 *      Author: peter
 */

#ifndef CREATURE_H_
#define CREATURE_H_

#include "../inc/Actor.h"

class Creature: public Actor {
public:
	Creature(int id, glm::vec3 scale, ObjectType objType, int objArray_length, GLuint texture,
			glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, GLuint programID,
            GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID, GLuint LightID, GLuint TextureID);
	virtual ~Creature();
	void draw();

  void
  setFPSJumping (bool jump);
  bool
  getFPSJumping () const;

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }
private:
	int counter = 0;
	float _sign = 1.0;
};



#endif /* CREATURE_H_ */
