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

private:
  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};

  glm::vec4 m_color{0.f, 0.f, 0.5f, 1.0f};
  GLuint m_program;

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

  void createBuffers();
  void standardize();
};

#endif