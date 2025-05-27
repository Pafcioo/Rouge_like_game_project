#pragma once
#include <SFML/Graphics.hpp>
#include "Game/GameplayInfoSource.h"
#include "Game/AIController/AICooldown.h"
#include "Game/AIController/AIDecision.h"
#include "Game/AIController/AIMovement.h"
#include "Game/AIController/AISensing.h"
#include "Game/AIController/AIState.h"
#include "Game/AIController/AIAttack.h"
#include "Game/AIController/AIControllerDifficulty.h"
#include "Game/Entity.h"


class AbstractAIController : public std::enable_shared_from_this<AbstractAIController>
{
    protected:
        std::shared_ptr<AbstractAIState> currentState;
        std::shared_ptr<GameplayInfoSource> gameplayInfo;
        std::shared_ptr<AbstractAIDecision> decisionComponent;
        std::shared_ptr<AbstractAIMovement> movementComponent;
        std::shared_ptr<AbstractAISensing> sensingComponent;
        std::shared_ptr<AbstractAICooldown> cooldownComponent;
        std::shared_ptr<AbstractAIAttack> attackComponent;
        std::shared_ptr<Entity> controlledEntity;
    public:
        virtual ~AbstractAIController() = default;
        //Setters
        virtual void setDecisionComponent(std::shared_ptr<AbstractAIDecision> decision);
        virtual void setMovementComponent(std::shared_ptr<AbstractAIMovement> movement);
        virtual void setSensingComponent(std::shared_ptr<AbstractAISensing> sensing);
        virtual void setCooldownComponent(std::shared_ptr<AbstractAICooldown> cooldown);
        virtual void setAttackComponent(std::shared_ptr<AbstractAIAttack> attack);
        virtual void setCurrentState(std::shared_ptr<AbstractAIState> state);
        //Getters
        virtual std::shared_ptr<AbstractAIDecision> getDecisionComponent();
        virtual std::shared_ptr<AbstractAIMovement> getMovementComponent();
        virtual std::shared_ptr<AbstractAISensing> getSensingComponent();
        virtual std::shared_ptr<AbstractAICooldown> getCooldownComponent();
        virtual std::shared_ptr<AbstractAIAttack> getAttackComponent();
        virtual std::shared_ptr<AbstractAIState> getCurrentState();
        virtual std::shared_ptr<GameplayInfoSource> getGameplayInfo();
        virtual std::shared_ptr<Entity> getControlledEntity();
        //Update method
        virtual void update(float deltaTime) = 0; 
};

class EnemyAIController : public AbstractAIController
{
    public:
        EnemyAIController(std::shared_ptr<Entity> entity, std::shared_ptr<GameplayInfoSource> gameplayInfoSource);
        ~EnemyAIController() override = default;
        void update(float deltaTime) override;
};
