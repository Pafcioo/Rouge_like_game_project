#include "Game/States/StateManager.h"

void StateManager::pushState(std::shared_ptr<GameState> newState)
{
    if (!stateStack.empty()) stateStack.back()->onPause();
    stateStack.push_back(newState);
    registerStateUI(newState);
    newState->onEnter();
}

void StateManager::popState()
{
    if (stateStack.empty()) return;
    auto top = stateStack.back();
    top->onExit();
    unregisterStateUI(top);
    stateStack.pop_back();
    if (!stateStack.empty()) stateStack.back()->onResume();
}

void StateManager::update(float deltaTime)
{
    for (int i = (int)stateStack.size() - 1; i >= 0; --i) {
        stateStack[i]->update(deltaTime);
        if (!stateStack[i]->isTranscendent())
            break;
    }
}

void StateManager::registerStateUI(const std::shared_ptr<GameState>& state) {
    for (auto& [layer, container] : state->getStateUIContainers()) {
        uiManager->addToLayer(layer, container);
    }
}

void StateManager::unregisterStateUI(const std::shared_ptr<GameState>& state) {
    for (auto& [layer, container] : state->getStateUIContainers()) {
        uiManager->removeFromLayer(layer, container);
    }
}