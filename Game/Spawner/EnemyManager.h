#include <SFML/Graphics.hpp>
#include "Game/Enemy.h"

class EnemyManager
{
    private:
        std::vector<std::shared_ptr<Enemy>> vectorOfEnemies;
    public:
        EnemyManager() = default;
        ~EnemyManager() = default;
        void addEnemy(std::shared_ptr<Enemy> enemy);
};