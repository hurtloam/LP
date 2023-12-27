/*
 * GameLogic2.h
 *
 *  Created on: Nov 6, 2016
 *      Author: peter
 */

#ifndef INC_GAMELOGIC2_H_
#define INC_GAMELOGIC2_H_

#include "../stage/inc/Stage.h"
#include "../inc/GameState.h"
#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <vector>

#define NO_TESTS 32

struct MoleculePos {
    int id;
    glm::vec3 initialPos;
    glm::vec3 winningPos;
};


class GameLogic2 {
public:
  GameLogic2(Stage *stage, ResObj& resObj, View& view);
	virtual ~GameLogic2();
//	bool checkMovement(LPObject *text_obj);
	void check();
	void updatePosition(LPObject *obj);
	int solved();
	void setAbsoluteTrans(int id, glm::vec3 trans);
	void evaluate();
	void evaluate2();
	void reset();
	void runWinningDialog();
	void easyGamePlayInit();
	void mediumGamePlayInit();
  void hardGamePlayInit();

	GameState gameState;
private:
	std::vector<int> moleculeList;

	std::vector<struct MoleculePos> moleculePosList;

	int noTests;
	glm::vec3 start_trans[NO_TESTS];
	glm::vec3 box_trans[NO_TESTS];
	glm::vec3 box_transX1[NO_TESTS];
	glm::vec3 box_transX2[NO_TESTS];
	glm::vec3 box_transX3[NO_TESTS];
	int solution_id[NO_TESTS];
	int try_id[NO_TESTS];
	int solvedItems[7];
	int try_checked[NO_TESTS];
	Stage *stage;
	ResObj& resObj;
	View& view;
	std::vector<glm::vec3> initPos;

};

#endif /* INC_GAMELOGIC_H2_ */
