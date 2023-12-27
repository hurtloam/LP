/*
 * LPObject.h
 *
 *  Created on: Dec 8, 2013
 *      Author: peter
 *
 *      Learning Platform Base Object.
 */

#ifndef LPOBJECT_H_
#define LPOBJECT_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>

#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec4.hpp>

#include <glm/gtx/euler_angles.hpp>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <LinearMath/btDefaultMotionState.h>
#include <SDL2/SDL.h>
#include <vector>

#include <cstdio>
#include <iostream>

#include "logging.h"

//#include "LPWatch.h"

using namespace std;

typedef struct _object obj;

class LPWatch;
//enum keys {
//  left, right, forward, backward, up, down, still
//};

class LPObject {
public:

  /**
   * Constructor for 3D objects being used on the Learning Platform.
   *
   *	const char * imagepath - Path to the texure image file or uv layout file
   *	const char objpath - Path to the object file defining all the vertices describing the 3D object.
   */
  LPObject (int id, glm::vec3 trans, glm::vec3 scale, LPWatch* watch);

  LPObject (int id, glm::vec3 trans, glm::vec3 scale, LPWatch* watch, bool useDDS);

  virtual ~LPObject();

enum MenuStatusE {
  DEFAULT = 0,
  ACTIVE = 1, // menuItem has not yet been selected
  SELECTED = 2,    // menuItem has been selected
  HIDDEN = 3   // The menuContainer is hidden
};

  virtual void draw() = 0;
  //	virtual GLuint getNormalbuffer() const = 0;
  //	virtual void setNormalbuffer(GLuint normalbuffer) = 0;
  virtual bool isStatic() = 0;
  //	virtual bool isDrawnOnce() = 0;
  virtual void createId() = 0;
  //	virtual int getId() = 0;
  virtual void
  move (bool flag) = 0;

