#include "window.hpp"
#include <iostream>
#include <cmath>

void Window::onCreate() {
    auto const assetsPath{abcg::Application::getAssetsPath()};
    m_gameData.m_totalTime = 0.0;
    m_gameData.m_velocityX = -0.2;
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
    std::cout << "estado do jogo restart: " << static_cast<int>(m_gameData.m_state) << "\n";
    m_bird.create(m_birdProgram, m_gameData);
    m_bg.create(m_bgProgram, m_gameData);
    m_pipes.create(m_pipeProgram, m_gameData);
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

  // Adiciona a tecla R para reiniciar o jogo se estiver no estado GameOver
    if (event.key.keysym.sym == SDLK_r && m_gameData.m_state == State::GameOver) {
      restart();
    }
}

void Window::onUpdate() {
  // Atualiza apenas se o jogo está em estado de Playing
  if (m_gameData.m_state == State::Playing) {
    auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};
    
    // Atualiza o tempo total e a pontuação
    m_gameData.m_totalTime += deltaTime;
    m_gameData.m_score = 30 * int(m_gameData.m_totalTime * 20);

    // Define o movimento de flap do pássaro quando a entrada "Up" é detectada
    if (m_gameData.m_input.test(static_cast<size_t>(Input::Up))) {
      m_bird.setFlap();
    }

    // Atualiza o fundo, o pássaro e os pipes
    m_bg.update(m_gameData, deltaTime);
    m_bird.update(m_gameData, deltaTime);
    m_pipes.update(m_gameData, deltaTime);

    // Verifica colisões
    checkCollisions();
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

    // ImU32 redColor = IM_COL32(255, 0, 0, 125); // RGBA
    // // Desenha um retângulo que cobre toda a janela
    // ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    // draw_list->AddRectFilled(ImVec2(0, 0), ImVec2(m_viewportSize.x, 50), redColor);
    {
        ImGui::SetNextWindowPos(ImVec2(0,0));
        ImGui::SetNextWindowSize(ImVec2(m_viewportSize.x,50));
        ImGuiWindowFlags const flags{ImGuiWindowFlags_NoBackground |
                                     ImGuiWindowFlags_NoTitleBar };//| ImGuiWindowFlags_NoInputs};
        ImGui::Begin(" ", nullptr, flags);
        ImGui::PushItemWidth(50);
        ImGui::SetCursorPos(ImVec2(10, 0));
        ImGui::PushItemWidth(100);
        ImVec4 corVermelha = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); 
        ImGui::PushStyleColor(ImGuiCol_Text, corVermelha);
        ImGui::Text("Score:%d", m_gameData.m_score);
        // ImGui::SliderFloat("Sustein", &m_bird.m_sustein.y, -10.0f, 10.0f);
        // ImGui::SetCursorPos(ImVec2(100, 0));
        // ImGui::SliderFloat("Flap time A", &m_bird.m_flapTimeA, 0.0f, 3.0f);
        // ImGui::SetCursorPos(ImVec2(300, 0));
        // ImGui::SliderFloat("Flap time B", &m_bird.m_flapTimeB, 0.0f, 3.0f);
        // ImGui::SetCursorPos(ImVec2(400, 0));
        // ImGui::SliderFloat("Flap power", &m_bird.m_flapPower.y, 0.0f, 100.0f);    
        // ImGui::SetCursorPos(ImVec2(0, 10));
        // ImGui::PushItemWidth(200);
        // ImGui::SliderFloat("Scale", &m_bird.m_scale, 0.0f, 5.0f);  
        ImGui::PopItemWidth(); 
        if (m_gameData.m_state == State::GameOver) {
          ImGui::Begin("Game Over", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
          // Cria uma janela centralizada com tamanho automático para o texto
          ImGui::SetNextWindowSize(ImVec2(0, 0));  // Deixa o tamanho da janela adaptável
          ImGui::SetNextWindowPos(ImVec2(m_viewportSize.x / 2, m_viewportSize.y / 2), 
                                  ImGuiCond_Always, ImVec2(0.5f, 0.5f)); // Centraliza a janela na tela
          // Define a cor vermelha e o tamanho maior para o texto
          ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Cor vermelha
          ImGui::SetWindowFontScale(2.0f); // Aumenta o tamanho do texto
          ImGui::Text("Game Over!");
          ImGui::Text("Pressione 'R' para reiniciar");
          // Restaura o estilo padrão
          ImGui::PopStyleColor();
          ImGui::SetWindowFontScale(1.0f); // Volta ao tamanho normal
          ImGui::End();
        }
        ImGui::End();
    }
}


void Window::checkCollisions() {
   glm::vec2 birdPosition = m_bird.m_translation;

  // Definir limites de colisão para a tela (supõe-se que a tela está normalizada de -1.0 a 1.0)
  float topLimit = 1.0f;
  float bottomLimit = -1.0f;

  // Verifica colisão com os limites superior e inferior da tela
  if (birdPosition.y >= topLimit || birdPosition.y <= bottomLimit) {
    m_gameData.m_state = State::GameOver;
    std::cout << "Colisão com a borda da tela! Game Over.\n";
    return; // Finaliza a verificação caso a colisão com a borda seja detectada
  }

  // Colisão do pássaro com os pipes
  for (auto &pipe : m_pipes.m_pipes) {
    float testX = birdPosition.x;
    float testY = birdPosition.y;
    float testX2 = birdPosition.x;
    float testY2 = birdPosition.y;

    float rX1 = pipe.m_p1.x + pipe.m_translation.x;
    float rY1 = pipe.m_p1.y;
    float rW = m_pipes.m_borderWidth;
    float rH = -1000.0;

    float rH2 = 1000.0;
    float rX2 = pipe.m_p2.x + pipe.m_translation.x;
    float rY2 = pipe.m_p2.y;

    // Teste Pipe baixo
    if (birdPosition.x < rX1) {
      testX = rX1;
    } else if (birdPosition.x > rX1 + rW) {
      testX = rX1 + rW;
    }
    if (birdPosition.y > rY1) {
      testY = rY1;
    } else if (birdPosition.y < rY1 + rH) {
      testY = rY1 + rH;
    }

    // Teste Pipe alto
    if (birdPosition.x < rX2) {
      testX2 = rX2;
    } else if (birdPosition.x > rX2 + rW) {
      testX2 = rX2 + rW;
    }
    if (birdPosition.y > rY2 + rH2) {
      testY2 = rY2 + rH2;
    } else if (birdPosition.y < rY2) {
      testY2 = rY2;
    }

    // Calcular distância para ambos os pipes
    float distX = birdPosition.x - testX;
    float distY = birdPosition.y - testY;
    float distance = std::sqrt((distX * distX) + (distY * distY));

    float distX2 = birdPosition.x - testX2;
    float distY2 = birdPosition.y - testY2;
    float distance2 = std::sqrt((distX2 * distX2) + (distY2 * distY2));

    if (distance <= 0.05f || distance2 <= 0.05f) {
      pipe.m_color = glm::vec4(1.0f, 0.0f, 0.07f, 1.0f); // Destacar o pipe colidido
      m_gameData.m_state = State::GameOver;
      std::cout << "Colisão com o pipe! Game Over.\n";
      return; // Interrompe a função ao detectar colisão
    }
  }
}