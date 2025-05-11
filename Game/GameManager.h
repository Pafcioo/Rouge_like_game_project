#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "Button.h"
#include "Player.h"
#include "Event.h"
#include "Map.h"
// The most important class of the game, that handles everything
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
    GameState currentGameState;
    sf::View defaultView;
    sf::View gameplayView;
public:
    GameManager();
    ~GameManager(){};
    void changeGameState(GameState newState);
    UIManager getUIManager();
    GameState getGameState() const;
    void changeGameplayViewBasedOnPlayer();
    void Play();
};
