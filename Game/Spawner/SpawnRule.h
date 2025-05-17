#pragma once
#include <SFML/Graphics.hpp>
#include "Game/Event.h"

class AbstractSpawner;

class SpawnRule
{
protected:
    AbstractSpawner* spawner = nullptr;

public:
    virtual ~SpawnRule() = default;
    void setSpawner(AbstractSpawner* s);
    virtual void update(float deltaTime, std::shared_ptr<EventBus> eventBus) = 0;
};

class TimeBasedRule : public SpawnRule
{
public:
    struct TimeRule
    {
        float spawnTime;       // Time until the first spawn
        float spawnInterval;   // Interval between subsequent spawns
        float endTime;         // Time after which spawning stops
        std::string labelOfSpawner;
    };

private:
    TimeRule timeRule;

public:
    TimeBasedRule(TimeRule rule) : timeRule(rule) {}
    ~TimeBasedRule() override = default;

    void update(float deltaTime, std::shared_ptr<EventBus> eventBus) override;
};