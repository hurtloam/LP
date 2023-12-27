/*
 * MenuContainer.cpp
 *
 *  Created on: Sep 6, 2015
 *      Author: peter
 */

#include "../inc/MenuContainer.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/type_vec3.hpp>

#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <glm/detail/type_vec3.hpp>
#include <GL/glew.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>

#include "../inc/StaticObj.h"
#include "../inc/ResObj.h"
#include <GL/glew.h>
#include <string.h>
#include <iostream>
#include "../inc/shader.hpp"
#include <ft2build.h>
#include <freetype/freetype.h>
#include FT_FREETYPE_H
#include "../inc/TextMenuItem.h"

using namespace std;

MenuContainer::MenuContainer(
		int id,
		glm::vec3 scale,
		list<std::pair<ObjectType, FuncPtr>> objectMap,
		GLuint texture,
		glm::vec3 trans,
		LPWatch* watch,
		ResObj& resObj,
		const View& view,
		LPUniform lpUniform) : StaticObj(
				id,
				scale,
				cube,
				texture,
				trans,
				watch,
				resObj,
				view,
		    lpUniform)

{
	objMap = objectMap;
	counter = 0;
  text_program_id = lpUniform.programID;

	b_motionState =
			new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(trans.x+10, trans.y, trans.z)));

//		b_shape = new btBoxShape(btVector3(1.0,0.1,0.5));

	b_shape = new btBoxShape(btVector3(0.7f,0.2f,0.05f));
	btScalar mass = 0;
	btRigidBody::btRigidBodyConstructionInfo b_rigidBodyCI(mass, b_motionState, b_shape);



	b_rigidBody = new btRigidBody(b_rigidBodyCI);

	//	b_rigidBody->setSleepingThresholds (0.0f, 0.0f);
	//	b_rigidBody->setAngularFactor (0.0f);

	//	b_rigidBody->setCollisionFlags(b_rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	b_rigidBody->setActivationState(DISABLE_DEACTIVATION);
	GLfloat blackish[4] = {0,0,0,1};
	GLfloat whitish[4] = {0,0,0,0};
	pos = trans;
	texture_local = texture;
	//	init();

  	setRotationMatrix_X(0);

}

void MenuContainer::init()
{
	int i = 0;
	TextMenuItem *lp_obj = NULL;

	for (list<std::pair<ObjectType, FuncPtr>>::iterator it = objMap.begin(); it != objMap.end(); ++it)
	{
		lp_obj = new TextMenuItem(++lp_text,
				glm::vec3(1.0f, 1.0f, 1.0f),
				(*it).first,
				undefined_object,
				texture_local,
				pos - glm::vec3(0.0f, i * 0.21f, -0.0f),
				watch,
				resObj,
				view,
				lpUniform);

		menuItemVector.push_back(lp_obj);
		//		indexMap.insert(std::pair<int, int>(i,i));
		//		objList.push_back(lp_obj);
		i++;
//		std::cout << "i=" << i << std::endl;

	}

	moreObj = new TextMenuItem(++lp_text,
			glm::vec3(1.0f, 1.0f, 1.0f),
			txt_MORE,
			undefined_object,
			texture_local,
			pos - glm::vec3(0.0f, (MENU_SIZE + 1) * 0.21f, -0.0f),
			//											pos,
                              watch,
			resObj,
			view,
			lpUniform);

	lessObj = new TextMenuItem(++lp_text,
			glm::vec3(1.0f, 1.0f, 1.0f),
			txt_LESS,
			undefined_object,
			texture_local,
			pos + glm::vec3(0.0f, 0.0f, 0.0f),
			//											pos,
                              watch,
			resObj,
			view,
			lpUniform);

	//	objList.push_back(menuItemVector[0]);
}

