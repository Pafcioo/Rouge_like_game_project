#include "Game/AIController/AIControllerDifficulty.h"
#include "Game/AIController/AIController.h"

EasyAIControllerDifficulty::EasyAIControllerDifficulty(std::shared_ptr<AbstractAIController> aiController)
{
    this->aiController = aiController;
}

BalancedAIControllerDifficulty::BalancedAIControllerDifficulty(std::shared_ptr<AbstractAIController> aiController)
{
    this->aiController = aiController;
}

DifficultAIControllerDifficulty::DifficultAIControllerDifficulty(std::shared_ptr<AbstractAIController> aiController)
{
    this->aiController = aiController;
}

void EasyAIControllerDifficulty::execute()
{
    aiController->setDifficultyComponent(std::make_shared<EasyAIControllerDifficulty>(this));
}

void BalancedAIControllerDifficulty::execute()
{
    aiController->setDifficultyComponent(std::make_shared<BalancedAIControllerDifficulty>(this));
}

void DifficultAIControllerDifficulty::execute()
{
    aiController->setDifficultyComponent(std::make_shared<DifficultAIControllerDifficulty>(this));
}