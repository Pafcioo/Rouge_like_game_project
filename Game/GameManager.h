#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "Button.h"
#include "Player.h"
#include "Event.h"
#include "Map.h"

class GameManager
{
private:
    sf::RenderWindow gameWindow;
    sf::Clock gameClock;
    EntityManager entityManager;
    InputManager inputManager;
    EventBus eventBus;
    UIManager uiManager;
    Map gameMap;
    sf::Font font;
    GameState currentGameState = GameState::MainMenu;
    sf::View defaultView = sf::View(sf::FloatRect({0,0},{1280, 720}));
    sf::View gameplayView = sf::View(sf::FloatRect({0,0},{1280, 720}));
public:
    GameManager();
    ~GameManager(){};
    void changeGameState(GameState newState);
    UIManager getUIManager();
    GameState getGameState() const { return currentGameState; }
    void changeGameplayViewBasedOnPlayerPosition()
    {
        Entity* player = entityManager.getPlayer(); // Assuming you have a method to get the player entity
        if (player)
        {
            sf::Vector2f playerPosition = player->getPosition();
            gameplayView.setCenter(playerPosition);
        }
    };

    void Play();
};
