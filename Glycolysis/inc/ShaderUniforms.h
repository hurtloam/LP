/*
 * ShaderUniforms.h
 *
 *  Created on: Feb 4, 2019
 *      Author: peter
 */

#ifndef INC_SHADERUNIFORMS_H_
#define INC_SHADERUNIFORMS_H_

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/glm.hpp>
#include <GL/glew.h>

class ShaderUniforms {
public:
  GLuint
  getProgramId () const;
  void
  setProgramId (GLuint programId);

  GLuint
  getMatrixId () const;
  void
  setMatrixId (GLuint matrixId);

  GLuint
  getModelMatrixId () const;
  void
  setModelMatrixId (GLuint modelMatrixId);

  GLuint
  getModelView3x3MatrixId () const {
    return ModelView3x3MatrixID;
  }
  void
  setModelView3x3MatrixId (GLuint modelView3x3MatrixId) {
    ModelView3x3MatrixID = modelView3x3MatrixId;
  }

  GLuint
  getLightId () const;
  void
  setLightId (GLuint lightId);

  GLuint
  getTextureId () const;
  void
  setTextureId (GLuint textureId);

  GLuint
  getViewMatrixId () const;
  void
  setViewMatrixId (GLuint viewMatrixId);


private:
  GLuint ViewMatrixID;
  GLuint programID;
  GLuint MatrixID;
  GLuint ModelMatrixID;
  GLuint ModelView3x3MatrixID;
  GLuint LightID;
  GLuint TextureID;
  GLuint colorID;
  GLuint Texture;
}
#endif /* INC_SHADERUNIFORMS_H_ */
