#include "fruta.hpp"
#include <iostream>



void Fruta::create(GLuint program, std::string fruit_1, std::string fruit_2, std::string fruit_3,glm::vec4 color1,glm::vec4 color2, glm::vec4 color3){
    m_program = program;
    m_isLive = true;
    m_fruta_1.create(m_program, fruit_1);
    m_fruta_1.setColor(color1);
    m_fruta_2.create(m_program, fruit_2);
    m_fruta_2.setColor(color2);
    m_fruta_3.create(m_program, fruit_3);
    m_fruta_3.setColor(color3);

    std::vector<Keyframe> keyframes1 = {
        {0.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::rotate(glm::mat4(1.0f), glm::radians(0.f),  glm::vec3(0.f, 0.0f, 1.0f)), glm::vec3(1.0f)},
        {0.25f, glm::vec3(0.0f, 0.0f, 0.0f), glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0.f, 0.0f, 1.0f)), glm::vec3(0.8f)},
        {0.5f, glm::vec3(0.0f, 0.0f, 0.0f), glm::rotate(glm::mat4(1.0f), glm::radians(0.f),  glm::vec3(0.f, 0.0f, 1.0f)), glm::vec3(0.0f)}
    };
    m_morre_animation.SetAnimation(std::make_shared<Animation>(keyframes1, 0.5f));

}
void Fruta::render(Camera camera){
    m_fruta_1.render(camera);
    m_fruta_2.render(camera);
    m_fruta_3.render(camera);
}
void Fruta::update(float deltaTime, GameData const &gamedata){
    if(m_isLive == false  && m_timer >= 0){
        m_morre_animation.Update(deltaTime);
        m_fruta_1.setAnimationMatrix(m_morre_animation.GetCurrentTransform());
        m_fruta_2.setAnimationMatrix(m_morre_animation.GetCurrentTransform());
        m_fruta_3.setAnimationMatrix(m_morre_animation.GetCurrentTransform());
        m_timer -= deltaTime; 
    }

    if(m_isLive == false  && m_timer <= 0){
        destroy();
    }
}
void Fruta::destroy(){
    m_fruta_1.destroy();
    m_fruta_2.destroy();
    m_fruta_3.destroy();
}