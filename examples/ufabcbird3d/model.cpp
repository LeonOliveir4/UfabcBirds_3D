//Classe padrao para qualquer opbjeto 3d que pode ser renderizado
#include "model.hpp"
#include <iostream>


template <> struct std::hash<Vertex> {
  size_t operator()(Vertex const &vertex) const noexcept {
    auto const h1{std::hash<glm::vec3>()(vertex.position)};
    return h1;
  }
};

void Model::createVertex() {
    m_vertices.clear();
    m_indices.clear();
    m_vertices = {//x y z
        Vertex{.position = glm::vec3{-0.5f, -0.5f, -0.5f}},
        Vertex{.position =glm::vec3{-0.5f, 0.5f, -0.5f}},
        Vertex{.position =glm::vec3{-0.5f, 0.5f, 0.5f}},
        Vertex{.position =glm::vec3{-0.5f, -0.5f, 0.5f}},
        Vertex{.position =glm::vec3{0.5f, -0.5f, -0.5f}},
        Vertex{.position =glm::vec3{0.5f, 0.5f, -0.5f}},
        Vertex{.position =glm::vec3{0.5f, 0.5f, 0.5f}},
        Vertex{.position =glm::vec3{0.5f, -0.5f, 0.5f}}
    };

    m_indices = {
        0, 1, 2,//
        0, 2, 3,
        0, 1, 4,//
        1, 4, 5,
        0, 3, 4,//
        3, 4, 7,
        2, 3, 7,//
        2, 6, 7,
        4, 5, 6,//
        4, 6, 7,
        1, 2, 5,//
        2, 5, 6
    };
}

void Model::createBuffers() {
    abcg::glGenBuffers(1, &m_VBO);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    abcg::glBufferData(GL_ARRAY_BUFFER,
                        sizeof(m_vertices.at(0)) * m_vertices.size(),
                        m_vertices.data(), GL_STATIC_DRAW);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

    abcg::glGenBuffers(1, &m_EBO);
    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                        sizeof(m_indices.at(0)) * m_indices.size(),
                        m_indices.data(), GL_STATIC_DRAW);
    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    abcg::glGenVertexArrays(1, &m_VAO);
    abcg::glBindVertexArray(m_VAO);
    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    auto const positionAttribute{abcg::glGetAttribLocation(m_program, "inPosition")};
    abcg::glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE,
                                sizeof(glm::vec3), nullptr);
    abcg::glEnableVertexAttribArray(positionAttribute);

        // End of binding
    abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
    abcg::glBindVertexArray(0);
}

void Model::create(GLuint program) {
    m_program = program;
    createVertex();
    createBuffers();
}

void Model::render(const Camera camera){//const float *viewMatrix, const float *projMatrix){
    abcg::glUseProgram(m_program);

    auto const viewMatrixLoc{abcg::glGetUniformLocation(m_program, "viewMatrix")};
    auto const projMatrixLoc{abcg::glGetUniformLocation(m_program, "projMatrix")};
    auto const modelMatrixLoc{abcg::glGetUniformLocation(m_program, "modelMatrix")};
    auto const colorLoc{abcg::glGetUniformLocation(m_program, "color")};

    abcg::glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &camera.getViewMatrix()[0][0]);
    abcg::glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &camera.getProjMatrix()[0][0]);
    abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);
    abcg::glUniform4f(colorLoc, m_color.r,m_color.g, m_color.b, m_color.a);

    abcg::glBindVertexArray(m_VAO);
    abcg::glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    abcg::glBindVertexArray(0);
    abcg::glUseProgram(0);
}

void Model::standardize() {
  // Center to origin and normalize largest bound to [-1, 1]

  // Get bounds
  glm::vec3 max(std::numeric_limits<float>::lowest());
  glm::vec3 min(std::numeric_limits<float>::max());
  for (auto const &vertex : m_vertices) {
    max = glm::max(max, vertex.position);
    min = glm::min(min, vertex.position);
  }

  // Center and scale
  //auto const center{(min + max) / 2.0f};
  auto const scaling{2.0f / glm::length(max - min)};
  for (auto &vertex : m_vertices) {
    vertex.position = (vertex.position) * scaling;
  }
}

void Model::destroy(){
  abcg::glDeleteBuffers(1, &m_EBO);
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}