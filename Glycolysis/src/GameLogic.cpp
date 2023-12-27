/*
 * GameLogic.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: peter
 */

#include "../inc/GameLogic.h"
#include "../stage/inc/Stage.h"
#include <iostream>
#include "../inc/NoSign.h"

using namespace std;

class NoSign;

GameLogic::GameLogic(Stage *stage, ResObj& resObj, View& view) : stage(stage), resObj(resObj), view(view)  {
	// TODO Auto-generated constructor stub

//		box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(/*stage->getObject(80001+i)->getScale().x*/0.0f, -0.15f, 0.1f);
	for (int i = 0; i < NO_TESTS; i++) {
		start_trans[i] = stage->getTextObject(22005+i)->getTrans();
		solution_id[i] = 22005+i;
		try_id[i] = 0;
		try_checked[i] = 0;
		box_transX1[i] = glm::vec3(700.0f, 700.0f, 700.0f);
		box_transX2[i] = glm::vec3(700.0f, 700.0f, 700.0f);
		box_trans[i] = glm::vec3(700.0f, 700.0f, 700.0f);
	}

	int i = 0;
	// Glucose
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(.8f, -0.25f, 0.1f);
	box_transX1[i] = box_trans[i];

	i++;
	// Hexokinase
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.1f, -0.25f, 0.1f);
	box_transX1[i] = box_trans[i];

	i++;
	// ATP
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.75f, -0.25f, 0.1f);
	box_transX2[i] = box_trans[i];

	i++;
	// ADP
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.75f, -0.25f, 0.1f);
	box_transX2[i] = box_trans[i];

	i++;
	// Glucose 6-phosphate
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(-1.0f, -0.25f, 0.1f);
	box_transX1[i] = box_trans[i];
	// added 0.1 on all above

	i++;
	// Phosphoglucose isomerase
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.05f, -0.15f, 0.15f);
	box_transX1[i] = box_trans[i];

	i++;
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(-1.15f, -0.25f, 0.1f);
	box_transX1[i] = box_trans[i];

	i++;
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(-0.3f, -0.25f, 0.1f);
	box_transX1[i] = box_trans[i];

	i++;
	// ATP
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.75f, -0.25f, 0.1f);
	box_transX2[i] = box_trans[i];

	i++;
	// ADP
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.75f, -0.25f, 0.1f);
	box_transX2[i] = box_trans[i];

	i++;
	// Fructose 1,6-bisphosphate
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(-1.15f, -0.25f, 0.1f);
	box_transX1[i] = box_trans[i];

	i++;
	// Aldolase
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.1f, -0.25f, 0.1f);
	box_transX2[i] = box_trans[i];

	i++;
	// Dihydroxyacetone phosphate
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.05f, -0.00f, 0.09f);
	box_transX1[i] = box_trans[i];

	i++;
	// Triose phosphate phosphate isomerase
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.05f, -0.04f, 0.08f);
	box_transX1[i] = box_trans[i];

	i++;
	// Glyceraldehyde 3-phosphate
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.05f, 0.05f, 0.3f);
	box_transX2[i] = box_trans[i];

	i++;
	// Glyceraldehyde 3-phosphate dehydrogenase
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.05f, 0.1f, 0.09f);
	box_transX1[i] = box_trans[i];

	i++;
	// Pi,NAD+
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.75f, -0.30f, 0.1f);
	box_transX2[i] = box_trans[i];

	i++;
	// NADH
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.75f, -0.25f, 0.1f);
	box_transX2[i] = box_trans[i];

	i++;
	// 1,3-Bisphosphoglycerate
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(-1.15f, -0.25f, 0.1f);
	box_transX1[i] = box_trans[i];

	i++;
	// Phosphoglycerate kinase
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.05f, 0.05f, 0.15f);
	box_transX1[i] = box_trans[i];

	i++;
	// ADP
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.75f, -0.25f, 0.1f);
	box_transX2[i] = box_trans[i];

	i++;
	// ATP
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.75f, -0.25f, 0.1f);
	box_transX2[i] = box_trans[i];

	i++;
	// 3-Phosphoglycerate
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(-1.15f, -0.25f, 0.1f);
	box_transX1[i] = box_trans[i];

	i++;
	// Phosphoglycerate mutase
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.05f, -0.05f, 0.15f);
	box_transX1[i] = box_trans[i];

	i++;
	// 2-Phosphoglycerate
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(-1.15f, -0.25f, 0.1f);
	box_transX1[i] = box_trans[i];

	i++;
	// Enolase
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(-0.3f, -0.25f, 0.1f);
	box_transX1[i] = box_trans[i];

	i++;
	// H2O
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.75f, -0.25f, 0.1f);
	box_transX2[i] = box_trans[i];

	i++;
	//  Phosphoenolpyruvate
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(-1.15f, -0.25f, 0.1f);
	box_transX1[i] = box_trans[i];

	i++;
	// Pyruvate kinase
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(-0.3f, -0.25f, 0.1f);
	box_transX1[i] = box_trans[i];

	i++;
	// ADP
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.75f, -0.25f, 0.1f);
	box_transX2[i] = box_trans[i];

	i++;
	// ATP
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.75f, -0.25f, 0.1f);
	box_transX2[i] = box_trans[i];

	i++;
	// Pyruvate
	box_trans[i] = stage->getObject(80001+i)->getTrans() + glm::vec3(0.8f, -0.25f, 0.1f);
	box_transX1[i] = box_trans[i];

	for (int i=0; i < NO_TESTS; i++)
	{
		std::cout << "WallCube id: " <<  stage->getObject(80001+i)->getId() << ", trans: (" << stage->getObject(80001+i)->getTrans().x << ", " << stage->getObject(80001+i)->getTrans().y << ", " << stage->getObject(80001+i)->getTrans().z << ") " << std::endl;
		std::cout << "Box_trans id: " <<  i << ", trans: (" << box_trans[i].x << ", " << box_trans[i].y << ", " << box_trans[i].z << ") " << std::endl;
		std::cout << "start_trans id: " <<  i << ", trans: (" << start_trans[i].x << ", " << start_trans[i].y << ", " << start_trans[i].z << ") " << std::endl;
	}

}

