#include "Ability.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"

float Ability::getCooldown() {return cooldown;}
float Ability::getCurrentCooldown() {return currentCooldown;}
float Ability::getDuration() {return duration;}
void Ability::setCooldown(float newCooldown) {cooldown = newCooldown;}
void Ability::setCurrentCooldown(float newCurrentCooldown) {currentCooldown = newCurrentCooldown;}
void Ability::setDuration(float newDuration) {duration = newDuration;}
void Ability::activate() {
    if (isReady) {
        isActive = true;
        currentCooldown = cooldown;
        currentDuration = duration;
    }
}
bool Ability::isAbilityActive() {return isActive;}
bool Ability::isAbilityReady() {return isReady;}
void Ability::setReady(bool newReady) {isReady = newReady;}
std::string Ability::getAbilityName() {return abilityName;}
void Ability::setAbilityName(std::string &newAbilityName) {abilityName = newAbilityName;}

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