#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_


#include "abcgOpenGL.hpp"

struct Keyframe {
    float time; // Tempo do quadro
    glm::vec3 position;
    glm::mat4 rotation;
    glm::vec3 scale;
};

class Animation {
public:
    Animation(const std::vector<Keyframe>& keyframes, float duration);

    // Retorna a transformação interpolada para o tempo atual
    glm::mat4 GetTransform(float time) const;

private:
    std::vector<Keyframe> m_keyFrames;
    float m_duration;

    // Interpola entre dois quadros-chave
    Keyframe Interpolate(const Keyframe& kf1, const Keyframe& kf2, float factor) const;
};

class Director {
public:
    void SetAnimation(const std::shared_ptr<Animation>& animation);
    void Update(float deltaTime);
    glm::mat4 GetCurrentTransform() ;

private:
    std::shared_ptr<Animation> m_currentAnimation{nullptr};
    float m_currentTime{0.0f};
};
#endif