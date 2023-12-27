/*
 * GameLogic2.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: peter
 */

#include "../inc/GameLogic2.h"
#include "../inc/Arrow.h"
#include "../inc/Ball.h"
#include "../inc/MenuContainer.h"
#include "../inc/TextMenuItem.h"
#include "../stage/inc/Stage.h"
#include <iostream>
#include "../inc/NoSign.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <map>

using namespace std;

class NoSign;

GameLogic2::GameLogic2(Stage *stage, ResObj& resObj, View& view) : stage(stage), resObj(resObj), view(view)  {

  easyGamePlayInit();

}

void GameLogic2::easyGamePlayInit() {
	std::cout << "ENTER  GameLogic2::easyGamePlayInit" << std::endl;
  float zCoord = 0.0f;
  initPos.push_back(glm::vec3(3.0f, 20.0f, 0.0f));
  initPos.push_back(glm::vec3(4.0f, 19.0f, 0.0f));
  initPos.push_back(glm::vec3(5.0f, 19.0f, 0.0f));
  initPos.push_back(glm::vec3(3.0f, 18.0f, 0.0f));
  initPos.push_back(glm::vec3(4.0f, 17.0f, 0.0f));
  initPos.push_back(glm::vec3(5.0f, 17.0f, 0.0f));
  initPos.push_back(glm::vec3(3.0f, 16.0f, 0.0f));
  initPos.push_back(glm::vec3(4.0f, 12.0f, 0.0f));
  initPos.push_back(glm::vec3(5.0f, 12.0f, 0.0f));
  initPos.push_back(glm::vec3(3.0f, 14.0f, 0.0f));
  initPos.push_back(glm::vec3(4.0f, 14.0f, 0.0f));
  std::cout << "GameLogic2::easyGamePlayInit step 1" << std::endl;
   //  /* initialize random seed:

  std::cout << "GameLogic2::easyGamePlayInit step 2" << std::endl;

  // Glucose
	struct MoleculePos molPos;
	molPos.id = 16001;
//	molPosList[0].initialPos = initPos[molPosList[0].id - 16001];
	molPos.winningPos = glm::vec3(0.0f, 21.0f, 0.0f);
	std::cout << "GameLogic2::easyGamePlayInit step 2.5" << std::endl;
	moleculePosList.push_back(molPos);
	// Glucose 6-phosphate
  struct MoleculePos molPos2;
  molPos2.id = 16002;
//	molPosList[1].initialPos = initPos[molPosList[1].id - 16001];
	molPos2.winningPos = glm::vec3(0.0f, 19.5f, 0.0f);
	moleculePosList.push_back(molPos2);

  // Fructose6-phosphate
  struct MoleculePos molPos3;
	molPos3.id = 16003;
//	molPosList[2].initialPos = initPos[molPosList[2].id - 16001];
	molPos3.winningPos = glm::vec3(0.0f, 18.0f, zCoord);
  moleculePosList.push_back(molPos3);

  // Fructose1,6-bisphosphate
  struct MoleculePos molPos4;
  molPos4.id = 16004;
//  molPosList[3].initialPos = initPos[molPosList[3].id - 16001];
  molPos4.winningPos = glm::vec3(0.0f, 16.5f, zCoord);
  moleculePosList.push_back(molPos4);

  // Dihydroxyacetone phosphate Not in the correct order
  struct MoleculePos molPos5;
  molPos5.id = 16005;
//  molPosList[4].initialPos = initPos[molPosList[4].id - 16001];
  molPos5.winningPos = glm::vec3(-1.0f, 15.8f, zCoord);
  moleculePosList.push_back(molPos5);

  // Glyceraldehyde 3-phosphate
  struct MoleculePos molPos6;
  molPos6.id = 16006;
//  molPosList[5].initialPos = initPos[molPosList[5].id - 16001];
  molPos6.winningPos = glm::vec3(0.0f, 14.6f, zCoord);
  moleculePosList.push_back(molPos6);

  // 1,3-Bisphosphoglycerate
  struct MoleculePos molPos7;
  molPos7.id = 16007;
//  molPosList[6].initialPos = initPos[molPosList[6].id - 16001];
  molPos7.winningPos = glm::vec3(0.0f, 12.9f, zCoord);
  moleculePosList.push_back(molPos7);

  // 3-Phosphoglycerate
  struct MoleculePos molPos8;
  molPos8.id = 16008;
//  molPosList[7].initialPos = initPos[molPosList[7].id - 16001];
  molPos8.winningPos = glm::vec3(0.0f, 11.7f, zCoord);
  moleculePosList.push_back(molPos8);

  // 2-Phosphoglycerate
  struct MoleculePos molPos9;
  molPos9.id = 16009;
//  molPosList[8].initialPos = initPos[molPosList[8].id - 16001];
  molPos9.winningPos = glm::vec3(0.0f, 10.5f, zCoord);
  moleculePosList.push_back(molPos9);

  // Phosphoenol pyruvate
  struct MoleculePos molPos10;
  molPos10.id = 16010;
//  molPosList[9].initialPos = initPos[molPosList[9].id - 16001];
  molPos10.winningPos = glm::vec3(0.0f, 9.3f, zCoord);
  moleculePosList.push_back(molPos10);

  // Pyruvate
  struct MoleculePos molPos11;
  molPos11.id = 16011;
//  molPosList[10].initialPos = initPos[molPosList[10].id - 16001];
  molPos11.winningPos = glm::vec3(0.0f, 8.1f, zCoord);
  moleculePosList.push_back(molPos11);

  std::cout << "GameLogic2::easyGamePlayInit step 4" << std::endl;
  srand (time(NULL));
  int index = 0;
  for (int i = 0; i < 11; i++) {
    if (i != 10) {
      index = std::rand() % (10-i);
    }
    std::cout << "i=" << i << ", " << "Index= " << index << ", initPos[" << index << "]=" << initPos[index].x << "," << initPos[index].y << "," << initPos[index].z << std::endl;
	  moleculePosList[i].initialPos = initPos[index];
	  initPos.erase(initPos.begin() + index);
      std::cout << "erase output: " << index << "\n";
  }
  std::cout << "GameLogic2::easyGamePlayInit step 5" << std::endl;

// init all molecules position at start of the task
  for (struct MoleculePos initState : moleculePosList) {
    stage->getObject(initState.id)->setAbsoluteTrans(initState.initialPos);
  }
  std::cout << "GameLogic2::easyGamePlayInit after setting initState.initialPos" << std::endl;
  /*
// Hexokinase id = 36002
  (static_cast<MenuContainer *>(stage->getTextObject(36002)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // ATP
  (static_cast<MenuContainer *>(stage->getTextObject(36016)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // ADP
  (static_cast<MenuContainer *>(stage->getTextObject(36017)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // Arrow 1
  (static_cast<Arrow *>(stage->getObject(c_arrow + 1)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // Phosphoglucose isomerase
  (static_cast<MenuContainer *>(stage->getTextObject(36004)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  //Arrow 2
  (static_cast<Arrow *>(stage->getObject(c_arrow + 2)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // Phosphofructokinase
  (static_cast<MenuContainer *>(stage->getTextObject(36007)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // ATP
  (static_cast<MenuContainer *>(stage->getTextObject(36116)))->setStatus(LPObject::MenuStatusE::DEFAULT);
  // ADP
  (static_cast<MenuContainer *>(stage->getTextObject(36117)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // Fructose 1,6-bisphosphate

  //Arrow 3
  (static_cast<Arrow *>(stage->getObject(c_arrow + 3)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // Aldolase
  (static_cast<MenuContainer *>(stage->getTextObject(36009)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  //Arrow 4
    (static_cast<Arrow *>(stage->getObject(c_arrow + 4)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // Triose phosphate phosphate isomerase
  (static_cast<MenuContainer *>(stage->getTextObject(36012)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // STAGE 2 ---------------------------------------------------------------

  //Arrow 5
  (static_cast<Arrow *>(stage->getObject(c_arrow + 5)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // Glyceraldehyde 3-phosphate dehydrogenase
  (static_cast<MenuContainer *>(stage->getTextObject(36021)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // Pi,NAD+
  (static_cast<MenuContainer *>(stage->getTextObject(36018)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // NADH
  (static_cast<MenuContainer *>(stage->getTextObject(36019)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  //Arrow 6
  (static_cast<Arrow *>(stage->getObject(c_arrow + 6)))->setStatus(LPObject::MenuStatusE::DEFAULT);


  // Phosphoglycerate kinase
  (static_cast<MenuContainer *>(stage->getTextObject(36025)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // ADP
  (static_cast<MenuContainer *>(stage->getTextObject(36217)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // ATP
  (static_cast<MenuContainer *>(stage->getTextObject(36216)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  //Arrow 7
  (static_cast<Arrow *>(stage->getObject(c_arrow + 7)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // Phosphoglycerate mutase
  (static_cast<MenuContainer *>(stage->getTextObject(36028)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  //Arrow 8
  (static_cast<Arrow *>(stage->getObject(c_arrow + 8)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // Enolase
  (static_cast<MenuContainer *>(stage->getTextObject(36031)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // H2O
  (static_cast<MenuContainer *>(stage->getTextObject(36020)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  //Arrow 9
  (static_cast<Arrow *>(stage->getObject(c_arrow + 9)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // Pyruvate kinase
  (static_cast<MenuContainer *>(stage->getTextObject(36033)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // ADP
  (static_cast<MenuContainer *>(stage->getTextObject(36317)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  // ATP
  (static_cast<MenuContainer *>(stage->getTextObject(36316)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  //Arrow 10
  (static_cast<Arrow *>(stage->getObject(c_arrow + 10)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  cout << "END GameLogic2::easyGamePlayInit" << endl;
   */
}

