/*
 * Text.h
 *
 *  Created on: Sep 5, 2015
 *      Author: peter
 */

#ifndef INC_TEXT_H_
#define INC_TEXT_H_

#include "../stage/inc/Stage.h"

class Text: public Stage {
public:
  Text (LPWatch* watch, ResObj& resObj, View& view);
	void init();
	virtual ~Text();
};

#endif /* INC_TEXT_H_ */
