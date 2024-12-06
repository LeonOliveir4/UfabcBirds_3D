#ifndef GROUND_HPP_
#define GROUND_HPP_

#include "abcgOpenGL.hpp"
#include "camera.hpp"
#include "model.hpp"

class Ground : public Model {
public:
  void createVertex() override;
  void render(Camera camera) override;

  float getLeftLimit() const { return -25.0f; } // Limite esquerdo
  float getRightLimit() const { return 25.0f; } // Limite direito
  float getBackLimit() const { return -25.0f; } // Limite traseiro
  float getFrontLimit() const { return 25.0f; }
};

#endif