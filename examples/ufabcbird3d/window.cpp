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
    if (event.key.keysym.sym == SDLK_q)
      m_truckSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_e)
      m_truckSpeed = 1.0f;
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
    if (event.key.keysym.sym == SDLK_q && m_truckSpeed < 0)
      m_truckSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_e && m_truckSpeed > 0)
      m_truckSpeed = 0.0f;
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
    m_model.setupVAO(m_program);
    m_ground.create(m_program);
}

void Window::onPaint() {
    abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

    abcg::glUseProgram(m_program);

    auto const viewMatrixLoc{abcg::glGetUniformLocation(m_program, "viewMatrix")};
    auto const projMatrixLoc{abcg::glGetUniformLocation(m_program, "projMatrix")};
    auto const modelMatrixLoc{
        abcg::glGetUniformLocation(m_program, "modelMatrix")};
    auto const colorLoc{abcg::glGetUniformLocation(m_program, "color")};

    abcg::glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE,
                             &m_camera.getViewMatrix()[0][0]);
    abcg::glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE,
                           &m_camera.getProjMatrix()[0][0]);

    abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_model.getModelMatrix()[0][0]);
    
    

    m_model.render();
    m_ground.render();
    abcg::glUseProgram(0);

}

void Window::onPaintUI() {
    abcg::OpenGLWindow::onPaintUI();
    {
        auto const widgetSize{ImVec2(218, 62)};
        ImGui::SetNextWindowPos(ImVec2(m_viewportSize.x - widgetSize.x - 5, 5));
        ImGui::SetNextWindowSize(widgetSize);
        ImGui::Begin("Widget window", nullptr, ImGuiWindowFlags_NoDecoration);
        {
             ImGui::PushItemWidth(120);
             ImGui::PushItemWidth(120);
             static std::size_t currentIndex{};
             auto fov  = m_camera.m_fov;
             ImGui::SliderFloat("FOV", &m_camera.m_fov, 10.f, 180.f); 
             if (fov != m_camera.m_fov) {
                m_camera.computeProjectionMatrix(m_viewportSize);
             }
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
}

void Window::onResize(glm::ivec2 const &size) {
    m_viewportSize = size;
    m_camera.computeProjectionMatrix(size);
}



void Window::onDestroy() {
    m_ground.destroy();
    m_model.destroy();
}