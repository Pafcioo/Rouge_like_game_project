#include "Game/States/StateManager.h"

void StateManager::pushState(std::shared_ptr<GameState> gameState)
{
    if (!stateStack.empty())
    {
        stateStack.back()->onExit();
    }
    stateStack.push_back(gameState);
    stateStack.back()->onEnter();
}

void StateManager::popState()
{
    if (!stateStack.empty()) {
        stateStack.back()->onExit();
        stateStack.pop_back();
    }
    if (!stateStack.empty())
        stateStack.back()->onEnter();  // opcjonalne
}

void StateManager::update(float deltaTime)
{
    if (auto state = getCurrentState())
        state->update(deltaTime);
}
