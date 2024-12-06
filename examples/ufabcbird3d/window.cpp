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

    showBirdInfo("Tucano");
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
        ImGui::Text("Aperte ESPAÇO para reiniciar.");
        ImGui::End();
    }

        {
            ImGui::PushItemWidth(120);
            auto position = m_bird.getPosition();
            auto scale = m_bird.getScale();

            static float cameraUp = m_camera.getUpDistance();
            static float cameraBack = m_camera.getBackwardDistance();
            ImGui::SliderFloat("X_position", &position.x, -10.0f, 10.f);
            ImGui::SliderFloat("Y_position", &position.y, -10.0f, 10.f);
            ImGui::SliderFloat("Z_position", &position.z, -10.0f, 10.f);

            ImGui::SliderFloat("Camera_up", &cameraUp, -10.0f, 10.f);
            ImGui::SliderFloat("Camera_back", &cameraBack, -10.0f, 10.f);

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
    m_gameData.m_state = State::Playing;
    m_gameData.m_input.reset();
    m_bird.reset();
    m_camera.reset();
}


void Window::onUpdate() {
  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};

    if (m_gameData.m_state == State::Playing) {
        m_bird.update(deltaTime, m_gameData);
        m_camera.update(m_bird.getPosition(), m_bird.getFoward(), m_bird.getUpVector());

        if (m_bird.getPosition().y < -0.5f || 
            glm::abs(m_bird.getPosition().x) > 25.0f || 
            glm::abs(m_bird.getPosition().z) > 25.0f) {
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
}

void Window::onResize(glm::ivec2 const &size) {
    m_viewportSize = size;
    m_camera.computeProjectionMatrix(size);
}

void Window::onDestroy() {
   m_ground.destroy();
   m_bird.destroy();
}