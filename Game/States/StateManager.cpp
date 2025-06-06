#include "Game/States/StateManager.h"
#include "Game/States/GameState.h"
#include "Game/GameManager.h"
#include <iostream>
#include <algorithm>

void StateManager::pushState(std::shared_ptr<GameState> newState)
{
    if (!stateStack.empty()) stateStack.back()->onPause();

    // Configure the new state only once here
    newState->setEventBus(eventBus);
    newState->setUIManager(uiManager);
    newState->setGameManager(gameManager);

    stateStack.push_back(newState);
    newState->onEnter();
    registerStateUI(newState);
}


void StateManager::popState()
{
    if (stateStack.empty()) return;
    auto top = stateStack.back();
    unregisterStateUI(top);
    top->onExit();
    stateStack.pop_back();
    if (!stateStack.empty()) stateStack.back()->onResume();
}

void StateManager::requestPushState(std::shared_ptr<GameState> newState)
{
    stateToPush = newState;
}

void StateManager::requestPopState()
{
    shouldPop = true;
}

void StateManager::applyStateChanges()
{
    if (shouldPop) {
        popState();
        shouldPop = false;
    }

    if (stateToPush) {
        // Check if state already exists
        bool found = false;
        for (auto& state : stateStack) {
            if (state.get() == stateToPush.get()) {
                found = true;
                break;
            }
        }

        if (!found) {
            pushState(stateToPush);
        } else {
            // Move to top if already exists
            auto it = std::find_if(stateStack.begin(), stateStack.end(), [this](const std::shared_ptr<GameState>& state) {
                return state.get() == stateToPush.get();
            });
            if (it != stateStack.end()) {
                auto existingState = *it;
                stateStack.erase(it);
                if (!stateStack.empty()) stateStack.back()->onPause();
                stateStack.push_back(existingState);
                existingState->onResume();
            }
        }

        stateToPush = nullptr;
    }
}

void StateManager::update(float deltaTime)
{
    for (int i = static_cast<int>(stateStack.size()) - 1; i >= 0; --i) {
        if (i >= static_cast<int>(stateStack.size())) continue; // safety check if state was popped
        stateStack[i]->update(deltaTime);
        if (!stateStack[i]->isTranscendent())
            break;
    }

    applyStateChanges();
}

void StateManager::draw(sf::RenderTarget& target) const
{
    std::vector<const GameState*> toDraw;

    // Step 1: Collect states from top to bottom until non-transparent
    for (int i = static_cast<int>(stateStack.size()) - 1; i >= 0; --i) {
        toDraw.push_back(stateStack[i].get());
        if (!stateStack[i]->isTransparent())
            break;
    }

    // Step 2: Draw from bottom to top
    for (int i = static_cast<int>(toDraw.size()) - 1; i >= 0; --i) {
        toDraw[i]->draw(target);
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

void StateManager::subscribeToEvents() {
    eventBus->subscribe<ChangeStateEvent>([this](const ChangeStateEvent& event) {
        requestPushState(event.gameState); // use deferred push
    });
    eventBus->subscribe<RevertStateEvent>([this](const RevertStateEvent&) {
        requestPopState(); // use deferred pop
    });
}
