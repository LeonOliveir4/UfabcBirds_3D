#ifndef FRUIT_HPP_
#define FRUIT_HPP_

#include "abcgOpenGL.hpp"
#include "gamedata.hpp"
#include "animation.hpp"
#include "camera.hpp"
#include "modelObj.hpp"

class Fruta {
public:
    virtual void create(GLuint program, std::string fruit_1, std::string fruit_2 , std::string fruit_3 ,glm::vec4 color1,glm::vec4 color2, glm::vec4 color3);
    virtual void render(Camera camera);
    void update(float deltaTime, GameData const &gamedata);
    virtual void destroy();

        // Getters
    const glm::vec3& getPosition() const { return m_position; }
    float getScale() const { return m_scale; }
    bool getIsLive() const { return m_isLive; }
    glm::vec3 getPivot() const{return m_pivot;}
    const glm::mat4& getMatrixRotation() const { return m_matrixRotation; }
    const glm::mat4& getMasterMatrix() const { return m_masterMatrix; }
    const glm::vec3 getUpVector() {return glm::normalize(glm::vec3(m_masterMatrix[1]));}
    const glm::vec3 getFoward() {return -glm::normalize(glm::vec3(m_matrixRotation[2]));}


    // Setters
    void setPosition(const glm::vec3& position) {
        m_position = position;
        updateMasterMatrix();
    }

    void setScale(float scale) {
        m_scale = scale;
        updateMasterMatrix();
    }

    void setPivot(glm::vec3 pivot){ 
        m_pivot = pivot;
        updateMasterMatrix();
    }
    void setMatrixRotation(const glm::mat4& matrixRotation) {
        m_matrixRotation = matrixRotation;
        updateMasterMatrix();
    }

    void setIsLive(bool live) {
        m_isLive = live;
    }



protected:
    ModelObj m_fruta_1;
    ModelObj m_fruta_2;
    ModelObj m_fruta_3;

    //color
    glm::vec4 m_color1{1.0f};
    glm::vec4 m_color2{1.0f};
    glm::vec4 m_color3{1.0f};
    //geometrics
    GLint m_program;
    glm::vec3 m_position{0.f, 0.f, 0.f};
    float m_scale{1.f};
    glm::mat4 m_matrixRotation{1.0f};
    glm::vec3 m_pivot{0.f, 0.f, 0.f};
    glm::mat4 m_masterMatrix{1.f};
    //Phisics
    glm::vec3 m_velocity{0.f};

    //animação
    Director m_morre_animation;
    bool m_isLive{true};
    float m_timer{0.5f};


    void updateAnimation(float deltaTime);
    void updateMasterMatrix() {
        m_masterMatrix = glm::translate(glm::mat4(1.0f), m_position)*glm::translate(glm::mat4(1.0f), -m_pivot)* m_matrixRotation *  glm::translate(glm::mat4(1.0f), m_pivot) * glm::scale(glm::mat4(1.0f), glm::vec3(m_scale));
        m_fruta_1.setMasterMatrix(m_masterMatrix);
        m_fruta_2.setMasterMatrix(m_masterMatrix);
        m_fruta_3.setMasterMatrix(m_masterMatrix);
    }    
};
#endif