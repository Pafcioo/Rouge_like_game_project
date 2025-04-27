#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "InputManager.h"
#include "Button.h"

class GameManager
{
private:
    sf::RenderWindow gameWindow;
    sf::Clock gameClock;
    EntityManager entityManager;
    InputManager inputManager;
    Button startButton;
    sf::Font font;
public:
    GameManager()
        : font("Assets/Roboto_Condensed-Black.ttf"), startButton(sf::Vector2f(100, 100), sf::Vector2f(200, 50), sf::Color::Green, "Start", 24, font) {};
    ~GameManager(){};

    void Play();
};