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
    //std::shared_ptr<UIContainer> uiContainer;
    UIManager uiManager;
    sf::Font font;
    GameState currentGameState = GameState::MainMenu;
public:
    GameManager();
    ~GameManager(){};
    void changeGameState(GameState newState) { currentGameState = newState; }
    void updateInputManager() {
         inputManager.setUIContainer(uiManager.getUIContainer(this->getGameState())); 
        }
    GameState getGameState() const { return currentGameState; }

    void Play();
};