void GameLogic2::reset() {

	std::cout << "size of moleculeList: " << moleculeList.size() << std::endl;
	std::cout << "size of moleculePosList: " << moleculePosList.size() << std::endl;
	std::cout << "size of initPos: " << initPos.size() << std::endl;

//	for (auto it = moleculeList.begin(); it!= moleculeList.end(); ++it) {
//	  moleculeList.erase(it);
//	}
  moleculeList.clear();
  moleculePosList.clear();

//	moleculePosList.erase(moleculePosList.begin(), moleculePosList.end());
	gameState.reset();
	stage->reloadActorList();
	easyGamePlayInit();

//  std::cout << "size of moleculePosList=" << moleculePosList.size() << ", size of gameState.sequenceList[k]->moleculeList[0]=" << gameState.sequenceList[0]->moleculeList.size() << "size of initPos=" << initPos.size() << std::endl;
}

void GameLogic2::mediumGamePlayInit() {

	std::cout << "ENTER  GameLogic2::easyGamePlayInit" << std::endl;
  float zCoord = 0.0f;
  initPos.push_back(glm::vec3(3.0f, 20.0f, 0.0f));
  initPos.push_back(glm::vec3(4.0f, 19.0f, 0.0f));
  initPos.push_back(glm::vec3(5.0f, 19.0f, 0.0f));
  initPos.push_back(glm::vec3(3.0f, 18.0f, 0.0f));
  initPos.push_back(glm::vec3(4.0f, 17.0f, 0.0f));
  initPos.push_back(glm::vec3(5.0f, 17.0f, 0.0f));
  initPos.push_back(glm::vec3(3.0f, 16.0f, 0.0f));
  initPos.push_back(glm::vec3(4.0f, 12.0f, 0.0f));
  initPos.push_back(glm::vec3(5.0f, 12.0f, 0.0f));
  initPos.push_back(glm::vec3(3.0f, 14.0f, 0.0f));
  initPos.push_back(glm::vec3(4.0f, 14.0f, 0.0f));
  std::cout << "GameLogic2::easyGamePlayInit step 1" << std::endl;
  /* initialize random seed: */

  std::cout << "GameLogic2::easyGamePlayInit step 2" << std::endl;

  // Glucose
	struct MoleculePos molPos;
	molPos.id = 16001;
//	molPosList[0].initialPos = initPos[molPosList[0].id - 16001];
	molPos.winningPos = glm::vec3(0.0f, 21.0f, 0.0f);
	std::cout << "GameLogic2::easyGamePlayInit step 2.5" << std::endl;
	moleculePosList.push_back(molPos);
	// Glucose 6-phosphate
  struct MoleculePos molPos2;
  molPos2.id = 16002;
//	molPosList[1].initialPos = initPos[molPosList[1].id - 16001];
	molPos2.winningPos = glm::vec3(0.0f, 19.5f, 0.0f);
	moleculePosList.push_back(molPos2);

  // Fructose6-phosphate
  struct MoleculePos molPos3;
	molPos3.id = 16003;
//	molPosList[2].initialPos = initPos[molPosList[2].id - 16001];
	molPos3.winningPos = glm::vec3(0.0f, 18.0f, zCoord);
  moleculePosList.push_back(molPos3);

  // Fructose1,6-bisphosphate
  struct MoleculePos molPos4;
  molPos4.id = 16004;
//  molPosList[3].initialPos = initPos[molPosList[3].id - 16001];
  molPos4.winningPos = glm::vec3(0.0f, 16.5f, zCoord);
  moleculePosList.push_back(molPos4);

  // Dihydroxyacetone phosphate Not in the correct order
  struct MoleculePos molPos5;
  molPos5.id = 16005;
//  molPosList[4].initialPos = initPos[molPosList[4].id - 16001];
  molPos5.winningPos = glm::vec3(-1.0f, 15.8f, zCoord);
  moleculePosList.push_back(molPos5);

  // Glyceraldehyde 3-phosphate
  struct MoleculePos molPos6;
  molPos6.id = 16006;
//  molPosList[5].initialPos = initPos[molPosList[5].id - 16001];
  molPos6.winningPos = glm::vec3(0.0f, 14.6f, zCoord);
  moleculePosList.push_back(molPos6);

  // 1,3-Bisphosphoglycerate
  struct MoleculePos molPos7;
  molPos7.id = 16007;
//  molPosList[6].initialPos = initPos[molPosList[6].id - 16001];
  molPos7.winningPos = glm::vec3(0.0f, 12.9f, zCoord);
  moleculePosList.push_back(molPos7);

  // 3-Phosphoglycerate
  struct MoleculePos molPos8;
  molPos8.id = 16008;
//  molPosList[7].initialPos = initPos[molPosList[7].id - 16001];
  molPos8.winningPos = glm::vec3(0.0f, 11.7f, zCoord);
  moleculePosList.push_back(molPos8);

  // 2-Phosphoglycerate
  struct MoleculePos molPos9;
  molPos9.id = 16009;
//  molPosList[8].initialPos = initPos[molPosList[8].id - 16001];
  molPos9.winningPos = glm::vec3(0.0f, 10.5f, zCoord);
  moleculePosList.push_back(molPos9);

  // Phosphoenol pyruvate
  struct MoleculePos molPos10;
  molPos10.id = 16010;
//  molPosList[9].initialPos = initPos[molPosList[9].id - 16001];
  molPos10.winningPos = glm::vec3(0.0f, 9.3f, zCoord);
  moleculePosList.push_back(molPos10);

  // Pyruvate
  struct MoleculePos molPos11;
  molPos11.id = 16011;
//  molPosList[10].initialPos = initPos[molPosList[10].id - 16001];
  molPos11.winningPos = glm::vec3(0.0f, 8.1f, zCoord);
  moleculePosList.push_back(molPos11);

  std::cout << "GameLogic2::easyGamePlayInit step 4" << std::endl;
  srand (time(NULL));
  for (int i = 0; i < 11; i++) {
	  int index = std::rand() % (11-i);
	  std::cout << "Index= " << index << std::endl;
	  moleculePosList[i].initialPos = initPos[index];
      initPos.erase(initPos.begin() + index);
  }
  std::cout << "GameLogic2::easyGamePlayInit step 5" << std::endl;

int questionId = 16051;
//// init all molecules position at start of the task
  for (struct MoleculePos initState : moleculePosList) {
      stage->getObject(initState.id)->setAbsoluteTrans(initState.initialPos);
//      stage->createQuestionCube(initState.winningPos, questionId++, 2);
  }



  // Hexokinase id = 36002
//  setAbsoluteTrans(16001, glm::vec3(-1.2, 20.14, 0.5));
  (static_cast<MenuContainer *>(stage->getTextObject(36002)))->setStatus(LPObject::MenuStatusE::DEFAULT);
//  stage->createMenu(++lp_menuContainer, objList, scale, glm::vec3(-1.2, 19.9, 0.5));

  // ATP
//  setAbsoluteTrans(16002, glm::vec3(1.5, 20.36, 0.5));
  (static_cast<MenuContainer *>(stage->getTextObject(36016)))->setStatus(LPObject::MenuStatusE::DEFAULT);
//  stage->createMenu(++lp_menuContainer, objList, scale, glm::vec3(1.1, 20.0, 0.5));

  // ADP
//  setAbsoluteTrans(36003, glm::vec3(1.5, 19.95, 0.5));
  (static_cast<MenuContainer *>(stage->getTextObject(36017)))->setStatus(LPObject::MenuStatusE::DEFAULT);
//  stage->createMenu(++lp_menuContainer, objList, scale, glm::vec3(1.1, 19.4, 0.5));

//   Glucose 6-phosphate
//  setAbsoluteTrans(36004, glm::vec3(0.0, 19.7, 0.5));
  (static_cast<MenuContainer *>(stage->getTextObject(36004)))->setStatus(LPObject::MenuStatusE::DEFAULT);
//  stage->createMenu(++lp_menuContainer, objList, scale, glm::vec3(0.0, 19.1, 0.5));


  (static_cast<Arrow *>(stage->getObject(c_arrow + 1)))->setStatus(LPObject::MenuStatusE::DEFAULT);

  cout << "END GameLogic2::mediumGamePlayInit" << endl;

}

