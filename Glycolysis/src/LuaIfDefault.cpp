#include <string>
#include "../inc/LuaIfDefault.h"
#include <iostream>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


LuaIfDefault::LuaIfDefault() {
}

LuaIfDefault::~LuaIfDefault() {
}

void LuaIfDefault::config(std::string configFile) {

  fileName = "/home/peter/ownCloud/GrundProg-master/GrundProg-master/belysning_av_klot.lua";
}

float LuaIfDefault::getIntensity(int resX, int resY, int x, int y) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  // set parameters in lua before loading script
  lua_pushinteger(L, resX);                        /* set width resolution in lua */
  lua_setfield(L, LUA_GLOBALSINDEX, "res_x");        /* set global 'res_x' */
  lua_pushinteger(L, resY);                        /* set height resolution in lua */
  lua_setfield(L, LUA_GLOBALSINDEX, "res_y");        /* set global 'res_y' */

  // load script
  luaL_dofile(L, fileName.c_str());
  float a;

  // call function getI in Lua
  lua_getfield(L, LUA_GLOBALSINDEX, "getI"); /* function to be called */
  lua_pushinteger(L, x);                        /* 1st argument */
  lua_pushinteger(L, y);                        /* 2st argument */
  lua_call(L, 2, 1);     /* call 'getI' with 2 arguments and 1 result */

  a = luaL_checknumber(L, -1);  // get the result value from function call
  lua_gc(L, LUA_GCCOLLECT, 0);  // collected garbage
  lua_close(L);
  return a;
}

void LuaIfDefault::changeLight(float x, float y) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  // load script
  luaL_dofile(L, fileName.c_str());

  // call function changeLight in Lua
  lua_getfield(L, LUA_GLOBALSINDEX, "change_light"); /* function to be called */
  lua_pushnumber(L, x);                        /* 1st argument */
  lua_pushnumber(L, y);                        /* 2st argument */
  lua_call(L, 2, 1);     /* call 'change_light' with 2 arguments and 1 result */

  lua_gc(L, LUA_GCCOLLECT, 0);  // collected garbage
  lua_close(L);
}
