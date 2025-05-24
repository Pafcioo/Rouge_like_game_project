#pragma once
#include "Entity.h"
#include "SFML/Graphics.hpp"

class Ability {
public:
    Ability() = default;
    virtual ~Ability() = default;
    void update(float deltaTime);
    virtual void influence(Entity* entity) = 0;
    float getCooldown() {return cooldown;}
    float getCurrentCooldown() {return currentCooldown;}
    float getDuration() {return duration;}
    void setCooldown(float newCooldown) {cooldown = newCooldown;}
    void setCurrentCooldown(float newCurrentCooldown) {currentCooldown = newCurrentCooldown;}
    void setDuration(float newDuration) {duration = newDuration;}
    void activate() {if (currentCooldown == 0) isActive = true;}
    void deactivate() {isActive = false;}
    bool isAbilityActive() {return isActive;}
    bool isAbilityReady() {return isReady;}
    void setReady(bool newReady) {isReady = newReady;}
    std::string getAbilityName() {return abilityName;}
    void setAbilityName(std::string &newAbilityName) {abilityName = newAbilityName;}
protected:
    float cooldown;
    float currentCooldown = 0;
    float duration;
    bool isActive;
    bool isReady;
    std::string abilityName;
};

class SprintAbility : public Ability {
public:
    SprintAbility() = default;
    ~SprintAbility() override = default;
    void influence(Entity* entity) override;
private:
    float boost;
};