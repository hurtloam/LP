/*
 * FallingCube.h
 *
 *  Created on: Nov 15, 2014
 *      Author: peter
 */

#ifndef FALLINGCUBE_H_
#define FALLINGCUBE_H_

#include "StaticObj.h"

class FallingCube: public StaticObj {
public:
	FallingCube(
			int id,
			glm::vec3 scale,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);

	virtual ~FallingCube();
	void draw();
	void move(bool flag);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }
private:

};

#endif /* FALLINGCUBE_H_ */