void GameLogic2::hardGamePlayInit() {

}

int GameLogic2::solved()
{
  if (gameState.isWinning()) {
    return 1;
//    runWinningDialog();// popup window with cheers!!
  }
  return 0;
}

/**
 * Check to see if the text is in the correct position, then it should be
 * coloured green otherwise red
 */
void GameLogic2::check() {

	for (int i = 0; i < NO_TESTS; i++)
	{
//		if (try_id[i] != 0 && try_checked[i] != 1)
		if (try_id[i] != 0)
		{

			if (try_id[i] == solution_id[i])
			{
				cout << "green" << endl;
				stage->getTextObject(try_id[i])->setColor(resObj.green);
				try_checked[i] = 1;
			}
			else
			{
				cout << "red" << endl;
				stage->getTextObject(try_id[i])->setColor(resObj.red);
				try_checked[i] = 1;
			}
		}
	}
}

void GameLogic2::evaluate() {
  //  for (struct Sequence* seq : gameState.sequenceList) {
  for (int k = 0; k < gameState.sequenceList.size(); k++) {
    if (gameState.sequenceList[k]->assessment == NOT_STARTED || gameState.sequenceList[k]->assessment == FAILED) {
      gameState.sequenceList[k]->assessment = SUCCESS;
      for (int i = 0; i < gameState.sequenceList[k]->moleculeList.size(); i++) {
        if (static_cast<MenuContainer *>(stage->getTextObject(gameState.sequenceList[k]->moleculeList[i]+35000))->getMenuItemObjectType(0) != gameState.sequenceList[k]->moleculeList[i]) {
//          std::cout << "ID=" << gameState.sequenceList[k]->moleculeList[i]+35000 << ", MenuItemID=" << (int)(static_cast<MenuContainer *>(stage->getTextObject(gameState.sequenceList[k]->moleculeList[i]+35000))->getMenuItemObjectType(0)) << std::endl;
          gameState.sequenceList[k]->assessment = FAILED;
        }
      }
      if (gameState.sequenceList[k]->assessment == SUCCESS && (k < gameState.sequenceList.size() - 1)) {
        (static_cast<Arrow *>(stage->getObject(c_arrow + 1 + k)))->setColorStatus(ColorStates::S_BLUE);
        k++;
        cout << "k= " << k << endl;
        for (int j = 0; j < gameState.sequenceList[k]->moleculeList.size(); j++) {
          cout << "Next SEQ ITEM ID = " << gameState.sequenceList[k]->moleculeList[j] + 35000 << endl;
          (static_cast<MenuContainer *>(stage->getTextObject(gameState.sequenceList[k]->moleculeList[j] + 35000)))->setStatus(LPObject::MenuStatusE::DEFAULT);
        }
        (static_cast<Arrow *>(stage->getObject(c_arrow + 1 + k)))->setStatus(LPObject::MenuStatusE::DEFAULT);
        cout << "Arrow Object id = " << c_arrow + 1 + k << ", getStatus = " << static_cast<Arrow *>(stage->getObject(c_arrow + 1 + k))->getStatus() << endl;
        // Change color on arrow and molecules
        // lock the molecules. Should not be possible to change them anymore, once there
        // is a successful choice made on all in a sequence.
        k = gameState.sequenceList.size();
      }
      else {
        k = gameState.sequenceList.size(); // finish the loop
      }
    }
  }

}


