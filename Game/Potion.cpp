#include <SFML/Graphics.hpp>
#include "Potion.h"
#include "Entity.h"

void HealPotion::activate(Entity *entity) {
    entity->setHealth(entity->getHealth()+effectAmount);
}
