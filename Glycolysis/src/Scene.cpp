/*
 * Scene.cpp
 *
 *  Created on: Dec 8, 2013
 *      Author: peter
 */

#include "../inc/Scene.h"
#include <iostream>
#include <glm/glm.hpp>
#include <cmath>
#include "../inc/shader.hpp"
#include "../inc/LPDebugDraw.h"
#include "LinearMath/btIDebugDraw.h"
#include "../inc/FPerson.h"
#include "../uniform_location_var/inc/LPUniform.h"
#include "../inc/logging.h"

using std::list;
//using namespace glm::pi();
//using namespace platformBase;




Scene::Scene(const char *vertexShader, const char *fragmentShader) :
    shader(vertexShader, fragmentShader)
{

	// Create and compile our GLSL program from the shaders
	/*
	 * 	const char * vertex_file_path - Vertex shader file path
	 *  const char * fragment_file_path - Fragment shader file path
	 */

  lpUniform.colorID = 0;
//  Texture = 0;

//  shader(vertexShader, fragmentShader);
  lpUniform.programID = shader.getProgramId();

	// Get a handle for our "MVP" uniform
  lpUniform.MatrixID = glGetUniformLocation(lpUniform.programID, "MVP");

  lpUniform.ViewMatrixID = glGetUniformLocation(lpUniform.programID, "V");
  lpUniform.ModelMatrixID = glGetUniformLocation(lpUniform.programID, "M");
  lpUniform.ModelView3x3MatrixID = glGetUniformLocation(lpUniform.programID, "MV3x3");
//	ViewMatrixID = glGetUniformLocation(programID, "color");
//	ModelMatrixID = glGetUniformLocation(programID, "coord");
  lpUniform.LightID = glGetUniformLocation(lpUniform.programID, "LightPosition_worldspace");
//	for () {
//	  gBoneID = = glGetUniformLocation(programID, name);
//	}

  for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(lpUniform.BoneLocationID); i++) {
    char Name[128];
    memset(Name, 0, sizeof(Name));
    snprintf(Name, sizeof(Name), "gBones[%d]", i);
    lpUniform.BoneLocationID[i] = glGetUniformLocation(lpUniform.programID, Name);
  }

  lpUniform.TextureID = glGetUniformLocation(lpUniform.programID, "myTextureSampler");
