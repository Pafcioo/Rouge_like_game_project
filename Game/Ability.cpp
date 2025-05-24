#include "Ability.h"
#include <SFML/Graphics.hpp>

void Ability::update(float deltaTime) {
    if (currentCooldown <= 0) {
        isReady = true;
        currentCooldown = cooldown;
    }
    if (isActive) {
        currentCooldown-=deltaTime;
        duration-=deltaTime;
    }
    if (duration <= 0) {
        isActive = false;
    }
}

void SprintAbility::influence(Entity *entity) {
    if (isActive) {
        entity->setSpeed(entity->getEntityBaseSpeed()+boost);
    }
    else {
        entity->setSpeed(entity->getEntityBaseSpeed());
    }
}

