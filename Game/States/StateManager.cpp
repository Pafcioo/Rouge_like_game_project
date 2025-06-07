#include "Game/States/StateManager.h"
#include "Game/States/GameState.h"
#include "Game/GameManager.h"
#include <iostream>
#include <algorithm>

// Push new state onto stack, pausing current state
void StateManager::pushState(std::shared_ptr<GameState> newState)
{
    if (!stateStack.empty()) stateStack.back()->onPause();

    newState->setEventBus(eventBus);
    newState->setUIManager(uiManager);
    newState->setGameManager(gameManager);

    stateStack.push_back(newState);
    newState->onEnter();
    registerStateUI(newState);
}

// Remove top state and resume previous one
void StateManager::popState()
{
    if (stateStack.empty()) return;
    
    auto top = stateStack.back();
    unregisterStateUI(top);
    top->onExit();
    stateStack.pop_back();
    
    if (!stateStack.empty()) stateStack.back()->onResume();
}

// Queue state changes for safe deferred execution
void StateManager::requestPushState(std::shared_ptr<GameState> newState)
{
    stateToPush = newState;
}

void StateManager::requestPopState()
{
    shouldPop = true;
}

// Process queued state changes with smart state reuse
void StateManager::applyStateChanges()
{
    if (shouldPop) {
        popState();
        shouldPop = false;
    }

    if (stateToPush) {
        // Look for existing state of same type to reuse
        auto it = std::find_if(stateStack.begin(), stateStack.end(), 
            [this](const std::shared_ptr<GameState>& state) {
                return typeid(*state) == typeid(*this->stateToPush);
            });

        if (it != stateStack.end()) {
            // Reuse existing state by removing states above it
            auto foundState = *it;
            bool wasOnTop = (stateStack.back() == foundState);
            
            if (!wasOnTop && !stateStack.empty()) {
                stateStack.back()->onPause();
            }
            
            for (auto iter = it + 1; iter != stateStack.end(); ++iter) {
                (*iter)->onExit();
            }
            
            stateStack.erase(it + 1, stateStack.end());
            
            if (!wasOnTop) {
                foundState->onResume();
            }
            
        } else {
            pushState(stateToPush);
        }

        stateToPush = nullptr;
    }
}

// Update states from top down, stopping at non-transcendent states
void StateManager::update(float deltaTime)
{
    for (int i = static_cast<int>(stateStack.size()) - 1; i >= 0; --i) {
        if (i >= static_cast<int>(stateStack.size())) continue; // Safety check
        stateStack[i]->update(deltaTime);
        if (!stateStack[i]->isTranscendent())
            break;
    }

    applyStateChanges();
}

// Render transparent states with proper layering
void StateManager::draw(sf::RenderTarget& target) const
{
    std::vector<const GameState*> toDraw;

    // Collect states from top down until non-transparent
    for (int i = static_cast<int>(stateStack.size()) - 1; i >= 0; --i) {
        toDraw.push_back(stateStack[i].get());
        if (!stateStack[i]->isTransparent())
            break;
    }

    // Draw from bottom to top
    for (int i = static_cast<int>(toDraw.size()) - 1; i >= 0; --i) {
        toDraw[i]->draw(target);
    }
}

// Register/unregister state UI with layers
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

// Subscribe to state change events for deferred execution
void StateManager::subscribeToEvents() {
    eventBus->subscribe<ChangeStateEvent>([this](const ChangeStateEvent& event) {
        requestPushState(event.gameState);
    });
    eventBus->subscribe<RevertStateEvent>([this](const RevertStateEvent&) {
        requestPopState();
    });
}