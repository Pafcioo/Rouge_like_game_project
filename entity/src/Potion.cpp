#include <SFML/Graphics.hpp>
#include "../inc/Potion.h"
#include "../inc/Entity.h"

void HealPotion::activate(Entity *entity) {
    entity->setHealth(entity->getHealth()+effectAmount);
    if (entity->getHealth() > 100) {
        entity->setHealth(100);
    }
}
