#pragma once
#include "SFML/Graphics.hpp"

class Entity;

class Ability {
public:
    Ability() {
        isActive = false;
        isReady = true;
        currentCooldown = 0;
        currentDuration = 0;
    }
    virtual ~Ability() = default;
    void update(float deltaTime);
    virtual void influence(Entity* entity) = 0;
    float getCooldown() {return cooldown;}
    float getCurrentCooldown() {return currentCooldown;}
    float getDuration() {return duration;}
    void setCooldown(float newCooldown) {cooldown = newCooldown;}
    void setCurrentCooldown(float newCurrentCooldown) {currentCooldown = newCurrentCooldown;}
    void setDuration(float newDuration) {duration = newDuration;}
    void activate() {
        if (isReady) {
            isActive = true;
            currentCooldown = cooldown;
            currentDuration = duration;
        }
    }
    void deactivate() {isActive = false;}
    bool isAbilityActive() {return isActive;}
    bool isAbilityReady() {return isReady;}
    void setReady(bool newReady) {isReady = newReady;}
    std::string getAbilityName() {return abilityName;}
    void setAbilityName(std::string &newAbilityName) {abilityName = newAbilityName;}
protected:
    float cooldown;
    float currentCooldown;
    float duration;
    float currentDuration;
    bool isActive;
    bool isReady;
    std::string abilityName;
};

class SprintAbility : public Ability {
public:
    SprintAbility() {
        cooldown = 10.f;
        duration = 1.f;
        boost = 200.f;
    };
    ~SprintAbility() override = default;
    void influence(Entity* entity) override;
private:
    float boost;
};