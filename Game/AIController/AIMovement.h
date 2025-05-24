#pragma once
#include <memory>

class AbstractAIController;

class AbstractAIMovement
{
    protected:
        int movementMulti;
    public:
        virtual ~AbstractAIMovement() = default;
        virtual void update(std::shared_ptr<AbstractAIController> aiController) = 0;
};

class AIMovement : public AbstractAIMovement
{
    public:
        AIMovement(int movement);
        ~AIMovement() = default;
        void update(std::shared_ptr<AbstractAIController> aiController) override;
};

