/*
 * Actor.cpp
 *
 *  Created on: Dec 8, 2013
 *      Author: peter
 */

#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
//#include <assimp/Importer.hpp>
//#include <assimp/postprocess.h>
//#include <assimp/scene.h>
#include "../inc/Actor.h"
#include "../inc/objloader.hpp"
#include "../inc/texture.hpp"
#include "../inc/shader.hpp"
#include "../inc/View.h"
#include "../inc/ResObj.h"

#include <vector>

//using namespace Assimp;

Actor::Actor(int id,
		glm::vec3 scale,
		ObjectType objType,
		int objArray_length,
		GLuint texture,
		glm::vec3 trans,
		LPWatch* watch,
		const ResObj& resObj,
		const View& view,
		GLuint programID,
		GLuint MatrixID,
		GLuint ViewMatrixID,
		GLuint ModelMatrixID,
		GLuint LightID,
		GLuint TextureID
) :
    LPObject (id, trans, scale, watch),
resObj(resObj),
view(view),
programID(programID),
MatrixID(MatrixID),
ViewMatrixID(ViewMatrixID),
ModelMatrixID(ModelMatrixID),
LightID(LightID),
TextureID(TextureID)
{
	Texture = texture;
	this->objType = objType;
	currentObj = objType;
	this-> objArray_length = objArray_length;
  
}

Actor::Actor(int id,
		glm::vec3 scale,
		ObjectType objType,
		int objArray_length,
		GLuint texture,
		glm::vec3 trans,
		bool useDDS,
		LPWatch* watch,
		const ResObj& resObj,
		const View& view,
		GLuint programID,
		GLuint MatrixID,
		GLuint ViewMatrixID,
		GLuint ModelMatrixID,
		GLuint LightID,
		GLuint TextureID) :
    LPObject (id, trans, scale, watch, useDDS),
				resObj(resObj),
				view(view),
				programID(programID),
				MatrixID(MatrixID),
				ViewMatrixID(ViewMatrixID),
				ModelMatrixID(ModelMatrixID),
				LightID(LightID),
				TextureID(TextureID)
{
	this->objType = objType;
	Texture = texture;
	currentObj = objType;
	this-> objArray_length = objArray_length;
	// TODO Auto-generated constructor stub
}


/**
 * @brief Draws the object.
 *
 * @param window
 * @param event
 */
void Actor::draw() {
	glUseProgram(programID);
  
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	ModelMatrix = glm::translate(ModelMatrix,getTrans()) * getRotationMatrix();
	glm::mat4 MVP = view.getProjectionMatrix() * view.getViewMatrix() * ModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glm::mat4 tmpViewMatrix = view.getViewMatrix();
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &tmpViewMatrix[0][0]);

	//	glm::vec3 lightPos = glm::vec3(30.0f,40.0f,30.0f);
	//	glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

	// EPEBROR
	// if check if we dont need to do glBindTexture every time

  useColorID = glGetUniformLocation(programID, "useColor");
  colorID = glGetUniformLocation(programID, "objColor");
  //setObjColor(glm::vec3(1.0f, 1.0f, 0.0f));

  if (useColorID == 999)
  {
    fprintf(stderr, "Error: colorID was never retrieved");
  }
  glUniform1f(useColorID, getUseColorId());
  glUniform3f(colorID, 1.0f, 0.0f, 0.0f);

	// Bind our texture in Texture Unit 2
	glActiveTexture(GL_TEXTURE2);

	glBindTexture(GL_TEXTURE_2D, this->Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 2
	glUniform1i(TextureID, 2);

	//	loadObjIntoBuffer();
	//	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	//	printf("DRAW: object number: %d\n", currentObj);
	glBindBuffer(GL_ARRAY_BUFFER, resObj.getVertexbuffer(currentObj));
	glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, resObj.getUvbuffer(currentObj));
	glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, resObj.getNormalbuffer(currentObj));
	glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
	);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, resObj.getVertices(currentObj).size());

  currentObj++;

  if (currentObj == objType + objArray_length * k) {
    currentObj = objType;

  }
}

Actor::~Actor() {

}

bool Actor::isStatic() {
	return false;
}

void Actor::createId() {

}

void
Actor::move (bool flag) {

}

void
Actor::move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal) {

}

//void Actor::setTrans(glm::vec3 t)
//{
//	trans = trans + t;
//}