void GameLogic2::evaluate2() {
  bool showIt = true;
  for (int k = 0; k < gameState.sequenceList.size(); k++) {
    gameState.sequenceList[k]->assessment = SUCCESS;

    // Checking the textual molecules, looping over the moleculeList for each sequence
    // the colour of the text is changed to green if the molecule is in the right spot
    for (int i = 0; i < gameState.sequenceList[k]->moleculeList.size(); i++) {
//      if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000) != nullptr /*&& stage->isAnyInCorrectPosition(gameState.sequenceList[k]->moleculeList[i])*/) {
        TRACE_DEBUG("gameState.sequenceList[%d]->moleculeList[%d]=%d", k, i, gameState.sequenceList[k]->moleculeList[i]);

        int collObj = stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000) != nullptr ? stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000)->getCollisionObj() : 0;
        int collObj100 = stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 100) != nullptr ? stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 100)->getCollisionObj() : 0;
        int collObj200 = stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 200) != nullptr ? stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 200)->getCollisionObj() : 0;
        int collObj300 = stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 300) != nullptr ? stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 300)->getCollisionObj() : 0;
        int collObj400 = stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 400) != nullptr ? stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 400)->getCollisionObj() : 0;

        if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 61000)->getCollisionObj() == (gameState.sequenceList[k]->moleculeList[i] + 21000)) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000)->setColor(resObj.green);
           TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000);
        }
        else if ( stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 61000)->getCollisionObj() == (gameState.sequenceList[k]->moleculeList[i] + 21000 - 100)) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 100)->setColor(resObj.green);
           TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000 - 100);
        }
        else if ( stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 61000)->getCollisionObj() == (gameState.sequenceList[k]->moleculeList[i] + 21000 + 100)) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 100)->setColor(resObj.green);
           TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000 + 100);
        }
        else if ( stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 61000)->getCollisionObj() == (gameState.sequenceList[k]->moleculeList[i] + 21000 + 200)) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 200)->setColor(resObj.green);
           TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000 + 200);
        }
        else if ( stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 61000)->getCollisionObj() == (gameState.sequenceList[k]->moleculeList[i] + 21000 - 200)) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 200)->setColor(resObj.green);
           TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000 - 200);
        }
        else if ( stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 61000)->getCollisionObj() == (gameState.sequenceList[k]->moleculeList[i] + 21000 + 300)) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 300)->setColor(resObj.green);
           TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000 + 300);
        }
        else if ( stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 61000)->getCollisionObj() == (gameState.sequenceList[k]->moleculeList[i] + 21000 - 300)) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 300)->setColor(resObj.green);
           TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000 - 300);
        }
        else if ( stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 61000)->getCollisionObj() == (gameState.sequenceList[k]->moleculeList[i] + 21000 + 400)) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 400)->setColor(resObj.green);
           TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000 + 400);
        }
        else if ( stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 61000)->getCollisionObj() == (gameState.sequenceList[k]->moleculeList[i] + 21000 - 400)) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 400)->setColor(resObj.green);
           TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000 - 400);
        }
        else if ( stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 61000)->getCollisionObj() == (gameState.sequenceList[k]->moleculeList[i] + 21000 + 500)) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 500)->setColor(resObj.green);
           TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000 + 500);
        }
        else if ( stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 61000)->getCollisionObj() == (gameState.sequenceList[k]->moleculeList[i] + 21000 - 500)) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 500)->setColor(resObj.green);
           TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000 - 500);
        }
        else {
          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000) != nullptr && !stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000)->isCorrectPosition()) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000)->setColor(resObj.black);
          }
          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 100) != nullptr && !stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 100)->isCorrectPosition()) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 100)->setColor(resObj.black);
          }
          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 100) != nullptr && !stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 100)->isCorrectPosition()) {
           stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 100)->setColor(resObj.black);
           }
          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 200) != nullptr && !stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 200)->isCorrectPosition()) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 200)->setColor(resObj.black);
          }
          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 200) != nullptr && !stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 200)->isCorrectPosition()) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 200)->setColor(resObj.black);
          }
          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 300) != nullptr && !stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 300)->isCorrectPosition()) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 300)->setColor(resObj.black);
          }
          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 300) != nullptr && !stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 300)->isCorrectPosition()) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 300)->setColor(resObj.black);
          }
          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 400) != nullptr && !stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 400)->isCorrectPosition()) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 400)->setColor(resObj.black);
          }
          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 400) != nullptr && !stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 400)->isCorrectPosition()) {
          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 400)->setColor(resObj.black);
          }
          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 500) != nullptr && !stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 500)->isCorrectPosition()) {
            stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 + 500)->setColor(resObj.black);
          }
          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 500) != nullptr && !stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 500)->isCorrectPosition()) {
            stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000 - 500)->setColor(resObj.black);
          }
          gameState.sequenceList[k]->assessment = FAILED;
        }
