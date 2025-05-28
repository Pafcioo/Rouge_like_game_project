#pragma once
#include <SFML/Graphics.hpp>
#include "Game/States/GameState.h"

class StateManager
{
    private:
        std::vector<std::shared_ptr<GameState>> stateStack;
    public:
        StateManager() = default;
        ~StateManager() = default;
        void pushState(std::shared_ptr<GameState> gameState);
        void popState();
        std::shared_ptr<GameState> getCurrentState();
        void update(float deltaTime);
};