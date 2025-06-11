#include <SFML/Graphics.hpp>
#include "../inc/Potion.h"

#include <iostream>

#include "../inc/Entity.h"

void HealPotion::activate(Entity *entity) {
    if (useCounter <= 0) {
        return;
    }
    entity->setHealth(entity->getHealth()+effectAmount);
    if (entity->getHealth() > 100) {
        entity->setHealth(100);
    }
    useCounter--;
    gameplayInfo->setInfo("potionAmount", useCounter);
    std::cout << useCounter << std::endl;
}
