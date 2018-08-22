#pragma once

#include "Screens/Screen.h"


namespace PongAI
{

class Level
{
  public:
    static void reset(const Handle<Screen>& screen);

    static size_t getBallHitCounter() { return m_ballHitCounter; }
    static void incrementBallHitCounter() { ++m_ballHitCounter; }
    static void resetBallHitCounter() { m_ballHitCounter = 0; }

    static size_t getPlayerScore() { return m_playerScore; }
    static void incrementPlayerScore() { ++m_playerScore; }

    static size_t getOpponentScore() { return m_opponentScore; }
    static void incrementOpponentScore() { ++m_opponentScore; }

  private:
    static size_t m_ballHitCounter;
    static size_t m_playerScore;
    static size_t m_opponentScore;
};

}