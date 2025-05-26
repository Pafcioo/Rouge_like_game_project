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
    float getCooldown();
    float getCurrentCooldown();
    float getDuration();
    void setCooldown(float newCooldown);
    void setCurrentCooldown(float newCurrentCooldown);
    void setDuration(float newDuration);
    void activate();
    bool isAbilityActive();
    bool isAbilityReady();
    void setReady(bool newReady);
    std::string getAbilityName();
    void setAbilityName(std::string &newAbilityName);
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