#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Game/States/GameState.h"

class GameManager;
class UIManager;
class EventBus;

class StateManager {
private:
    std::vector<std::shared_ptr<GameState>> stateStack;
    std::shared_ptr<UIManager> uiManager;
    std::shared_ptr<GameManager> gameManager;
    std::shared_ptr<EventBus> eventBus;

    // Deferred state changes
    bool shouldPop = false;
    std::shared_ptr<GameState> stateToPush = nullptr;

    void applyStateChanges();

public:
    StateManager(std::shared_ptr<UIManager> uiManager, std::shared_ptr<GameManager> gameManager, std::shared_ptr<EventBus> eventBus)
        : uiManager(uiManager), gameManager(gameManager), eventBus(eventBus) {}

    ~StateManager() = default;

    void subscribeToEvents();

    // Immediate methods (used internally)
    void pushState(std::shared_ptr<GameState> newState);
    void popState();

    // Deferred methods (safe to call from within GameState)
    void requestPushState(std::shared_ptr<GameState> newState);
    void requestPopState();

    void update(float deltaTime);
    void draw(sf::RenderTarget& target) const;

    std::shared_ptr<GameState> getCurrentState();
    void registerStateUI(const std::shared_ptr<GameState>& state);
    void unregisterStateUI(const std::shared_ptr<GameState>& state);
};
