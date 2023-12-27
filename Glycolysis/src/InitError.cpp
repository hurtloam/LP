/*
 * InitError.cpp
 *
 *  Created on: Nov 30, 2013
 *      Author: peter
 */

#include <exception>
#include <string>
#include <SDL2/SDL.h>

#include "../inc/InitError.h"

namespace platformBase {

InitError::InitError():
  exception(), msg(SDL_GetError()) {}
InitError::InitError(const std::string& m):
  exception(), msg(m) {}
InitError::~InitError() throw() {}
const char* InitError::what() const throw() {
    return msg.c_str();
}



} /* namespace platformBase */