//
//        if (collObj == (gameState.sequenceList[k]->moleculeList[i] + 61000) || collObj == (gameState.sequenceList[k]->moleculeList[i] + 61000 + 100) || collObj == (gameState.sequenceList[k]->moleculeList[i] + 61000 + 200) || collObj == (gameState.sequenceList[k]->moleculeList[i] + 61000 + 300) || collObj == (gameState.sequenceList[k]->moleculeList[i] + 61000 -100) || collObj == (gameState.sequenceList[k]->moleculeList[i] + 61000 -200) || collObj == (gameState.sequenceList[k]->moleculeList[i] + 61000 - 300)
//            || collObj100 == (gameState.sequenceList[k]->moleculeList[i] + 61000) || collObj100 == (gameState.sequenceList[k]->moleculeList[i] + 61000 + 100) || collObj100 == (gameState.sequenceList[k]->moleculeList[i] + 61000 + 200) || collObj100 == (gameState.sequenceList[k]->moleculeList[i] + 61000 + 300) || collObj100 == (gameState.sequenceList[k]->moleculeList[i] + 61000 -100) || collObj100 == (gameState.sequenceList[k]->moleculeList[i] + 61000 -200) || collObj100 == (gameState.sequenceList[k]->moleculeList[i] + 61000 - 300)
//            || collObj200 == (gameState.sequenceList[k]->moleculeList[i] + 61000) || collObj200 == (gameState.sequenceList[k]->moleculeList[i] + 61000 + 100) || collObj200 == (gameState.sequenceList[k]->moleculeList[i] + 61000 + 200) || collObj200 == (gameState.sequenceList[k]->moleculeList[i] + 61000 + 300) || collObj200 == (gameState.sequenceList[k]->moleculeList[i] + 61000 -100) || collObj200 == (gameState.sequenceList[k]->moleculeList[i] + 61000 -200) || collObj200 == (gameState.sequenceList[k]->moleculeList[i] + 61000 - 300)
//            || collObj300 == (gameState.sequenceList[k]->moleculeList[i] + 61000) || collObj300 == (gameState.sequenceList[k]->moleculeList[i] + 61000 + 100) || collObj300 == (gameState.sequenceList[k]->moleculeList[i] + 61000 + 200) || collObj300 == (gameState.sequenceList[k]->moleculeList[i] + 61000 + 300) || collObj300 == (gameState.sequenceList[k]->moleculeList[i] + 61000 -100) || collObj300 == (gameState.sequenceList[k]->moleculeList[i] + 61000 -200) || collObj300 == (gameState.sequenceList[k]->moleculeList[i] + 61000 - 300)
//            ){


