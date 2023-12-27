/*
 * L_ResObj.h
 *
 *  Created on: Jul 5, 2018
 *      Author: peter
 *
 *      Interface towards Lua
 */

#ifndef L_RESOBJ_H_
#define L_RESOBJ_H_

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <cstdio>
#include <iostream>

#include "../inc/ResObj.h"
class L_ResObj {
public:
  static ResObj *resObj_ptr;
  static int *test;
  static int value;

  L_ResObj() = delete;
  virtual ~L_ResObj() = delete;

//  static int createMolecule(lua_State *l);
//  static int createAnimalCell(lua_State *l);

  static int loadStaticObjFiles(lua_State *l);

  static ResObj* getResObj();
  static void setResObj(ResObj* resObj);
};

#endif // L_RESOBJ_H_
