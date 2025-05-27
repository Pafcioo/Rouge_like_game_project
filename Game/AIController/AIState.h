#pragma once
#include <memory>

class AbstractAIController;

class AbstractAIState
{
    public:
        virtual ~AbstractAIState() = default;
        virtual void update(std::shared_ptr<AbstractAIController> aiController, float deltaTime) = 0;
};

class PatrolState : public AbstractAIState
{
    public:
        void update(std::shared_ptr<AbstractAIController> aiController, float deltaTime) override;
};

class AttackState : public AbstractAIState
{
    public:
        void update(std::shared_ptr<AbstractAIController> aiController, float deltaTime) override;
};

class ChaseState : public AbstractAIState
{
    public:
        void update(std::shared_ptr<AbstractAIController> aiController, float deltaTime) override;
};