//        if (collObj == (gameState.sequenceList[k]->moleculeList[i] + 61000)
//            || collObj == (gameState.sequenceList[k]->moleculeList[i] + 100 + 61000)
//            || collObj == (gameState.sequenceList[k]->moleculeList[i] + 200 + 61000)
//            || collObj == (gameState.sequenceList[k]->moleculeList[i] + 300 + 61000)
//
//            || collObj == (gameState.sequenceList[k]->moleculeList[i] - 100 + 61000)
//            || collObj == (gameState.sequenceList[k]->moleculeList[i] - 200 + 61000)
//            || collObj == (gameState.sequenceList[k]->moleculeList[i] - 300 + 61000)) {
//          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000)->setColor(resObj.green);
//          TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000);


//        TRACE_DEBUG("Evaluate2 1 collObj=%d", collObj);
//        if ((gameState.sequenceList[k]->moleculeList[i] + 61000) == collObj) {
//          TRACE_DEBUG("Evaluate2 2");
//          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000)->setColor(resObj.green);
//          TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000);
//        }
//        else {
//          gameState.sequenceList[k]->assessment = FAILED;
//          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000) != nullptr) {
//            stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000)->setColor(resObj.black);
//          }
//        }
//
//        if ((gameState.sequenceList[k]->moleculeList[i] + 61000) == collObj100) {
//          TRACE_DEBUG("Evaluate2 3");
//          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000+100)->setColor(resObj.green);
//          TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000+100);
//        }
//        else {
//          gameState.sequenceList[k]->assessment = FAILED;
//          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000+100) != nullptr) {
//            stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000+100)->setColor(resObj.black);
//          }
//        }
//
//        if ( (gameState.sequenceList[k]->moleculeList[i] + 61000) == collObj200) {
//          TRACE_DEBUG("Evaluate2 4");
//          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000+200)->setColor(resObj.green);
//          TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000+200);
//        }
//        else {
//          gameState.sequenceList[k]->assessment = FAILED;
//          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000+200) != nullptr) {
//            stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000+200)->setColor(resObj.black);
//          }
//        }
//
//        if ((gameState.sequenceList[k]->moleculeList[i] + 61000) == collObj300) {
//          TRACE_DEBUG("Evaluate2 5");
//          stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000+300)->setColor(resObj.green);
//          TRACE_DEBUG("id=%d, Turning it green", gameState.sequenceList[k]->moleculeList[i] + 21000+300);
//          // do nothing
//        }
//        else {
//          gameState.sequenceList[k]->assessment = FAILED;
//          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000+300) != nullptr) {
//            stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000+300)->setColor(resObj.black);
//          }
//        }



