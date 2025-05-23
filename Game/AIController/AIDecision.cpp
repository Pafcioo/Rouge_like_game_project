#include "Game/AIController/AIDecision.h"
#include "Game/AIController/AIController.h"

void AIDecision::update(std::shared_ptr<AbstractAIController> aiController)
{
    auto sensingBase = aiController->getSensingComponent();
    auto vision = std::dynamic_pointer_cast<VisionSensing>(sensingBase);
    if (vision)
    {
        if(vision->getVisibility())
        {
            aiController->setCurrentState(std::make_shared<ChaseState>());
        }
        else
        {
            aiController->setCurrentState(std::make_shared<PatrolState>());
        }
    }
    auto controlledEntity = aiController->getControlledEntity();
}