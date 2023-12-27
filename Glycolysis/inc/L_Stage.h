/*
 * L_Stage.h
 *
 *  Created on: Jan 9, 2018
 *      Author: peter
 *
 *      Interface towards Lua
 */

#ifndef L_STAGE_H_
#define L_STAGE_H_

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <cstdio>
#include <iostream>

#include "../stage/inc/Stage.h"
class L_Stage {
public:
  static Stage *stage_ptr;
  static int *test;
  static int value;

  L_Stage() = delete;
  virtual ~L_Stage() = delete;

  static int createMolecule(lua_State *l);
  static int createAnimalCell(lua_State *l);
  static int createArrow(lua_State *l);
  static int createMoleculeSpot(lua_State *l);
  static int createTextSpot(lua_State *l);
  static int createText(lua_State *l);
  static int createBall(lua_State *l);
  static Stage* getStage();
  static void setStage(Stage* stage);
};

#endif // L_STAGE_H_
