#include "ground.hpp"

void Ground::createVertex() {

  m_vertices = {
                Vertex{.position = glm::vec3(-3.0f, 0.0f, +3.0f)},
                Vertex{.position = glm::vec3(-3.0f, 0.0f, -3.0f)},
                Vertex{.position = glm::vec3(+3.0f, 0.0f, -3.0f)},
                Vertex{.position = glm::vec3(+3.0f, 0.0f, +3.0f)}};
  m_indices = {
                0, 1, 2,
                0, 2, 3
  };

}

void Ground::render(Camera camera) {
  abcg::glUseProgram(m_program);
  abcg::glBindVertexArray(m_VAO);
  auto const viewMatrixLoc{abcg::glGetUniformLocation(m_program, "viewMatrix")};
  auto const projMatrixLoc{abcg::glGetUniformLocation(m_program, "projMatrix")};
  auto const modelMatrixLoc{abcg::glGetUniformLocation(m_program, "modelMatrix")};
  auto const colorLoc{abcg::glGetUniformLocation(m_program, "color")};
  // Draw a grid of 2N+1 x 2N+1 tiles on the xz plane, centered around the
  // origin
 auto const N{10};
   for (auto const z : iter::range(-N, N + 1)) {
     for (auto const x : iter::range(-N, N + 1)) {
      // Set model matrix as a translation matrix
      // glm::mat4 model{1.0f};
      setPosition(glm::vec3(x*6.0f, 0.0f, z*6.0f));
      abcg::glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &camera.getViewMatrix()[0][0]);
      abcg::glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &camera.getProjMatrix()[0][0]);
      abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);

      // Set color (checkerboard pattern)
      auto const gray{(z + x) % 2 == 0 ? 1.0f : 2.0f};
      abcg::glUniform4f(colorLoc, 0.2, gray *0.4, 0.2, 1.0f);

      abcg::glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
     }
  }

  abcg::glBindVertexArray(0);
  abcg::glUseProgram(0);
}