void GameLogic::solved()
{
	int noOfSolved = 0;
	int noOfCorrect = 0;
	for (int i = 0; i< NO_TESTS; i++)
	{
//		noOfSolved += try_checked[i];
		if (try_id[i] == solution_id[i])
		{
			noOfCorrect++;
		}
	}
	dynamic_cast<NoSign *>(stage->getTextObject(NO_ID))->setNo(noOfCorrect);
	dynamic_cast<NoSign *>(stage->getTextObject(NO_ID+1))->setNo(noOfCorrect);
}

/**
 * Check to see if the text is in the correct position, then it should be
 * coloured green otherwise red
 */
void GameLogic::check() {

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

/**
 *
 * @param text_obj
 * @return
 */
//bool GameLogic::checkMovement(LPObject *text_obj)
//{
//	if (text_obj->getTrans().x + 1.5 > box_trans[text_obj->getId() - 22005].x)
//	{
//		int index = 0;
//		float diff[NO_TESTS];
//		for (int i = 0; i < NO_TESTS; i++)
//		{
//			diff[i] = 0.0f;
//		}
//		diff[index] = fabs(text_obj->getTrans().y - box_trans[index].y);
//		for (int i = 1; i < NO_TESTS; i++)
//		{
//			diff[i] = fabs(text_obj->getTrans().y - box_trans[i].y);
//			if (diff[i] < diff[index] )
//			{
//				index = i;
//			}
//		}
//		if (try_id[index] == 0)
//		{
//			text_obj->setTrans(box_trans[index] - text_obj->getTrans() /*-    glm::vec3(stage->getObject(80001+index)->getScale().x/2.0 0.0f, 0.0f, 0.0f)*/);
////			text_obj->setTrans(box_trans[index] - text_obj->getTrans());
//			try_id[index] = text_obj->getId();
//		}
////		else
////		{
////			if (text_obj->getTrans().x + 2.5 > box_trans[text_obj->getId() - 22005].x)
////			{
////				if (text_obj->getId() == 22020)
////				{
////					text_obj->setTrans(box_trans[index] - text_obj->getTrans() /*-    glm::vec3(stage->getObject(80001+index)->getScale().x/2.0 0.0f, 0.0f, 0.0f)*/);
////					try_id[index] = text_obj->getId();
////				}
////			}
//			else
//			{
//				text_obj->setTrans(start_trans[text_obj->getId() - 22005] - text_obj->getTrans() );
//				text_obj->setColor(resObj.black);
//			}
////		}
//	}
//	else
//	{
//		text_obj->setTrans(start_trans[text_obj->getId() - 22005] - text_obj->getTrans() );
//		text_obj->setColor(resObj.black);
//	}
//	return true;
//}


bool GameLogic::checkMovement(LPObject *text_obj)
{
	if (text_obj->getId() > 22004 && text_obj->getId() < 22050)
	{
	if (text_obj->getTrans().x  < -0.5f &&  text_obj->getTrans().x > -4.5f)
	{
		int index = 0;
		float diff[NO_TESTS];
		for (int i = 0; i < NO_TESTS; i++)
		{
			diff[i] = 0.0f;
		}
		diff[index] = fabs(text_obj->getTrans().y - box_transX1[index].y);
		for (int i = 1; i < NO_TESTS; i++)
		{
			diff[i] = fabs(text_obj->getTrans().y - box_transX1[i].y);
			if (diff[i] < diff[index] )
			{
				index = i;
			}
		}
		if (try_id[index] == 0)
		{
			text_obj->setTrans(box_transX1[index] - text_obj->getTrans() /*-    glm::vec3(stage->getObject(80001+index)->getScale().x/2.0 0.0f, 0.0f, 0.0f)*/);
			try_id[index] = text_obj->getId();
		}
		else
			{
				text_obj->setTrans(start_trans[text_obj->getId() - 22005] - text_obj->getTrans() );
				text_obj->setColor(resObj.black);
			}
	}
	else if (text_obj->getTrans().x  < 5.5f &&  text_obj->getTrans().x > 0.0f)
	{
		int index = 0;
		float diff[NO_TESTS];
		for (int i = 0; i < NO_TESTS; i++)
		{
			diff[i] = 0.0f;
		}
		diff[index] = fabs(text_obj->getTrans().y - box_transX2[index].y);
		for (int i = 1; i < NO_TESTS; i++)
		{
			diff[i] = fabs(text_obj->getTrans().y - box_transX2[i].y);
			if (diff[i] < diff[index] )
			{
				index = i;
			}
		}
		if (try_id[index] == 0)
		{
			text_obj->setTrans(box_transX2[index] - text_obj->getTrans() /*-    glm::vec3(stage->getObject(80001+index)->getScale().x/2.0 0.0f, 0.0f, 0.0f)*/);
			try_id[index] = text_obj->getId();
		}
		else
			{
				text_obj->setTrans(start_trans[text_obj->getId() - 22005] - text_obj->getTrans() );
				text_obj->setColor(resObj.black);
			}
	}
	else
	{
		text_obj->setTrans(start_trans[text_obj->getId() - 22005] - text_obj->getTrans() );
		text_obj->setColor(resObj.black);
	}

	check();
	for (int i = 0; i < NO_TESTS; i++)
	{
		std::cout << "try id: " <<  try_id[i] << endl;
	}
	}
	return true;
}


/**
 * Updates the position's free or occupied status
 * This is done when the button is pressed
 * @param obj the text object in the position we want to check
 */
void GameLogic::updatePosition(LPObject *obj)
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

GameLogic::~GameLogic()
{
  std::cout << "ENTER ~GameLogic()" << std::endl;
	// TODO Auto-generated destructor stub
}


