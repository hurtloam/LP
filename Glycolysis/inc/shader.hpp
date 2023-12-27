/*
 * shader.hpp
 *
 *  Created on: Dec 3, 2013
 *      Author: peter
 */

#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <glm/glm.hpp>

class Shader {
public:
  GLuint programId;

  Shader(const char * vertex_file_path, const char * fragment_file_path);

//  GLuint LoadShaders(const char * vertex_file_path,
//      const char * fragment_file_path);
  GLuint getProgramId() const;
  void use();
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setVec2(const std::string &name, const glm::vec2 &value) const;
  void setVec2(const std::string &name, float x, float y) const;
  void setVec3(const std::string &name, const glm::vec3 &value) const;
  void setVec3(const std::string &name, float x, float y, float z) const;
  void setVec4(const std::string &name, const glm::vec4 &value) const;
  void setVec4(const std::string &name, float x, float y, float z, float w);
  // ------------------------------------------------------------------------
  void setMat2(const std::string &name, const glm::mat2 &mat) const;
  // ------------------------------------------------------------------------
  void setMat3(const std::string &name, const glm::mat3 &mat) const;
  // ------------------------------------------------------------------------
  void setMat4(const std::string &name, const glm::mat4 &mat) const;

};


#endif /* SHADER_HPP_ */
