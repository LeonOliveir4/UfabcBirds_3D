#include "window.hpp"
#include <iostream>

//Mapeamento de controle da camera
void Window::onEvent(SDL_Event const &event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_SPACE && m_gameData.m_state == State::GameOver) {
            restartGame();
            return;
        }

        if (m_gameData.m_state == State::Playing) {
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
    }

    if (event.type == SDL_KEYUP) {
        if (m_gameData.m_state == State::Playing) {
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
    m_bird.create(m_program, assetsPath + "tucano/");
    m_ground.create(m_program);
    //frutas
    createFrutas();
    showBirdInfo("Tucano");
}

void Window::createFrutas() {
    auto const assetsPath{abcg::Application::getAssetsPath()};
    auto &re{m_randomEngine}; 
    std::uniform_real_distribution<float> randomHeight(0.1f, 15.0f);
    std::uniform_real_distribution<float> randomPlane(-40.0f, 40.0f);
    fruta1.create(m_program, assetsPath + "guarana/olho.obj",assetsPath + "guarana/olho_branco.obj",assetsPath + "guarana/casca.obj", glm::vec4(0.f,0.f,0.f,1.0f),glm::vec4(1.f,1.f,1.f,1.0f),glm::vec4(0.802f,0.f,0.184f,0.018f));
    fruta1.setPosition(glm::vec3(randomPlane(re),randomHeight(re),randomPlane(re)));
    fruta2.create(m_program, assetsPath + "acai/acai.obj",assetsPath + "acai/acai.obj",assetsPath + "acai/acai.obj", glm::vec4(0.220f,0.006f,0.604f,1.f),glm::vec4(0.220f,0.006f,0.604f,1.f),glm::vec4(0.220f,0.006f,0.604f,1.f));
    fruta2.setPosition(glm::vec3(randomPlane(re),randomHeight(re),randomPlane(re)));
    fruta3.create(m_program, assetsPath + "jabuticaba/jabuticaba.obj",assetsPath + "jabuticaba/jabuticaba.obj",assetsPath + "jabuticaba/jabuticaba.obj", glm::vec4(0.373f,0.017f,0.497f,1.f),glm::vec4(0.373f,0.017f,0.497f,1.f),glm::vec4(0.373f,0.017f,0.497f,1.f));
    fruta3.setPosition(glm::vec3(randomPlane(re),randomHeight(re),randomPlane(re)));
    fruta4.create(m_program, assetsPath + "guarana/olho.obj",assetsPath + "guarana/olho_branco.obj",assetsPath + "guarana/casca.obj", glm::vec4(0.f,0.f,0.f,1.0f),glm::vec4(1.f,1.f,1.f,1.0f),glm::vec4(0.802f,0.f,0.184f,0.018f));
    fruta4.setPosition(glm::vec3(randomPlane(re),randomHeight(re),randomPlane(re)));
    fruta5.create(m_program, assetsPath + "acai/acai.obj",assetsPath + "acai/acai.obj",assetsPath + "acai/acai.obj", glm::vec4(0.220f,0.006f,0.604f,1.f),glm::vec4(0.220f,0.006f,0.604f,1.f),glm::vec4(0.220f,0.006f,0.604f,1.f));
    fruta5.setPosition(glm::vec3(randomPlane(re),randomHeight(re),randomPlane(re)));
    fruta6.create(m_program, assetsPath + "jabuticaba/jabuticaba.obj",assetsPath + "jabuticaba/jabuticaba.obj",assetsPath + "jabuticaba/jabuticaba.obj", glm::vec4(0.373f,0.017f,0.497f,1.f),glm::vec4(0.373f,0.017f,0.497f,1.f),glm::vec4(0.373f,0.017f,0.497f,1.f));
    fruta6.setPosition(glm::vec3(randomPlane(re),randomHeight(re),randomPlane(re)));
    fruta7.create(m_program, assetsPath + "guarana/olho.obj",assetsPath + "guarana/olho_branco.obj",assetsPath + "guarana/casca.obj", glm::vec4(0.f,0.f,0.f,1.0f),glm::vec4(1.f,1.f,1.f,1.0f),glm::vec4(0.802f,0.f,0.184f,0.018f));
    fruta7.setPosition(glm::vec3(randomPlane(re),randomHeight(re),randomPlane(re)));
    fruta8.create(m_program, assetsPath + "acai/acai.obj",assetsPath + "acai/acai.obj",assetsPath + "acai/acai.obj", glm::vec4(0.220f,0.006f,0.604f,1.f),glm::vec4(0.220f,0.006f,0.604f,1.f),glm::vec4(0.220f,0.006f,0.604f,1.f));
    fruta8.setPosition(glm::vec3(randomPlane(re),randomHeight(re),randomPlane(re)));
    fruta9.create(m_program, assetsPath + "jabuticaba/jabuticaba.obj",assetsPath + "jabuticaba/jabuticaba.obj",assetsPath + "jabuticaba/jabuticaba.obj", glm::vec4(0.373f,0.017f,0.497f,1.f),glm::vec4(0.373f,0.017f,0.497f,1.f),glm::vec4(0.373f,0.017f,0.497f,1.f));
    fruta9.setPosition(glm::vec3(randomPlane(re),randomHeight(re),randomPlane(re)));
    fruta10.create(m_program, assetsPath + "guarana/olho.obj",assetsPath + "guarana/olho_branco.obj",assetsPath + "guarana/casca.obj", glm::vec4(0.f,0.f,0.f,1.0f),glm::vec4(1.f,1.f,1.f,1.0f),glm::vec4(0.802f,0.f,0.184f,0.018f));
    fruta10.setPosition(glm::vec3(randomPlane(re),randomHeight(re),randomPlane(re)));
    fruta11.create(m_program, assetsPath + "acai/acai.obj",assetsPath + "acai/acai.obj",assetsPath + "acai/acai.obj", glm::vec4(0.220f,0.006f,0.604f,1.f),glm::vec4(0.220f,0.006f,0.604f,1.f),glm::vec4(0.220f,0.006f,0.604f,1.f));
    fruta11.setPosition(glm::vec3(randomPlane(re),randomHeight(re),randomPlane(re)));
    fruta12.create(m_program, assetsPath + "jabuticaba/jabuticaba.obj",assetsPath + "jabuticaba/jabuticaba.obj",assetsPath + "jabuticaba/jabuticaba.obj", glm::vec4(0.373f,0.017f,0.497f,1.f),glm::vec4(0.373f,0.017f,0.497f,1.f),glm::vec4(0.373f,0.017f,0.497f,1.f));
    fruta12.setPosition(glm::vec3(randomPlane(re),randomHeight(re),randomPlane(re)));
};

void Window::onPaint() {
    abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);


    m_bird.render(m_camera);
    fruta1.render(m_camera);
    fruta2.render(m_camera);
    fruta3.render(m_camera);
    fruta4.render(m_camera);
    fruta5.render(m_camera);
    fruta6.render(m_camera);
    fruta7.render(m_camera);
    fruta8.render(m_camera);
    fruta9.render(m_camera);
    fruta10.render(m_camera);
    fruta11.render(m_camera);
    fruta12.render(m_camera);
    m_ground.render(m_camera);
    abcg::glUseProgram(0); 
}

