#include "Ability.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"

void Ability::update(float deltaTime) {
    if (currentCooldown <= 0) {
        isReady = true;
        isActive = false;
        currentCooldown = 0;
    }
    else {
        currentCooldown -= deltaTime;
        isReady = false;
    }
    if (currentDuration <= 0) {
        isActive = false;
        currentDuration = 0;
    }
    else {
        currentDuration -= deltaTime;
    }
}

void SprintAbility::influence(Entity *entity) {
    if (isActive) {
        std::cout << "Sprinting" << std::endl;
        entity->setSpeed(entity->getEntityBaseSpeed()+boost);
    }
    else {
        entity->setSpeed(entity->getEntityBaseSpeed());
    }
}