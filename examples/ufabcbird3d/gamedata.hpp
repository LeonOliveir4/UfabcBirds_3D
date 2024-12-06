#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <bitset>
#include "abcgOpenGL.hpp"

enum class Input { PitchPos, PitchNeg, YawPos, YawNeg, RollPos, RollNeg, Restart};
enum class State { GameOver, Playing};

struct GameData {
    State m_state{State::Playing};
    std::bitset<7> m_input;
    int m_pontos{0};
    //glm::vec2 m_gravity{glm::vec2(0.f, -19.8f)};
    //glm::vec2 m_maxCoord{glm::vec2(20.f)};
    //float m_velocityX;
    //float m_totalTime{0};
    //int m_score{0};
};

#endif