void Window::onPaintUI() {
    abcg::OpenGLWindow::onPaintUI();
    if (m_showPopup) {
        auto const popupWidth = 400.0f;
        auto const popupHeight = 150.0f;
        auto const popupPosX = 10.0f;
        auto const popupPosY = 60.0f;

        ImGui::SetNextWindowPos(ImVec2(popupPosX, popupPosY), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(popupWidth, popupHeight));

        ImGuiWindowFlags const flagsPopup{ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize};
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.3f, 0.9f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));

        ImGui::Begin("Popup", nullptr, flagsPopup);
        ImGui::TextWrapped("%s", m_displayedText.c_str());
        ImGui::End();

        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
    }

    {
        auto const widgetSize{ImVec2(218, 200)};
        ImGui::SetNextWindowPos(ImVec2(m_viewportSize.x - widgetSize.x - 5, 5));
        ImGui::SetNextWindowSize(widgetSize);
        ImGui::Begin("Widget window", nullptr, ImGuiWindowFlags_NoDecoration);
    if (m_gameData.m_state == State::GameOver) {
        auto const windowSize = ImVec2(300, 100);

        auto const windowPos = ImVec2(
            (m_viewportSize.x - windowSize.x) / 2.0f,
            (m_viewportSize.y - windowSize.y) / 2.0f);

        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(windowSize);

        ImGui::Begin("Game Over Screen", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
        ImGui::Text("Game Over!");
        ImGui::Text("Sua pontuação foi %d pontos.", m_gameData.m_pontos);
        ImGui::Text("Aperte ESPAÇO para reiniciar.");
        ImGui::End();
    }

        {
            ImGui::PushItemWidth(120);
            auto position = m_bird.getPosition();
            auto scale = m_bird.getScale();

            static float cameraUp = m_camera.getUpDistance();
            static float cameraBack = m_camera.getBackwardDistance();
            ImGui::SliderFloat("X_position", &position.x, -25.0f, 25.f);
            ImGui::SliderFloat("Y_position", &position.y, -25.0f, 25.f);
            ImGui::SliderFloat("Z_position", &position.z, -25.0f, 25.f);

            ImGui::SliderFloat("Camera_up", &cameraUp, -10.0f, 10.f);
            ImGui::SliderFloat("Camera_back", &cameraBack, -10.0f, 10.f);
            ImGui::Text("Pontuacao: %d", m_gameData.m_pontos);

            m_camera.setUp(cameraUp);
            m_camera.setBackward(cameraBack);

            m_camera.computeProjectionMatrix(m_viewportSize);
            m_bird.setScale(scale);
        }
        ImGui::End();
    }
}

