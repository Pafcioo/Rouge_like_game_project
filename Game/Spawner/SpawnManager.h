#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Spawner.h"
#include "Game/Event.h"

class SpawnRule
{
    public:
        virtual ~SpawnRule() = default;
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
    std::vector<TimeRule> timeRules;

public:
    TimeBasedRule(std::vector<TimeRule> rules) : timeRules(std::move(rules)) {}
    ~TimeBasedRule() override = default;

    void update(float deltaTime, std::shared_ptr<EventBus> eventBus) override
    {
        for (auto& rule : timeRules)
        {
            rule.spawnTime -= deltaTime;
            rule.endTime -= deltaTime;

            // Stop processing this rule if endTime has passed
            if (rule.endTime <= 0)
            {
                continue;
            }

            // Check if it's time to spawn
            if (rule.spawnTime <= 0)
            {
                // Publish a spawn event
                eventBus->publish(SpawnEvent({rule.labelOfSpawner}));

                // Reset the spawn time to the interval
                rule.spawnTime += rule.spawnInterval;
            }
        }

        // Optionally, remove rules that have expired
        timeRules.erase(
            std::remove_if(timeRules.begin(), timeRules.end(),
                           [](const TimeRule& rule) { return rule.endTime <= 0; }),
            timeRules.end());
    }
};

class SpawnManager
{
    private:
        std::vector<std::shared_ptr<SpawnRule>> spawnRules;
        std::shared_ptr<AbstractSpawner> spawner;
        std::shared_ptr<EventBus> eventBus;
    public:
        SpawnManager(std::shared_ptr<EventBus> eventBus) : eventBus(eventBus) {};
        ~SpawnManager() = default;
        void addSpawnRule(std::shared_ptr<SpawnRule> spawnRule)
        {
            spawnRules.push_back(std::move(spawnRule));
        }
        void setSpawner(std::shared_ptr<AbstractSpawner> spawner)
        {
            this->spawner = spawner;
        }
        void update(float deltaTime)
        {
            for (auto& rule : spawnRules)
            {
                rule->update(deltaTime, eventBus);
            }
        }

};