#include <SFML/Graphics.hpp>
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
        struct TimeRule;
    private:
        std::vector<TimeRule> timeRules;
    public:
        TimeBasedRule(std::vector<TimeRule> rules) : timeRules(std::move(rules)) {}
        ~TimeBasedRule() override = default;
        struct TimeRule
        {
            float spawnTime;
            std::string labelOfSpawner;
        };
        void update(float deltaTime, std::shared_ptr<EventBus> eventBus) override
        {
            for (auto& rule : timeRules)
            {
                rule.spawnTime -= deltaTime;
                if (rule.spawnTime <= 0)
                {
                    eventBus->publish(SpawnEvent({rule.labelOfSpawner}));
                    rule.spawnTime = 0; // Reset or remove the rule as needed
                }
            }
        }
};

class SpawnManager
{
    private:
        std::vector<SpawnRule> spawnRules;
        std::shared_ptr<AbstractSpawner> spawner;
        std::shared_ptr<EventBus> eventBus;
    public:
        SpawnManager(std::shared_ptr<EventBus> eventBus) : eventBus(eventBus) {};
        ~SpawnManager() = default;
        void addSpawnRule(std::shared_ptr<SpawnRule> spawnRule)
        {
            spawnRules.push_back(*spawnRule);
        }
        void update(float deltaTime)
        {
            for (auto& rule : spawnRules)
            {
                rule.update(deltaTime, eventBus);
            }
        }

};