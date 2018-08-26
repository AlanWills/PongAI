#pragma once

#include "Objects/Script.h"
#include "Network.h"


namespace PongAI
{

class AIController : public CelesteEngine::Script
{
  DECLARE_SCRIPT(AIController)

  public:
    Neuron::Network* getNetwork() { return m_network; }
    const Neuron::Network* getNetwork() const { return m_network; }

  protected:
    void onInitialize() override;
    void onDeath() override;

  private:
    typedef CelesteEngine::Script Inherited;

    void cleanUpNetwork();

    Neuron::Network* m_network;
};

}