//          else {
//            gameState.sequenceList[k]->assessment = FAILED;
//            if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000) != nullptr) {
//              stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000)->setColor(resObj.black);
//            }
//          }

          // Checking the 3d molecule objects, looping over the moleculeObjects list for each sequence,
          // there is no colouring change done on these,
          for (int j = 0; j < gameState.sequenceList[k]->moleculeObjects.size(); j++) {
            for (int v = 0; v < moleculePosList.size(); v++) {
              if (moleculePosList[v].id == gameState.sequenceList[k]->moleculeObjects[j]) {
                if (!stage->getObject(gameState.sequenceList[k]->moleculeObjects[j])->isCorrectPosition()) {
                  gameState.sequenceList[k]->assessment = FAILED;
                }
              }
            }
          }

//        }
//        else {
//          gameState.sequenceList[k]->assessment = FAILED;
//          if (stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000) != nullptr) {
//            stage->getTextObject(gameState.sequenceList[k]->moleculeList[i] + 21000)->setColor(resObj.black);
//          }
//        }
//      }
//      else {
//        gameState.sequenceList[k]->assessment = FAILED;
//      }
    }
    if (gameState.sequenceList[k]->assessment == SUCCESS) {
      if (stage->getObject(c_arrow + 1 + k)->getObjType() == (int)ball) {
        (static_cast<Ball *>(stage->getObject(c_arrow + 1 + k)))->setColorStatus(ColorStates::S_BLUE);
      }else {
      (static_cast<Arrow *>(stage->getObject(c_arrow + 1 + k)))->setColorStatus(ColorStates::S_BLUE);
      }
    }
    else {
      if (stage->getObject(c_arrow + 1 + k)->getObjType() == (int)ball) {
        (static_cast<Ball *>(stage->getObject(c_arrow + 1 + k)))->setColorStatus(ColorStates::S_DEFAULT);
      }else {
      (static_cast<Arrow *>(stage->getObject(c_arrow + 1 + k)))->setColorStatus(ColorStates::S_DEFAULT);
      }
    }
  }
}

