#include <iostream>
#include <SFML/Graphics.hpp>
#include "../inc/Entity.h"
#include "../inc/Ability.h"

// Initialize ability in ready state
Ability::Ability() 
{
    isActive = false;
    isReady = true;
    currentCooldown = 0;
    currentDuration = 0;
}

// Getters
float Ability::getCooldown() 
{
    return cooldown;
}

float Ability::getCurrentCooldown() 
{
    return currentCooldown;
}

float Ability::getDuration() 
{
    return duration;
}

bool Ability::isAbilityActive() 
{
    return isActive;
}

bool Ability::isAbilityReady() 
{
    return isReady;
}

std::string Ability::getAbilityName() 
{
    return abilityName;
}

// Setters
void Ability::setCooldown(float newCooldown) 
{
    cooldown = newCooldown;
}

void Ability::setCurrentCooldown(float newCurrentCooldown) 
{
    currentCooldown = newCurrentCooldown;
}

void Ability::setDuration(float newDuration) 
{
    duration = newDuration;
}

void Ability::setReady(bool newReady) 
{
    isReady = newReady;
}

void Ability::setAbilityName(std::string &newAbilityName) 
{
    abilityName = newAbilityName;
}

// Activate ability if ready
void Ability::activate() 
{
    if (isReady) 
    {
        isActive = true;
        currentCooldown = cooldown;
        currentDuration = duration;
    }
}

// Update cooldown and duration timers
void Ability::update(float deltaTime) 
{
    if (currentCooldown <= 0) 
    {
        isReady = true;
        isActive = false;
        currentCooldown = 0;
    }
    else 
    {
        currentCooldown -= deltaTime;
        isReady = false;
    }
    
    if (currentDuration <= 0) 
    {
        isActive = false;
        currentDuration = 0;
    }
    else 
    {
        currentDuration -= deltaTime;
    }
}

// Sprint ability constructor
SprintAbility::SprintAbility() 
{
    cooldown = 10.f;
    duration = 1.f;
    boost = 200.f;
}

// Apply speed boost when active
void SprintAbility::influence(Entity *entity) 
{
    if (isActive) 
    {
        entity->setSpeed(entity->getEntityBaseSpeed()+boost);
    }
    else 
    {
        entity->setSpeed(entity->getEntityBaseSpeed());
    }
}