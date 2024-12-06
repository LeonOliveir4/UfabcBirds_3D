#include "bird.hpp"
#include <iostream>

void Bird::create(GLuint program, std::string bird_path, GameData const &gamedata){
    m_program = program;
    m_bird_path = bird_path;
    m_bico.create(m_program, m_bird_path + "bico.obj");
    m_bico.setColor(glm::vec4(0.921f,0.694f,0.203f,1.0f));
    m_corpo.create(m_program, m_bird_path + "corpo.obj");
    m_corpo.setColor(glm::vec4(0.f, 0.f, 0.f , 1.0f));
    m_asa_esquerda.create(m_program, m_bird_path + "asa_esquerda.obj");
    m_asa_esquerda.setColor(glm::vec4(0.f, 0.f, 0.f , 1.0f));
    m_asa_direita.create(m_program, m_bird_path + "asa_direita.obj");
    m_asa_direita.setColor(glm::vec4(0.f, 0.f, 0.f , 1.0f));
    m_rabo.create(m_program, m_bird_path + "rabo.obj");
    m_rabo.setColor(glm::vec4(0.f, 0.f, 0.f , 1.0f));
}
void Bird::render(Camera camera){
    m_bico.render(camera);
    m_corpo.render(camera);
    m_asa_esquerda.render(camera);
    m_asa_direita.render(camera);
    m_rabo.render(camera);
}

void Bird::pitch(float speed){ //rotacao em x
    auto const speedRads = glm::radians(speed);
    glm::mat4 matrixRotationPitch = glm::rotate(glm::mat4(1.0f), -speedRads , glm::vec3(1.0f, 0.0f, 0.0f));
    m_matrixRotation *= matrixRotationPitch;
    updateMasterMatrix();
}
void Bird::roll(float speed){ // rotacao em z
    auto const speedRads = glm::radians(speed);
    glm::mat4 matrixRotationRoll = glm::rotate(glm::mat4(1.0f), speedRads, glm::vec3(0.0f, 0.0f, 1.0f));
    m_matrixRotation *= matrixRotationRoll;
    updateMasterMatrix();
}
void Bird::yaw(float speed){ // rotacao em y
    auto const speedRads = glm::radians(speed);
    glm::mat4 matrixRotationYaw = glm::rotate(glm::mat4(1.0f), speedRads, glm::vec3(0.0f, 1.0f, 0.0f));
    m_matrixRotation *= matrixRotationYaw;
    updateMasterMatrix();
}

void Bird::update(float deltaTime, GameData const &gamedata) {
    if (gamedata.m_input[gsl::narrow<size_t>(Input::PitchPos)]) {
        std::cout << "PitchPos" <<"\n";
        pitch(m_pitchVelocity);
    }
    if (gamedata.m_input[gsl::narrow<size_t>(Input::PitchNeg)]) {
        std::cout << "PitchNeg" <<"\n";
        pitch(-m_pitchVelocity);
    }
    if (gamedata.m_input[gsl::narrow<size_t>(Input::YawPos)]) {
        std::cout << "YawPos" <<"\n";
        yaw(m_yawVelocity);
    }
    if (gamedata.m_input[gsl::narrow<size_t>(Input::YawNeg)]) {
        std::cout << "YawNeg" <<"\n";
        yaw(-m_yawVelocity);
    }
    if (gamedata.m_input[gsl::narrow<size_t>(Input::RollPos)]) {
        std::cout << "RollPos" <<"\n";
        roll(m_rollVelocity);
    }
    if (gamedata.m_input[gsl::narrow<size_t>(Input::RollNeg)]) {
        std::cout << "RollNeg" <<"\n";
        roll(-m_rollVelocity);
    }
    m_velocity = getFoward() * 2.0f;
    m_position += m_velocity * deltaTime;
}
void Bird::destroy(){
    m_bico.destroy();
    m_corpo.destroy();
    m_asa_esquerda.destroy();
    m_asa_direita.destroy();
    m_rabo.destroy();
}