#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"
#include "ground.hpp"
#include "modelObj.hpp"
#include "model.hpp"
#include "camera.hpp"

class Window : public abcg::OpenGLWindow {
protected:
    void onEvent(SDL_Event const &event) override;
    void onCreate() override;
    void onUpdate() override;
    void onPaint() override;
    void onPaintUI() override;
    void onResize(glm::ivec2 const &size) override;
    void onDestroy() override;

private:
    glm::ivec2 m_viewportSize{};
    ModelObj m_model;
    Model m_model_test;
    Ground m_ground;
    Camera m_camera;
    GLuint m_program{};
    float m_dollySpeed{};
    float m_truckSpeed{};
    float m_panSpeed{};
    float m_tiltSpeed{};
    float m_elevationSpeed{};
};

#endif