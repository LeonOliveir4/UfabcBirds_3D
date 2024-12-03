#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "abcgOpenGL.hpp"

struct Vertex {
  glm::vec3 position{};

  friend bool operator==(Vertex const &, Vertex const &) = default;
};

class ModelObj {
public:
  void loadObj(std::string_view path, bool standardize = true);
  void render() const;
  void setupVAO(GLuint program);
  void destroy() const;

  glm::mat4 const &getModelMatrix() const {return m_modelMatrix;}

private:

  //Buffers do opengl
  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};
  //buffer de cor
  glm::vec4 m_color{0.f, 0.f, 0.5f, 1.0f};
  //Shaders
  GLuint m_program;
  //matriz do modelo
  glm::mat4 m_modelMatrix{1.0f};
  //Vertex e indices lidos pelo 
  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;
  
  //modificadores
  glm::vec3 m_position{0.f,0.f,0.f};
  float m_scale{1.f};
  glm::vec3 m_axis{1.0f};
  glm::mat4 m_matrixRotation{1.0f};

  void createBuffers();
  void standardize();
};

#endif