void Window::showBirdInfo(const std::string& birdName) {
    auto it = BirdDescriptions::descriptions.find(birdName);
    if (it != BirdDescriptions::descriptions.end()) {
        m_popupText = it->second;
        m_displayedText.clear();
        m_showPopup = true;
        m_popupTimeElapsed = 0.0f;
        m_currentCharIndex = 0;
    }
}


void Window::restartGame() {
    createFrutas();
    m_gameData.m_state = State::Playing;
    m_gameData.m_input.reset();
    m_gameData.m_pontos = 0;
    m_bird.reset();
    m_camera.reset();
}


void Window::onUpdate() {
  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};

    if (m_gameData.m_state == State::Playing) {
        m_bird.update(deltaTime, m_gameData);
        m_camera.update(m_bird.getPosition(), m_bird.getFoward(), m_bird.getUpVector());

        if (m_bird.getPosition().y < -0.5f || 
            glm::abs(m_bird.getPosition().x) > 125.0f || 
            glm::abs(m_bird.getPosition().z) > 125.0f) {
            m_gameData.m_state = State::GameOver;
            m_gameData.m_input.reset();
        }
    }

    if (m_showPopup) {
        m_popupTimeElapsed += deltaTime;
        if (m_popupTimeElapsed >= m_textDisplaySpeed && m_currentCharIndex < m_popupText.size()) {
            m_displayedText += m_popupText[m_currentCharIndex];
            ++m_currentCharIndex;
            m_popupTimeElapsed = 0.0f;  // Reseta o contador de tempo
        }

        if (m_currentCharIndex >= m_popupText.size() && m_popupTimeElapsed >= 5.0f) {
            m_showPopup = false;
        }
    }
  fruta1.update(deltaTime, m_gameData);
  fruta2.update(deltaTime, m_gameData);
  fruta3.update(deltaTime, m_gameData);
  fruta4.update(deltaTime, m_gameData);
  fruta5.update(deltaTime, m_gameData);
  fruta6.update(deltaTime, m_gameData);
  fruta7.update(deltaTime, m_gameData);
  fruta8.update(deltaTime, m_gameData);
  fruta9.update(deltaTime, m_gameData);
  fruta10.update(deltaTime, m_gameData);
  fruta11.update(deltaTime, m_gameData);
  fruta12.update(deltaTime, m_gameData);

  m_bird.update(deltaTime, m_gameData);
  m_camera.update(m_bird.getPosition(),m_bird.getFoward(), m_bird.getUpVector());
  checkCollisions();
}

