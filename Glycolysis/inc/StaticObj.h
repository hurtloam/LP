/*
 * StaticObj.h
 *
 *  Created on: Jan 6, 2014
 *      Author: peter
 */

#ifndef STATICOBJ_H_
#define STATICOBJ_H_


#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/euler_angles.hpp>
#include "LPObject.h"
#include "View.h"
#include "ResObj.h"
#include <sys/time.h>

#include "../uniform_location_var/inc/LPUniform.h"




#ifdef WIN32
static long long GetCurrentTimeMillis()
{
  return GetTickCount();
}
#else
static long long GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);

  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;

  return ret;
}
#endif




class StaticObj: public LPObject {
public:
	StaticObj(int id,
			glm::vec3 scale,
			ObjectType objType,
			GLuint texture,
			glm::vec3 trans,
			LPWatch* watch,
			ResObj& resObj,
			const View& view,
			LPUniform lpUniform);

	virtual ~StaticObj();
	void internalDraw(ObjectType obj, buffer* buf);
	void internalDraw(buffer* buf);
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
  void
  move (bool flag);
  void
  move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);

	int getObjType() {return objType;}
	ObjectType getObjectType() { return objType; }
	void setObjectType(ObjectType o) { objType = o; }

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }



  const glm::vec3& getObjColor() const {
    return objColor;
  }

  void setObjColor(const glm::vec3& objColor = glm::vec3(0.5, 0.5, 0.0)) {
    this->objColor = objColor;
  }

  GLfloat getUseColor() const {
    return useColor;
  }

  void setUseColor(GLfloat useColor = 1.0) {
    this->useColor = useColor;
  }

  void SetBoneTransform(GLuint Index, glm::mat4& Transform);

  GLint getColorId() const
  {
    return colorID;
  }

  void setColorId(GLint colorId = 999)
  {
    colorID = colorId;
  }

  GLint getLightId2() const
  {
    return LightID2;
  }

  void setLightId2(GLint lightId2)
  {
    LightID2 = lightId2;
  }

  GLint getUseColorId() const
  {
    return useColorID;
  }

  void setUseColorId(GLint useColorId = 999)
  {
    useColorID = useColorId;
  }

  const LPUniform& getLpUniform() const
  {
    return lpUniform;
  }

  void setLpUniform(const LPUniform& lpUniform)
  {
    this->lpUniform = lpUniform;
  }

protected:
  ResObj& resObj;
	const View& view;
//  GLint TextureID;
//  GLint ModelMatrixID;
//  GLint ViewMatrixID;
  GLuint Texture;
//  GLint MatrixID;
  GLint LightID;
//  GLint programID;

  GLint MatrixID2;
  GLint programID2;
//  GLint TextureID2;
  GLint ModelMatrixID2;
  GLint ViewMatrixID2;
//  GLuint Texture;
  GLint LightID2;

  GLint useColorID = 999;
  GLint colorID = 999;

  GLint lightPowerID = 999;

//  GLuint BoneLocationID[MAX_BONES];
  LPUniform lpUniform;

//	GLfloat lightPower = 1500;
	glm::vec3 objColor = glm::vec3(0.2, 0.2, 0.2);

//	void drawPhysicsBox();

private:
  struct point {
    GLfloat x;
    GLfloat y;
    GLfloat s;
    GLfloat t;
  };


	glm::mat4 ModelMatrix;

	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;

	ObjectType currentObj;
	bool walking = true;
	glm::mat4 MVP;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
//	GLuint VertexArrayID;
	bool drawnOnce = false;
	GLfloat useColor = 1.0;



//  GLuint texture_local;
  //GLuint texture_local2;


protected:
  GLuint text_program_id;
  GLint attribute_coord = -1;
  GLint uniform_tex = -1;
  GLint uniform_color = -1;
  GLint attribute_UV = -1;
	ObjectType objType;
  long long m_startTime;
  float animTime = 0.0;
  vector<glm::mat4> Transforms;
  int cnt = 0;
  float currAnimTime;
  ObjectType tmpObjectType;
};

#endif /* STATICOBJ_H_ */
