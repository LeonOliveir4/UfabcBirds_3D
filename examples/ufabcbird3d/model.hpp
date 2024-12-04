#ifndef MODEL_CUBE_
#define MODEL_CUBE_


#include "abcgOpenGL.hpp"
#include "camera.hpp"

class Model{
public:
    virtual void create(GLuint program);
    virtual void render(const Camera camera);
    virtual void destroy() ;
    // Getters
    const glm::vec3& getPosition() const { return m_position; }
    float getScale() const { return m_scale; }
    const glm::mat4& getMatrixRotation() const { return m_matrixRotation; }

    // Getter para a matriz do modelo
    const glm::mat4& getModelMatrix() const { return m_modelMatrix; }

    // Setters
    void setPosition(const glm::vec3& position) {
        m_position = position;
        updateModelMatrix();
    }

    void setScale(float scale) {
        m_scale = scale;
        updateModelMatrix();
    }

    void setMatrixRotation(const glm::mat4& matrixRotation) {
        m_matrixRotation = matrixRotation;
        updateModelMatrix();
    }

protected:
//Opengl buffers and program
    GLuint m_VAO{};
    GLuint m_VBO{};
    GLuint m_EBO{};
    GLuint m_program{};
//Base Color
    glm::vec4 m_color{0.f, 0.f, 0.5f, 1.0f};
//Identity Matrix
    glm::mat4 m_modelMatrix{1.0f};
//Position, scale and rotaion atributes
    glm::vec3 m_position{0.f, 0.f, 0.f};
    float m_scale{1.f};
    glm::mat4 m_matrixRotation{1.0f};
//Index indices and vertex
    std::vector<glm::vec3> m_vertices;
    std::vector<GLuint> m_indices;
    void updateModelMatrix() {
        m_modelMatrix = glm::translate(glm::mat4(1.0f), m_position) *
                                m_matrixRotation *
                                glm::scale(glm::mat4(1.0f), glm::vec3(m_scale));
    }
};
#endif