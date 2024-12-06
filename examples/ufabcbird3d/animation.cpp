#include "animation.hpp"

Animation::Animation(const std::vector<Keyframe>& keyFrames, float duration){
    m_keyFrames = keyFrames;
    m_duration = duration;
}

glm::mat4 Animation::GetTransform(float time) const {
    //loop infinito
    time = fmod(time, m_duration);

    //Quadros para interpolar
    Keyframe k1, k2;
    for (size_t i = 0; i < m_keyFrames.size() -1; ++i){
        if(time >= m_keyFrames[i].time && time <= m_keyFrames[1 + i].time) {
            k1 = m_keyFrames[i];
            k2 = m_keyFrames[i + 1];
            break;
        }
    }
    float factor = (time - k1.time) / (k2.time - k1.time);

    Keyframe k_interpoled = Interpolate(k1, k2, factor);
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), k_interpoled.position);
    glm::mat4 rotation = glm::mat4(k_interpoled.rotation);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), k_interpoled.scale);
    return translation * rotation * scale;
}

Keyframe Animation::Interpolate(const Keyframe& k1, const Keyframe& k2, float factor) const {
    Keyframe result;
    result.position = glm::mix(k1.position, k2.position, factor);
    result.rotation = glm::mat4_cast(glm::slerp(glm::quat_cast(k1.rotation), glm::quat_cast(k2.rotation), factor));
    result.scale = glm::mix(k1.scale, k2.scale, factor);
    return result;
}

void Director::SetAnimation(const std::shared_ptr<Animation>& animation) {
    m_currentAnimation = animation;
    m_currentTime = 0.0f; // Reinicia a animação
}

void Director::Update(float deltaTime) {
    if (m_currentAnimation) {
        m_currentTime += deltaTime;
    }
}

glm::mat4 Director::GetCurrentTransform()  {
    if (m_currentAnimation) {
        return m_currentAnimation->GetTransform(m_currentTime);
    }
    return glm::mat4(1.0f); // Matriz identidade se nenhuma animação estiver ativa
}