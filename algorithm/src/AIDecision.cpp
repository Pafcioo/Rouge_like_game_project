#include "Game/AIController/AIDecision.h"
#include "Game/AIController/AIController.h"

AIDecision::AIDecision()
{
    stateSwitchDelay = 0.5f; // seconds, adjust as needed
    stateSwitchTimer = 0.0f;
}

void AIDecision::update(std::shared_ptr<AbstractAIController> aiController, float deltaTime)
{
    stateSwitchTimer += deltaTime;
    if (stateSwitchTimer < stateSwitchDelay)
        return;

    auto sensingBase = aiController->getSensingComponent();
    auto vision = std::dynamic_pointer_cast<VisionSensing>(sensingBase);
    if (vision)
    {
        if(vision->getInRange())
        {
            aiController->setCurrentState(std::make_shared<AttackState>());
        }
        else if(vision->getVisibility())
        {
            aiController->setCurrentState(std::make_shared<ChaseState>());
        }
        else
        {
            aiController->setCurrentState(std::make_shared<PatrolState>());
        }
        stateSwitchTimer = 0.0f; // Reset timer after switching state
    }
}