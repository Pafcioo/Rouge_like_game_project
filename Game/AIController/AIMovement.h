#pragma once

class AbstractAIController;

class AbstractAIMovement
{
    public:
        virtual ~AbstractAIMovement() = default;
        virtual void update(std::shared_ptr<AbstractAIController> aiController) = 0;
};

class AIMovement : public AbstractAIMovement
{
    public:
        AIMovement() = default;
        ~AIMovement() = default;
        virtual void update(std::shared_ptr<AbstractAIController> aiController) = 0;
};

