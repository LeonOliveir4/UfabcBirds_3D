#include "bird.hpp"
#include <cmath>
#include <iostream>

#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/rotate_vector.hpp>

void Bird::create(GLuint program, GameData const &gamedata){
    destroy();

    m_program = program;
    //O passaro sempre inicia no centro da tela// 
    m_realPosition = glm::vec2(gamedata.m_maxCoord / 2.f ); // Comeca no centro da tela, a 5m de altura
    
    m_total_time = 0.0;
    m_scaleLoc = abcg::glGetUniformLocation(m_program, "scale");
    m_flapLoc = abcg::glGetUniformLocation(m_program, "flap");
    m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");

    m_scale = {0.125f};
    m_translation = glm::vec2(0);
    m_velocity = glm::vec2(0);

    std::array vertices{
      //bico
      glm::vec2{0.43f,0.f},glm::vec2{0.76f,0.f}, glm::vec2{0.44f,0.11f},
      glm::vec2{0.44f,0.11f},glm::vec2{0.8f,0.06f}, glm::vec2{0.76f,0.f},
      glm::vec2{0.8f,0.06f}, glm::vec2{0.9f,0.f}, glm::vec2{0.76f,0.f},
      glm::vec2{0.9f,0.f}, glm::vec2{0.96f,-0.15f}, glm::vec2{0.76f,0.f},
      glm::vec2{0.82f,-0.11f}, glm::vec2{0.96f,-0.15f}, glm::vec2{0.76f,0.f},
      glm::vec2{0.5f,-0.08f}, glm::vec2{0.82f,-0.11f}, glm::vec2{0.76f,0.f},
      glm::vec2{0.43f,0.f}, glm::vec2{0.76f,0.f}, glm::vec2{0.5f,-0.08f},
      glm::vec2{0.43f,0.f}, glm::vec2{0.43f,-0.063f}, glm::vec2{0.5f,-0.08f},
      //corpo
      glm::vec2{0.43f,-0.063f}, glm::vec2{0.44f,0.11f},glm::vec2{0.31f,0.01f},
      glm::vec2{0.31f,0.01f},  glm::vec2{0.08f,-0.07f}, glm::vec2{0.43f,-0.063f},
      glm::vec2{0.43f,-0.063f}, glm::vec2{-0.12f,-0.18f}, glm::vec2{0.08f,-0.07f},
      glm::vec2{0.44f,0.11f}, glm::vec2{0.34f,0.17f}, glm::vec2{0.31f,0.01f},
      glm::vec2{0.34f,0.17f},glm::vec2{0.31f,0.01f},  glm::vec2{0.08f,-0.07f},
      glm::vec2{0.34f,0.17f}, glm::vec2{-0.39f,0.01f},  glm::vec2{0.08f,-0.07f},
      glm::vec2{-0.39f,0.01f}, glm::vec2{-0.12f,-0.18f}, glm::vec2{0.08f,-0.07f},
      glm::vec2{-0.39f,0.01f}, glm::vec2{-0.12f,-0.18f}, glm::vec2{-0.29f,-0.17f},
      glm::vec2{-0.39f,0.01f},glm::vec2{-0.52f,-0.07f},glm::vec2{-0.29f,-0.17f},
      glm::vec2{-0.95f,-0.02f},glm::vec2{-0.39f,0.01f}, glm::vec2{-0.52f,-0.07f},
      glm::vec2{-0.52f,-0.07f}, glm::vec2{-0.85f,-0.15f}, glm::vec2{-0.95f,-0.02f},

      //ASAS
      glm::vec2{0.01f,0.01f}, glm::vec2{-0.08f,0.23f},glm::vec2{-0.39f,0.01f},
      glm::vec2{-0.51f,0.19f},glm::vec2{-0.39f,0.01f}, glm::vec2{-0.08f,0.23f},
      glm::vec2{-0.51f,0.19f},glm::vec2{-0.08f,0.23f},glm::vec2{-0.06,0.61f},
      glm::vec2{-0.51f,0.19f},glm::vec2{-0.52f,0.44f}, glm::vec2{-0.06,0.61f}


      // glm::vec2{0.43f,0.f}, //0 C
      // glm::vec2{0.76f,0.f}, // 1 D
      // glm::vec2{0.44f,0.11f}, //2 e
      // glm::vec2{0.8f,0.06f}, //3 F
      // glm::vec2{0.9f,0.f}, //4 G
      // glm::vec2{0.96f,-0.15f},  //5 H
      // glm::vec2{0.43f,-0.063f},  //6 I 
      // glm::vec2{0.5f,-0.08f}, //7 J
      // glm::vec2{0.82f,-0.11f}, //8 K
      // glm::vec2{-0.12f,-0.18f}, //9 L
      // glm::vec2{0.08f,-0.07f},  // 10 M
      // glm::vec2{0.31f,0.01f},  // 11 N
      // glm::vec2{0.34f,0.17f},  //12 0
      // glm::vec2{-0.39f,0.01f},  //13 P
      // glm::vec2{-0.29f,-0.17f}, //14 Q
      // glm::vec2{-0.52f,-0.07f},  //15 R
      // glm::vec2{-0.85f,-0.15f}, //16 S
      // glm::vec2{-0.95f,-0.02f},  //17 T
      // glm::vec2{0.01f,0.01f},  // 18 U
      // glm::vec2{-0.08f,0.23f},  //19 V
      // glm::vec2{-0.51f,0.19f},  //20 W
      // glm::vec2{-0.52f,0.44f},  //21  Z
      // glm::vec2{-0.06,0.61f} //22 Z2
    };  


    std::array<int, 69>const indices{
                          //bico
                          0, 1, 2, //cde
                          2, 3, 1, //efd
                          3, 4, 1, //fgd
                          4, 5, 1, //ghd
                          8, 5, 1, //khd
                          7, 8, 1, //jkd
                          0, 1, 7, //cdj
                          0, 6, 7,
                          //corpo
                          6, 2, 11,
                          11, 10, 6,
                          6, 9, 10,
                          2, 12, 11,
                          12, 11, 10,
                          12, 13, 10,
                          13, 9, 10,
                          13, 9, 14,
                          13, 15, 14,
                          17, 13, 15,
                          15, 16, 17,
                          //asa
                          18, 19, 13, // uvp
                          20, 13, 19, //wpv 
                          20, 19, 22, //wvz2
                          20, 21, 22 //cij

                          }; 

    // 0 AMARELO
    // 1 LARNAJA
    // 2 BRANCO
    // 3 PRETO
    std::array<int, 69> const colorIndices{
                          //BICO
                          0, 0, 0,
                          0, 0, 0,
                          3, 3, 3,
                          3, 3, 3,
                          1, 1, 1,
                          0, 0, 0,
                          0, 0, 0,
                          3, 3, 3,
                          //CORPO
                          2, 2, 2,
                          2, 2, 2,
                          2, 2, 2,
                          3, 3, 3,
                          3, 3, 3,
                          3, 3, 3,
                          3, 3, 3,
                          3, 3, 3,
                          3, 3, 3,
                          3, 3, 3,
                          3, 3, 3,
                          //ASA
                          4, 4, 4,
                          4, 4, 4,
                          4, 4, 4,
                          4, 4, 4,};

    abcg::glGenBuffers(1,&m_CBO);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
    abcg::glBufferData(GL_ARRAY_BUFFER,sizeof(colorIndices), colorIndices.data(), GL_STATIC_DRAW);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

    abcg::glGenBuffers(1, &m_VBO);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), 
                        GL_STATIC_DRAW);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

    abcg::glGenBuffers(1, &m_EBO);
    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
                     GL_STATIC_DRAW);
    abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLint positionAttribute{abcg::glGetAttribLocation(m_program, "inPosition")};
    GLint colorIndexAttribute{abcg::glGetAttribLocation(m_program, "inColorIndex")};

    abcg::glGenVertexArrays(1, &m_VAO);
    abcg::glBindVertexArray(m_VAO);
    abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
    abcg::glEnableVertexAttribArray(positionAttribute);

    abcg::glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
    abcg::glVertexAttribIPointer(colorIndexAttribute, 1, GL_INT, 0, (void*)0);
    abcg::glEnableVertexAttribArray(colorIndexAttribute);

    abcg::glBindVertexArray(0);

}

