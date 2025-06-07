#include "Game/AIController/AIController.h"
#include "Game/AIController/AIAttack.h"
#include <iostream>
AIAttack::AIAttack(int attack)
{
    attackMulti = attack;
}

void AIAttack::update(std::shared_ptr<AbstractAIController> aiController)
{
    auto enemy = aiController->getControlledEntity();
    if(aiController->getGameplayInfo()->hasInfo("playerPos"))
    {
        sf::Vector2f playerPos = aiController->getGameplayInfo()->getInfo<sf::Vector2f>("playerPos");
        enemy->attack(playerPos);
    }
}