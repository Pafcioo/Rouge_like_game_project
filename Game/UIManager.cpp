#include <iostream>
#include "math.h"
#include "UIManager.h"
#include "GameManager.h"

UIManager::UIManager(GameManager& gameManager):gameManager_(gameManager){
    backgroundShape_.setFillColor(backgroundColor_);
    backgroundShape_.setSize(sf::Vector2f(1280.f, 720.f));
}

void UIManager::drawBackground(sf::RenderTarget& target, sf::RenderStates states){
    target.draw(backgroundShape_, states);
}

void UIManager::updateActiveUI(GameState newGameState) {
    // Push the current state to the stack if it's not already the top
    if (uiHistory_.empty() || uiHistory_.top() != newGameState) {
        uiHistory_.push(newGameState);
    }

    // Update the active state of all UIs
    for (auto& [state, container] : uiContainers_) {
        if (state == newGameState) {
            container->setIsUIActive(true); // Activate the container for the new state
        } else {
            container->setIsUIActive(false); // Deactivate all other containers
        }
    }
}

void UIManager::goBackToPreviousUI() {
    if (!uiHistory_.empty()) {
        uiHistory_.pop(); // Remove the current state
    }

    if (!uiHistory_.empty()) {
        GameState previousState = uiHistory_.top(); // Get the previous state
        updateActiveUI(previousState); // Activate the previous UI
        gameManager_.changeGameState(previousState);
    }
}

void UIManager::addUIContainer(GameState state, std::shared_ptr<UIContainer> container) {
    uiContainers_[state] = std::move(container);
}

void UIManager::drawUI(sf::RenderTarget& target, GameState currentState) {
    auto it = uiContainers_.find(currentState);
    if (it != uiContainers_.end() && it->second) {
        // Draw background UIs if the current UI allows it
        if (it->second->canHaveBackgroundUI()) {
            // Iterate through the stack and draw previous UIs
            std::stack<GameState> tempStack = uiHistory_; // Copy the stack
            std::vector<GameState> uisToDraw; // Store UIs to draw in order

            // Collect UIs to draw
            while (!tempStack.empty()) {
                GameState prevState = tempStack.top();
                tempStack.pop();

                // Skip the current state
                if (prevState == currentState) continue;

                auto prevIt = uiContainers_.find(prevState);
                if (prevIt != uiContainers_.end() && prevIt->second) {
                    uisToDraw.push_back(prevState);
                }
            }

            auto it = uisToDraw.rend();
            it--;
            auto prevIt = uiContainers_.find(*it);
            prevIt ->second->drawAll(target, sf::RenderStates::Default);

            // Draw the background for the current UI
            drawBackground(target, sf::RenderStates::Default);
        }

        // Draw the current UI
        it->second->drawAll(target, sf::RenderStates::Default);
    }
}

std::shared_ptr<UIContainer> UIManager::createUI(EventBus& eventBus, GameState state,sf::Font& font){
    auto container = std::make_shared<UIContainer>(state, eventBus, globalEventCooldownClock_);
    if (state == GameState::MainMenu) {
        container->createUIElement<Text>(
            sf::Vector2f(100.f,30.f),
            font,
            "Main Menu",
            48,
            sf::Color::White,
            "MainMenuTitle"
        );
        container->createUIElement<Button>(
            eventBus,
            "PlayTheGameButton",
            sf::Vector2f(100.f,50.f),
            sf::Vector2f(100.f,100.f),
            sf::Color::Black,
            "Play",
            font,
            24,
            [&](){
                gameManager_.changeGameState(GameState::Playing);
            }
        );
        container->createUIElement<Button>(
            eventBus,
            "OptionsButton",
            sf::Vector2f(100.f, 50.f),
            sf::Vector2f(100.f, 200.f),
            sf::Color::Black,
            "Options",
            font,
            24,
            [&](){
                std::cout<<"test";
                gameManager_.changeGameState(GameState::Options);
            }
        );
        container->createUIElement<Button>(
            eventBus,
            "QuitButton",
            sf::Vector2f(100.f, 50.f),
            sf::Vector2f(100.f, 300.f),
            sf::Color::Black,
            "Quit",
            font,
            24,
            [](){
                std::cout<<"Button clicked 3";
            }
        );
        container->createUIElement<Image>(
            "PlayerImage",
            0.3,
            sf::Vector2f(500.f,400.f),
            sf::degrees(0),
            "Assets/player.png"
        );
    }
    if (state == GameState::Options) {
        container->setCanHaveBackgroundUI(true);
        container->createUIElement<GameElement>(
            "BackgroundOption",
            sf::Vector2f(600,300),
            sf::Vector2f(640,360),
            sf::Color::Black,
            ShapeType::Rectangle,
            true
        );
        container->createUIElement<Button>(
            eventBus,
            "PlayTheGameButton",
            sf::Vector2f(100.f,100.f),
            sf::Vector2f(500.f,360.f),
            sf::Color::Green,
            "Play",
            font,
            12,
            [&](){
                std::cout<<"test";
                gameManager_.changeGameState(GameState::Playing);
            },
            true
        );
        container->createUIElement<Button>(
            eventBus,
            "OptionsButton",
            sf::Vector2f(100.f, 100.f),
            sf::Vector2f(600.f, 360.f),
            sf::Color::Blue,
            "Go back",
            font,
            12,
            [&](){
                gameManager_.getUIManager().goBackToPreviousUI();
            },
            true
        );
        container->createUIElement<Button>(
            eventBus,
            "OptionsButton",
            sf::Vector2f(100.f, 100.f),
            sf::Vector2f(700.f, 360.f),
            sf::Color::Blue,
            "Go back to main menu",
            font,
            12,
            [&](){
                gameManager_.changeGameState(GameState::MainMenu);
            },
            true
        );
    }
    else if (state == GameState::Playing) {
        container->createUIElement<GameElement>(
            "EnergyBar",
            sf::Vector2f(300.f, 30.f), // Corrected
            sf::Vector2f(50.f, 600.f), // Added size
            sf::Color::Red, // Added color
            ShapeType::Rectangle
        );
        container->createUIElement<GameElement>(
            "HealthBar",
            sf::Vector2f(300.f, 30.f), // Corrected
            sf::Vector2f(50.f, 650.f), // Added size
            sf::Color::Red, // Added color
            ShapeType::Rectangle
        );
        container->createUIElement<Button>(
            eventBus,
            "OptionsButton",
            sf::Vector2f(100.f, 50.f),
            sf::Vector2f(1000.f, 50.f),
            sf::Color::Black,
            "Options",
            font,
            12,
            [&](){
                gameManager_.changeGameState(GameState::Options);
            }
        );
    }
    container->subscribeToEvents();
    return container;
}

void UIManager::initAllUI(EventBus& eventBus, sf::Font& font)
{
    for (auto state : {GameState::MainMenu, GameState::Options, GameState::Paused, GameState::Playing}) {
        auto container = createUI(eventBus, state, font);
        addUIContainer(state, container);
    }
}

std::shared_ptr<UIContainer> UIManager::getUIContainer(GameState state) {
    auto it = uiContainers_.find(state);
    if (it != uiContainers_.end()) {
        return it->second;
    }
    return nullptr;
}