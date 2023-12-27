/*
 * Actor.h
 *
 *  Created on: Dec 8, 2013
 *      Author: peter
 */

#ifndef ACTOR_H_
#define ACTOR_H_

#define GLM_ENABLE_EXPERIMENTAL
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/euler_angles.hpp>
#include "LPObject.h"
#include "View.h"
#include "ResObj.h"

class Actor: public LPObject {
public:

	/**
	 *
	 * @param vertex_file_path
	 * @param fragment_file_path
	 * @param imagepath
	 * @param objpath
	 */
	Actor(int id, glm::vec3 scale, ObjectType objType, int objArray_length, GLuint texture,
			   glm::vec3 trans, LPWatch* watch, const ResObj& resObj, const View& view, GLuint programID,
         GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID, GLuint LightID, GLuint TextureID);
/**
 *
 * @param vertex_file_path
 * @param fragment_file_path
 * @param imagepath
 * @param objpath
 * @param useDDS
 */
	Actor(int id, glm::vec3 scale, ObjectType objType, int objArray_length, GLuint texture, glm::vec3 trans,
			   bool useDDS, LPWatch* watch, const ResObj& resObj, const View& view, GLuint programID,
         GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID, GLuint LightID, GLuint TextureID);

	/** \brief Draws the object.
	 *
	 * @param window
	 * @param event
	 */
	void draw();
	virtual ~Actor();
	void loadObjIntoBuffer();
	bool isStatic();
	bool isDrawnOnce(){return drawnOnce;}

	void setWalking() {walking = true;};
	void setStanding() {walking = false;};
	bool isWalking() {return walking;};
	int getObjType () {return objType;};

  GLuint getTexture()
  {
    return Texture;
  }
  ;

  void sawIt(glm::vec3 position, int id) override
  {
    return;
  }

	void createId();
	//		int getId();
	void setCurrentObj(int obj) {currentObj = obj;};
	int getCurrentObj() {return currentObj;};

  void
  move (bool flag);

  void
  move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal);

  GLuint getColorId() const {
    return colorID;
  }

  void setColorId(GLuint colorId = 999) {
    colorID = colorId;
  }

  GLuint getUseColorId() const {
    return useColorID;
  }

  void setUseColorId(GLuint useColorId = 999) {
    useColorID = useColorId;
  }

private:

	const ResObj& resObj;
	const View& view;
	GLuint programID;
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint LightID;
	GLuint TextureID;

	obj objArray[32];
	int objArray_length = 0;

	ObjectType objType;

	int currentObj = 0;
	bool walking = false;

	GLuint useColorID = 999;
	GLuint colorID = 999;

	GLuint Texture;

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	GLuint VertexArrayID[23];
	GLuint currentVAO_ID = 0;

	bool drawnOnce = false;

	int k = 1;
};

#endif /* ACTOR_H_ */
