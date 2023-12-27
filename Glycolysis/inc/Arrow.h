/*
 * Wall.h
 *
 *  Created on: Oct 04, 2015
 *      Author: peter
 */

#ifndef ARROW_H_
#define ARROW_H_

#include "StaticObj.h"

class Arrow: public StaticObj {
public:
	Arrow(
			int id,
			glm::vec3 scale,
			ObjectType obj,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
			LPUniform lpUniform);

	virtual ~Arrow();
	void draw();
  void
  move (bool flag);
  void move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);
//	enum MenuStatusE {
//	  DEFAULT = 0,
//	  ACTIVE = 1, // menuItem has not yet been selected
//	  SELECTED = 2,    // menuItem has been selected
//	  HIDDEN = 3   // The menuContainer is hidden
//	};


	void setStatus(MenuStatusE s) {status = s;cout << "Arrow: STATUS=" << s << endl;}

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

	int getStatus() {
	  return static_cast<int>(status);
	}

	void setColorStatus(ColorStates s) { colorStatus = s; }

private:
	ObjectType objType;
	MenuStatusE status = MenuStatusE::HIDDEN;
	ColorStates colorStatus = ColorStates::S_DEFAULT;

};

#endif /* ARROW_H_ */
