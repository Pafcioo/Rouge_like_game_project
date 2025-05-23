#include "Game/AIController/AISensing.h"
#include "Game/AIController/AIController.h"

VisionSensing::VisionSensing(float range)
{
    visionRange = range;
    isEntityVisible = false;
}

void VisionSensing::update(std::shared_ptr<AbstractAIController> aiController)
{
    auto gameplayInfo = aiController->getGameplayInfo();
    auto playerPos = gameplayInfo->getInfo<sf::Vector2f>("playerPosition");
    auto controlledEntityPos = aiController->getControlledEntity()->getPosition();

    auto distanceBetweenEntitiesVector = playerPos - controlledEntityPos;
    float distance = distanceBetweenEntitiesVector.length();
    if(distance < visionRange)
    {
        isEntityVisible = true;
    }
    else
    {
        isEntityVisible = false;
    }
}

bool VisionSensing::getVisibility()
{
    return isEntityVisible;
}