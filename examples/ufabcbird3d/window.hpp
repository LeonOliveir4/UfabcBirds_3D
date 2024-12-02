#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"
#include "model.hpp"
#include "camera.hpp"

class Window : public abcg::OpenGLWindow {
protected:
    void onEvent(SDL_Event const &event) override;
    void onCreate() override;
    void onUpdate() override;
    void onPaint() override;
    void onResize(glm::ivec2 const &size) override;
    void onDestroy() override;

private:
    glm::ivec2 m_viewportSize{};

    Model m_model;
    Camera m_camera;
    GLuint m_program{};
    float m_dollySpeed{};
    float m_truckSpeed{};
    float m_panSpeed{};
};

#endif