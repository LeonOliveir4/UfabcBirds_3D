#ifndef MODEL_CUBE_
#define MODEL_CUBE_


#include "abcgOpenGL.hpp"
#include "camera.hpp"

struct Vertex {
  glm::vec3 position{};

  friend bool operator==(Vertex const &, Vertex const &) = default;
};

class Model{
public:
    virtual void create(GLuint program);
    virtual void createBuffers();
    virtual void createVertex();
    virtual void render(const Camera camera);
    virtual void destroy() ;
    // Getters
    const glm::vec3& getPosition() const { return m_position; }
    float getScale() const { return m_scale; }
    glm::vec3 getPivot() const{return m_pivot;}
    const glm::mat4& getMatrixRotation() const { return m_matrixRotation; }
    const glm::mat4& getAnimationMatrix() const { return m_animationMatrix; }

    // Getter para a matriz do modelo
    const glm::mat4& getModelMatrix() const { return m_modelMatrix; }

    glm::vec4 getColor() const {return m_color;}
    // Setters
    void setPosition(const glm::vec3& position) {
        m_position = position;
        updateModelMatrix();
    }

    void setScale(float scale) {
        m_scale = scale;
        updateModelMatrix();
    }

    void setPivot(glm::vec3 pivot){
        m_pivot = pivot;
        updateModelMatrix();
    }
    void setMatrixRotation(const glm::mat4& matrixRotation) {
        m_matrixRotation = matrixRotation;
        updateModelMatrix();
    }

    void setColor(glm::vec4 color) {
        m_color = color;
    }

    // ta peiga
    void setMasterMatrix(const glm::mat4& masterMatrix) {
        m_masterMatrix = masterMatrix;
        updateModelMatrix();
    }

    void setAnimationMatrix(const glm::mat4& AnimationMatrix) {
        m_animationMatrix = AnimationMatrix;
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
    glm::mat4 m_masterMatrix{1.0f};
//Position, scale and rotaion atributes
    glm::vec3 m_position{0.f, 0.f, 0.f};
    float m_scale{1.f};
    glm::mat4 m_matrixRotation{1.0f};
    glm::vec3 m_pivot{0.f, 0.f, 0.f};
//Index indices and vertex
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;
//Matriz de animacao
    glm::mat4 m_animationMatrix{1.0f};
    void standardize();
    void updateModelMatrix() {
        m_modelMatrix = m_masterMatrix*m_animationMatrix*glm::translate(glm::mat4(1.0f), m_position)*glm::translate(glm::mat4(1.0f), -m_pivot)* m_matrixRotation *  glm::translate(glm::mat4(1.0f), m_pivot) * glm::scale(glm::mat4(1.0f), glm::vec3(m_scale));
    }
};
#endif