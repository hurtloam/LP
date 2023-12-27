/*
 * EventSM.h
 *
 *  Created on: 22 dec. 2018
 *      Author: peter
 */

#ifndef _UNIFORM_LOCATION_VAR_INC_LP_UNIFORM_H_
#define _UNIFORM_LOCATION_VAR_INC_LP_UNIFORM_H_

#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>

static const GLuint MAX_BONES = 100;

class LPUniform {
public:
  GLuint programID;
  GLuint MatrixID;
  GLuint ViewMatrixID;
  GLuint ModelMatrixID;
  GLuint LightID;
  GLuint TextureID;
  GLuint colorID;
  GLuint ModelView3x3MatrixID;
  GLuint BoneLocationID[MAX_BONES];
};

#endif // _UNIFORM_LOCATION_VAR_INC_LP_UNIFORM_H_
