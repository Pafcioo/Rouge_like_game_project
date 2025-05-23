#pragma once

class AbstractAIController;

class AbstractAIDecision
{
    public:
        virtual ~AbstractAIDecision() = default;
        virtual void update(std::shared_ptr<AbstractAIController> aiController) = 0;
};

class AIDecision : public AbstractAIDecision
{
    public:
        AIDecision() = default;
        ~AIDecision() override = default;
        void update(std::shared_ptr<AbstractAIController> aiController) override;
};