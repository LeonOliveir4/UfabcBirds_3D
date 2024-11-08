#include "bg.hpp"
#include <iostream>

void Bg::create(GLuint program, GameData const &gameData){
    destroy();
    std::cout << "estado do jogo antes do bg: " << static_cast<char>(gameData.m_state) << "\n";
    m_program = program;
    m_time = 0.0f;
    m_timeLoc = abcg::glGetUniformLocation(m_program, "time");
    m_resolutionLoc = abcg::glGetUniformLocation(m_program, "resolution");
    std::array vertices{
        glm::vec2{-1.0f,-1.0f},glm::vec2{-1.0f,1.0f},glm::vec2{1.0f,1.0f},
        glm::vec2{-1.0f,-1.0f},glm::vec2{1.0f,-1.0f},glm::vec2{1.0f,1.0f},
    };

    GLint positionAttribute{abcg::glGetAttribLocation(m_program,"inPosition")};
    abcg::glGenVertexArrays(1, &m_VAO);
    abcg::glBindVertexArray(m_VAO);
    abcg::glGenBuffers(1,&m_VBO);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    abcg::glEnableVertexAttribArray(positionAttribute);
    abcg::glBindVertexArray(0);
}

void Bg::paint(){
    abcg::glUseProgram(m_program);
    
    abcg::glBindVertexArray(m_VAO);
    abcg::glUniform1f(m_timeLoc, m_time);
    abcg::glUniform2f(m_resolutionLoc, m_resolution.x, m_resolution.y);

    abcg::glDrawArrays(GL_TRIANGLES, 0, 6);
    abcg::glBindVertexArray(0);
    abcg::glUseProgram(0);

}
void Bg::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}

void Bg::update(float deltaTime){
    m_time += deltaTime;
}

