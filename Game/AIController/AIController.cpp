#include "Game/AIController/AIController.h"

EnemyAIController::EnemyAIController(std::shared_ptr<Entity> entity, std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
{
    controlledEntity = entity;
    gameplayInfo = gameplayInfoSource;
    decisionComponent = std::make_shared<AIDecision>();
    currentState = std::make_shared<PatrolState>();
}

void EnemyAIController::update(float deltaTime)
{
    if (currentState) {
        currentState->update(shared_from_this(), deltaTime);
    }
    if (sensingComponent){
        sensingComponent->update(shared_from_this());
    }
    if (decisionComponent){
        decisionComponent->update(shared_from_this(), deltaTime);
    }
    if (cooldownComponent){
        cooldownComponent->update(shared_from_this(), deltaTime);
    }
}
//Setters
void AbstractAIController::setDecisionComponent(std::shared_ptr<AbstractAIDecision> decision)
{
    decisionComponent = decision;
}

void AbstractAIController::setMovementComponent(std::shared_ptr<AbstractAIMovement> movement)
{
    movementComponent = movement;
}

void AbstractAIController::setSensingComponent(std::shared_ptr<AbstractAISensing> sensing)
{
    sensingComponent = sensing;
}

void AbstractAIController::setCooldownComponent(std::shared_ptr<AbstractAICooldown> cooldown)
{
    cooldownComponent = cooldown;
}

void AbstractAIController::setAttackComponent(std::shared_ptr<AbstractAIAttack> attack)
{
    attackComponent = attack;
}

void AbstractAIController::setCurrentState(std::shared_ptr<AbstractAIState> state)
{
    currentState = state;
}
//Getters
std::shared_ptr<AbstractAIDecision> AbstractAIController::getDecisionComponent()
{
    return decisionComponent;
}

std::shared_ptr<AbstractAIMovement> AbstractAIController::getMovementComponent()
{
    return movementComponent;
}

std::shared_ptr<AbstractAISensing> AbstractAIController::getSensingComponent()
{
    return sensingComponent;
}

std::shared_ptr<AbstractAICooldown> AbstractAIController::getCooldownComponent()
{
    return cooldownComponent;
}

std::shared_ptr<AbstractAIAttack> AbstractAIController::getAttackComponent()
{
    return attackComponent;
}

std::shared_ptr<AbstractAIState> AbstractAIController::getCurrentState()
{
    return currentState;
}

std::shared_ptr<GameplayInfoSource> AbstractAIController::getGameplayInfo()
{
    return gameplayInfo;
}

std::shared_ptr<Entity> AbstractAIController::getControlledEntity()
{
    return controlledEntity;
}
