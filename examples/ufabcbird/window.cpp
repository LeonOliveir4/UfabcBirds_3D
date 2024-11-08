#include "window.hpp"
#include <iostream>
#include <cmath>

void Window::onCreate() {
    auto const assetsPath{abcg::Application::getAssetsPath()};
    m_gameData.m_totalTime = 0.0;
    m_gameData.m_velocityX = -0.2;
    std::cout << "Initialize shaders \n";
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
    m_pipeProgram =
      abcg::createOpenGLProgram({{.source = assetsPath + "pipe.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "pipe.frag",
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
    m_gameData.m_totalTime = 0.0f;
    m_gameData.m_score = 0;
    m_bird.create(m_birdProgram, m_gameData);
    m_bg.create(m_bgProgram, m_gameData);
    m_pipes.create(m_pipeProgram, m_gameData);

    // Configurações do popup
    m_showPopup = true;
    m_popupTimeElapsed = 0.0f;
    m_currentCharIndex = 0;
    m_popupText = "Este é o Tucano!\n"
                  "Você sabia?\n"
                  "Os tucanos vivem nas florestas tropicais da América do Sul!\n"
                  "Eles têm bicos grandes e coloridos, que ajudam a pegar frutas e pequenos insetos.\n"
                  "Curiosidade: apesar do tamanho do bico, ele é leve e o tucano consegue voar facilmente.";
    m_displayedText.clear(); // Inicialmente, o texto exibido está vazio
}

void Window::onEvent(SDL_Event const &event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::Up));
    }
    if (event.key.keysym.sym == SDLK_r && m_gameData.m_state == State::GameOver) {
      restart();
    }
  }
  if (event.type == SDL_KEYUP) {
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Up));
    }
  }
}

void Window::onUpdate() {
  if (m_gameData.m_state == State::Playing) {
    auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};
    m_gameData.m_totalTime += deltaTime;
    m_gameData.m_score = 30 * int(m_gameData.m_totalTime * 20);
    checkCollisions();
    m_bg.update(deltaTime);
    m_bird.update(m_gameData, deltaTime);
    m_pipes.update(m_gameData, deltaTime);

    if (m_showPopup) {
            m_popupTimeElapsed += deltaTime;
            if (m_popupTimeElapsed >= m_textDisplaySpeed && m_currentCharIndex < m_popupText.size()) {
                m_displayedText += m_popupText[m_currentCharIndex];
                ++m_currentCharIndex;
                m_popupTimeElapsed = 0.0f;
            }

            if (m_currentCharIndex >= m_popupText.size() && m_popupTimeElapsed >= 5.0f) {
                m_showPopup = false;
            }
        }
  }
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT);
  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);
  m_bg.paint();
  m_pipes.paint();
  m_bird.paint(m_gameData);
}

void Window::onPaintUI() {
    abcg::OpenGLWindow::onPaintUI();

    // Barra de pontuação no topo da tela
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(m_viewportSize.x, 50));
    ImGuiWindowFlags const flagsTop{ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar};
    ImGui::Begin("Score", nullptr, flagsTop);
    ImVec4 corVermelha = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_Text, corVermelha);
    ImGui::SetCursorPos(ImVec2(10, 0));
    ImGui::Text("Score: %d", m_gameData.m_score);
    ImGui::PopStyleColor();
    ImGui::End();

    if (m_showPopup) {
        ImGui::SetNextWindowPos(ImVec2(10, 60));
        ImGui::SetNextWindowSizeConstraints(ImVec2(200, 150), ImVec2(400, 300));
        ImGuiWindowFlags const flagsPopup{ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize};

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.3f, 0.9f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
        ImGui::Begin("Popup", nullptr, flagsPopup);
        ImGui::TextWrapped("%s", m_displayedText.c_str());
        ImGui::End();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
    }

    if (m_gameData.m_state == State::GameOver) {
        ImGui::SetNextWindowPos(ImVec2(m_viewportSize.x / 2, m_viewportSize.y / 2), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::Begin("Game Over", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
        ImGui::SetWindowFontScale(2.0f);
        ImGui::Text("Game Over!");
        ImGui::Text("Pressione 'R' para reiniciar");
        ImGui::PopStyleColor();
        ImGui::SetWindowFontScale(1.0f);
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
  abcg::glDeleteProgram(m_pipeProgram);
  m_bg.destroy(); 
  m_pipes.destroy();
  m_bird.destroy();
}

void Window::checkCollisions() {
    float birdY = m_bird.m_translation.y;
    float topLimit = 1.0f;
    float bottomLimit = -1.0f;

    // Verifica colisão com o topo e o fundo da tela
    if (birdY >= topLimit || birdY <= bottomLimit) {
        m_gameData.m_state = State::GameOver;
        std::cout << "Colisão com a borda da tela! Game Over.\n";
        return; // Para a verificação se uma colisão com a borda foi detectada
    }

    // Verifica colisão do pássaro com os pipes
    for (auto &pipe : m_pipes.m_pipes) {
        float cX = m_bird.m_translation.x;
        float cY = m_bird.m_translation.y;

        // Dados do pipe inferior
        float rX1 = pipe.m_p1.x + pipe.m_translation.x;
        float rY1 = pipe.m_p1.y;
        float rW = m_pipes.m_borderWidth;
        float rH = -1000.0; // Altura negativa para o pipe inferior

        // Dados do pipe superior
        float rX2 = pipe.m_p2.x + pipe.m_translation.x;
        float rY2 = pipe.m_p2.y;
        float rH2 = 1000.0; // Altura positiva para o pipe superior

        // Colisão com o pipe inferior
        float testX1 = cX;
        float testY1 = cY;

        if (cX < rX1) testX1 = rX1;
        else if (cX > rX1 + rW) testX1 = rX1 + rW;
        if (cY > rY1) testY1 = rY1;
        else if (cY < rY1 + rH) testY1 = rY1 + rH;

        float distX1 = cX - testX1;
        float distY1 = cY - testY1;
        float distance1 = std::sqrt((distX1 * distX1) + (distY1 * distY1));

        if (distance1 <= 0.05f) {
            pipe.m_color = glm::vec4(1.0f, 0.0f, 0.07f, 1.0f); // Marca o pipe colidido
            m_gameData.m_state = State::GameOver;
            std::cout << "Colisão com o pipe inferior! Game Over.\n";
            return;
        }

        // Colisão com o pipe superior
        float testX2 = cX;
        float testY2 = cY;

        if (cX < rX2) testX2 = rX2;
        else if (cX > rX2 + rW) testX2 = rX2 + rW;
        if (cY > rY2 + rH2) testY2 = rY2 + rH2;
        else if (cY < rY2) testY2 = rY2;

        float distX2 = cX - testX2;
        float distY2 = cY - testY2;
        float distance2 = std::sqrt((distX2 * distX2) + (distY2 * distY2));

        if (distance2 <= 0.05f) {
            pipe.m_color = glm::vec4(1.0f, 0.0f, 0.07f, 1.0f); // Marca o pipe colidido
            m_gameData.m_state = State::GameOver;
            std::cout << "Colisão com o pipe superior! Game Over.\n";
            return;
        }
    }
}