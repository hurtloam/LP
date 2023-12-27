
#include <string>
#include <cstdio>
#include <iostream>
#include "../inc/LuaInteractive.h"
#include "../inc/L_Stage.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}




LuaInteractive::LuaInteractive(Stage* stage) : stage(stage) {
}

LuaInteractive::~LuaInteractive() {
}

void LuaInteractive::cli() {
  int argc = 1;
  char * argv[] = {"Lua Terminal"};

  char buff[256];
  int error;
  lua_State *L = lua_open();   /* opens Lua */
  luaL_newstate();
  luaL_openlibs(L);

  L_Stage::setStage(stage);

  // createMolecule version
  lua_pushcfunction(L, L_Stage::createMolecule);
  lua_setglobal(L, "createMolecule");

  std::cout << "-= Learning Platform =-\nLua Interactive CLI (using Lua version 5.1)" << std::endl;
  while (fgets(buff, sizeof(buff), stdin) != NULL) {
      error = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
          lua_pcall(L, 0, 0, 0);
      if (error) {
          fprintf(stderr, "%s", lua_tostring(L, -1));
          lua_pop(L, 1);  /* pop error message from the stack */
      }
  }
  lua_close(L);

}

