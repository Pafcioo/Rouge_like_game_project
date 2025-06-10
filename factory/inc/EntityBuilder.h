#pragma once
#include <SFML/Graphics.hpp>
#include "../../entity/inc/Entity.h"
#include "EnemyFactory.h"
#include "../../logic/inc/SpawnRule.h"

class EntityBuilder
{
    protected:
        std::shared_ptr<GameplayInfoSource> gameplayInfo;
    public:
        virtual ~EntityBuilder(){};
        virtual void setWeapon(std::shared_ptr<Weapon> weapon) const = 0;
        virtual void setItem(std::shared_ptr<Item> item) const = 0;
        virtual void setAbility(std::shared_ptr<Ability> ability) const = 0;
        virtual void setDifficulty(std::shared_ptr<AIControllerDifficulty> difficulty) const = 0;
};

class EnemyBuilder : public EntityBuilder
{
    private:
        std::shared_ptr<Entity> enemy;
        std::shared_ptr<EntityFactory> enemyFactory;
    public:
        EnemyBuilder(std::shared_ptr<EntityFactory> factory) : enemyFactory(factory) {};
        ~EnemyBuilder() override = default;
        void setWeapon(std::shared_ptr<Weapon> weapon) const override;
        void setItem(std::shared_ptr<Item> item) const override;
        void setAbility(std::shared_ptr<Ability> ability) const override;
        void setDifficulty(std::shared_ptr<AIControllerDifficulty> difficulty) const override;
        void reset(std::shared_ptr<SpawnConfig> config, std::shared_ptr<GameplayInfoSource> gameplayInfoSource);
        std::shared_ptr<Entity> getEnemy() const;
};