//	TextureID  = glGetUniformLocation(programID, "tex");

	glm::vec3 lightPos = glm::vec3(30.0f,40.0f,30.0f);
  glUniform3f(lpUniform.LightID, lightPos.x, lightPos.y, lightPos.z);


	tmpCounter = 0;

	// Bullet stuff below...
	broadphase = new btDbvtBroadphase();

  collisionConfiguration = new btDefaultCollisionConfiguration ();
  dispatcher = new btCollisionDispatcher (collisionConfiguration);

	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

  dynamicsWorld->setGravity (btVector3 (0, -15.81f, 0));


	// Setting a ground
  groundShape = new btStaticPlaneShape (btVector3 (0, 0, 0), 1);
  groundMotionState = new btDefaultMotionState (btTransform (btQuaternion (0, 0, 0, 1), btVector3 (0, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);

//	btIDebugDraw *debugDrawer = new LPDebugDraw(this, vi);
//	dynamicsWorld->setDebugDrawer(debugDrawer);

  creature = nullptr;

  logOutputPtr = new int(1);
  setLogging(logOutputPtr, 1);

}

void Scene::addActor(LPObject *a) {
  int x, y, z, id;
  if (((Actor*) a)->getId() == 1000) {
    creature = (Actor*) a;
  }

  if (((Actor*) a)->getObjType() == sniper1) {
    sniper = (Actor*) a;
  }

  if (a->getRigidBody() != NULL) {
    cout << "Adding obj as UserPointer" << endl;
    a->getRigidBody ()->setUserPointer (a);
    dynamicsWorld->addRigidBody (a->getRigidBody ());
  }
  actorList.push_back (a);
}

void Scene::removeActor(LPObject *a) {
  cout << "ENTER removeActor" << endl;
  if (a->getRigidBody() != nullptr) {
    dynamicsWorld->removeRigidBody(a->getRigidBody());
  }
  else {
    cout << "ERROR: cannot remove a->getRigidBody (), nullptr returned" << endl;
  }
  cout << "After removeRigidBody on id=" << a->getId() << endl;
  actorList.remove(a);
  cout << "After actorList.remove(a)" << endl;
  delete (a);
  cout << "After delete(a)" << endl;
}

void Scene::removeActor(int actorId)
{
  for (auto actor : actorList) {
    if (actor->getId() == actorId) {
      SDL_Log("Scene::removeActor : Deleting the object with id=%d", actorId);
      if (actor->getRigidBody() != nullptr) {
        dynamicsWorld->removeRigidBody(actor->getRigidBody());
      }
      else {
        cout << "ERROR: cannot remove a->getRigidBody (), nullptr returned" << endl;
      }
      actorList.remove(actor);
      delete (actor);
		}
	}
}

void init()
{
}

Scene::~Scene()
{
  std::cout << "ENTER Scene::~Scene()" << std::endl;
  SDL_Log("Scene::~Scene() : before actorList loop: actorList.size() = %d", (int) actorList.size());
  for (auto actor : actorList) {
    if (actor->getRigidBody() != nullptr) {
      dynamicsWorld->removeRigidBody(actor->getRigidBody());
    }
    delete actor;
	}
  actorList.clear();
  dynamicsWorld->removeRigidBody(groundRigidBody);
  delete groundShape;
  delete groundMotionState;
  delete groundRigidBody;

  // delete all bulletphysics:
  std::cout << "About to Delete 1" << std::endl;
  delete broadphase;
  std::cout << "About to Delete 2" << std::endl;
  delete collisionConfiguration;
  std::cout << "About to Delete 3" << std::endl;
  delete dispatcher;
  std::cout << "About to Delete 4" << std::endl;
  delete solver;
  std::cout << "About to Delete 5" << std::endl;
//  delete groundShape;
//  std::cout << "About to Delete 6" << std::endl;
//  delete groundMotionState;
  std::cout << "About to Delete 7" << std::endl;
//  delete groundRigidBody;
  std::cout << "About to Delete dynamicsWorld" << std::endl;
  std::cout << "m_collisionObjects=" << dynamicsWorld->getCollisionObjectArray().size() << std::endl;

	delete(dynamicsWorld);
  std::cout << "After Delete of dynamicsWorld" << std::endl;

  std::cout << "END Scene::~Scene()" << std::endl;
}

GLuint Scene::getLightId() const {
  return lpUniform.LightID;
}

void Scene::setLightId(GLuint lightId) {
  lpUniform.LightID = lightId;
}

GLuint Scene::getMatrixId() const {
  return lpUniform.MatrixID;
}

void Scene::setMatrixId(GLuint matrixId) {
  lpUniform.MatrixID = matrixId;
}

GLuint Scene::getModelMatrixId() const {
  return lpUniform.ModelMatrixID;
}

void Scene::setModelMatrixId(GLuint modelMatrixId) {
  lpUniform.ModelMatrixID = modelMatrixId;
}

GLuint Scene::getProgramId() const {
  return lpUniform.programID;
}

void Scene::setProgramId(GLuint programId) {
  lpUniform.programID = programId;
}

GLuint Scene::getTextureId() const {
  return lpUniform.TextureID;
}

void Scene::setTextureId(GLuint textureId) {
  lpUniform.TextureID = textureId;
}

GLuint Scene::getViewMatrixId() const {
  return lpUniform.ViewMatrixID;
}

void Scene::setViewMatrixId(GLuint viewMatrixId) {
  lpUniform.ViewMatrixID = viewMatrixId;
}


void Scene::draw()
{
//  glUseProgram(programID);
	for (auto iter : getActorList()) {
		iter->draw();
	}
}


void
Scene::move (std::vector<std::pair<int, int>> collisionDetected, glm::vec3 normal)
{
  for (auto iter : getActorList ())
  {
      iter->move (collisionDetected, normal);
  }
}

LPObject* Scene::getObject(int id)
{
	for (auto obj: actorList)
	{
		if (obj->getId() == id)
		{
			return obj;
		}
	}
  TRACE_DEBUG("failed to find object id=%d", id);
//  std::cout << "failed to find object id=" << id << ", in actorList" << std::endl;
//  TRACE_DEBUG("List of all objects: ");
//  for (auto obj : actorList)
//  {
//    TRACE_DEBUG("object id=%d , in actorList", obj->getId());
//  }
	return NULL;
}

std::vector<LPObject*> Scene::getObjectFromObjType(ObjectType objType)
{
  std::vector<LPObject*> objList;
  for (auto obj : actorList) {
    if (obj->getObjType() == objType) {
      objList.push_back(obj);
    }
  }
  return objList;
}


void Scene::printCoord(int id) {
	int tmp;
	tmp = id;
	if (sniper->getTrans().x > (coordinate.x + 1.0) || sniper->getTrans().x < (coordinate.x - 1.0)) {
		printf("sniper position: (%f, %f, %f)  -- coordinate: (%f, %f, %f) -- Rounded: (%f, %f, %f)\n", sniper->getTrans().x, sniper->getTrans().y, sniper->getTrans().z, coordinate.x, coordinate.y, coordinate.z, glm::roundEven(sniper->getTrans()).x, glm::roundEven(sniper->getTrans()).y, glm::roundEven(sniper->getTrans()).z);
		coordinate = sniper->getTrans();
	}
}

void Scene::saveActorList(list<std::string> *objList)
{
	cout << "Enter method saveActorList" << endl;
	for (auto item : actorList) {
		char buf[256];
		cout << "Saving actor id=" << item->getId() << endl;
		sprintf(buf, "id:%d,objType:%d,position:(%f,%f,%f),rotation:(%f,%f,%f),scale:(%f,%f,%f),texture:%d\n",
				item->getId(),
				item->getObjType(),
				item->getTrans().x,
				item->getTrans().y,
				item->getTrans().z,
				item->getOrientation().x,
				item->getOrientation().y,
        item->getOrientation().z,
				item->getScale().x,
				item->getScale().y,
				item->getScale().z,
				item->getTexture());
		objList->push_back(buf);
	}
}

bool
Scene::isOccupied (glm::vec3 spot)
{
  for (auto iter : actorList)
    {
    if (iter->getId () != 1000 && iter->getId () != 24001 && iter->getId () != 20000 && iter->getId () != 8001)
        {
      if (fabsf (spot.x - iter->getTrans ().x) < 1.5f && fabsf (spot.y - iter->getTrans ().y) < 3.0f && fabsf (spot.z - iter->getTrans ().z) < 1.5f)
            //                      if (ceil(spot.x) == ceil(iter->getTrans().x) &&
            //                                      ceil(spot.y) == ceil(iter->getTrans().y) &&
            //                                      ceil(spot.z) == ceil(iter->getTrans().z) )
//        iter->getRigidBody ()->checkCollideWith (sniper->getRigidBody ());
            return true;
        }

//    std::cout << "Sniper pos: (" << sniper->getTrans ().x << ", " << sniper->getTrans ().y << ", " << sniper->getTrans ().z << ")" << std::endl;
    }
  return false;
}

bool
Scene::isSniperColliding (glm::vec3 spot) {
  for (auto iter : actorList)
  {
    if (iter->getId () != 1000 && iter->getId () != 24001 && iter->getId () != 20000 && iter->getId () != 8001)
    {
//      if (iter->getRigidBody ()->checkCollideWith (sniper->getRigidBody ()))
//      {
        //                      if (ceil(spot.x) == ceil(iter->getTrans().x) &&
        //                                      ceil(spot.y) == ceil(iter->getTrans().y) &&
        //                                      ceil(spot.z) == ceil(iter->getTrans().z) )
//        iter->getRigidBody()->checkCollideWith(sniper->getRigidBody());
//        std::cout << "Sniper pos: Collision detected! " << std::endl;

//        return true;
//      }
//      else
//      {
//        std::cout << "Sniper pos: (" << sniper->getTrans ().x << ", " << sniper->getTrans ().y << ", " << sniper->getTrans ().z << ")" << std::endl;

//      }

//    std::cout << "Sniper pos: (" << sniper->getTrans ().x << ", " << sniper->getTrans ().y << ", " << sniper->getTrans ().z << ")" << std::endl;
    }
    return false;
  }

}

LPUniform Scene::getLPUniform()
{
  return lpUniform;
}

//void Scene::SetBoneTransform(uint Index, glm::mat4& Transform)
//{
////  SDL_Log("Scene::SetBoneTransform Input parameters : index=%d, MAX_BONES=%d", Index, MAX_BONES);
//
//  assert(Index < MAX_BONES);
//  const GLfloat m[4][4] = { { Transform[0][0], Transform[0][1], Transform[0][2], Transform[0][3] }, { Transform[1][0], Transform[1][1], Transform[1][2], Transform[1][3] }, { Transform[2][0], Transform[2][1], Transform[2][2], Transform[2][3] }, {
//      Transform[3][0], Transform[3][1], Transform[3][2], Transform[3][3] } };
//
//  //Transform.Print();
//  glUniformMatrix4fv(BoneLocationID[Index], 1, GL_TRUE, (const GLfloat*) m);
//
//}
