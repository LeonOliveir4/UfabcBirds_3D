#include "bird.hpp"

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
}
void Bird::render(Camera camera){
    m_bico.render(camera);
    m_corpo.render(camera);
    m_asa_esquerda.render(camera);
    m_asa_direita.render(camera);
    m_rabo.render(camera);
}
void Bird::destroy(){
    m_bico.destroy();
    m_corpo.destroy();
    m_asa_esquerda.destroy();
    m_asa_direita.destroy();
    m_rabo.destroy();
}