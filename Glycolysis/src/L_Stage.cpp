#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include "../inc/L_Stage.h"
#include "../stage/inc/Stage.h"


int L_Stage::value = 1; // initializer
Stage* L_Stage::stage_ptr = nullptr; // initializer

/* assume that table is at index 1 (-6) */
double getfield(lua_State *l, const char *key, int stackpos)
{
  double result;
  lua_getfield(l, stackpos, key);
  if (!lua_isnumber(l, -1)) {
    std::cout << "invalid component in pos" << std::endl;
  }
  result = lua_tonumber(l, -1);
  lua_pop(l, 1);  /* remove number */
  return result;
}

int L_Stage::createMolecule (lua_State *l) {
//  std::cout << "type of the top stack element: " << lua_typename(l, lua_type(l,-1)) << std::endl;
  glm::vec3 molPos =  glm::vec3(
                      getfield(l, "x", 1), getfield(l, "y", 1), getfield(l, "z", 1));

//  std::cout << "Retrieve arg 2" << std::endl;
  std::cout << "type stack -1: " << lua_typename(l, lua_type(l, -1)) << std::endl;
//  std::cout << "type stack -2: " << lua_typename(l, lua_type(l, -2)) << std::endl;
//  std::cout << "type stack -3: " << lua_typename(l, lua_type(l, -3)) << std::endl;
//  std::cout << "type stack -4: " << lua_typename(l, lua_type(l, -4)) << std::endl;
//  std::cout << "type stack -5: " << lua_typename(l, lua_type(l, -5)) << std::endl;
//  std::cout << "type stack -6: " << lua_typename(l, lua_type(l, -6)) << std::endl;
//  std::cout << "type stack -7: " << lua_typename(l, lua_type(l, -7)) << std::endl;
//  std::cout << "type stack -8: " << lua_typename(l, lua_type(l, -8)) << std::endl;

  int id = luaL_checkinteger(l, 2);
//  std::cout << "From Lua: id=" << id << std::endl;
  int obj = luaL_checkinteger(l, 3);
//  std::cout << "From Lua: obj=" << obj << std::endl;
  std::string mInfo1 = luaL_checkstring(l, 4);
  std::string mInfo2 = luaL_checkstring(l, 5);
  std::string mInfo3 = luaL_checkstring(l, 6);
//  std::cout << "From Lua: mInfo1=" << mInfo1 << std::endl;
//  std::cout << "From Lua: mInfo2=" << mInfo2 << std::endl;
//  std::cout << "From Lua: mInfo3=" << mInfo3 << std::endl;
//  std::cout << "From Lua: pos = (" << molPos.x << ", " << molPos.y << ", "<< molPos.z << ")" << std::endl;

  stage_ptr->createMolecule(molPos,
                            id,
                            (ObjectType)obj,
                             1,
                             mInfo1, mInfo2, mInfo3);
  return 1;
}

int L_Stage::createAnimalCell(lua_State *l)
{
  glm::vec3 scaling = glm::vec3(getfield(l, "x", 1), getfield(l, "y", 1), getfield(l, "z", 1));
  glm::vec3 molPos = glm::vec3(getfield(l, "x", 2), getfield(l, "y", 2), getfield(l, "z", 2));

  int id = luaL_checkinteger(l, 3);
  std::string mInfo1 = luaL_checkstring(l, 4);
  std::string mInfo2 = luaL_checkstring(l, 5);
  std::string mInfo3 = luaL_checkstring(l, 6);
  stage_ptr->createAnimalCell(scaling, molPos, id, 1, mInfo1, mInfo2, mInfo3);
  return 1;
}

int L_Stage::createArrow(lua_State *l)
{
  glm::vec3 scaling = glm::vec3(getfield(l, "x", 1), getfield(l, "y", 1), getfield(l, "z", 1));
  glm::vec3 pos = glm::vec3(getfield(l, "x", 2), getfield(l, "y", 2), getfield(l, "z", 2));
//  std::cout << "From Lua: pos = (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
//  std::cout << "From Lua: scaling = (" << scaling.x << ", " << scaling.y << ", " << scaling.z << ")" << std::endl;
  int id = luaL_checkinteger(l, 3);
  int obj = luaL_checkinteger(l, 4);
  int texture = luaL_checkinteger(l, 5);
  std::string mInfo1 = luaL_checkstring(l, 6);
  std::string mInfo2 = luaL_checkstring(l, 7);
  std::string mInfo3 = luaL_checkstring(l, 8);

  stage_ptr->createArrow(scaling, pos, id, (ObjectType) obj, texture, mInfo1, mInfo2, mInfo3);
  return 1;
}

int L_Stage::createMoleculeSpot(lua_State *l)
{
  int id = luaL_checkinteger(l, 1);
  int obj = luaL_checkinteger(l, 2);
  glm::vec3 shape = glm::vec3(getfield(l, "x", 3), getfield(l, "y", 3), getfield(l, "z", 3));
  glm::vec3 scale = glm::vec3(getfield(l, "x", 4), getfield(l, "y", 4), getfield(l, "z", 4));
  int texture = 1;
  glm::vec3 pos = glm::vec3(getfield(l, "x", 5), getfield(l, "y", 5), getfield(l, "z", 5));
  stage_ptr->createMoleculeSpot(id, (ObjectType) obj, shape, scale, texture, pos);
  return 1;
}

int L_Stage::createTextSpot(lua_State *l)
{
  int id = luaL_checkinteger(l, 1);
  int obj = luaL_checkinteger(l, 2);
  glm::vec3 shape = glm::vec3(getfield(l, "x", 3), getfield(l, "y", 3), getfield(l, "z", 3));
  glm::vec3 scale = glm::vec3(getfield(l, "x", 4), getfield(l, "y", 4), getfield(l, "z", 4));
  int texture = 0;
  glm::vec3 pos = glm::vec3(getfield(l, "x", 5), getfield(l, "y", 5), getfield(l, "z", 5));
  stage_ptr->createTextSpot(id, (ObjectType) obj, shape, scale, texture, pos);
  return 1;
}

int L_Stage::createText(lua_State *l) {
  glm::vec3 pos = glm::vec3(getfield(l, "x", 1), getfield(l, "y", 1), getfield(l, "z", 1));
  int id = luaL_checkinteger(l, 2);
  int obj = luaL_checkinteger(l, 3);
  int texture = 1;
  stage_ptr->createText(pos, id, (ObjectType) obj, texture);
  return 1;
}

int L_Stage::createBall(lua_State *l) {
  int id = luaL_checkinteger(l, 1);
  glm::vec3 pos = glm::vec3(getfield(l, "x", 2), getfield(l, "y", 2), getfield(l, "z", 2));
  int texture = luaL_checkinteger(l, 3);
  stage_ptr->createBall(id, pos, texture); // texture = 0 will set color usage in the ball object
  return 1;
}
static int createText(lua_State *l);

void L_Stage::setStage(Stage* stage) {
  L_Stage::stage_ptr = stage;
}
