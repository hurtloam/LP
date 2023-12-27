/*
 * SkyBox.h
 *
 *  Created on: Dec 31, 2014
 *      Author: peter
 */

#ifndef SKYBOX_H_
#define SKYBOX_H

#include "StaticObj.h"

class SkyBox: public StaticObj {
public:
	SkyBox(int id,
			glm::vec3 scale,
			ObjectType objType,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);

	virtual ~SkyBox();
	void draw();
	void move(bool flag);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

};

#endif /* SKYBOX_H_ */
