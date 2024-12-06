#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
             
void Camera::computeProjectionMatrix(glm::vec2 const &size) {
    m_projMatrix = glm::mat4(1.0f);
    auto const aspect(size.x / size.y);
    m_projMatrix = glm::perspective(glm::radians(m_fov), aspect, 0.1f, 100.0f);
}

void Camera::computeViewMatrix(){
    m_viewMatrix = glm::lookAt(m_eye, m_at, m_up);
}

void Camera::update(glm::vec3 targetPosition, glm::vec3 targetForward, glm::vec3 targetUpVector) {
    if(m_isfollow){
        m_at = targetPosition;
        glm::vec3 backward = -glm::normalize( targetForward);
        m_eye = targetPosition + (backward * m_backwardDistance) + (targetUpVector * m_upDistance);
        m_up = targetUpVector;
        computeViewMatrix();
    }
}


void Camera::dolly(float speed){
    auto const forward{glm::normalize(m_at - m_eye)};

    m_eye = m_eye + (speed * forward);
    m_at = m_at + (speed * forward);

    computeViewMatrix();
}

void Camera::truck(float speed){
    auto const forward{glm::normalize(m_at - m_eye)};
    auto const left{glm::normalize(glm::cross(m_up, forward))};

    //move para direita se speed > 0 e esquerda se speed < 0;
    m_at = m_at - (left * speed);
    m_eye = m_eye - (left * speed);

    computeViewMatrix();
}

void Camera::elevation(float speed){
    //Sobe e desce
    m_at = m_at + (m_up * speed);
    m_eye = m_eye + (m_up * speed);

    computeViewMatrix();
}

void Camera::pan(float speed) {
    glm::mat4 transform{1.0f};

    transform = glm::translate(transform, m_eye);
    transform = glm::rotate(transform, -speed, m_up);
    transform = glm::translate(transform, -m_eye);

    m_at = transform * glm::vec4(m_at, 1.0f);

    computeViewMatrix();    
}

void Camera::tilt(float speed){
    glm::mat4 transform{1.0f};
    auto const forward{glm::normalize(m_at - m_eye)};
    auto const left{glm::normalize(glm::cross(m_up, forward))};

    transform = glm::translate(transform, m_eye);
    transform = glm::rotate(transform, -speed, left);
    transform = glm::translate(transform, -m_eye);

    m_at = transform * glm::vec4(m_at, 1.0f);

    computeViewMatrix();
}

void Camera::reset() {
    m_eye = glm::vec3(0.0f, 0.0f, 3.0f);
    m_at = glm::vec3(0.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    computeViewMatrix();
}