#include "algorithm/inc/AISensing.h"
#include "algorithm/inc/AIController.h"

VisionSensing::VisionSensing(float vision, float attack)
{
    visionRange = vision;
    attackRange = attack;
    isEntityVisible = false;
    isInRangeToAttack = false;
}

void VisionSensing::update(std::shared_ptr<AbstractAIController> aiController)
{
    auto gameplayInfo = aiController->getGameplayInfo();
    if(gameplayInfo->hasInfo("playerPos"))
    {
        auto playerPos = gameplayInfo->getInfo<sf::Vector2f>("playerPos");
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
        if(distance < attackRange)
        {
            isInRangeToAttack = true;
        }
        else
        {
            isInRangeToAttack = false;
        }
    }
    
}

bool VisionSensing::getVisibility()
{
    return isEntityVisible;
}

bool VisionSensing::getInRange()
{
    return isInRangeToAttack;
}