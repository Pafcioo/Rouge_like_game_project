#include "../inc/AIController.h"
#include "../inc/AIAttack.h"

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
        auto direction = playerPos -enemy->getPosition();
        enemy->attack(direction);
    }
}