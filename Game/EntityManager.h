#pragma once
#include <SFML/Graphics.hpp>

class EntityManager
{
    public:
        EntityManager() = default;
        ~EntityManager() = default;

        void drawEntities(sf::RenderWindow& window);
};