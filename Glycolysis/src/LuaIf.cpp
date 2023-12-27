
#include <string>
#include "../inc/LuaIf.h"
#include "../inc/L_Stage.h"
#include "../inc/L_ResObj.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

LuaIf::LuaIf(Stage* stage, ResObj* resObj) :
    stage(stage), resObj(resObj)
{
}

LuaIf::~LuaIf() {
}

int LuaIf::config(std::string configFile)
{
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  L_Stage::setStage(stage);
  L_ResObj::setResObj(resObj);

  // createMolecule
  lua_pushcfunction(L, L_Stage::createMolecule);
  lua_setglobal(L, "createMolecule");

  // createAnimalCell
  lua_pushcfunction(L, L_Stage::createAnimalCell);
  lua_setglobal(L, "createAnimalCell");

  // createArrow
  lua_pushcfunction(L, L_Stage::createArrow);
  lua_setglobal(L, "createArrow");

  // createMoleculeSpot
  lua_pushcfunction(L, L_Stage::createMoleculeSpot);
  lua_setglobal(L, "createMoleculeSpot");

  // createTextSpot
  lua_pushcfunction(L, L_Stage::createTextSpot);
  lua_setglobal(L, "createTextSpot");

  // createText
  lua_pushcfunction(L, L_Stage::createText);
  lua_setglobal(L, "createText");

  // createBall
  lua_pushcfunction(L, L_Stage::createBall);
  lua_setglobal(L, "createBall");

  // loadStaticObjFiles
  lua_pushcfunction(L, L_ResObj::loadStaticObjFiles);
  lua_setglobal(L, "loadStaticObjFiles");

  // load configuration
  if (luaL_dofile(L, configFile.c_str()) != 0) {
    std::cout << "ERROR in LuaIf::config(...): luaL_dofile failed to run config file = " << configFile.c_str() << std::endl;

    lua_gc(L, LUA_GCCOLLECT, 0);  // collected garbage
    lua_close(L);
    return 1;
  }
  lua_gc(L, LUA_GCCOLLECT, 0);  // collected garbage
  lua_close(L);

  return 0;
}
