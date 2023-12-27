#include "../inc/LPObject.h"
#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>

LPObject::LPObject (int id, glm::vec3 trans, glm::vec3 scale, LPWatch* watch) :
    watch (watch) {
  this->trans = trans;
  this->id = id;
  b_rigidBody = NULL;
  this->scale = scale;
  this->HP = 1000;
  this->XP = 20;


}

LPObject::LPObject (int id, glm::vec3 trans, glm::vec3 scale, LPWatch* watch, bool useDDS) :
    watch (watch)
{
  this->trans = trans;
  this->id = id;
  this->scale = scale;
  this->HP = 5;
  this->XP = 1;
}

LPObject::~LPObject() {
  if (b_shape != nullptr) {
    delete b_shape;
  }
  if (b_motionState != nullptr) {
    delete b_motionState;
  }
  if (b_rigidBody != nullptr) {
    delete b_rigidBody;
  }
}

void
LPObject::setFPSJumping (bool jump) {
  fpsJumping = jump;
}

bool
LPObject::getFPSJumping () const {
  return fpsJumping;
}
