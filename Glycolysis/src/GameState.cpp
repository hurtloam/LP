/*
 * GameState.cpp
 *
 *  Created on: Nov 8, 2016
 *      Author: peter
 */

#include "../inc/GameState.h"

GameState::GameState() {
  init();
}

void GameState::reset() {
	for (int i = 0; i < sequenceList.size(); i++) {
		sequenceList[i]->moleculeList.clear();
		delete sequenceList[i];
		sequenceList.clear();
	}
	init();
}

GameState::~GameState() {
  for (int i = 0; i < sequenceList.size(); i++) {
    sequenceList[i]->moleculeList.clear();
    delete sequenceList[i];
    sequenceList.clear();
  }
}

void GameState::init() {
  int id = 0;

  string name1 = "Glucose 6-phosphate";
  std::vector<ObjectType> moleculeList;
  std::vector<int> moleculeObjects;

  moleculeList.push_back(txt_2);
  moleculeList.push_back(txt_16); // ATP
  moleculeList.push_back(txt_17); // ADP

  moleculeObjects.push_back(16001); // id's of the molecules
  moleculeObjects.push_back(16002);

  sequenceList.push_back(createSequence(++id, name1, moleculeList, moleculeObjects));

  moleculeList.clear();
  name1.clear();
  string name2 = "Fructose 6-phosphate";
  std::vector<ObjectType> moleculeList2;
  std::vector<int> moleculeObjects2;
  moleculeList2.push_back(txt_4);

  moleculeObjects2.push_back(16002);
  moleculeObjects2.push_back(16003);

  sequenceList.push_back(createSequence(++id, name2, moleculeList2, moleculeObjects2));

  string name3 = "Fructose 1,6-bisphosphate";
  std::vector<ObjectType> moleculeList3;
  std::vector<int> moleculeObjects3;
  moleculeList3.push_back(txt_7);
  moleculeList3.push_back(txt_116); // ATP
  moleculeList3.push_back(txt_117); // ADP
//  moleculeList3.push_back(txt_8);

  moleculeObjects3.push_back(16003);
  moleculeObjects3.push_back(16004);

  sequenceList.push_back(createSequence(++id, name3, moleculeList3, moleculeObjects3));

  string name4 = "Dihydroxyacetone phosphate";
  std::vector<ObjectType> moleculeList4;
  std::vector<int> moleculeObjects4;
  moleculeList4.push_back(txt_9);
//  moleculeList4.push_back(txt_10);

  moleculeObjects4.push_back(16004);
  moleculeObjects4.push_back(16005);

  sequenceList.push_back(createSequence(++id, name4, moleculeList4, moleculeObjects4));

  string name5 = "Glyceraldehyde 3-phosphate";
  std::vector<ObjectType> moleculeList5;
  std::vector<int> moleculeObjects5;
  moleculeList5.push_back(txt_12);
//  moleculeList5.push_back(txt_14);

  moleculeObjects5.push_back(16005);
  moleculeObjects5.push_back(16006);

  sequenceList.push_back(createSequence(++id, name5, moleculeList5, moleculeObjects5));

  string name6 = "1,3-Bisphosphoglycerate";
  std::vector<ObjectType> moleculeList6;
  std::vector<int> moleculeObjects6;
  moleculeList6.push_back(txt_21);
  moleculeList6.push_back(txt_18);
  moleculeList6.push_back(txt_19);
//  moleculeList6.push_back(txt_24);

  moleculeObjects6.push_back(16006);
  moleculeObjects6.push_back(16007);

  sequenceList.push_back(createSequence(++id, name6, moleculeList6, moleculeObjects6));


  string name7 = "3-Phosphoglycerate";
  std::vector<ObjectType> moleculeList7;
  std::vector<int> moleculeObjects7;
  moleculeList7.push_back(txt_25);
  moleculeList7.push_back(txt_217);  // ADP
  moleculeList7.push_back(txt_216);  // ATP
//  moleculeList7.push_back(txt_27);

  moleculeObjects7.push_back(16007);
  moleculeObjects7.push_back(16008);

  sequenceList.push_back(createSequence(++id, name7, moleculeList7, moleculeObjects7));

  string name8 = "2-Phosphoglycerate";
  std::vector<ObjectType> moleculeList8;
  std::vector<int> moleculeObjects8;
  moleculeList8.push_back(txt_28);
//  moleculeList8.push_back(txt_30);

  moleculeObjects8.push_back(16008);
  moleculeObjects8.push_back(16009);

  sequenceList.push_back(createSequence(++id, name8, moleculeList8, moleculeObjects8));

  string name9 = "Phosphoenolpyruvate";
  std::vector<ObjectType> moleculeList9;
  std::vector<int> moleculeObjects9;
  moleculeList9.push_back(txt_31);
  moleculeList9.push_back(txt_20);
//  moleculeList9.push_back(txt_32);

  moleculeObjects9.push_back(16009);
  moleculeObjects9.push_back(16010);

  sequenceList.push_back(createSequence(++id, name9, moleculeList9, moleculeObjects9));

  string name10 = "Pyruvate";
  std::vector<ObjectType> moleculeList10;
  std::vector<int> moleculeObjects10;
  moleculeList10.push_back(txt_33);
  moleculeList10.push_back(txt_317);
  moleculeList10.push_back(txt_316);
//  moleculeList10.push_back(txt_34);

  moleculeObjects10.push_back(16010);
  moleculeObjects10.push_back(16011);

  sequenceList.push_back(createSequence(++id, name10, moleculeList10, moleculeObjects10));


  // push a new sequenceList for the textual question on Regulatory functions

  string name11 = "Hexokinase Regulation";
  std::vector<ObjectType> moleculeList11;
  std::vector<int> moleculeObjects11;
  moleculeList11.push_back(txt_Glucose_6_phosphate);

  sequenceList.push_back(createSequence(++id, name11, moleculeList11, moleculeObjects11));

  string name12 = "Phosphofructokinase Regulation";
  std::vector<ObjectType> moleculeList12;
  std::vector<int> moleculeObjects12;
  moleculeList12.push_back(txt_416);
  moleculeList12.push_back(txt_Citrate);
  moleculeList12.push_back(txt_AMP);

  sequenceList.push_back(createSequence(++id, name12, moleculeList12, moleculeObjects12));

  string name13 = "Pyruvate kinase Regulation";
  std::vector<ObjectType> moleculeList13;
  std::vector<int> moleculeObjects13;
  moleculeList13.push_back(txt_516);
  moleculeList13.push_back(txt_Alanin);
  moleculeList13.push_back(txt_8);

  sequenceList.push_back(createSequence(++id, name13, moleculeList13, moleculeObjects13));
}

struct Sequence* GameState::createSequence(int& id, string& name, std::vector<ObjectType>& moleculeList, std::vector<int>& moleculeObjects) {
  Sequence * seq = new Sequence();
  seq->id = id;
  seq->name = name;
  seq->assessment = NOT_STARTED;
  seq->moleculeList = moleculeList;
  seq->moleculeObjects = moleculeObjects;
  return seq;
}

bool GameState::isWinning() {
  for (int k = 0; k < sequenceList.size(); k++) {
//  for (int k = 0; k < 1; k++) {
    if (sequenceList[k]->assessment != SUCCESS) {
      winningStatus = W_DEFAULT;
      return false;
    }
  }
  if (winningStatus != W_ALREADY_WON) {
    winningStatus = W_ALREADY_WON;
    return true;
  }
//  else
//  {
//    return false;
//  }
}