void Window::onResize(glm::ivec2 const &size) {
    m_viewportSize = size;
    m_camera.computeProjectionMatrix(size);
}

void Window::onDestroy() {
  fruta1.destroy();
  fruta2.destroy();
  fruta3.destroy();
  fruta4.destroy();
  fruta5.destroy();
  fruta6.destroy();
   m_ground.destroy();
   m_bird.destroy();
}

void Window::checkCollisions(){
    if(fruta1.getIsLive()){
        std::cout<<"Distancia da furta 1: "<<glm::distance2(m_bird.getPosition(), fruta1.getPosition())<<"\n";
        if(glm::distance2(m_bird.getPosition(), fruta1.getPosition()) <= 5.0f ){
            m_gameData.m_pontos += 1;
            fruta1.setIsLive(false);
        }
    }
    if(fruta2.getIsLive()){
        if(glm::distance2(m_bird.getPosition(), fruta2.getPosition()) <= 5.0f ){
            m_gameData.m_pontos += 1;
            fruta2.setIsLive(false);
        }
    }
    if(fruta3.getIsLive()){
        if(glm::distance2(m_bird.getPosition(), fruta3.getPosition()) <= 5.0f ){
            m_gameData.m_pontos += 1;
            fruta3.setIsLive(false);
        }
    }
    if(fruta4.getIsLive()){
        if(glm::distance2(m_bird.getPosition(), fruta4.getPosition()) <= 5.0f ){
            m_gameData.m_pontos += 1;
            fruta4.setIsLive(false);
        }
    }
    if(fruta5.getIsLive()){
        if(glm::distance2(m_bird.getPosition(), fruta5.getPosition()) <= 5.0f ){
            m_gameData.m_pontos += 1;
            fruta5.setIsLive(false);
        }
    }
    if(fruta6.getIsLive()){
        if(glm::distance2(m_bird.getPosition(), fruta6.getPosition()) <= 5.0f ){
            m_gameData.m_pontos += 1;
            fruta6.setIsLive(false);
        }
    }
    if(fruta7.getIsLive()){
        if(glm::distance2(m_bird.getPosition(), fruta7.getPosition()) <= 5.0f ){
            m_gameData.m_pontos += 1;
            fruta7.setIsLive(false);
        }
    }
    if(fruta8.getIsLive()){
        if(glm::distance2(m_bird.getPosition(), fruta8.getPosition()) <= 5.0f ){
            m_gameData.m_pontos += 1;
            fruta8.setIsLive(false);
        }
    }
    if(fruta9.getIsLive()){
        if(glm::distance2(m_bird.getPosition(), fruta9.getPosition()) <= 5.0f ){
            m_gameData.m_pontos += 1;
            fruta9.setIsLive(false);
        }
    }
    if(fruta10.getIsLive()){
        if(glm::distance2(m_bird.getPosition(), fruta10.getPosition()) <= 5.0f ){
            m_gameData.m_pontos += 1;
            fruta10.setIsLive(false);
        }
    }
    if(fruta11.getIsLive()){
        if(glm::distance2(m_bird.getPosition(), fruta11.getPosition()) <= 5.0f ){
            m_gameData.m_pontos += 1;
            fruta11.setIsLive(false);
        }
    }
    if(fruta12.getIsLive()){
        if(glm::distance2(m_bird.getPosition(), fruta12.getPosition()) <= 5.0f ){
            m_gameData.m_pontos += 1;
            fruta12.setIsLive(false);
        }
    }
}