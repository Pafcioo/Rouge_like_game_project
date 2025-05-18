#include <SFML/Graphics.hpp>
#include "Game/Entity.h"
#include "EnemyFactory.h"
#include "Game/Spawner/SpawnRule.h"

class EntityBuilder
{
    public:
        virtual ~EntityBuilder(){};
        virtual void setWeapon() const = 0;
        virtual void setItem() const = 0;
        virtual void setAbility() const = 0;
};

class EnemyBuilder : public EntityBuilder
{
    private:
        std::shared_ptr<Entity> enemy;
        std::shared_ptr<EntityFactory> enemyFactory;
    public:
        EnemyBuilder(std::shared_ptr<EntityFactory> factory) : enemyFactory(factory) {};
        ~EnemyBuilder() override = default;
        void setWeapon() const override;
        void setItem() const override;
        void setAbility() const override;
        void reset(std::shared_ptr<SpawnConfig> config);
        std::shared_ptr<Entity> getEnemy() const { return enemy; }
};

// class PlayerBuilder : public EntityBuilder
// {
//     private:
//         std::shared_ptr<Entity> player;
//     public:
//         PlayerBuilder() = default;
//         ~PlayerBuilder() override = default;
//         void setWeapon() const override;
//         void setItem() const override;
//         void setAbility() const override;
//         std::shared_ptr<Entity> getPlayer() const { return player; }
// };