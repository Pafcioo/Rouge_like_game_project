#include "GameManager.h"
#include <iostream>

#include "Entity.h"
#include "Player.h"
#include "Projectile.h"


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

void GameManager::changeGameState(GameState newState) {
    lastGameState = currentGameState; // Save the last game state before changing
    currentGameState = newState;
    
    if (newState == GameState::Options) {
        auto optionsContainer = uiManager.getUIContainer(GameState::Options);
        optionsContainer->overlayStates.clear();
        if (lastGameState == GameState::MainMenu) {
            optionsContainer->overlayStates.push_back(GameState::MainMenu);
        } else if (lastGameState == GameState::Playing) {
            optionsContainer->overlayStates.push_back(GameState::Playing);
        }
        // Dodaj kolejne przypadki jeśli chcesz
    }
}

void GameManager::updateInputManager() {
    inputManager.setUIContainer(uiManager.getUIContainer(this->getGameState())); 
}

void GameManager::handleInput(float deltaTime) {
    if (!inputManager.handleInput(gameWindow).empty()) {
        std::vector<std::unique_ptr<Command>> commands = inputManager.handleInput(gameWindow);
        for (auto& command : commands) {
            //std::cout << "Executing command..." << std::endl;
            command->executeCommand(entityManager.getPlayer(), deltaTime);
        }
    }
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
        handleInput(deltaTime);
        uiManager.drawUI(gameWindow, this->getGameState());
        entityManager.updateEntities(deltaTime);
        entityManager.drawEntities(gameWindow);
        gameWindow.display();
    }
}