#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include "../inc/ResObj.h"
#include "../inc/L_ResObj.h"


int L_ResObj::value = 1; // initializer
ResObj* L_ResObj::resObj_ptr = nullptr; // initializer


int L_ResObj::loadStaticObjFiles(lua_State *l)
{
  std::cout << "ENTER L_ResObj::loadStaticObjFiles" << std::endl;
  std::string name = "";
  std::string wikiName = "";
  int obj = 99;
  std::string objPath;

  if (lua_isstring(l, 1)) {
    objPath = luaL_checkstring(l, 1);
    std::cout << "From Lua: objPath=" << objPath << std::endl;
  }
  else {
    std::cout << luaL_error(l, "Wrong format, not a string");
  }

  if (lua_isnumber(l, 2)) {
    obj = luaL_checkint(l, 2);
  }
  else {
    std::cout << luaL_error(l, "Wrong format, not an integer");
  }

  if (lua_isstring(l, 3)) {
    name = luaL_checkstring(l, 3);
  }
  else {
    std::cout << luaL_error(l, "Wrong format, not a string");
  }

  if (lua_isstring(l, 4)) {
    wikiName = luaL_checkstring(l, 4);
  }
  else {
    std::cout << luaL_error(l, "Wrong format, not a string");
  }

  resObj_ptr->loadStaticObjFiles(objPath.c_str(), (ObjectType) obj, name.c_str(), wikiName.c_str());
  return 1;
}

void L_ResObj::setResObj(ResObj* resObj)
{
  L_ResObj::resObj_ptr = resObj;
}
