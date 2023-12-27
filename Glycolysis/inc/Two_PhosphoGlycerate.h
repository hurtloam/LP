/*
 * Two_PhosphoGlycerate.h
 *
 *  Created on: Dec 31, 2014
 *      Author: peter
 */

#ifndef TWO_PHOSPHO_GLYCERATE_H_
#define TWO_PHOSPHO_GLYCERATE_H_

#include "StaticObj.h"

class Two_PhosphoGlycerate: public StaticObj {
public:
  Two_PhosphoGlycerate(int id, glm::vec3 scale, ObjectType objType, GLuint texture, glm::vec3 trans, LPWatch* watch, ResObj& resObj, const View& view, LPUniform lpUniform);
	virtual ~Two_PhosphoGlycerate();
	void draw();
	void move(bool flag);
};

#endif /* TWO_PHOSPHO_GLYCERATE_H_ */
