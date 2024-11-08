#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"

#include "bird.hpp"
#include "pipe.hpp"
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
    void checkCollisions();

public:
    GameData m_gameData; 
    
private:
    glm::ivec2 m_viewportSize{};
    GLuint m_birdProgram{};
    GLuint m_bgProgram{};
    GLuint m_pipeProgram{};

    Bird m_bird;
    Pipes m_pipes;
    Bg m_bg;
    
    abcg::Timer m_restartTimer;

    bool m_showPopup{true};
    float m_popupTimeElapsed{0.0f};
    std::string m_popupText;
    std::string m_displayedText;
    size_t m_currentCharIndex{0};
    float m_textDisplaySpeed{0.05f};

    void restart();
};


#endif