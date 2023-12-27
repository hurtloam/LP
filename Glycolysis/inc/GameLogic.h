/*
 * GameLogic.h
 *
 *  Created on: Dec 1, 2015
 *      Author: peter
 */

#ifndef INC_GAMELOGIC_H_
#define INC_GAMELOGIC_H_

#include "../stage/inc/Stage.h"

#define NO_TESTS 32

class GameLogic {
public:
	GameLogic(Stage *stage, ResObj& resObj, View& view);
	virtual ~GameLogic();
	bool checkMovement(LPObject *text_obj);
	void check();
	void updatePosition(LPObject *obj);
	void solved();

private:
	int noTests;
	glm::vec3 start_trans[NO_TESTS];
	glm::vec3 box_trans[NO_TESTS];
	glm::vec3 box_transX1[NO_TESTS];
	glm::vec3 box_transX2[NO_TESTS];
	glm::vec3 box_transX3[NO_TESTS];
	int solution_id[NO_TESTS];
	int try_id[NO_TESTS];
	int try_checked[NO_TESTS];
	Stage *stage;
	ResObj& resObj;
	View& view;

};

#endif /* INC_GAMELOGIC_H_ */
