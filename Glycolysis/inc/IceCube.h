/*
 * IceCube.h
 *
 *  Created on: Oct 25, 2014
 *      Author: peter
 */

#ifndef ICECUBE_H_
#define ICECUBE_H_

#include "Actor.h"
#include "View.h"
#include "ResObj.h"

class IceCube: public Actor {
public:
	IceCube(int id,
			glm::vec3 scale,
			ObjectType objType,
			int objArray_length,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
			GLuint programID,
			GLuint MatrixID,
			GLuint ViewMatrixID,
			GLuint ModelMatrixID,
			GLuint LightID,
			GLuint TextureID);


	virtual ~IceCube();
	void draw();
  void
  move (bool flag);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

private:
	int counter = 0;
	float _sign = 1.0;

};

#endif /* ICECUBE_H_ */
