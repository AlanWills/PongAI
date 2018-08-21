#pragma once

#include "Game/Game.h"


namespace PongAI
{

class PongGame : public CelesteEngine::Game
{
  protected:
    void onInitialize() override;

  private:
    typedef CelesteEngine::Game Inherited;
};

}