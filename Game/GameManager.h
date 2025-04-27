#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"

class GameManager
{
private:
    sf::RenderWindow gameWindow;
    sf::Clock gameClock;
    EntityManager entityManager;

public:
    GameManager(){};
    ~GameManager(){};

    void Play();
};