#include "model.hpp"


void Model::create(GLuint program) {
    std::array vertices{//x y z
        glm::vec3{-0.5f, -0.5f, -0.5f},
        glm::vec3{-0.5f, 0.5f, -0.5f},
        glm::vec3{-0.5f, 0.5f, 0.5f},
        glm::vec3{-0.5f, -0.5f, 0.5f},
        glm::vec3{0.5f, -0.5f, -0.5f},
        glm::vec3{0.5f, 0.5f, -0.5f},
        glm::vec3{0.5f, 0.5f, 0.5f},
        glm::vec3{0.5f, -0.5f, 0.5f}
    };

    std::array indices{
        1, 2, 3,//
        1, 3, 4,
        1, 2, 5,//
        2, 5, 6,
        1, 4, 5,//
        4, 5, 6,
        3, 4, 8,//
        3, 4, 7,
        5, 6, 7,//
        6, 7, 8
    };
    abcg::glGenBuffers(1, &m_VBO);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    abcg::glBufferData(GL_ARRAY_BUFFER,
                        sizeof(vertices.at(0)) * vertices.size(),
                        vertices.data(), GL_STATIC_DRAW);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

    abcg::glGenBuffers(1, &m_EBO);
    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                        sizeof(indices.at(0)) * indices.size(),
                        indices.data(), GL_STATIC_DRAW);
    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    abcg::glGenVertexArrays(1, &m_VAO);
    abcg::glBindVertexArray(m_VAO);
    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    auto const positionAttribute{abcg::glGetAttribLocation(program, "inPosition")};
    abcg::glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE,
                                sizeof(glm::vec3), nullptr);
    abcg::glEnableVertexAttribArray(positionAttribute);

        // End of binding
    abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
    abcg::glBindVertexArray(0);
}

void Model::render(){
    abcg::glUseProgram(m_program);
    abcg::glBindVertexArray(m_VAO);
    auto const colorLoc{abcg::glGetUniformLocation(m_program, "color")};
    abcg::glUniform4f(colorLoc, m_color.r,m_color.g, m_color.b, m_color.a);
    abcg::glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, nullptr);
    abcg::glBindVertexArray(0);
}

void Model::destroy(){
  abcg::glDeleteBuffers(1, &m_EBO);
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}