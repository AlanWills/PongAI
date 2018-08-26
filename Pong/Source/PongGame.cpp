#include "stdafx.h"

#include "PongGame.h"
#include "Screens/Loading/ScreenLoader.h"
#include "Rendering/SpriteRenderer.h"
#include "Input/KeyboardRigidBody2DController.h"
#include "Physics/RectangleCollider.h"
#include "AI/AIController.h"
#include "Level.h"


namespace PongAI
{
  //------------------------------------------------------------------------------------------------
  void PongGame::onInitialize()
  {
    Inherited::onInitialize();

    getPhysicsManager()->setGravityScale(0.0f);

    Path gameplayScreen(getResourcesDirectory(), "Data", "Screens", "GameplayScreen.asset");
    Handle<Screen> screen = ScreenLoader::load(gameplayScreen);

    Path leftHandPaddle("Data", "Prefabs", "LeftHandPaddle.asset");
    const Handle<Prefab>& leftHandPaddlePrefab = getResourceManager()->load<Prefab>(leftHandPaddle);

    Path rightHandPaddle("Data", "Prefabs", "RightHandPaddle.asset");
    const Handle<Prefab>& rightHandPaddlePrefab = getResourceManager()->load<Prefab>(rightHandPaddle);

    Path ball("Data", "Prefabs", "Ball.asset");
    const Handle<Prefab>& ballPrefab = getResourceManager()->load<Prefab>(ball);

    // Top Collider
    {
      screen->findGameObjectWithName("Top Collider")->findComponent<Physics::RectangleCollider>()->setDimensions(getViewportDimensions().x, 10);
    }

    // Right Collider
    {
      screen->findGameObjectWithName("Right Collider")->findComponent<Physics::RectangleCollider>()->setDimensions(10, getViewportDimensions().y);
    }

    // Bottom Collider
    {
      screen->findGameObjectWithName("Bottom Collider")->findComponent<Physics::RectangleCollider>()->setDimensions(getViewportDimensions().x, 10);
    }

    // Left Collider
    {
      screen->findGameObjectWithName("Left Collider")->findComponent<Physics::RectangleCollider>()->setDimensions(10, getViewportDimensions().y);
    }

    // Player
    {
      const Handle<GameObject>& playerPaddle = leftHandPaddlePrefab->instantiate(screen);
      
      const Handle<Input::KeyboardRigidBody2DController>& playerController = playerPaddle->findComponent<Input::KeyboardRigidBody2DController>();
      playerController->setIncrementMode(Input::KeyboardRigidBody2DController::IncrementMode::kToggle);
      playerController->setLinearVelocityDelta(600);
      playerController->setIncreaseYLinearVelocityKey(GLFW_KEY_W);
      playerController->setDecreaseYLinearVelocityKey(GLFW_KEY_S);

      Physics::addSimulatedBody(playerPaddle->findComponent<Physics::Collider>(), playerPaddle->findComponent<Physics::RigidBody2D>());
    }

    // Opponent
    {
      const Handle<GameObject>& opponentPaddle = rightHandPaddlePrefab->instantiate(screen);
      
      const Handle<Input::KeyboardRigidBody2DController>& opponentController = opponentPaddle->findComponent<Input::KeyboardRigidBody2DController>();
      opponentController->setIncrementMode(Input::KeyboardRigidBody2DController::IncrementMode::kToggle);
      opponentController->setLinearVelocityDelta(600);
      opponentController->setIncreaseYLinearVelocityKey(GLFW_KEY_UP);
      opponentController->setDecreaseYLinearVelocityKey(GLFW_KEY_DOWN);

      // Topology scriptable object
      const Handle<AIController>& aiController = opponentPaddle->findComponent<AIController>();
      aiController->getNetwork()->initializeTopology(std::vector<size_t>());

      Physics::addSimulatedBody(opponentPaddle->findComponent<Physics::Collider>(), opponentPaddle->findComponent<Physics::RigidBody2D>());
    }

    // Ball
    {
      const Handle<GameObject>& ball = ballPrefab->instantiate(screen);

      Physics::addSimulatedBody(ball->findComponent<Physics::Collider>());
    }

    Level::reset(screen);
  }
}