void MenuContainer::init2Lines()
{
  int i = 0;
  TextMenuItem *lp_obj = NULL;

  for (list<std::pair<ObjectType, FuncPtr>>::iterator it = objMap.begin(); it != objMap.end(); ++it)
  {
    list<std::pair<ObjectType, FuncPtr>>::iterator secondObjIterator = ++it;
    lp_obj = new TextMenuItem(++lp_text,
        glm::vec3(1.0f, 1.0f, 1.0f),
        (*it).first,
        (*secondObjIterator).first,
        texture_local,
        pos - glm::vec3(0.0f, i * 0.21f, -0.0f),
        watch,
        resObj,
        view,
        lpUniform);

    menuItemVector.push_back(lp_obj);
    //    indexMap.insert(std::pair<int, int>(i,i));
    //    objList.push_back(lp_obj);
    i++;
//    std::cout << "i=" << i << std::endl;

  }

  moreObj = new TextMenuItem(++lp_text,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_MORE,
      undefined_object,
      texture_local,
      pos - glm::vec3(0.0f, (MENU_SIZE + 1) * 0.21f, -0.0f),
      //                      pos,
                              watch,
      resObj,
      view,
      lpUniform);

  lessObj = new TextMenuItem(++lp_text,
      glm::vec3(1.0f, 1.0f, 1.0f),
      txt_LESS,
      undefined_object,
      texture_local,
      pos + glm::vec3(0.0f, 0.0f, 0.0f),
      //                      pos,
                              watch,
      resObj,
      view,
      lpUniform);

  //  objList.push_back(menuItemVector[0]);
}


void MenuContainer::initObject()
{
	int i = 0;
	TextMenuItem *lp_obj = NULL;

	for (list<std::pair<ObjectType, FuncPtr>>::iterator it = objMap.begin(); it != objMap.end(); ++it)
	{
		lp_obj = new TextMenuItem(++lp_text,
				glm::vec3(1.0f, 1.0f, 1.0f),
				(*it).first,
				undefined_object,
				texture_local,
				pos - glm::vec3(0.0f, i * 0.21f, 0.0f),
				watch,
				resObj,
				view,
				lpUniform);

		menuItemVector.push_back(lp_obj);
		i++;
//		std::cout << "i=" << i << std::endl;

	}

	moreObj = new TextMenuItem(++lp_text,
			glm::vec3(1.0f, 1.0f, 1.0f),
			txt_MORE,
			undefined_object,
			texture_local,
			pos - glm::vec3(0.0f, (MENU_SIZE + 1) * 0.21f, 0.0f),
			//											pos,
                              watch,
			resObj,
			view,
			lpUniform);

	lessObj = new TextMenuItem(++lp_text,
			glm::vec3(1.0f, 1.0f, 1.0f),
			txt_LESS,
			undefined_object,
			texture_local,
			pos, //+ glm::vec3(0.0f, 0.21f, 0.0f),
			//											pos,
                              watch,
			resObj,
			view,
			lpUniform);
}


MenuContainer::~MenuContainer()
{
	glDisable(GL_BLEND);
	//	delete textObjectFirst;
	//	delete textObjectSecond;

}

