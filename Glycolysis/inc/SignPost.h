/*
 * SignPost.h
 *
 *  Created on: Dec 1, 2015
 *      Author: peter
 */

#ifndef SIGNPOST_H_
#define SIGNPOST_H

#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include "TextObject.h"
#include "../inc/StaticObj.h"

class SignPost: public StaticObj {
public:
  SignPost(TextObject *first_obj, TextObject *second_obj, int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view,
      LPUniform lpUniform);
	virtual ~SignPost();
	void draw();
	void move(bool flag);
	void setTrans(glm::vec3 tr);
	void setColor(GLfloat const _color[4]);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

private:
	TextObject *textObjectFirst;
	TextObject *textObjectSecond;
	int counter;
};

#endif /* SIGNPOST_H_ */
