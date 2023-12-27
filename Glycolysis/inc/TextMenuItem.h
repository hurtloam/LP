/*
 * TextObject.h
 *
 *  Created on: Sep 6, 2015
 *      Author: peter
 */

#ifndef INC_TEXTMENUITEM_H_
#define INC_TEXTMENUITEM_H_

#include "StaticObj.h"
#include <string.h>
#include <iostream>

#include "TextObject.h"

using namespace std;

class TextMenuItem: public StaticObj {
public:
	TextMenuItem(
			int id,
			glm::vec3 scale,
			ObjectType obj1,
			ObjectType obj2,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);
	void init();
	virtual ~TextMenuItem();
	void draw();
//	void draw(ObjectType obj);
	void move(bool flag);
  void
  move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal) {
  }

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

	void setTrans(glm::vec3 tr);

//	void setColor(GLfloat const _color[4]);

	void setTextColor(GLfloat const _color[4]);
	void setMenuColor(GLfloat const _color[4]);

	void setIsItemSelected(bool t) {isItemSelected = t; }

	void setBoxSize(GLfloat boxSize) { this->boxSize = boxSize; }

  GLfloat getBoxSize() const {
    return boxSize;
  }

private:
	void internalDraw(bool isItemSelected);
	bool isItemSelected = false;
	float x;
	float y;
	float x_start;
	float y_start;
	float sx;
	float sy;
	char text[256];

	GLuint text_program_id;
	GLint attribute_coord = -1;
	GLint uniform_tex = -1;
	GLint uniform_color = -1;
	GLint attribute_UV = -1;

	GLuint texture_local;
	GLuint texture_local2;


//	glm::vec4 black = glm::vec4(0, 0, 0, 1);
//	glm::vec4 red = glm::vec4(1.f, 0.f, 0.f, 1.f);
//	glm::vec4 green = glm::vec4(0.f, 1.f, 0.f, 1.f);
//	glm::vec4 transparent_green = glm::vec4(0.f, 1.f, 0.f, 0.5f);

//	GLfloat black[4] = { 0, 0, 0, 1 };
//	GLfloat red[4] = { 1, 0, 0, 1 };
//	GLfloat transparent_green[4] = { 0.f, 1.f, 0.f, 0.5f };
//	GLfloat green[4] = { 0, 1, 0, 1 };
//	GLfloat color[4];

//	glm::vec4 color;

	struct point {
		GLfloat x;
		GLfloat y;
		GLfloat s;
		GLfloat t;
	};
	glm::vec3 pos;
//	FT_Library ft;
//	list<FT_Face> faces;
//	list<point[4]> boxes;
	unsigned char *fontBuffer;

	const char *fontfilename;
	GLuint vbo[64];
	GLuint tex[64];

	int counter;

	ObjectType localObj1;
	ObjectType localObj2;
	TextObject *textObjectFirst;
	TextObject *textObjectSecond;

	GLfloat boxSize = 1.6f;
};

#endif /* INC_TEXTMENUITEM_H_ */