void Bird::paint(GameData const &gamedata) {
    if (gamedata.m_state != State::Playing)
      return;
    
    abcg::glUseProgram(m_program);

    abcg::glBindVertexArray(m_VAO);
    abcg::glUniform1i(m_flapLoc, m_flapWing);
    abcg::glUniform1f(m_scaleLoc, m_scale);
    abcg::glUniform2fv(m_translationLoc, 1,  &m_translation.x);
    
    //abcg::glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);
    abcg::glDrawArrays(GL_TRIANGLES, 0, 23 * 3);
    abcg::glBindVertexArray(0);
    abcg::glUseProgram(0);
}

void Bird::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteBuffers(1, &m_EBO);
  abcg::glDeleteBuffers(1, &m_CBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}

void Bird::update(GameData const &gamedata, float deltaTime){
    // Apply 
  if (gamedata.m_input[gsl::narrow<size_t>(Input::Up)] && 
      gamedata.m_state == State::Playing) {
    std::cout << "up" <<"\n";
    m_isFlapping = true;
  }
  //Do the phisics
  if (m_isFlapping){
    flap(deltaTime);
  }
  std::cout << "flapping: " << static_cast<int>(m_isFlapping) << "\n";

  if (m_realPosition.y > 0.0f) {
    m_velocity += (gamedata.m_gravity + m_sustein) * deltaTime;
    m_total_time += deltaTime;
  }
  if (m_realPosition.y < 0.0f) {
    m_realPosition.y = 0.0f;
    m_velocity = glm::vec2(0.f, 0.f);
  }

  m_realPosition += m_velocity * deltaTime;
  m_translation = normalizeCoord(m_realPosition, gamedata);
  // std::cout << "real position: " << m_realPosition.x << "," << m_realPosition.y << "\n";
  // std::cout << "normalized position: " << m_translation.x << "," << m_translation.y << "\n";
  // std::cout << "Velocity: " << m_velocity.x << "," << m_velocity.y << "\n";
  // std::cout << "Total time until bird fall to the ground:" << m_total_time << "\n"; 
}

glm::vec2 Bird::normalizeCoord(glm::vec2 coord, GameData const &gamedata ) {
  glm::vec2 normalizeFactor = gamedata.m_maxCoord / 2.f;
  return (coord - normalizeFactor) / normalizeFactor;
}

void Bird::flap(float deltaTime) {
  if (m_flapDuration <= m_flapTimeA){
    m_flapWing = true;
    m_velocity = m_flapPower;
  }
  if (m_flapDuration >= m_flapTimeB){
    m_flapWing = false;
  }
  if (m_flapDuration >= m_flapTimeB + 0.1f) {
    m_flapDuration = 0.0f;
    m_isFlapping = false;
  }
  m_flapDuration += deltaTime;

}

void Bird::setFlap() {
  if (!m_isFlapping) {  // Verifica se o pássaro já não está no meio de um flap
    m_flapWing = true;
    m_velocity = m_flapPower;
    m_isFlapping = true;  // Inicia o ciclo de batida de asas
    m_flapDuration = 0.0f; // Reinicia o tempo de duração do flap
  }
}