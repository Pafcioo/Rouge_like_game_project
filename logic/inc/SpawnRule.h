#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class GameplayInfoSource;

class AbstractSpawner;

class EntityBuilder;

class EnemyBuilder;

class SpawnComponent;

class SpawnConfig
{
protected:
    sf::Vector2f position;
public:
    virtual ~SpawnConfig() = default;
    const sf::Vector2f& getPosition() const;
};

class EntitySpawnConfig : public SpawnConfig
{
protected:
    int health;
    float speed;
    sf::Texture* texture;
    std::vector<std::shared_ptr<SpawnComponent>> components;
public:
    EntitySpawnConfig(int health, float speed, sf::Vector2f position, sf::Texture* texture)
        : health(health), speed(speed), texture(texture)
    {
        this->position = position;
    }
    ~EntitySpawnConfig() = default;
    int getHealth() const;
    float getSpeed() const;
    sf::Texture* getTexture() const;
    virtual void configureBuilder(std::shared_ptr<EntityBuilder> builder, std::shared_ptr<GameplayInfoSource> gameplayInfoSource){};
    void add(std::shared_ptr<SpawnComponent> component);
    void remove(std::shared_ptr<SpawnComponent> component);
};

class EnemySpawnConfig : public EntitySpawnConfig
{
public:
    EnemySpawnConfig(int health, float speed, sf::Vector2f position, sf::Texture* texture)
        : EntitySpawnConfig(health, speed, position, texture) {}
    ~EnemySpawnConfig() = default;
    void configureBuilder(std::shared_ptr<EntityBuilder> builder, std::shared_ptr<GameplayInfoSource> gameplayInfoSource) override;
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
        float spawnTime;
        float spawnInterval;
        float endTime;
    };
private:
    TimeRule timeRule;
public:
    TimeBasedRule(TimeRule rule) : timeRule(rule) {}
    ~TimeBasedRule() override = default;
    void update(float deltaTime, std::shared_ptr<AbstractSpawner> spawner, std::shared_ptr<SpawnConfig> config) override;
};