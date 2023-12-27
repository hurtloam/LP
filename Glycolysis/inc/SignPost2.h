/*
 * SignPost2.h
 *
 *  Created on: Dec 1, 2015
 *      Author: peter
 */

#ifndef SIGNPOST2_H_
#define SIGNPOST2_H

#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include "TextObject.h"
#include "StaticObj.h"

class SignPost2: public StaticObj {
public:
  SignPost2 (TextObject *first_obj, TextObject *second_obj, TextObject *third_obj, int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch,
             ResObj& resObj, const View& view, LPUniform lpUniform);
	virtual ~SignPost2();
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
	TextObject *textObjectThird;
	int counter;
};

#endif /* SIGNPOST2_H_ */
