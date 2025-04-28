#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "InputManager.h"
#include "UIContainer.h"
#include "Button.h"

class GameManager
{
private:
    sf::RenderWindow gameWindow;
    sf::Clock gameClock;
    EntityManager entityManager;
    InputManager inputManager;
    UIContainer uiContainer;
    sf::Font font;
public:
    GameManager();
    ~GameManager(){};

    void Play();
};