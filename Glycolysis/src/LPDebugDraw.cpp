/*
 * LPDebugDraw.cpp
 *
 *  Created on: Sep 4, 2016
 *      Author: peter
 */

#include "../inc/LPDebugDraw.h"
#include "../inc/LineObj.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//namespace platformBase {

  LPDebugDraw::LPDebugDraw(
      Scene* scene, LPWatch* watch, View* view) :
          scene(scene),
          watch (watch),
          view(view),
          line(nullptr),
          debugMode (btIDebugDraw::DBG_DrawWireframe)
//          debugMode (btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE)
  {
  line = new LineObj (997, glm::vec3 (1.0f, 1.0f, 1.0f), 0, glm::vec3 (0.0f, 0.0f, 0.0f), watch, view, scene->getProgramId (), scene->getMatrixId (), scene->getViewMatrixId (),
                      scene->getModelMatrixId (),
                      scene->getLightId (), scene->getTextureId ());
  }

  LPDebugDraw::~LPDebugDraw() {
    // TODO Auto-generated destructor stub
  }

  void LPDebugDraw::drawLine(const btVector3& from,
                             const btVector3& to,
                             const btVector3& color)
  {
//  line = new LineObj (997, glm::vec3 (1.0f, 1.0f, 1.0f), 0, glm::vec3 (0.0f, 0.0f, 0.0f), view, scene->getProgramId (), scene->getMatrixId (), scene->getViewMatrixId (), scene->getModelMatrixId (),
//                      scene->getLightId (), scene->getTextureId ());


    std::vector<glm::vec3> lineCoord{
  { from.getX (), from.getY (), from.getZ () },
  { to.getX (), to.getY (), to.getZ () }

//  { from.getX () + 0.0001, from.getY () + 0.0001, from.getZ () + 0.0001 },
//  { to.getX () + 0.0001, to.getY () + 0.0001, to.getZ () + 0.0001 },
//
//  { from.getX () + 0.0002, from.getY (), from.getZ () },
//  { to.getX () + 0.0002, to.getY (), to.getZ () },
//
//  { from.getX () + 0.0003, from.getY () + 0.0003, from.getZ () },
//  { to.getX () + 0.0003, to.getY () + 0.0003, to.getZ () }

  };
    line->setLineCoord(lineCoord);
    line->setColor(glm::vec4(color.getX(), color.getY(), color.getZ(), 1.0f));
  line->draw ();
  }

  void  LPDebugDraw::drawContactPoint(
      const btVector3& PointOnB,
      const btVector3& normalOnB,
      btScalar distance,
      int lifeTime,
      const btVector3& color)
  {
    // TODO
  }

  void  LPDebugDraw::reportErrorWarning(const char* warningString)
  {
    // TODO
  }

  void  LPDebugDraw::draw3dText(const btVector3& location,const char* textString)
  {
    // TODO
  }

  void  LPDebugDraw::setDebugMode(int debugMode)
  {
    this->debugMode = debugMode;
  }

  int   LPDebugDraw::getDebugMode() const
  {
    return this->debugMode;
  }

//} /* namespace platformBase */
