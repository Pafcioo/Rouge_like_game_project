#include <SFML/Graphics.hpp>
#include "../inc/Potion.h"
#include "../inc/Entity.h"

void HealPotion::activate(Entity *entity) {
    entity->setHealth(entity->getHealth()+effectAmount);
}
