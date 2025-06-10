#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Entity;

class Ability {
public:
    Ability();
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
    SprintAbility();
    ~SprintAbility() override = default;
    void influence(Entity* entity) override;
private:
    float boost;
};