#pragma once

#include "../inc/LPObject.h"
#include <glm/detail/type_vec3.hpp>
class LPWatch
{
public:
  LPWatch () = default;
  virtual
  ~LPWatch () = default;

  // Implemented in LearningPlatform
  virtual void
  registerWatch (int id, LPObject* requester) = 0;
private:

};
