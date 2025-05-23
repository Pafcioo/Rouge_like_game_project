#pragma once

class AbstractAIController;

class AbstractAICooldown
{
    public:
        virtual ~AbstractAICooldown() = default;
        virtual void update(std::shared_ptr<AbstractAIController> aiController) = 0;
};