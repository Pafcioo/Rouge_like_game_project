#include "Game/AIController/AIState.h"
#include "Game/AIController/AIController.h"

void ChaseState::update(std::shared_ptr<AbstractAIController> aiController, float deltaTime)
{
    auto movementComponent = aiController->getMovementComponent();
    movementComponent->update(aiController, deltaTime);
}

void AttackState::update(std::shared_ptr<AbstractAIController> aiController, float deltaTime)
{
    auto cooldownComponent = aiController->getCooldownComponent();
    cooldownComponent->update(aiController, deltaTime);
}

void PatrolState::update(std::shared_ptr<AbstractAIController> aiController, float deltaTime)
{
    
}