//bool GameLogic2::checkMovement(LPObject *text_obj) {
//  if (text_obj != nullptr) {
//      if (text_obj->getId() > 22004 && text_obj->getId() < 22050) {
//          if (text_obj->getTrans().x  < -0.5f &&  text_obj->getTrans().x > -4.5f) {
//              int index = 0;
//              float diff[NO_TESTS];
//              for (int i = 0; i < NO_TESTS; i++){
//                  diff[i] = 0.0f;
//              }
//              diff[index] = fabs(text_obj->getTrans().y - box_transX1[index].y);
//              for (int i = 1; i < NO_TESTS; i++) {
//                  diff[i] = fabs(text_obj->getTrans().y - box_transX1[i].y);
//                  if (diff[i] < diff[index] ) {
//                      index = i;
//                  }
//              }
//              if (try_id[index] == 0) {
//                  text_obj->setTrans(box_transX1[index] - text_obj->getTrans() /*-    glm::vec3(stage->getObject(80001+index)->getScale().x/2.0 0.0f, 0.0f, 0.0f)*/);
//                  try_id[index] = text_obj->getId();
//              }
//              else {
//                  text_obj->setTrans(start_trans[text_obj->getId() - 22005] - text_obj->getTrans() );
//                  text_obj->setColor(resObj.black);
//              }
//          }
//          else if (text_obj->getTrans().x  < 5.5f &&  text_obj->getTrans().x > 0.0f) {
//              int index = 0;
//              float diff[NO_TESTS];
//              for (int i = 0; i < NO_TESTS; i++) {
//                  diff[i] = 0.0f;
//              }
//              diff[index] = fabs(text_obj->getTrans().y - box_transX2[index].y);
//              for (int i = 1; i < NO_TESTS; i++) {
//                  diff[i] = fabs(text_obj->getTrans().y - box_transX2[i].y);
//                  if (diff[i] < diff[index] )
//                    {
//                      index = i;
//                    }
//              }
//              if (try_id[index] == 0) {
//                  text_obj->setTrans(box_transX2[index] - text_obj->getTrans() /*-    glm::vec3(stage->getObject(80001+index)->getScale().x/2.0 0.0f, 0.0f, 0.0f)*/);
//                  try_id[index] = text_obj->getId();
//              }
//              else {
//                  text_obj->setTrans(start_trans[text_obj->getId() - 22005] - text_obj->getTrans() );
//                  text_obj->setColor(resObj.black);
//              }
//          }
//          else {
//              text_obj->setTrans(start_trans[text_obj->getId() - 22005] - text_obj->getTrans() );
//              text_obj->setColor(resObj.black);
//          }
//          check();
//          for (int i = 0; i < NO_TESTS; i++) {
//              std::cout << "try id: " <<  try_id[i] << endl;
//          }
//      }
//  }
//  return true;
//}


/**
 * Updates the position's free or occupied status
 * This is done when the button is pressed
 * @param obj the text object in the position we want to check
 */
void GameLogic2::updatePosition(LPObject *obj)
{
  for (int i = 0; i < NO_TESTS; i++)
  {
    if ((obj->getTrans().y + 0.05) > (box_trans[i].y - 0.05) && (obj->getTrans().y - 0.05) < (box_trans[i].y + 0.05) )
    {
      //			cout << "Trans y ok, obj = " << "(" << obj->getTrans().x << ", " << obj->getTrans().y << ", " << obj->getTrans().z << ")" << endl;
      //			cout << "Trans y ok, box_trans[" << i << "] = " << "(" << box_trans[i].x << ", " << box_trans[i].y << ", " << box_trans[i].z << ")" << endl;
      //			if ((obj->getTrans().x + 1.3) > (box_trans[i].x - 0.1))
      if ((obj->getTrans().x + 0.05) > (box_trans[i].x - 0.05) && (obj->getTrans().x - 0.05) < (box_trans[i].x + 0.05))

      {
        cout << "Trans x ok" << endl;
        try_id[i] = 0;
        try_checked[i] = 0;
      }
    }
  }
  for (int i = 0; i < NO_TESTS; i++)
  {
    std::cout << "Box_Trans id: " <<  stage->getObject(80001+i)->getId() << ", trans: (" << stage->getObject(80001+i)->getTrans().x << ", " << stage->getObject(80001+i)->getTrans().y << ", " << stage->getObject(80001+i)->getTrans().z << ") " << std::endl;
  }
}

void GameLogic2::setAbsoluteTrans(int id, glm::vec3 trans)
{
 stage->getTextObject(id)->setTrans(trans - stage->getTextObject(id)->getTrans());
}


GameLogic2::~GameLogic2()
{
  moleculeList.clear();
  moleculePosList.clear();
  initPos.clear();
}

void GameLogic2::runWinningDialog() {
  const SDL_MessageBoxButtonData buttons[] = {
         { /* .flags, .buttonid, .text */        0, 0, "OK" },

     };
     const SDL_MessageBoxColorScheme colorScheme = {
         { /* .colors (.r, .g, .b) */
             /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
             { 191,  191,   191 },
             /* [SDL_MESSAGEBOX_COLOR_TEXT] */
             {   0, 0,   0 },
             /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
       { 191,  191,   191 },
             /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
             {   127,   127, 127 },
             /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
             { 191,   191, 191 }
         }
     };
     const SDL_MessageBoxData messageboxdata = {
         SDL_MESSAGEBOX_INFORMATION, /* .flags */
         NULL, /* .window */
         "SUCCESS!!!", /* .title */
         "SUCCESS!!!", /* .message */
         SDL_arraysize(buttons), /* .numbuttons */
         buttons, /* .buttons */
         &colorScheme /* .colorScheme */
     };
     int buttonid;
     if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
         SDL_Log("error displaying message box");
     }
     if (buttonid == -1) {
         SDL_Log("no selection");
     } else {
         SDL_Log("selection was %s", buttons[buttonid].text);
     }



}
