#ifndef GROUND_HPP_
#define GROUND_HPP_

#include "abcgOpenGL.hpp"
#include "camera.hpp"
#include "model.hpp"

class Ground : public Model {
public:
  void createVertex() override;
  void render(Camera camera) override;
};

#endif