#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera {
public:
    void computeViewMatrix();
    void computeProjectionMatrix(glm::vec2 const &size);
    void update(glm::vec3 targetPosition, glm::vec3 targetForward, glm::vec3 targetUpVector);
    void setFollow(bool is_follow) { m_isfollow = is_follow; }
    void setBackward(float distance) { m_backwardDistance = distance; }
    void setUp(float distance) { m_upDistance = distance; }
    void dolly(float speed);
    void truck(float speed);
    void pan(float speed);
    void tilt(float speed);
    void elevation(float speed);

    void reset();

    float getBackwardDistance() const { return m_backwardDistance; }
    float getUpDistance() const { return m_upDistance; }

    glm::mat4 const &getViewMatrix() const { return m_viewMatrix; }
    glm::mat4 const &getProjMatrix() const { return m_projMatrix; }
    float m_fov{70.0f};

private:
    glm::vec3 m_eye{0.0f, 0.5f, 2.5f}; // Camera position
    glm::vec3 m_at{0.0f, 0.5f, 0.0f};  // Look-at point
    glm::vec3 m_up{0.0f, 1.0f, 0.0f};  // "up" direction

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projMatrix;

    float m_backwardDistance{5.0f};
    float m_upDistance{5.0f};
    bool m_isfollow{false};
};

#endif