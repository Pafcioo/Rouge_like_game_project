#include <SFML/Graphics.hpp>
#include "GameplayInfoSource.h"
#include "EnemyManager.h"
#include "Factory/EnemyFactory.h"
#include "Game/Event.h"
#include <unordered_map>

class AbstractSpawner
{
    public:
        virtual ~AbstractSpawner() = default;
        virtual void spawn(const std::string& enemyType) = 0;
    protected:
        std::shared_ptr<GameplayInfoSource> gameplayInfoSource;
        std::shared_ptr<EnemyManager> enemyManager;
        std::shared_ptr<EventBus> eventBus;
        std::unordered_map<std::string, std::shared_ptr<EnemyFactory>> factories;
};

class Spawner : public AbstractSpawner
{
    public:
        Spawner(std::shared_ptr<EventBus> eventBus,
                std::shared_ptr<GameplayInfoSource> gameplayInfoSource,
                std::shared_ptr<EnemyManager> enemyManager);
        ~Spawner() override = default;
        void spawn(const std::string& enemyType) override;
        void registerFactory(const std::string& enemyType, std::shared_ptr<EnemyFactory> factory);
};
