#pragma once
#include <memory>

class AbstractAIController;

class AIControllerDifficulty
{
    protected:
        std::shared_ptr<AbstractAIController> aiController;
    public:
        virtual ~AIControllerDifficulty() = default;
        virtual void execute() = 0;
};

class EasyAIControllerDifficulty : public AIControllerDifficulty
{
    public:
        EasyAIControllerDifficulty(std::shared_ptr<AbstractAIController> aiController);
        void execute() override;
};

class BalancedAIControllerDifficulty : public AIControllerDifficulty
{
    public:
        BalancedAIControllerDifficulty(std::shared_ptr<AbstractAIController> aiController);
        void execute() override;
};  

class DifficultAIControllerDifficulty : public AIControllerDifficulty
{
    public:
        DifficultAIControllerDifficulty(std::shared_ptr<AbstractAIController> aiController);
        void execute() override;
};