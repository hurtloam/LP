/*
 * Molecule.h
 *
 *  Created on: Oct 28, 2017
 *      Author: peter
 */

#ifndef MOLECULE_H_
#define MOLECULE_H_

#include "StaticObj.h"

class Molecule: public StaticObj {
public:
	Molecule(
			int id,
			glm::vec3 scale,
			ObjectType objType,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
      LPUniform lpUniform);

	virtual ~Molecule();
	void draw();
	void move(bool flag);
  void move(std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);

  void
  sawIt(glm::vec3 position, int id);


};

#endif /* MOLECULE_H_ */
