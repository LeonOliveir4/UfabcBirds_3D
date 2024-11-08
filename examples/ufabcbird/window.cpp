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
}

void Window::onUpdate() {
  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};
  m_gameData.m_totalTime += deltaTime;
  m_gameData.m_score = 30 * int(m_gameData.m_totalTime * 20);
  checkCollisions();
  m_bg.update(m_gameData, deltaTime);
  m_bird.update(m_gameData, deltaTime);
  m_pipes.update(m_gameData, deltaTime);
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT);
  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);
  m_bg.paint();
  m_pipes.paint();
  m_bird.paint();
  
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

void Window::checkCollisions(){
  //colisao do passaro e dos pipes
  for (auto  &pipe : m_pipes.m_pipes){
    float testX = m_bird.m_translation.x;
    float testY = m_bird.m_translation.y;

    float testX2 = m_bird.m_translation.x;
    float testY2 = m_bird.m_translation.y;

    float cX = m_bird.m_translation.x;
    float cY = m_bird.m_translation.y;


    float rX1 = (pipe.m_p1.x + pipe.m_translation.x);
    float rY1 = (pipe.m_p1.y);
    float rW = m_pipes.m_borderWidth;
    float rH = -1000.0;

    float rH2 = 1000.0;
    float rX2 = (pipe.m_p2.x + pipe.m_translation.x);
    float rY2 = (pipe.m_p2.y);
    

    //Teste Pipe baixo
    if(cX < rX1){
      testX = rX1;
    } else if(cX > rX1 + rW){
      testX = rX1 + rW;
    }
    if (cY > rY1){
      testY = rY1; // acima
    } else if(cY < rY1+rH){
      testY = rY1 + rH; // abaixo
    }
    //Teste pipe alto
    if(cX < rX2){
      testX2 = rX2;
    } else if(cX > rX2 + rW){
      testX2 = rX2 + rW;
    }
    if (cY > rY2 + rH2){
      testY2 = rY2 + rH2; // acima
    } else if(cY < rY2){
      testY2 = rY2; // abaixo
    }

   //std::cout << "m_bird position: " << m_bird.m_translation.x << ", " << m_bird.m_translation.y << "\n";
    float distX = cX-testX;
    float distY = cY-testY;
    float distance = std::sqrt( (distX*distX) + (distY*distY) );
    float distX2 = cX-testX2;
    float distY2 = cY-testY2;
    float distance2 = std::sqrt( (distX2*distX2) + (distY2*distY2) );
   // std::cout <<"pipe:"<<rX1<<" , "<< rY1  <<"    distance: " << distance <<"   Distance X:" <<distX<<"   Distance Y:" <<distY<<"\n";
    glm::vec4 red = glm::vec4(1.0, 0.0,0.07,1.0);
    if (distance <= 0.05 || distance2 <= 0.05){
      //Detectou aqui neste IF
      pipe.m_color = glm::vec4(1.0, 0.0,0.07,1.0);
    }
  }
}