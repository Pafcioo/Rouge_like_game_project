#include <iostream>
#include "UIManager.h"
#include "InputManager.h"

void UIManager::addUIContainer(GameState state, std::shared_ptr<UIContainer> container) {
    uiContainers_[state] = std::move(container);
}

void UIManager::drawUI(sf::RenderTarget& target, GameState state) {
    auto it = uiContainers_.find(state);
    if (it != uiContainers_.end() && it->second) {
        it->second->drawAll(target, sf::RenderStates::Default);
    }
}

void UIManager::initMainMenuUI(InputManager& inputManager, sf::Font& font, std::function<void(GameState)> changeStateCallback) {
    auto mainMenuContainer = std::make_shared<UIContainer>();
    auto button = std::make_unique<Button>(
        inputManager,
        sf::Vector2f(100.f, 100.f),
        font,
        sf::Vector2f(200.f, 50.f),
        sf::Color::Green,
        "Start",
        24
    );
    button->setCallback([changeStateCallback]() {
        changeStateCallback(GameState::Paused);
        std::cout << "Start button clicked!" << std::endl;
    });
    mainMenuContainer->addElement(std::move(button));
    addUIContainer(GameState::MainMenu, mainMenuContainer);
}

void UIManager::initOptionsUI(InputManager& inputManager, sf::Font& font, std::function<void(GameState)> changeStateCallback) {
    auto mainMenuContainer = std::make_shared<UIContainer>();
    auto button = std::make_unique<Button>(
        inputManager,
        sf::Vector2f(100.f, 200.f),
        font,
        sf::Vector2f(200.f, 50.f),
        sf::Color::Yellow,
        "Start",
        24
    );
    button->setCallback([changeStateCallback]() {
        changeStateCallback(GameState::MainMenu);
        std::cout << "Button clicked!" << std::endl;
    });
    mainMenuContainer->addElement(std::move(button));
    addUIContainer(GameState::Paused, mainMenuContainer);
}

UIContainer* UIManager::getUIContainer(GameState state) {
    auto it = uiContainers_.find(state);
    if (it != uiContainers_.end()) {
        return it->second.get();
    }
    return nullptr;
}