#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "abcgOpenGL.hpp"
#include "camera.hpp"
#include "model.hpp"


class ModelObj : public Model{
public:
  using Model::create;  // Exponha a versão base
  void create(GLuint program, std::string_view path, bool standardize = false);

protected:
  std::string_view m_path{};
  bool m_standardize{false};
  void loadObj();
};

#endif