#ifndef PIPE_HPP_
#define PIPE_HPP_

#include <list>
#include <random>


#include "abcgOpenGL.hpp"
#include "gamedata.hpp"

class Pipes {
public:
    struct Pipe {
        GLuint m_VAO{};
        GLuint m_VBO{};
        float m_height{};
        glm::vec2 m_p1{};
        glm::vec2 m_p2{};
        glm::vec2 m_translation{};
        glm::vec2 m_velocity{};
        glm::vec4 m_color{};
    };

    void create(GLuint program, GameData const &gamedata);
    void paint();
    void destroy();
    void update(GameData const &gamedatam, float deltaTime);

    float  m_borderWidth{}; // LAGURA E ALTURA DA borda do cano 
    float  m_borderHeight{}; // ALTURA DA borda do cano 
    glm::vec2 m_gap{}; // Distancia entre o cano de baixo e cima
    glm::vec4 m_color{};
    float m_velocityX;
    
    float m_birthTime{};
    float m_birthRate{6.0f};
    std::list<Pipe> m_pipes;
    Pipe createPipe();

    
private:
    GLuint m_program{};
    GLuint m_translationLoc{};
    GLuint m_colorLoc{};
    std::default_random_engine m_randomEngine;
    std::uniform_real_distribution<float> m_randomDist{-3.0f, 3.0f};
};

#endif