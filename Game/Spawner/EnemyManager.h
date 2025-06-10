#pragma once
#include <SFML/Graphics.hpp>
#include "Game/Enemy.h"

class EnemyManager
{
    private:
        std::vector<std::shared_ptr<Entity>> vectorOfEnemies;
        std::shared_ptr<GameplayInfoSource> gameplayInfo;
    public:
        EnemyManager() = default;
        ~EnemyManager() = default;
        void addEnemy(std::shared_ptr<Entity> enemy);
        void draw(sf::RenderTarget& target);
        void update(float deltaTime);
        std::vector<std::shared_ptr<Entity>> getEnemies();
        void setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfo);
};