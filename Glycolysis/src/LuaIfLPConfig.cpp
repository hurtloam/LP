#include <string>
#include "../inc/LuaIfLPConfig.h"
#include "../inc/LPConfig.hpp"
#include <iostream>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


LuaIfLPConfig::LuaIfLPConfig(LPConfig* lpConfig) : lpConfig(lpConfig) {
}

LuaIfLPConfig::~LuaIfLPConfig() {
}

void LuaIfLPConfig::setConfigFile(std::string configFile) {
    fileName.assign(configFile);
}

void LuaIfLPConfig::configLP() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  // load script
  if (luaL_dofile(L, fileName.c_str()) != 0) {
    std::cout << "ERROR in LuaIfLPConfig::configLP(): luaL_dofile failed to run config file = " << fileName.c_str() << std::endl;
  }

  lua_getfield(L, LUA_GLOBALSINDEX, "title"); /* Title */
  std::cout << "type stack -1: " << lua_typename(L, lua_type(L, -1)) << std::endl;
  lpConfig->title.assign(luaL_checkstring(L, -1));  // get the result value from Lua

  lua_getfield(L, LUA_GLOBALSINDEX, "screenWidth"); /* screen resolution */
    std::cout << "type stack -1: " << lua_typename(L, lua_type(L, -1)) << std::endl;
  lpConfig->screenWidth = luaL_checkinteger(L, -1);  // get the result value from Lua

  lua_getfield(L, LUA_GLOBALSINDEX, "screenHeight"); /* screen resolution */
  lpConfig->screenHeight = luaL_checkinteger(L, -1);  // get the result value from Lua

  lua_getfield(L, LUA_GLOBALSINDEX, "multiThreadOn"); /* Splash screen will be used if multi thread is active  */
  if (lua_isboolean(L, -1)) {
    lpConfig->multiThreadOn = lua_toboolean(L, -1);  // get the result value from Lua
  } else {
	  std::cout << luaL_error(L, "Wrong format on multiThreadOn, not a boolean");
  }

  lua_getfield(L, LUA_GLOBALSINDEX, "logPriority"); /* Log Priority */
  if (lua_isnumber(L, -1)) {
    lpConfig->logPriority = luaL_checkinteger(L, -1);  // get the result value from Lua
  }
  else {
    std::cout << luaL_error(L, "Wrong format on logPriority, not an integer");
  }

  // SDL_BASE
  lua_getfield(L, LUA_GLOBALSINDEX, "LP_OPEN_GL_CONTEXT_MAJOR_VERSION"); /* OpenGL version */
  lpConfig->LP_OPEN_GL_CONTEXT_MAJOR_VERSION = luaL_checkinteger(L, -1);  // get the result value from Lua

  lua_getfield(L, LUA_GLOBALSINDEX, "LP_OPEN_GL_CONTEXT_MINOR_VERSION"); /* OpenGL version */
  lpConfig->LP_OPEN_GL_CONTEXT_MINOR_VERSION = luaL_checkinteger(L, -1);  // get the result value from Lua

  lua_getfield(L, LUA_GLOBALSINDEX, "LP_OPEN_GL_DOUBLEBUFFER"); /* double buffer */
  lpConfig->LP_OPEN_GL_DOUBLEBUFFER = luaL_checkinteger(L, -1);
  lua_getfield(L, LUA_GLOBALSINDEX, "LP_OPEN_GL_DEPTH_SIZE"); /* depth size */
  lpConfig->LP_OPEN_GL_DEPTH_SIZE = luaL_checkinteger(L, -1);

  lua_getfield(L, LUA_GLOBALSINDEX, "LP_OPEN_GL_MULTISAMPLEBUFFERS"); /* multisample buffers*/
  lpConfig->LP_OPEN_GL_MULTISAMPLEBUFFERS = luaL_checkinteger(L, -1);
  lua_getfield(L, LUA_GLOBALSINDEX, "LP_OPEN_GL_MULTISAMPLESAMPLES"); /* multisamplesamples */
  lpConfig->LP_OPEN_GL_MULTISAMPLESAMPLES = luaL_checkinteger(L, -1);

  lua_getfield(L, LUA_GLOBALSINDEX, "LP_OPEN_GL_ACCELERATED_VISUAL"); /* accelerated visual */
  lpConfig->LP_OPEN_GL_ACCELERATED_VISUAL = luaL_checkinteger(L, -1);

  lua_gc(L, LUA_GCCOLLECT, 0);  // collected garbage
  lua_close(L);
}
