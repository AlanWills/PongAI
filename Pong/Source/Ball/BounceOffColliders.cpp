#include "stdafx.h"

#include "Objects/GameObject.h"
#include "Ball/BounceOffColliders.h"
#include "Physics/RectangleCollider.h"
#include "Physics/RigidBody2D.h"
#include "Level.h"

using namespace CelesteEngine;
using namespace CelesteEngine::Physics;


namespace PongAI
{
  REGISTER_SCRIPT(BounceOffColliders, 1)

  //------------------------------------------------------------------------------------------------
  BounceOffColliders::BounceOffColliders()
  {
  }

  //------------------------------------------------------------------------------------------------
  BounceOffColliders::~BounceOffColliders()
  {
  }

  //------------------------------------------------------------------------------------------------
  void BounceOffColliders::onCollisionEnter(const ConstHandle<Physics::Collider>& collider)
  {
    // YEAH THIS DESPERATELY NEEDS GENERALISATION, BUT I DON'T HAVE THE TIME RIGHT NOW SO WILL JUST DO THIS INSTEAD.
    const Handle<RigidBody2D>& thisRigidBody = getGameObject()->findComponent<RigidBody2D>();
    const glm::vec3& thisPosition = getTransform()->getTranslation();
    const glm::vec2& thisHalfDims = getGameObject()->findComponent<RectangleCollider>()->getDimensions() * 0.5f;
    const glm::vec3& collisionPosition = collider->getTransform()->getTranslation();
    const glm::vec2& collisionHalfDims = collider.as<RectangleCollider>()->getDimensions() * 0.5f;

    if (collider->getGameObject()->getTag() == internString("VerticalBoundary"))
    {
      // We have collided with the boundaries on the left or right hand side
      if ((thisPosition.x - thisHalfDims.x) < (collisionPosition.x + collisionHalfDims.x))
      {
        // Check this left against collision right
        // Player has lost - update scores and reset level
        Level::incrementOpponentScore();
        Level::reset(getGameObject()->getOwnerScreen());
      }
      else if ((thisPosition.x + thisHalfDims.x) > (collisionPosition.x - collisionHalfDims.x))
      {
        // Check this right against collision left
        // Opponent has lost - update scores and reset level
        Level::incrementPlayerScore();
        Level::reset(getGameObject()->getOwnerScreen());
      }
    }
    else if (collider->getGameObject()->getTag() == internString("HorizontalBoundary"))
    {
      // We have collided with the boundaries on the top or bottom
      if ((thisPosition.y + thisHalfDims.y) > (collisionPosition.y - collisionHalfDims.y))
      {
        // Check this top against collision bottom
        thisRigidBody->setLinearVelocity(thisRigidBody->getLinearVelocity().x, thisRigidBody->getLinearVelocity().y * -1);
      }
      else if ((thisPosition.y - thisHalfDims.y) < (collisionPosition.y + collisionHalfDims.y))
      {
        // Check this bottom against collision top
        thisRigidBody->setLinearVelocity(thisRigidBody->getLinearVelocity().x, thisRigidBody->getLinearVelocity().y * -1);
      }
    }
    else if (collider->getGameObject()->getTag() == internString("Paddle"))
    {
      // Do paddle collisions here
      if ((thisPosition.x - thisHalfDims.x) < (collisionPosition.x + collisionHalfDims.x))
      {
        // Check this left against collision right
        thisRigidBody->setLinearVelocity(thisRigidBody->getLinearVelocity().x * -1, thisRigidBody->getLinearVelocity().y);

        // Update ball hit counter
        Level::incrementBallHitCounter();
        if (Level::getBallHitCounter() > 4)
        {
          Level::resetBallHitCounter();
          thisRigidBody->setLinearVelocity(thisRigidBody->getLinearVelocity() * glm::vec2(1.1f));
        }
      }
      else if ((thisPosition.x + thisHalfDims.x) > (collisionPosition.x - collisionHalfDims.x))
      {
        // Check this right against collision left
        thisRigidBody->setLinearVelocity(thisRigidBody->getLinearVelocity().x * -1, thisRigidBody->getLinearVelocity().y);

        // Update ball hit counter
        Level::incrementBallHitCounter();
        if (Level::getBallHitCounter() > 4)
        {
          Level::resetBallHitCounter();
          thisRigidBody->setLinearVelocity(thisRigidBody->getLinearVelocity() * glm::vec2(1.1f));
        }
      }
    }
  }
}