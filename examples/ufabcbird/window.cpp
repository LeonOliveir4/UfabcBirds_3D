#include "window.hpp"
#include <iostream>

void Window::onCreate() {
    auto const assetsPath{abcg::Application::getAssetsPath()};
    std::cout << "Initialize shaders \n";
    std::cout << "estado do jogo: " << static_cast<char>(m_gameData.m_state);
    m_birdProgram =
      abcg::createOpenGLProgram({{.source = assetsPath + "bird.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "bird.frag",
                                  .stage = abcg::ShaderStage::Fragment}});
    m_bgProgram =
      abcg::createOpenGLProgram({{.source = assetsPath + "bg.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "bg.frag",
                                  .stage = abcg::ShaderStage::Fragment}});
    std::cout << "Shader ok \n";
    abcg::glClearColor(0.5f, 0.5f, 0.5f, 1);
#if !defined(__EMSCRIPTEN__)
  abcg::glEnable(GL_PROGRAM_POINT_SIZE);
#endif
    restart();
}

void Window::restart() {
    m_gameData.m_state = State::Playing;
    std::cout << "estado do jogo restart: " << static_cast<int>(m_gameData.m_state) << "\n";
    m_bird.create(m_birdProgram, m_gameData);
    m_bg.create(m_bgProgram, m_gameData);
}

void Window::onEvent(SDL_Event const &event) {
  // Keyboard events
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::Up));
  }
  if (event.type == SDL_KEYUP) {
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Up));
  }
}

void Window::onUpdate() {
  if (m_gameData.m_state != State::Playing &&
      m_restartTimer.elapsed() > 3) {
    restart();
    return;
  }

  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};
  m_bg.update(m_gameData, deltaTime);
  m_bird.update(m_gameData, deltaTime);

  if (m_gameData.m_state == State::Playing) {
    checkCollisions();
  }
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT);
  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);
  m_bg.paint();
  m_bird.paint(m_gameData);
  
}

void Window::onPaintUI() {
    abcg::OpenGLWindow::onPaintUI();
    ImU32 redColor = IM_COL32(255, 0, 0, 125); // RGBA
    // Desenha um retângulo que cobre toda a janela
    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    draw_list->AddRectFilled(ImVec2(0, 0), ImVec2(m_viewportSize.x, 50), redColor);
    {
        ImGui::SetNextWindowPos(ImVec2(0,0));
        ImGui::SetNextWindowSize(ImVec2(m_viewportSize.x,50));
        ImGuiWindowFlags const flags{ImGuiWindowFlags_NoBackground |
                                    ImGuiWindowFlags_NoTitleBar };//| ImGuiWindowFlags_NoInputs};
        ImGui::Begin(" ", nullptr, flags);
        ImGui::PushItemWidth(50);
        ImGui::SetCursorPos(ImVec2(0, 0));
        ImGui::PushItemWidth(100);
        ImGui::SliderFloat("Sustein", &m_bird.m_sustein.y, -10.0f, 10.0f);
        ImGui::SetCursorPos(ImVec2(100, 0));
        ImGui::SliderFloat("Flap time A", &m_bird.m_flapTimeA, 0.0f, 3.0f);
        ImGui::SetCursorPos(ImVec2(300, 0));
        ImGui::SliderFloat("Flap time B", &m_bird.m_flapTimeB, 0.0f, 3.0f);
        ImGui::SetCursorPos(ImVec2(400, 0));
        ImGui::SliderFloat("Flap power", &m_bird.m_flapPower.y, 0.0f, 100.0f);    
        ImGui::SetCursorPos(ImVec2(0, 10));
                ImGui::PushItemWidth(200);
        ImGui::SliderFloat("Scale", &m_bird.m_scale, 0.0f, 5.0f);  
        ImGui::PopItemWidth();

        if (m_gameData.m_state == State::GameOver) {
          ImGui::Text("Game Over!");
        }

        ImGui::End();
    }
}

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;

  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::onDestroy() {
  abcg::glDeleteProgram(m_birdProgram);
  abcg::glDeleteProgram(m_bgProgram);
  m_bg.destroy(); 
  m_bird.destroy();
}

void Window::checkCollisions() {
   glm::vec2 birdPosition = m_bird.m_translation;

  // Definir limites de colisão (supõe-se que a tela está normalizada de -1.0 a 1.0)
  float topLimit = 1.0f;
  float bottomLimit = -1.0f;
  
  // Verifica se o pássaro ultrapassou os limites superior ou inferior
  if (birdPosition.y >= topLimit || birdPosition.y <= bottomLimit) {
    m_gameData.m_state = State::GameOver;
    std::cout << "Colisão detectada! Game Over.\n";
  }
}