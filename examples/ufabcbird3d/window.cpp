#include "window.hpp"
#include <iostream>

//Mapeamento de controle da camera
void Window::onEvent(SDL_Event const &event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::PitchPos));
    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::PitchNeg));
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::YawPos));
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::YawNeg));
    if (event.key.keysym.sym == SDLK_q)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::RollPos));
    if (event.key.keysym.sym == SDLK_e)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::RollNeg));
  }
  if (event.type == SDL_KEYUP) {
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) 
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::PitchPos));
    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::PitchNeg));
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::YawPos));
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::YawNeg));
    if (event.key.keysym.sym == SDLK_q)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::RollPos));
    if (event.key.keysym.sym == SDLK_e)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::RollNeg));
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

    m_camera.setFollow(true);
    m_bird.create(m_program, assetsPath + "tucano/", m_gameData);
    m_ground.create(m_program);
}

void Window::onPaint() {
    abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);


    m_bird.render(m_camera);
    m_ground.render(m_camera);
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
            auto position = m_bird.getPosition();
            auto scale = m_bird.getScale();

            static float cameraUp = m_camera.getUpDistance();
            static float cameraBack = m_camera.getBackwardDistance();
            ImGui::SliderFloat("FOV", &m_camera.m_fov, 10.f, 180.f); 
            ImGui::SliderFloat("X_position", &position.x, -10.0f, 10.f);
            ImGui::SliderFloat("Y_position", &position.y, -10.0f, 10.f);
            ImGui::SliderFloat("Z_position", &position.z, -10.0f, 10.f); 

            ImGui::SliderFloat("Camera_up", &cameraUp, -10.0f, 10.f);
            ImGui::SliderFloat("Camera_back", &cameraBack, -10.0f, 10.f);

            m_camera.setUp(cameraUp);
            m_camera.setBackward(cameraBack); 


            m_camera.computeProjectionMatrix(m_viewportSize);
            //m_bird.setMatrixRotation(rotationMatrix);
            m_bird.setScale(scale);
             
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

  m_bird.update(deltaTime, m_gameData);
  m_camera.update(m_bird.getPosition(),m_bird.getFoward(), m_bird.getUpVector());
}

void Window::onResize(glm::ivec2 const &size) {
    m_viewportSize = size;
    m_camera.computeProjectionMatrix(size);
}

void Window::onDestroy() {
   m_ground.destroy();
   m_bird.destroy();
}