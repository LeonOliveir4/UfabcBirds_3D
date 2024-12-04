#include "window.hpp"
#include <iostream>

//Mapeamento de controle da camera
void Window::onEvent(SDL_Event const &event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
      m_dollySpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
      m_dollySpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_panSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_panSpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_y)
      m_tiltSpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_h)
      m_tiltSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_q)
      m_truckSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_e)
      m_truckSpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_o)
      m_elevationSpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_l)
      m_elevationSpeed = -1.0f;
  }
  if (event.type == SDL_KEYUP) {
    if ((event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) &&
        m_dollySpeed > 0)
      m_dollySpeed = 0.0f;
    if ((event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) &&
        m_dollySpeed < 0)
      m_dollySpeed = 0.0f;
    if ((event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) &&
        m_panSpeed < 0)
      m_panSpeed = 0.0f;
    if ((event.key.keysym.sym == SDLK_RIGHT ||
         event.key.keysym.sym == SDLK_d) &&
        m_panSpeed > 0)
      m_panSpeed = 0.0f;
        if (event.key.keysym.sym == SDLK_y)
      m_tiltSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_h)
      m_tiltSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_q && m_truckSpeed < 0)
      m_truckSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_e && m_truckSpeed > 0)
      m_truckSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_o)
      m_elevationSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_l)
      m_elevationSpeed = 0.0f;
  }
}


void Window::onCreate(){
    auto const assetsPath{abcg::Application::getAssetsPath()};

    abcg::glClearColor(0.537f, 0.817f, 0.920f, 1.);
    abcg::glEnable(GL_DEPTH_TEST);

    m_program = abcg::createOpenGLProgram({{.source = assetsPath + "model.vert",
                                            .stage = abcg::ShaderStage::Vertex},
                                            {.source = assetsPath + "model.frag",
                                            .stage = abcg::ShaderStage::Fragment}});
    m_model.loadObj(assetsPath + "bird_test.obj");
    m_model_test.create(m_program);
    m_model.setupVAO(m_program);
    m_ground.create(m_program);
}

void Window::onPaint() {
    abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

    m_model_test.render(m_camera);
  
    m_ground.render();
    abcg::glUseProgram(0); 

}

void Window::onPaintUI() {
    abcg::OpenGLWindow::onPaintUI();
    {
        auto const widgetSize{ImVec2(218, 200)};
        ImGui::SetNextWindowPos(ImVec2(m_viewportSize.x - widgetSize.x - 5, 5));
        ImGui::SetNextWindowSize(widgetSize);
        ImGui::Begin("Widget window", nullptr, ImGuiWindowFlags_NoDecoration);
        {
             ImGui::PushItemWidth(120);
             auto fov  = m_camera.m_fov;
             auto position = m_model_test.getPosition();
             auto scale = m_model_test.getScale();
             static float rotationX{0.0f}; 
             static float rotationY{0.0f}; 
             static float rotationZ{0.0f}; 
             ImGui::SliderFloat("FOV", &m_camera.m_fov, 10.f, 180.f); 
             ImGui::SliderFloat("X_position", &position.x, -10.0f, 10.f);
             ImGui::SliderFloat("Y_position", &position.y, -10.0f, 10.f);
             ImGui::SliderFloat("Z_position", &position.z, -10.0f, 10.f); 
             ImGui::SliderFloat("X_rotation", &rotationX, -180.0f, 180.f);
             ImGui::SliderFloat("Y_rotation", &rotationY, -180.0f, 180.f);
             ImGui::SliderFloat("Z_rotation", &rotationZ, -180.0f, 180.f); 
             ImGui::SliderFloat("scale", &scale, 0.0f, 5.f); 

            m_model_test.setPosition(position);
            auto const radX = glm::radians(rotationX);
            auto const radY = glm::radians(rotationY);
            auto const radZ = glm::radians(rotationZ);

            glm::mat4 rotationMatrixX = glm::rotate(glm::mat4(1.0f), radX, glm::vec3(1.0f, 0.0f, 0.0f));
            glm::mat4 rotationMatrixY = glm::rotate(glm::mat4(1.0f), radY, glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 rotationMatrixZ = glm::rotate(glm::mat4(1.0f), radZ, glm::vec3(0.0f, 0.0f, 1.0f));

            glm::mat4 rotationMatrix = rotationMatrixZ * rotationMatrixY * rotationMatrixX;
            m_model_test.setPosition(position);
            m_camera.computeProjectionMatrix(m_viewportSize);
            m_model_test.setMatrixRotation(rotationMatrix);
            m_model_test.setScale(scale);
             
        }
        ImGui::End();
    }
}





void Window::onUpdate() {
  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};

  // Update LookAt camera
  m_camera.dolly(m_dollySpeed * deltaTime);
  m_camera.truck(m_truckSpeed * deltaTime);
  m_camera.pan(m_panSpeed * deltaTime);
  m_camera.tilt(m_tiltSpeed * deltaTime);
  m_camera.elevation(m_elevationSpeed * deltaTime);
}

void Window::onResize(glm::ivec2 const &size) {
    m_viewportSize = size;
    m_camera.computeProjectionMatrix(size);
}

void Window::onDestroy() {
    m_model_test.destroy();
    m_ground.destroy();
    m_model.destroy();
}