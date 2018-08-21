#include "stdafx.h"

#include "PongGame.h"
#include "Screens/Loading/ScreenLoader.h"
#include "Rendering/SpriteRenderer.h"
#include "Input/KeyboardTranslationScript.h"


namespace PongAI
{
  //------------------------------------------------------------------------------------------------
  void PongGame::onInitialize()
  {
    Inherited::onInitialize();

    Path gameplayScreen(getResourcesDirectory(), "Data", "Screens", "GameplayScreen.asset");
    Handle<Screen> screen = ScreenLoader::load(gameplayScreen);

    Path paddle("Data", "Prefabs", "Paddle.asset");
    const Handle<Prefab>& prefab = getResourceManager()->load<Prefab>(paddle);

    const Handle<GameObject>& playerPaddle = prefab->instantiate(screen);
    playerPaddle->getTransform()->setTranslation(playerPaddle->findComponent<Rendering::SpriteRenderer>()->getDimensions().x * 0.5f, getViewportDimensions().y * 0.5f);

    const Handle<KeyboardTranslationScript>& playerController = playerPaddle->findComponent<KeyboardTranslationScript>();
    playerController->setPanSpeed(300);
    playerController->setMoveUpKey(GLFW_KEY_W);
    playerController->setMoveDownKey(GLFW_KEY_S);
  }
}