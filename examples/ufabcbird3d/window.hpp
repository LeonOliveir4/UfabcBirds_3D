#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"
#include <random>

#include "gamedata.hpp"
#include "ground.hpp"
#include "modelObj.hpp"
#include "model.hpp"
#include "bird.hpp"
#include "fruta.hpp"
#include "camera.hpp"
#include "birdDescriptions.hpp"

class Window : public abcg::OpenGLWindow {
protected:
    void onEvent(SDL_Event const &event) override;
    void onCreate() override;
    void onUpdate() override;
    void onPaint() override;
    void onPaintUI() override;
    void onResize(glm::ivec2 const &size) override;
    void onDestroy() override;
    void createFrutas();
    void checkCollisions();
public:
    GameData m_gameData; 

private:
    glm::ivec2 m_viewportSize{};
    Bird m_bird;
    Ground m_ground;
    Fruta fruta1;
    Fruta fruta2;
    Fruta fruta3;
    Fruta fruta4;
    Fruta fruta5;
    Fruta fruta6;
    Fruta fruta7;
    Fruta fruta8;
    Fruta fruta9;
    Fruta fruta10;
    Fruta fruta11;
    Fruta fruta12;

    Camera m_camera;
    GLuint m_program{};

    void showBirdInfo(const std::string& birdName);

    bool m_showPopup{true};
    float m_popupTimeElapsed{0.0f};
    std::string m_popupText;
    std::string m_displayedText;
    size_t m_currentCharIndex{0};
    float m_textDisplaySpeed{0.05f};

    void restartGame();
    std::default_random_engine m_randomEngine;
};

#endif