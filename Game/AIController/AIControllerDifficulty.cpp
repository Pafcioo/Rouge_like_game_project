#include "Game/AIController/AIControllerDifficulty.h"
#include "Game/AIController/AIController.h"

void AIControllerDifficulty::setAIController(std::shared_ptr<AbstractAIController> controller)
{
    aiController = controller;
}

void EasyAIControllerDifficulty::execute()
{
    aiController->setSensingComponent(std::make_shared<VisionSensing>(500.f,200.f));// In future implementation there will be attack and vision range based on entities properties
    aiController->setMovementComponent(std::make_shared<AIMovement>(1));
    aiController->setAttackComponent(std::make_shared<AIAttack>(1));
    aiController->setCooldownComponent(std::make_shared<AICooldown>(1));
}

void BalancedAIControllerDifficulty::execute()
{
    aiController->setSensingComponent(std::make_shared<VisionSensing>(500.f,200.f));// In future implementation there will be attack and vision range based on entities properties
    aiController->setMovementComponent(std::make_shared<AIMovement>(1.25f));
    aiController->setAttackComponent(std::make_shared<AIAttack>(1.25f));
    aiController->setCooldownComponent(std::make_shared<AICooldown>(0.75f));
}

void DifficultAIControllerDifficulty::execute()
{
    aiController->setSensingComponent(std::make_shared<VisionSensing>(500.f,200.f));// In future implementation there will be attack and vision range based on entities properties
    aiController->setMovementComponent(std::make_shared<AIMovement>(1.75f));
    aiController->setAttackComponent(std::make_shared<AIAttack>(1.75f));
    aiController->setCooldownComponent(std::make_shared<AICooldown>(0.5f));
}