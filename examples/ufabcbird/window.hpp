#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"
#include "gamedata.hpp"

#include "bird.hpp"
#include "bg.hpp"
#include "gamedata.hpp"

class Window : public abcg::OpenGLWindow {
protected:
    void onEvent(SDL_Event const &event)override;
    void onCreate()override;
    void onUpdate()override;
    void onPaint()override;
    void onPaintUI()override;
    void onResize(glm::ivec2 const &size)override;
    void onDestroy()override;

public:
    GameData m_gameData; 
    
private:
    glm::ivec2 m_viewportSize{};
    GLuint m_birdProgram{};
    GLuint m_bgProgram{};

    Bird m_bird;
    Bg m_bg;
    
    abcg::Timer m_restartTimer;

    void restart();
    void checkCollisions();
};


#endif