#pragma once
#include <SFML/Graphics.hpp>
#include "Game/Enemy.h"

class EnemyManager
{
    private:
        std::vector<std::shared_ptr<Entity>> vectorOfEnemies;
    public:
        EnemyManager() = default;
        ~EnemyManager() = default;
        void addEnemy(std::shared_ptr<Entity> enemy);
        void drawEnemies(sf::RenderWindow& window);
        void update(float deltaTime);
        std::vector<std::shared_ptr<Entity>> getEnemies();
};