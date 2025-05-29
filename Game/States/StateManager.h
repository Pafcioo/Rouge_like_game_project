#pragma once
#include <SFML/Graphics.hpp>
#include "Game/States/GameState.h"

class StateManager
{
    private:
        std::vector<std::shared_ptr<GameState>> stateStack;
        std::shared_ptr<UIManager> uiManager;
    public:
        StateManager(std::shared_ptr<UIManager> uiManager)
            : uiManager(uiManager) {};
        ~StateManager() = default;
        void pushState(std::shared_ptr<GameState> newState);
        void popState();
        void update(float deltaTime);
        std::shared_ptr<GameState> getCurrentState();
        void registerStateUI(const std::shared_ptr<GameState>& state);
        void unregisterStateUI(const std::shared_ptr<GameState>& state);
};