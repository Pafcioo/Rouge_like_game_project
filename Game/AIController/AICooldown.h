#pragma once
#include <memory>

class AbstractAIController;

class AbstractAICooldown
{
    protected:
        float cooldownMulti;
        float timeSinceLastAction;
    public:
        virtual ~AbstractAICooldown() = default;
        virtual void update(std::shared_ptr<AbstractAIController> aiController, float deltaTime) = 0;
};

class AICooldown : public AbstractAICooldown
{
    public:
        AICooldown(float cooldown);
        ~AICooldown() = default;
        void update(std::shared_ptr<AbstractAIController> aiController, float deltaTime) override;
};