#pragma once
#include <SFML/Graphics.hpp>

class AbstractSpawner;

class SpawnConfig
{
protected:
    int health;
    float speed;
    sf::Vector2f position;
    sf::Texture* texture; // Use pointer to avoid copying
public:
    SpawnConfig(int health, float speed, sf::Vector2f position, sf::Texture* texture)
        : health(health), speed(speed), position(position), texture(texture) {}
    virtual ~SpawnConfig() = default;
    int getHealth() const;
    float getSpeed() const;
    const sf::Vector2f& getPosition() const;
    sf::Texture* getTexture() const;
};

class EntitySpawnConfig : public SpawnConfig
{
public:
    EntitySpawnConfig(int health, float speed, sf::Vector2f position, sf::Texture* texture)
        : SpawnConfig(health, speed, position, texture) {}
    ~EntitySpawnConfig() override = default;
};

class SpawnRule
{
public:
    virtual ~SpawnRule() = default;
    virtual void update(float deltaTime, std::shared_ptr<AbstractSpawner> spawner, std::shared_ptr<SpawnConfig> config) = 0;
};

class TimeBasedRule : public SpawnRule
{
public:
    struct TimeRule
    {
        float spawnTime;       // Time until the first spawn
        float spawnInterval;   // Interval between subsequent spawns
        float endTime;         // Time after which spawning stops
    };
private:
    TimeRule timeRule;
public:
    TimeBasedRule(TimeRule rule) : timeRule(rule) {}
    ~TimeBasedRule() override = default;
    void update(float deltaTime, std::shared_ptr<AbstractSpawner> spawner, std::shared_ptr<SpawnConfig> config) override;
};