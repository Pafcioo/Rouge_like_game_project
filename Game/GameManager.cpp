#include "GameManager.h"
#include <iostream>


struct ChangeStateFunctor {
    GameManager* manager;
    void operator()(GameState newState) const {
        manager->changeGameState(newState);
        manager->updateInputManager();
    }
};


GameManager::GameManager() : font("Assets/Roboto_Condensed-Black.ttf")
{
    uiManager.initAllUI(inputManager, font, ChangeStateFunctor{this},[this]() {
        return this->getGameState();
    });
    inputManager.setUIContainer(uiManager.getUIContainer(this->getGameState()));
}


void GameManager::Play()
{
    // Create a window
    gameWindow.create(sf::VideoMode({1280, 720}), "SFML Game");
    gameWindow.setFramerateLimit(60);

    // Main loop
    while (gameWindow.isOpen())
    {
        sf::Time elapsed = gameClock.restart();
        float deltaTime = elapsed.asSeconds();
        if(deltaTime > 1/60.f) deltaTime = 1.f / 60.f; 
        gameWindow.clear();
        if(inputManager.handleInput(gameWindow)!=nullptr){
            inputManager.handleInput(gameWindow)->executeCommand();
        }
        uiManager.drawUI(gameWindow, this->getGameState());
        gameWindow.display();
    }
}