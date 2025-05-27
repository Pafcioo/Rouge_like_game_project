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
        virtual void setAIController(std::shared_ptr<AbstractAIController> controller);
};

class EasyAIControllerDifficulty : public AIControllerDifficulty
{
    public:
        EasyAIControllerDifficulty() = default;
        void execute() override;
};

class BalancedAIControllerDifficulty : public AIControllerDifficulty
{
    public:
        BalancedAIControllerDifficulty() = default;
        void execute() override;
};  

class DifficultAIControllerDifficulty : public AIControllerDifficulty
{
    public:
        DifficultAIControllerDifficulty() = default;
        void execute() override;
};