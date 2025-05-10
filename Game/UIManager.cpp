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

void UIManager::updateActiveUI(GameState currentGameState) {
    for (auto& [state, container] : uiContainers_) {
        if (state == currentGameState) {
            container->setIsUIActive(true); // Activate the container for the current state
        } else {
            container->setIsUIActive(false); // Deactivate all other containers
        }
    }
}

void UIManager::addUIContainer(GameState state, std::shared_ptr<UIContainer> container) {
    uiContainers_[state] = std::move(container);
}

void UIManager::drawUI(sf::RenderTarget& target, GameState state) {
    auto it = uiContainers_.find(state);
    if (it != uiContainers_.end() && it->second) {
        // Draw background UIs if allowed
        if (it->second->canHaveBackgroundUI()) {
            for (auto& [prevState, container] : uiContainers_) {
                if (prevState != state && container) {
                    container->drawAll(target, sf::RenderStates::Default);
                }
            }
            drawBackground(target, sf::RenderStates::Default);
        }
    // Draw the current UI
    it->second->drawAll(target, sf::RenderStates::Default);
    }
}

std::shared_ptr<UIContainer> UIManager::createUI(EventBus& eventBus, GameState state,sf::Font& font, bool canHaveBackgroundUI){
    auto container = std::make_shared<UIContainer>(state, eventBus, canHaveBackgroundUI, globalEventCooldownClock_);
    if (state == GameState::MainMenu) {
        container->createUIElement<Text>(
            sf::Vector2f(50.f,100.f),
            font,
            "Main Menu",
            24,
            sf::Color::White,
            "MainMenuTitle"
        );
        container->createUIElement<Button>(
            eventBus,
            "PlayTheGameButton",
            sf::Vector2f(100.f,50.f),
            sf::Vector2f(100.f,100.f),
            sf::Color::Green,
            "Play",
            font,
            12,
            [&](){
                gameManager_.changeGameState(GameState::Playing);
            }
        );
        container->createUIElement<Button>(
            eventBus,
            "OptionsButton",
            sf::Vector2f(100.f, 50.f),
            sf::Vector2f(100.f, 200.f),
            sf::Color::Blue,
            "Options",
            font,
            12,
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
            sf::Color::Blue,
            "Quit",
            font,
            12,
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
        container->createUIElement<Button>(
            eventBus,
            "PlayTheGameButton",
            sf::Vector2f(100.f,50.f),
            sf::Vector2f(100.f,100.f),
            sf::Color::Green,
            "Play",
            font,
            12,
            [&](){
                std::cout<<"test";
                gameManager_.changeGameState(GameState::Playing);
            }
        );
        container->createUIElement<Button>(
            eventBus,
            "OptionsButton",
            sf::Vector2f(100.f, 50.f),
            sf::Vector2f(100.f, 200.f),
            sf::Color::Blue,
            "Go back to menu",
            font,
            12,
            [&](){
                gameManager_.changeGameState(GameState::MainMenu);
            }
        );
    }
    else if (state == GameState::Playing) {
        container->createUIElement<GameElement>(
            "HealthBar",
            sf::Vector2f(100.f, 600.f), // Corrected
            sf::Vector2f(200.f, 20.f), // Added size
            sf::Color::Red, // Added color
            ShapeType::Rectangle
        );
        container->createUIElement<Button>(
            eventBus,
            "OptionsButton",
            sf::Vector2f(100.f, 50.f),
            sf::Vector2f(100.f, 200.f),
            sf::Color::Blue,
            "Go back to menu",
            font,
            12,
            [&](){
                gameManager_.changeGameState(GameState::MainMenu);
            }
        );
    }
    container->subscribeToEvents();
    return container;
}

void UIManager::initAllUI(EventBus& eventBus, sf::Font& font)
{
    for (auto state : {GameState::MainMenu, GameState::Options, GameState::Paused, GameState::Playing}) {
        auto container = createUI(eventBus, state, font, false);
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