/*
 * TextObject.h
 *
 *  Created on: Sep 6, 2015
 *      Author: peter
 */

#ifndef INC_TEXTOBJECT_H_
#define INC_TEXTOBJECT_H_

#include "StaticObj.h"
#include <string.h>
#include <iostream>

using namespace std;

class TextObject: public StaticObj {
public:
	TextObject(
			int id,
			glm::vec3 scale,
			ObjectType obj,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);
	virtual ~TextObject();
	void draw();
	void draw(ObjectType obj);
  void move(std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);
  void move(bool flag);
	float getTextWidth() {return text_width;}

private:
	float x;
	float y;
	float x_start;
	float y_start;
	float sx;
	float sy;
	char text[256];

	GLint attribute_coord = -1;
	GLint uniform_tex = -1;
	GLint uniform_color = -1;
	GLint attribute_UV = -1;
	struct point {
		GLfloat x;
		GLfloat y;
		GLfloat s;
		GLfloat t;
	};
	glm::vec3 pos;
	unsigned char *fontBuffer;

	const char *fontfilename;
	GLuint vbo[64];
	GLuint tex[64];

	float text_width;
	int counter;
};

#endif /* INC_TEXTOBJECT_H_ */
