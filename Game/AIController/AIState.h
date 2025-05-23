#pragma once

class AbstractAIController;

class AbstractAIState
{
    public:
        virtual ~AbstractAIState() = default;
        virtual void update(std::shared_ptr<AbstractAIController> aiController) = 0;
};

class PatrolState : public AbstractAIState
{
    public:
        void update(std::shared_ptr<AbstractAIController> aiController) override;
};

class AttackState : public AbstractAIState
{
    public:
        void update(std::shared_ptr<AbstractAIController> aiController) override;
};

class ChaseState : public AbstractAIState
{
    public:
        void update(std::shared_ptr<AbstractAIController> aiController) override;
};