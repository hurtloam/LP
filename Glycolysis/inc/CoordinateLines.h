/*
 * CoordinateLines.h
 *
 *  Created on: Apr 5, 2015
 *      Author: peter
 */

#ifndef SRC_COORDINATELINES_H_
#define SRC_COORDINATELINES_H_

#include "LPObject.h"
#include "View.h"
#include "ResObj.h"
#include "../uniform_location_var/inc/LPUniform.h"

class CoordinateLines: public LPObject {
public:
  CoordinateLines(int id,
      glm::vec3 scale,
      glm::vec3 trans,
      LPWatch* watch,
      ResObj& resObj,
      const View& view,
      GLuint programID,
      GLuint MatrixID,
      GLuint ViewMatrixID,
      GLuint ModelMatrixID,
      GLuint LightID,
      GLuint TextureID);

  virtual ~CoordinateLines();
  void draw(ObjectType obj);
  void draw();

  float getHorizontalAngle() const;
    void setHorizontalAngle(float horizontalAngle = 3.14f);
    float getVerticalAngle() const;
    void setVerticalAngle(float verticalAngle = 0.0f);

    bool isStatic();

    GLuint getNormalbuffer() const;

    void setNormalbuffer(GLuint normalbuffer);

    bool isDrawnOnce() {return drawnOnce;}

    void createId();

  GLuint getTexture()
  {
    return Texture;
  }
  ;

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

    glm::vec3 getOrientation() {return gOrientation;}
    void setOrientation(float o) {
      gOrientation.y = gOrientation.y + o;
    }

    void setRotationMatrix(float r) {
      setOrientation(r);
      RotationMatrix = glm::eulerAngleYXZ(gOrientation.y+r, gOrientation.x, gOrientation.z);
    }

    glm::mat4 getRotationMatrix() {return RotationMatrix;}

  void
  move (bool flag);
  void
  move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);

  int getObjType() {return objType;}

private:
  const ResObj& resObj;
  const View& view;
  GLuint programID;
  GLuint MatrixID; GLuint ViewMatrixID;
  GLuint ModelMatrixID;
  GLuint LightID;
  GLuint TextureID;

  // Initial horizontal angle : toward -Z
  float horizontalAngle = 3.14f;
  // Initial vertical angle : none
  float verticalAngle = 0.0f;

  // As an example, rotate arount the vertical axis at 180 degrees/sec
  glm::vec3 gOrientation = glm::vec3(0.0f, 0.0f, 0.0f);

  // Build the model matrix
  glm::mat4 RotationMatrix;


  ObjectType currentObj;
  bool walking = true;
  GLuint Texture;
  glm::mat4 MVP;
  glm::mat4 ViewMatrix;
  glm::mat4 ProjectionMatrix;
  glm::mat4 ModelMatrix;
  GLuint VertexArrayID;
  bool drawnOnce = false;
  ObjectType objType = coordinate_lines;
};

#endif /* SRC_COORDINATELINES_H_ */
