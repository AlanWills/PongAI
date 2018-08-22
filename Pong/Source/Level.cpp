#define _USE_MATH_DEFINES
#include "stdafx.h"

#include "Level.h"
#include "Screens/ScreenUtils.h"
#include "Physics/RigidBody2D.h"
#include "Maths/RandomGenerator.h"
#include "Rendering/SpriteRenderer.h"

#include <cmath>

using namespace CelesteEngine::Physics;


namespace PongAI
{
  size_t Level::m_ballHitCounter = 0;
  size_t Level::m_playerScore = 0;
  size_t Level::m_opponentScore = 0;

  //------------------------------------------------------------------------------------------------
  void Level::reset(const Handle<Screen>& screen)
  {
    // Player
    {
      const Handle<GameObject>& player = screen->findGameObjectWithName("Player");
      player->getTransform()->setTranslation(player->findComponent<Rendering::SpriteRenderer>()->getDimensions().x * 0.5f, getViewportDimensions().y * 0.5f);
    }

    // Opponent
    {
      const Handle<GameObject>& opponent = screen->findGameObjectWithName("Opponent");
      opponent->getTransform()->setTranslation(getViewportDimensions().x - opponent->findComponent<Rendering::SpriteRenderer>()->getDimensions().x * 0.5f, getViewportDimensions().y * 0.5f);
    }

    // Ball
    {
      const Handle<GameObject>& ball = screen->findGameObjectWithName("Ball");
      ball->getTransform()->setTranslation(getViewportDimensions() * 0.5f);

      const Handle<RigidBody2D>& ballRigidBody = ball->findComponent<RigidBody2D>();

      float phi = Random::generate(static_cast<float>(-M_PI) * 0.25f, static_cast<float>(M_PI) * 0.25f);
      float ndx = std::cos(phi);
      float ndy = std::sin(phi);
      ballRigidBody->setLinearVelocity(ballRigidBody->getLinearVelocity() * glm::vec2(ndx, ndy));
    }

    m_ballHitCounter = 0;
    m_playerScore = 0;
    m_opponentScore = 0;
  }
}