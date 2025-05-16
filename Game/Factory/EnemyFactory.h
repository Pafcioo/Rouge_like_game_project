#include <SFML/Graphics.hpp>
#include "Game/Enemy.h"

class EnemyFactory
{
    public:
        virtual ~EnemyFactory() = default;
        virtual std::shared_ptr<Enemy> createEnemy(const int health, const float speed, const sf::Vector2f position, const sf::Texture &texture) = 0;
};

class BasicEnemyFactory : public EnemyFactory
{
    public:
        std::shared_ptr<Enemy> createEnemy(const int health, const float speed, const sf::Vector2f position, const sf::Texture &texture) override;
};