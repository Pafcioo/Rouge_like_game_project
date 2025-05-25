#include "Game/AIController/AIMovement.h"
#include "Game/AIController/AIController.h"

AIMovement::AIMovement(int movement)
{
    movementMulti = movement;
}

void AIMovement::update(std::shared_ptr<AbstractAIController> aiController, float deltaTime)
{
    auto enemy = aiController->getControlledEntity();
    sf::Vector2f enemyPos = enemy->getPosition();
    if(aiController->getGameplayInfo()->hasInfo("playerPos"))
    {
        sf::Vector2f playerPos = aiController->getGameplayInfo()->getInfo<sf::Vector2f>("playerPos");
        sf::Vector2f direction = playerPos - enemyPos;
        float distance = direction.length();
        if(distance > 0.01f)
        {
            direction = direction.normalized();
            enemy->move(direction*deltaTime);
        }
    }
}