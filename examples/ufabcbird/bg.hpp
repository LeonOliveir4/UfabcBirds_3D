#ifndef BG_HPP_
#define BG_HPP_

#include "abcgOpenGL.hpp"
#include "gamedata.hpp"

class Bg {
public:
    void create(GLuint program, GameData const &gamedata);
    void paint();
    void destroy();
    void update(float deltaTime);

    float m_time;
    glm::vec2 m_resolution{800,800};

private:
    GLuint m_program{};
    GLuint m_timeLoc{};
    GLuint m_resolutionLoc{};

    GLuint m_VAO{};
    GLuint m_VBO{};
};

#endif