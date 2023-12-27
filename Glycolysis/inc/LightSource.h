/*
 * LightSource.h
 *
 *  Created on: Feb 31, 2014
 *      Author: peter
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H

#include "StaticObj.h"

class LightSource: public StaticObj {
public:
  LightSource(int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view,
      LPUniform lpUniform);
	virtual ~LightSource();
	void draw();
	void move(bool flag);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

};

#endif /* LIGHTSOURCE_H_ */
