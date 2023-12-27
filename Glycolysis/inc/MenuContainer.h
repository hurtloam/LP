/*
 * TextObject.h
 *
 *  Created on: Sep 6, 2015
 *      Author: peter
 */

#ifndef INC_MENUCONTAINER_H_
#define INC_MENUCONTAINER_H_

#include "StaticObj.h"
#include <string.h>
#include <iostream>

#include "TextObject.h"
#include "TextMenuItem.h"
#include <list>
#include <map>

using namespace std;

const int DEFAULT_START = 1;
const int MENU_SIZE = 8;

typedef void (*FuncPtr) (void);

class MenuContainer: public StaticObj {
public:
	MenuContainer(
			int id,
			glm::vec3 scale,
			list<std::pair<ObjectType, FuncPtr>> objectMap,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);
	void init();
	void init2Lines();
	void initObject();
	virtual ~MenuContainer();
	void draw();
//	void draw(ObjectType obj);
  void
  move (bool flag);

  void
  move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal) {
  }
	void setTrans(glm::vec3 t);
	void setRelativeTrans(glm::vec3 t);
	void setStatusActive() {
		status = MenuStatusE::ACTIVE;
		cout << "STATUS=" << status << endl;
	}
	void setStatus(MenuStatusE s) {status = s; cout << "MenuContainer: STATUS=" << s << endl;}

	void setMenuItem(int item);

	void setStatusDefault();

	void setStatusDefaultOn() { status = MenuStatusE::DEFAULT; }

	void setStatusSelected();

	void setStatusHidden();

	ObjectType getMenuItemObjectType(int i) {return menuItemVector[i]->getObjectType(); }

	int getStatus() {
		return static_cast<int>(status);
	}

	void markMenuItem(int mY);

	void markInitMenuItem(SDL_Window* window, int mX, int mY);

	bool selectMenuItem(SDL_Window* window, int mX, int mY);

	int getMenuItem(int id);

	void setTextItemColor(int index, GLfloat* color);

	void resetItemSelected();

//	void setTrans(glm::vec3 tr);

//	void setColor(GLfloat const _color[4]);
  void
  sawIt (glm::vec3 position, int id) {
  }

private:
	void internalDraw();
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

	list<std::pair<ObjectType, FuncPtr>> objMap;
	TextObject *textObjectFirst;
	TextObject *obj = NULL;

//	std::map<int, int> indexMap;
	vector<TextMenuItem*> menuItemVector;
	TextMenuItem* moreObj;
	TextMenuItem* lessObj;
	list<TextMenuItem*> objList;
	MenuStatusE status = MenuStatusE::HIDDEN;

	int initmY = 0;
	int initmX = 0;
	SDL_Window* _window;
	int selected = 0;
	bool moreFlag = false;
	bool lessFlag = false;
	int start, stop;
};

#endif /* INC_MENUCONTAINER_H_ */
