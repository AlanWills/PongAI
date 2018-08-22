#pragma once

#include "Objects/Script.h"


namespace PongAI
{

class BounceOffColliders : public CelesteEngine::Script
{
  DECLARE_SCRIPT(BounceOffColliders)

  protected:
    /// Called after the component's gameobject has collided with a collider it was not in collision with last frame
    void onCollisionEnter(const ConstHandle<Physics::Collider>& collider) override;
};

}