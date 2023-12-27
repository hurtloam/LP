/*
 * LPDebugDraw.h
 *
 *  Created on: Sep 4, 2016
 *      Author: peter
 */

#ifndef INC_LPDEBUGDRAW_H_
#define INC_LPDEBUGDRAW_H_

#include "LinearMath/btIDebugDraw.h"
#include "../inc/View.h"
#include "../inc/Scene.h"
#include "../inc/LPWatch.h"
#include "../inc/LineObj.h"

//namespace platformBase {

class LPDebugDraw: public  btIDebugDraw{
public:
  LPDebugDraw (Scene* scene, LPWatch* watch, View* view);
  virtual ~LPDebugDraw();

  void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
//  void drawL(glm::vec3 from, glm::vec3 to, glm::vec3 color);
  void  drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);
  void  reportErrorWarning(const char* warningString);
  void  draw3dText(const btVector3& location,const char* textString);
  void  setDebugMode(int debugMode);
  int   getDebugMode() const;

  void
  SetMatrices (glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix, GLuint programId) {
    glUseProgram (programId); // Use Fixed-function pipeline (no shaders)
    glMatrixMode (GL_MODELVIEW);
    glLoadMatrixf (&pViewMatrix[0][0]);
    glMatrixMode (GL_PROJECTION);
    glLoadMatrixf (&pProjectionMatrix[0][0]);
  }
private:
  Scene *scene;
  View* view;
  LPWatch* watch;
  LineObj *line;
  int debugMode;
};

//} /* namespace platformBase */

#endif /* INC_LPDEBUGDRAW_H_ */