  virtual void
  move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal) = 0;
  glm::vec3 getTrans() {return trans;}

  glm::vec2 getMouseCoord() {return savedMouseCoord;}

  glm::vec3 getSavedTrans() {return savedTrans;}

  virtual void setTrans(glm::vec3 t)
  {
    trans = trans + t;
  }

  virtual void setMouseCoord(glm::vec2 t)
    {
      savedMouseCoord = t;
    }

  virtual void setSavedTrans(glm::vec3 t)
    {
      savedTrans = t;
    }

  virtual void setRelativeTrans(glm::vec3 t)
    {
      trans = trans + t;
    }

  virtual void setAbsoluteTrans(glm::vec3 t) {
    trans = t;
  }

  void adjustToGrid()
  {
//    if ((id > 16000) && (id < 16015)) {
        //    const float granularity = 0.1f;
    const float granularity = 1.0f;
        const float halfGran = 0.5f * granularity;

        float restX = 1.0f*abs((int)round(trans.x - round(trans.x)*10))/10.0;
        float restY = 1.0f*abs((int)round(trans.y - round(trans.y)*10))/10.0;
        float restZ = 1.0f*abs((int)round(trans.z - round(trans.z)*10))/10.0;
        float roundedX = round(trans.x / granularity) * granularity;
        float roundedY = round(trans.y / granularity) * granularity;
        float roundedZ = round(trans.z / granularity) * granularity;
        std::cout << "restX=" << restX << endl;
        std::cout << "Initial roundedX=" << roundedX << std::endl;

        if (restX <= granularity)
          {
            if ((granularity - restX) < halfGran)
              {
                roundedX += granularity;
              }
            else
              {
                //				roundedX -= granularity;
              }
          }
        else
          {
            if ((restX - granularity) < halfGran)
              {
                roundedX -= granularity;
              }
            else
              {
                //				roundedX += granularity;

              }
          }
        std::cout << "trans.x=" << trans.x << ", roundedX=" << roundedX << std::endl;
        trans.x = roundedX;

        if (restY <= granularity)
          {
            if ((granularity - restY) < halfGran)
              {
                roundedY += granularity;
              }
          }
        else
          {
            if ((restY - granularity) < halfGran)
              {
                roundedY -= granularity;
              }
          }
        trans.y = roundedY;


        if (restZ <= granularity)
          {
            if ((granularity - restZ) < halfGran)
              {
                roundedZ += granularity;
              }
          }
        else
          {
            if ((restZ - granularity) < halfGran)
              {
                roundedZ -= granularity;
              }
          }
        //		trans.z = round(trans.z) + 0.5f;
        trans.z = roundedZ;
//    }
  }
  virtual int getObjType() = 0;
  virtual GLuint getTexture() = 0;
  int getId() {
    return id;
  }

  const glm::vec3& getScale() const {
    return scale;
  }

  void setScale(const glm::vec3& scale) {
    this->scale = scale;
  }

  glm::vec3 getOrientation() {return gOrientation;}

  void setOrientation(glm::vec3 r)
  {
    gOrientation = r;
  }

  void setOrientationX(float o) {
    gOrientation.x = gOrientation.x + o;
  }

  void setOrientationY(float o) {
    gOrientation.y = gOrientation.y + o;
  }

  void setOrientationZ(float o) {
    gOrientation.z = gOrientation.z + o;
  }

  void setRotationMatrix_Y(float r) {
    setOrientationY(r);
    RotationMatrix = glm::eulerAngleYXZ(gOrientation.y, gOrientation.x, gOrientation.z);
  }

  void setRotationMatrix_X(float r) {
    setOrientationX(r);
    RotationMatrix = glm::eulerAngleYXZ(gOrientation.y, gOrientation.x, gOrientation.z);
  }


  void setRotationMatrix_Z(float r) {
    setOrientationZ(r);
    RotationMatrix = glm::eulerAngleYXZ(gOrientation.y, gOrientation.x, gOrientation.z);
  }

  void setRotationMatrix(glm::vec3 r) {
    setOrientation(r);
    RotationMatrix = glm::eulerAngleYXZ(r.y, r.x, r.z);
  }

  glm::mat4 getRotationMatrix() {return RotationMatrix;}


  btRigidBody* getRigidBody()
  {
    return b_rigidBody;
  }

  virtual void setColor(GLfloat const _color[4])
  {
    color[0] = _color[0];
    color[1] = _color[1];
    color[2] = _color[2];
    color[3] = _color[3];
  }

  const glm::vec3& getLightPos() const {
    return lightPos;
  }

  void setLightPos(
      const glm::vec3& lightPos ) {
    this->lightPos = lightPos;
  }

    const string&
    getMoleculeInfo1 () const
    {
      return moleculeInfo1;
    }

    void
    setMoleculeInfo1 (const string& moleculeInfo1)
    {
      this->moleculeInfo1 = moleculeInfo1;
    }

    const string&
    getMoleculeInfo2 () const
    {
      return moleculeInfo2;
    }

    void
    setMoleculeInfo2 (const string& moleculeInfo2)
    {
      this->moleculeInfo2 = moleculeInfo2;
    }

    const string&
    getMoleculeInfo3 () const
    {
      return moleculeInfo3;
    }

    void
    setMoleculeInfo3 (const string& moleculeInfo3)
    {
      this->moleculeInfo3 = moleculeInfo3;
    }

    bool
    isIsHidden () const
    {
      return isHidden;
    }

    void
    setIsHidden (bool isHidden = false)
    {
      this->isHidden = isHidden;
    }

    void setLightPower(GLfloat lp) {
      lightPower = lp;
    }

    GLfloat getLightPower() {
      return lightPower;
    }

  void
  setFPSJumping (bool jump);

  bool
  getFPSJumping () const;

  virtual void
  sawIt(glm::vec3 position, int id)
  {
    return;
  }

  bool isCorrectPosition()
  {
    return correctPosition;
  }
  bool correctPosition;

  int getCollisionObj()
  {
    return collisionObj;
  }

  int collisionObj;


  const glm::vec3&
  getPosition () const {
    return position;
  }

  void
  setPosition (const glm::vec3& position) {
    this->position = position;
  }

  float
  getV () const {
    return v;
  }

  void
  setV (float v) {
    this->v = v;
  }

  float
  getX () const {
    return x;
  }

  void
  setX (float x) {
    this->x = x;
  }

  float
  getY () const {
    return y;
  }

  void
  setY (float y) {
    this->y = y;
  }

  float
  getZ () const {
    return z;
  }

  void
  setZ (float z) {
    this->z = z;
  }

  bool
  isDead () const {
    return dead;
  }

  void
  setDead (bool dead) {
    this->dead = dead;
  }

  int
  getHp () const {
    return HP;
  }

  void
  setHp (int hp) {
    HP = hp;
  }

  int
  getXp () const {
    return XP;
  }

  void
  setXp (int xp) {
    XP = xp;
  }

  bool
  isWinning () const {
    return winning;
  }

  void
  setWinning (bool winning = false) {
    this->winning = winning;
  }

protected:
  bool fpsJumping = true;
  btRigidBody* b_rigidBody = nullptr;
  btCollisionShape* b_shape = nullptr;
  btVector3 min,max;
  btDefaultMotionState* b_motionState = nullptr;


  GLfloat color[4];
  GLfloat lightPower = 1500;
//  GLfloat lightPower = 50;

  glm::vec3 scale;
  LPWatch* watch;
  int *logOutputPtr = nullptr;
private:
  float z;
  float x;

  float v;
  float y;
  glm::vec3 position;



  string moleculeInfo1;
  string moleculeInfo2;
  string moleculeInfo3;
  // As an example, rotate around the vertical axis at 180 degrees/sec
  glm::vec3 gOrientation = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::mat4 RotationMatrix;
//  glm::vec3 lightPos = glm::vec3 (0.0f, 20.0f, 0.0f);
  glm::vec3 lightPos = glm::vec3(0.0f,20.0f,45.0f);
  // Build the model matrix
  bool useDDS;
  int id;
  int objType;

  glm::vec3 trans = glm::vec3(0.0f,0.0f,0.0f);

  glm::vec3 savedTrans = glm::vec3(0.0f,0.0f,0.0f);
  glm::vec2 savedMouseCoord = glm::vec2(0.0f,0.0f);

  bool isHidden = false;

  int HP = 0;
  int XP = 0;
  bool dead = false;
  bool winning = false;

};

#endif /* LPOBJECT_H_ */
