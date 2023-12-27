/*
 * GameLogic2.h
 *
 *  Created on: Nov 6, 2016
 *      Author: peter
 */

#ifndef INC_GAME_STATE_H_
#define INC_GAME_STATE_H_

#include "../stage/inc/Stage.h"

enum Assessment {
  NOT_STARTED,
  STARTED,
  SUCCESS,
  FAILED
};

enum Winning {
  W_DEFAULT,
  W_ALREADY_WON
};

struct Sequence{
  int id;
  string name;
  Assessment assessment;
  std::vector<ObjectType> moleculeList; // textual molecules, their objType
  std::vector<int> moleculeObjects; // 3d objects, their id
};

class GameState {
public:
  GameState();
	virtual ~GameState();
  void init();
  void reset();
//  Sequence* createSequence(int& id, string& name, std::vector<ObjectType>& moleculeList);
  Sequence* createSequence(int& id, string& name, std::vector<ObjectType>& moleculeList, std::vector<int>& moleculeObjects);
  bool isWinning();
  Assessment getAssessment(int index) {
    if (sequenceList.size() > 12) {
      return sequenceList[index]->assessment;
    }
    return Assessment::NOT_STARTED;
  }
//  bool setWinning(bool win);
  Winning winningStatus = W_DEFAULT;

	std::vector<struct Sequence*> sequenceList;
private:

};

#endif /* INC_GAME_STATE_H_ */
