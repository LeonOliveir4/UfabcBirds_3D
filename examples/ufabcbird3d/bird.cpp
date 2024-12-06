#include "bird.hpp"
#include <iostream>

void Bird::create(GLuint program, std::string bird_path){
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

    //animate
    std::vector<Keyframe> keyframes1 = {
        {0.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::rotate(glm::mat4(1.0f), glm::radians(36.f),  glm::vec3(0.f, 0.0f, 1.0f)), glm::vec3(1.0f)},
        {0.25f, glm::vec3(0.0f, 0.0f, 0.0f), glm::rotate(glm::mat4(1.0f), glm::radians(-24.f), glm::vec3(0.f, 0.0f, 1.0f)), glm::vec3(1.0f)},
        {0.5f, glm::vec3(0.0f, 0.0f, 0.0f), glm::rotate(glm::mat4(1.0f), glm::radians(36.f),  glm::vec3(0.f, 0.0f, 1.0f)), glm::vec3(1.0f)}
    };

    std::vector<Keyframe> keyframes2 = {
        {0.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::rotate(glm::mat4(1.0f), glm::radians(-36.0f), glm::vec3(0.f, 0.0f, 1.0f)), glm::vec3(1.0f)},
        {0.25f, glm::vec3(0.0f, 0.0f, 0.0f), glm::rotate(glm::mat4(1.0f), glm::radians(24.0f),  glm::vec3(0.f, 0.0f, 1.0f)), glm::vec3(1.0f)},
        {0.5f, glm::vec3(0.0f, 0.0f, 0.0f), glm::rotate(glm::mat4(1.0f), glm::radians(-36.0f), glm::vec3(0.f, 0.0f, 1.0f)), glm::vec3(1.0f)}
    };

    m_asa_esquerda_director.SetAnimation(std::make_shared<Animation>(keyframes1, 0.5f));
    m_asa_direita_director.SetAnimation(std::make_shared<Animation>(keyframes2, 0.5f));
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

void Bird::update(float deltaTime, GameData &gamedata) {
    if (gamedata.m_state != State::Playing) return;
    
    if (gamedata.m_input[gsl::narrow<size_t>(Input::PitchPos)]) {
        pitch(m_pitchVelocity);
    }
    if (gamedata.m_input[gsl::narrow<size_t>(Input::PitchNeg)]) {
        pitch(-m_pitchVelocity);
    }
    if (gamedata.m_input[gsl::narrow<size_t>(Input::YawPos)]) {
        yaw(m_yawVelocity);
    }
    if (gamedata.m_input[gsl::narrow<size_t>(Input::YawNeg)]) {
        yaw(-m_yawVelocity);
    }
    if (gamedata.m_input[gsl::narrow<size_t>(Input::RollPos)]) {
        roll(m_rollVelocity);
    }
    if (gamedata.m_input[gsl::narrow<size_t>(Input::RollNeg)]) {
        roll(-m_rollVelocity);
    }
    // Simula gravidade para o pássaro (se necessário)
    //float gravity = -9.8f * deltaTime;  // Gravidade constante
    //m_position.y += gravity;

    m_velocity = getFoward() * 2.0f;
    m_position += m_velocity * deltaTime;

    float groundLevel = -0.8f;
    float birdRadius = 0.5f;

    if ((m_position.y - birdRadius) <= groundLevel) {
        std::cout << "Colisão com o chão detectada!\n";
        gamedata.m_state = State::GameOver;
    }

    float leftLimit = -125.0f;
    float rightLimit = 125.0f;
    float backLimit = -125.0f;
    float frontLimit = 125.0f;

    if (m_position.x < leftLimit || m_position.x > rightLimit || 
        m_position.z < backLimit || m_position.z > frontLimit) {
        std::cout << "Fora dos limites do chão!\n";
        gamedata.m_state = State::GameOver;
        return;
    }

    updateAnimation(deltaTime);
}
void Bird::destroy(){
    m_bico.destroy();
    m_corpo.destroy();
    m_asa_esquerda.destroy();
    m_asa_direita.destroy();
    m_rabo.destroy();
}

void Bird::reset() {
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_velocity = glm::vec3(0.0f);
    m_matrixRotation = glm::mat4(1.0f);
    updateMasterMatrix();
}

void Bird::updateAnimation(float deltaTime){
    m_asa_esquerda_director.Update(deltaTime);
    m_asa_direita_director.Update(deltaTime);
    m_asa_esquerda.setAnimationMatrix(m_asa_esquerda_director.GetCurrentTransform());
    m_asa_direita.setAnimationMatrix(m_asa_direita_director.GetCurrentTransform());
}