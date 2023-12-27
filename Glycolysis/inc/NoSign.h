/*
 * SignPost.h
 *
 *  Created on: Dec 1, 2015
 *      Author: peter
 */

#ifndef NOSIGN_H_
#define NOSIGN_H

#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include "TextObject.h"
#include "StaticObj.h"

class NoSign: public StaticObj {
public:
  NoSign(TextObject *first_obj, TextObject *second_obj, int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view,
      LPUniform lpUniform);
	virtual ~NoSign();
	void draw();
  void move(bool flag);
	void setTrans(glm::vec3 tr);
	void setColor(GLfloat const _color[4]);
	void setNo(int no);
	ObjectType setInternalNo(int no);

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

private:
	ObjectType obj_typeFirst;
	ObjectType obj_typeSecond;
	TextObject *textObjectFirst;
	TextObject *textObjectSecond;
	int counter;
};

#endif /* NOSIGN_H_ */