void MenuContainer::internalDraw()
{
	counter++;
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	ModelMatrix = glm::translate(ModelMatrix,getTrans()) * getRotationMatrix();
	glm::mat4 MVP = view.getProjectionMatrix() * view.getViewMatrix() * ModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
  glUniformMatrix4fv(lpUniform.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  glUniformMatrix4fv(lpUniform.ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
  glUniformMatrix4fv(lpUniform.ViewMatrixID, 1, GL_FALSE, &(view.getViewMatrix())[0][0]);

	if(text_program_id == 0)
		printf("programID faulty\n");

	attribute_coord = glGetAttribLocation(text_program_id, "coord");
	uniform_tex = glGetUniformLocation(text_program_id, "tex");
	uniform_color = glGetUniformLocation(text_program_id, "color");

	if(attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1)
	{
		fprintf(stderr, "WARNING: Some values not initialized: attribute_coord=%d, uniform_tex=%d, uniform_color=%d\n", attribute_coord, uniform_tex, uniform_color);
		std::cout << "MenuContainer" << std::endl;
	}

	//		/* Enable blending, necessary for our alpha texture */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glUniform4fv(uniform_color, 1, color);
	glUniform1i(uniform_tex, 0);

	//	list<GLuint>::const_iterator texture =  resObj.txtObjArray[getObjType() - 1000].text_tex.begin();
	//	for(GLuint l : resObj.getText_vbo(getObjectType()))
	//	{
	// texure test
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_local);
	//		glUniform1i(uniform_tex, 0);
	// texure test

	/* Set up the VBO for our vertex data */
	glEnableVertexAttribArray(attribute_coord);

	int x2 = 0;
	int y2 = 1;
	int w = 5.0f;
	int h = 1.5f;
	//		point box[4] = {
	//							{x2, -y2, 0, 0},
	//							{x2 + w, -y2, 1, 0},
	//							{x2, -y2 - h, 0, 1},
	//							{x2 + w, -y2 - h, 1, 1},
	//					};


	//		point box[4] = {
	//				{-2.0f, 1.0f, 0.0f, 0.0f},
	//				{2.0f, 1.0f, 1.0f, 0.0f},
	//				{-2.0f, -1.0f, 0.0f, 1.0f},
	//				{2.0f , -1.0f, 1.0f, 1.0f},
	//		};
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	point box[4] = {
			{-1.1f, .2f, 0.0f, 0.0f},
			{0.9f, .2f, 1.0f, 0.0f},
			{-1.1f, -.4f, 0.0f, 1.0f},
			{0.9f , -.4f, 1.0f, 1.0f},
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(
			attribute_coord,
			4,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0);
	/* Draw the character on the screen */
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//	}
	glDisableVertexAttribArray(attribute_coord);
	glDisable(GL_BLEND);

}
void MenuContainer::draw()
{
//		internalDraw();

	//	int index = getMenuItem(txt_9);
	switch(status)
	{
	case MenuStatusE::HIDDEN:
	  // Do nothing
	  break;

	case MenuStatusE::DEFAULT:
		//		objList.front()->draw();
		start = DEFAULT_START;
		stop = MENU_SIZE + 1;

		//TESTING
		selected = DEFAULT_START;
		menuItemVector[DEFAULT_START]->setTextColor(resObj.white);
		menuItemVector[DEFAULT_START]->setMenuColor(resObj.transparent_green);

		for (int i = start+1; i < stop; i++)
		{
		  menuItemVector[i]->setTextColor(resObj.black);
		  menuItemVector[i]->setMenuColor(resObj.dark_gray);
		}


		stop = (menuItemVector.size() - 1) > stop ? stop : menuItemVector.size() - 1;
		menuItemVector[0]->setBoxSize(1.2);
		menuItemVector[0]->draw();
		break;
	case MenuStatusE::ACTIVE:
	  // Changes to status ACTIVE when the menu list is dropped down and shown
	{
		if (start > DEFAULT_START)
		{
		  lessObj->setBoxSize(2.7);
			lessObj->draw();
		}
		for (int i = start; i < stop; i++)
		{
		  menuItemVector[i]->setBoxSize(2.7);
			menuItemVector[i]->draw();
		}
		if (stop < menuItemVector.size())
		{
		  moreObj->setBoxSize(2.7);
			moreObj->draw();
		}
		break;
	}
	case MenuStatusE::SELECTED:
		if (lessFlag)
		{
			stop = start;
			start -= MENU_SIZE;
			int j = DEFAULT_START;
			//			stop = (menuItemVector.size() - 1) > stop ? stop : menuItemVector.size() - 1;
			for (int i = start; i < stop; i++)
			{
				menuItemVector[i]->setTrans(menuItemVector[j]->getTrans() - menuItemVector[i]->getTrans());
				menuItemVector[i]->draw();
				j++;
			}
			status = MenuStatusE::ACTIVE;

			if (start > 1)
			{
				lessObj->setTextColor(resObj.white);
				lessObj->setMenuColor(resObj.transparent_green);
				moreFlag = false;
				lessFlag = true;
			}
			else
			{
				lessFlag = false;
				moreFlag = false;
				selected = 1;
				menuItemVector[DEFAULT_START]->setTextColor(resObj.white);
				menuItemVector[DEFAULT_START]->setMenuColor(resObj.transparent_green);
			}
			break;
		}
		else if (moreFlag)
		{
			start += MENU_SIZE;
			stop += MENU_SIZE;
			int j = DEFAULT_START;
			stop = (menuItemVector.size()) > stop ? stop : menuItemVector.size();
			for (int i = start; i < stop; i++)
			{
				menuItemVector[i]->setTrans(menuItemVector[j]->getTrans() - menuItemVector[i]->getTrans());
				menuItemVector[i]->draw();
				j++;
			}
			status = MenuStatusE::ACTIVE;
			moreFlag = false;

			lessObj->setTextColor(resObj.white);
			lessObj->setMenuColor(resObj.transparent_green);
			moreFlag = false;
			lessFlag = true;
			break;
		}
		else
		{
		  // reset the menu so next time we will scroll from the beginning
		  setStatusDefault();
		  menuItemVector[0]->setIsItemSelected(true);
			menuItemVector[0]->draw();

			break;
		}
	}
}

void MenuContainer::resetItemSelected() {
  for (TextMenuItem* i : menuItemVector) {
    i->setIsItemSelected(false);
  }
}

void MenuContainer::markMenuItem(int mY)
{
	//	int val = abs (initmY - mY/ 50);
	int val = ((mY - initmY )/ 30);
	if (val > 0 && val < (stop - start + DEFAULT_START))
	{
		selected = start + val - DEFAULT_START;
		cout << "selected=" << selected << endl;
		menuItemVector[selected]->setTextColor(resObj.white);
		menuItemVector[selected]->setMenuColor(resObj.transparent_green);

		lessObj->setTextColor(resObj.black);
		lessObj->setMenuColor(resObj.dark_gray);

		moreObj->setTextColor(resObj.black);
		moreObj->setMenuColor(resObj.dark_gray);

		if ((selected != start) && (selected > 0))
		{
			cout << "POSITION1" << endl;
			menuItemVector[selected-1]->setTextColor(resObj.black);
			menuItemVector[selected-1]->setMenuColor(resObj.dark_gray);
		}

		if (selected != (stop) && selected < (menuItemVector.size() - 1))
		{
			cout << "POSITION2" << endl;
			menuItemVector[selected+1]->setTextColor(resObj.black);
			menuItemVector[selected+1]->setMenuColor(resObj.dark_gray);
		}
		cout << "POSITION3" << endl;
		moreFlag = false;
		lessFlag = false;
	}
	else if (val == 0)
	{

    cout << "POSITION4, STATUS=" << status << endl;
		menuItemVector[selected]->setTextColor(resObj.black);
		menuItemVector[selected]->setMenuColor(resObj.dark_gray);


		if (start == DEFAULT_START)
		{
	  //TESTING
		  selected = DEFAULT_START;
	    menuItemVector[DEFAULT_START]->setTextColor(resObj.white);
	    menuItemVector[DEFAULT_START]->setMenuColor(resObj.transparent_green);
		}
		else
		{
		lessObj->setTextColor(resObj.white);
		lessObj->setMenuColor(resObj.transparent_green);
		moreFlag = false;
		lessFlag = true;
		}
	}
	else if (val == (stop - start + 1))
	{
		cout << "POSITION5" << endl;
		if ((menuItemVector.size() - 1) == selected)
		{
		  menuItemVector[selected]->setTextColor(resObj.white);
		  menuItemVector[selected]->setMenuColor(resObj.transparent_green);
	    moreFlag = false;
	    lessFlag = false;
		}
		else
		{
		  menuItemVector[selected]->setTextColor(resObj.black);
		  menuItemVector[selected]->setMenuColor(resObj.dark_gray);
		  menuItemVector[0]->setTextColor(resObj.black);
		  menuItemVector[0]->setMenuColor(resObj.dark_gray);

		  moreObj->setTextColor(resObj.white);
		  moreObj->setMenuColor(resObj.transparent_green);
		  moreFlag = true;
		  lessFlag = false;
		}

	}
//	else if (val > (stop - start + 2 ))
//	{
//	  const_cast<View*>(view)->warpMouseInWindow(_window, initmX, initmY+ 30 * MENU_SIZE);
//	}
	else if (val < 0)
	{
	  view.warpMouseInWindow(_window, initmX, initmY);
	}

	cout << "y-coord=" << mY << ", val=" << val << ", selected=" << selected << ", size of MenuItemVector=" << menuItemVector.size() << ", start=" << start << ", stop=" << stop << endl;
}

bool MenuContainer::selectMenuItem(SDL_Window* window, int mX, int mY)
{
	int sh = view.getScreenHeight();
	int sw = view.getScreenWidth();
	glm::vec3 tmpTrans = menuItemVector[selected]->getTrans();
	int height = sh / 3 * tmpTrans.y - view.getPosition().y;
	//		sh - selected * 100;
	cout << "HEIGHT = " << height << endl;
	view.warpMouseInWindow(window, initmX, sh/2);

	if (lessFlag || moreFlag)
	{
		setStatusSelected();
		lessObj->setTextColor(resObj.black);
		lessObj->setMenuColor(resObj.dark_gray);
		moreObj->setTextColor(resObj.black);
		moreObj->setMenuColor(resObj.dark_gray);

		return true;
	}
	else
	{
		tmpTrans = menuItemVector[selected]->getTrans();
		menuItemVector[selected]->setTrans(menuItemVector[0]->getTrans() - menuItemVector[selected]->getTrans());
		menuItemVector[0]->setTrans(tmpTrans - menuItemVector[0]->getTrans());
		cout << "Inside selectMenuItem: STATUS=" << status << endl;

		TextMenuItem* item = menuItemVector[0];
		menuItemVector[0] = menuItemVector[selected];
		menuItemVector[selected] = item;

		setStatusSelected();
		cout << "Changing status to status=" << status << endl;
		return false;
	}
}

int MenuContainer::getMenuItem(int id)
{
	for (int i = 0; i < menuItemVector.size(); i++)
	{
		if (menuItemVector[i]->getId() == id)
		{
			return i;
		}
	}
	return 0;
}

void MenuContainer::setStatusDefault()
{
	status = MenuStatusE::DEFAULT;
	// Change to switch/case
	if (getId() == 36012  || getId() == 36014) {
	  setTrans(glm::vec3(-0.5f, -1.4f, -0.2f));
	}
	else if(getId() == 36031) { // Enolase
	  setTrans(glm::vec3(-0.5f, -0.7f, -0.2f));
	}
	else if(getId() == 36020) { //H2O
	  setTrans(glm::vec3(-0.5f, -0.9f, -0.2f));
	}
  else if(getId() == 36032) { //Phosphoenolpyruvate
    setTrans(glm::vec3(-0.5f, -1.1f, -0.2f));
  }
  else if(getId() == 36033) { //Pyruvate kinase
    setTrans(glm::vec3(-0.5f, -1.4f, -0.2f));
  }
  else if(getId() == 36317) { //ADP
    setTrans(glm::vec3(-0.5f, -1.4f, -0.2f));
  }
  else if(getId() == 36316) { //ATP
    setTrans(glm::vec3(-0.5f, -1.6f, -0.2f));
  }
  else if(getId() == 36034) { //Pyruvate
    setTrans(glm::vec3(-0.5f, -1.8f, -0.2f));
  }
	else
	{
	  setTrans(glm::vec3(-0.5f, -0.5f, -0.2f));
	}
	cout << "STATUS=" << status << endl;
}

//void MenuContainer::setStatusHidden()
//{
//  status = MenuStatusE::DEFAULT;
//  setTrans(glm::vec3(0.0f, 0.0f, -1.0f));
//  cout << "STATUS=" << status << endl;
//}

void MenuContainer::setStatusSelected()
{
	status = MenuStatusE::SELECTED;
	cout << "STATUS=" << status << endl;
}

void MenuContainer::markInitMenuItem(SDL_Window* window, int mX, int mY)
{
	cout << "y-coord=" << mY << endl;
	_window  = window;
	initmY = mY;
	initmX = mX;
	selected = 1;
	menuItemVector[0]->setIsItemSelected(false);
}

void MenuContainer::setTrans(glm::vec3 t)
{
	StaticObj::setTrans(t);
	for (TextMenuItem* l:menuItemVector)
	{
		l->setTrans(t);
	}
	moreObj->setTrans(t);
	lessObj->setTrans(t);
}

void MenuContainer::setRelativeTrans(glm::vec3 t)
{
  StaticObj::setTrans(t);
  for (TextMenuItem* l:menuItemVector)
  {
    l->setTrans(t);
  }
  moreObj->setRelativeTrans(t);
  lessObj->setTrans(t);
}

void MenuContainer::move(bool flag)
{
	//	 for the physics
	btTransform trans;
	btVector3 bvec;
	getRigidBody()->getMotionState()->getWorldTransform(trans);
	bvec = trans.getOrigin();

	// this made him move push stuff around
	trans.setOrigin(btVector3(getTrans().x, getTrans().y, getTrans().z));
	getRigidBody()->getMotionState()->setWorldTransform(trans);
	getRigidBody()->setCenterOfMassTransform (trans);
	for (TextMenuItem* l:menuItemVector)
	{
    l->move (flag);
	}
  moreObj->move (flag);
  lessObj->move (flag);
}

void MenuContainer::setMenuItem(int index)
{
  glm::vec3 tmpTrans;
  tmpTrans = menuItemVector[index]->getTrans();
      menuItemVector[index]->setTrans(menuItemVector[0]->getTrans() - menuItemVector[index]->getTrans());
      menuItemVector[0]->setTrans(tmpTrans - menuItemVector[0]->getTrans());
      cout << "Inside setMenuItem: STATUS=" << status << ", index=" << index << endl;

      TextMenuItem* item = menuItemVector[0];
      menuItemVector[0] = menuItemVector[index];
      menuItemVector[index] = item;
}

//void MenuContainer::setTextItemColor(int index, glm::vec3 color)
//{
//  menuItemVector[index]->setObjColor(color);
//}

void MenuContainer::setTextItemColor(int index, GLfloat* c)
{

  menuItemVector[index]->setTextColor(c);
}
