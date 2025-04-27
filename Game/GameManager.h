#pragma once
#include <SFML/Graphics.hpp>

class GameManager
{
private:
    sf::RenderWindow gameWindow;
    sf::Clock gameClock;
public:
    GameManager();
    ~GameManager();

    void Play();
};