/*
 * MenuItem.h
 *
 *  Created on: Dec 1, 2015
 *      Author: peter
 */

#ifndef MENUITEM_H_
#define MENUITEM_H

#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include "TextObject.h"
#include "StaticObj.h"

class MenuItem: public StaticObj {
public:
  MenuItem(TextObject *first_obj, TextObject *second_obj, int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view,
      LPUniform lpUniform);
	virtual ~MenuItem();
	void draw();
	void move(bool flag);
	void setTrans(glm::vec3 tr);
	void setColor(GLfloat const _color[4]);
  void
  sawIt (glm::vec3 position, int id) {
  }
private:
	TextObject *textObjectFirst;
	TextObject *textObjectSecond;
	int counter;
};

#endif /* MENUITEM_H_ */
