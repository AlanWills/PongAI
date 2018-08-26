#include "stdafx.h"

#include "AI/AIController.h"
#include "Objects/GameObject.h"


namespace PongAI
{
  REGISTER_SCRIPT(AIController, 2)

  //------------------------------------------------------------------------------------------------
  AIController::AIController() :
    m_network(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  AIController::~AIController()
  {
  }

  //------------------------------------------------------------------------------------------------
  void AIController::onInitialize()
  {
    Inherited::onInitialize();

    cleanUpNetwork();

    m_network = new Neuron::Network();
  }

  //------------------------------------------------------------------------------------------------
  void AIController::onDeath()
  {
    Inherited::onDeath();

    cleanUpNetwork();
  }

  //------------------------------------------------------------------------------------------------
  void AIController::cleanUpNetwork()
  {
    if (m_network != nullptr)
    {
      delete m_network;
    }
  }
}