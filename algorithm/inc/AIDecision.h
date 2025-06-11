#pragma once
#include <memory>

class AbstractAIController;

class AbstractAIDecision
{
    protected:
        float stateSwitchDelay;
        float stateSwitchTimer;
    public:
        virtual ~AbstractAIDecision() = default;
        virtual void update(std::shared_ptr<AbstractAIController> aiController, float deltaTime) = 0;
};

class AIDecision : public AbstractAIDecision
{
    public:
        AIDecision();
        ~AIDecision() override = default;
        void update(std::shared_ptr<AbstractAIController> aiController, float deltaTime) override;
};