#ifndef BIRD_HPP_
#define BIRD_HPP_

#include "abcgOpenGL.hpp"
#include "camera.hpp"
#include "modelObj.hpp"

class Bird {
public:
    virtual void create(GLuint program, std::string bird_path);
    virtual void render(Camera camera);
    void update(float deltaTime);
    void pitch(float speed); //rotacao em x
    void roll(float speed); // rotacao em z
    void yaw(float speed); // rotacao em y
    virtual void destroy();

        // Getters
    const glm::vec3& getPosition() const { return m_position; }
    float getScale() const { return m_scale; }
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



protected:
    ModelObj m_bico;
    ModelObj m_asa_esquerda;
    ModelObj m_asa_direita;
    ModelObj m_corpo;
    ModelObj m_rabo;

    std::string m_bird_path;
    //geometrics
    GLint m_program;
    glm::vec3 m_position{0.f, 0.f, 0.f};
    float m_scale{1.f};
    glm::mat4 m_matrixRotation{1.0f};
    glm::vec3 m_pivot{0.f, 0.f, 0.f};
    glm::mat4 m_masterMatrix{1.f};
    //Phisics
    glm::vec3 m_velocity{0.f};

    void updateMasterMatrix() {
        m_masterMatrix = glm::translate(glm::mat4(1.0f), m_position)*glm::translate(glm::mat4(1.0f), -m_pivot)* m_matrixRotation *  glm::translate(glm::mat4(1.0f), m_pivot) * glm::scale(glm::mat4(1.0f), glm::vec3(m_scale));
        m_bico.setMasterMatrix(m_masterMatrix);
        m_asa_esquerda.setMasterMatrix(m_masterMatrix);
        m_asa_direita.setMasterMatrix(m_masterMatrix);
        m_corpo.setMasterMatrix(m_masterMatrix);
        m_rabo.setMasterMatrix(m_masterMatrix);
    }    
};
#endif