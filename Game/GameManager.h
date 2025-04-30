#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "Button.h"

class GameManager
{
private:
    sf::RenderWindow gameWindow;
    sf::Clock gameClock;
    EntityManager entityManager;
    InputManager inputManager;
    std::shared_ptr<UIContainer> uiContainer;
    UIManager uiManager;
    sf::Font font;
public:
    GameManager();
    ~GameManager(){};

    void Play();
};