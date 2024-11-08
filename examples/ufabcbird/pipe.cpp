#include "pipe.hpp"
#include <iostream>
#include <random>

#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/rotate_vector.hpp>

void Pipes::create(GLuint program, GameData const &gamedata) {
    destroy();
    m_birthTime = 0.f;
    m_program = program;
    m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
    m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");
    m_color = glm::vec4(0.0, 0.68,0.07,1.0);
    m_gap = glm::vec2{0., 0.5};
    m_borderWidth = 0.4;
    m_borderHeight = 0.1;
    m_velocityX = gamedata.m_velocityX;

    Pipes::Pipe pipe_exemplo = createPipe();
    m_pipes.clear();
    m_pipes.push_back(pipe_exemplo);
};

Pipes::Pipe Pipes::createPipe() {
    Pipe pipe;
    auto &re{m_randomEngine}; 
    std::uniform_real_distribution<float> randomHeight(-0.7, 0.7);
    pipe.m_height = (randomHeight(re));
    pipe.m_color = glm::vec4(0.0, 0.68,0.07,1.0);
    pipe.m_translation = glm::vec2{1.4, 0.}; // imprime fora da tela
    pipe.m_velocity = glm::vec2{0., m_velocityX};
    pipe.m_p1 = glm::vec2{-0.2, pipe.m_height};
    pipe.m_p2 = pipe.m_p1 + m_gap;



    //        |       |
    //        |       |
    //       _|       |_
    //    p2|___________|
    //                        ^  gap
    //       ___________      v
    //    p1|_         _|     ^
    //        |       |       |   h
    //        |       |       |
    //        |       |       v

    std::array vertices {
                        //PIPE BAIXO
                        //borda
                        pipe.m_p1, glm::vec2{pipe.m_p1.x + m_borderWidth, pipe.m_p1.y}, glm::vec2{pipe.m_p1.x + m_borderWidth, pipe.m_p1.y - m_borderHeight},
                        pipe.m_p1, glm::vec2{pipe.m_p1.x, pipe.m_p1.y- m_borderHeight}, glm::vec2{pipe.m_p1.x + m_borderWidth, pipe.m_p1.y - m_borderHeight},
                        //corpo
                        glm::vec2{pipe.m_p1.x + 0.05,pipe.m_p1.y}, glm::vec2{pipe.m_p1.x + 0.05, -1000.0}, glm::vec2{pipe.m_p1.x + m_borderWidth - 0.05, pipe.m_p1.y -1000.0},
                        glm::vec2{pipe.m_p1.x + 0.05,pipe.m_p1.y}, glm::vec2{pipe.m_p1.x + m_borderWidth - 0.05, pipe.m_p1.y}, glm::vec2{pipe.m_p1.x + m_borderWidth - 0.05, pipe.m_p1.y -1000.0},

                        //PIPE ALTO
                        //BORDA
                        pipe.m_p2, glm::vec2{pipe.m_p2.x + m_borderWidth, pipe.m_p2.y}, glm::vec2{pipe.m_p2.x + m_borderWidth, pipe.m_p2.y + m_borderHeight},
                        pipe.m_p2, glm::vec2{pipe.m_p2.x, pipe.m_p2.y + m_borderHeight}, glm::vec2{pipe.m_p2.x + m_borderWidth, pipe.m_p2.y + m_borderHeight},
                        //corpo
                        glm::vec2{pipe.m_p2.x + 0.05,pipe.m_p2.y}, glm::vec2{pipe.m_p2.x + 0.05, +1000.0}, glm::vec2{pipe.m_p2.x + m_borderWidth - 0.05, pipe.m_p2.y + 1000.0},
                        glm::vec2{pipe.m_p2.x + 0.05,pipe.m_p2.y}, glm::vec2{pipe.m_p2.x + m_borderWidth - 0.05, pipe.m_p2.y}, glm::vec2{pipe.m_p2.x + m_borderWidth - 0.05, pipe.m_p2.y + 1000.0},
    };

    abcg::glGenBuffers(1, &pipe.m_VBO);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, pipe.m_VBO);
    abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    
    GLint positionAttribute(abcg::glGetAttribLocation(m_program, "inPosition"));

    //VAO
    abcg::glGenVertexArrays(1, &pipe.m_VAO);
    abcg::glBindVertexArray(pipe.m_VAO);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, pipe.m_VBO);
    abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    abcg::glEnableVertexAttribArray(positionAttribute);
    abcg::glBindVertexArray(0);

    return pipe;
}

void Pipes::paint( ) {
  abcg::glUseProgram(m_program);
  for (auto const &pipe : m_pipes) {
    abcg::glBindVertexArray(pipe.m_VAO);
    abcg::glUniform2fv(m_translationLoc, 1, &pipe.m_translation.x);
    abcg::glUniform4fv(m_colorLoc, 1, &pipe.m_color.r);

    abcg::glDrawArrays(GL_TRIANGLES, 0, 8 * 3);
    abcg::glBindVertexArray(0);
  }
  abcg::glUseProgram(0);
} 

void Pipes::update(GameData const &gamedata, float deltaTime){
  m_velocityX = gamedata.m_velocityX;
  //atualiza a poosicao dos 
  m_birthTime += deltaTime;
  if (m_birthTime > m_birthRate) {
    m_pipes.push_back(createPipe());
    m_birthTime = 0.0;
  }

  for(auto &pipe : m_pipes){
    pipe.m_translation += glm::vec2(gamedata.m_velocityX, 0.0) * deltaTime;
  };
  //Remove os pipes dentro da tela
  m_pipes.remove_if([](auto const &a) { return a.m_translation.x < -1.5f; });
  
}

void Pipes::destroy() {
  for( auto &pipe: m_pipes){
    abcg::glDeleteBuffers(1, &pipe.m_VBO);
    abcg::glDeleteVertexArrays(1, &pipe.m_VAO);
  }
}