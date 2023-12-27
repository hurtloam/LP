/*
 * LuaIf.h
 *
 *  Created on: Jan 9, 2018
 *      Author: peter
 *
 *      Interface towards Lua
 */

#ifndef LUAIF_H_
#define LUAIF_H_

#include <string>

class Stage;
class ResObj;

class LuaIf {
public:
  LuaIf(Stage* stage, ResObj* resObj);
    virtual ~LuaIf();
  int config(std::string configFile);
private:
    Stage* stage;
  ResObj* resObj;
};

#endif // LUAIF_H_
