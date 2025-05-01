#include <iostream>
#include "UIManager.h"
#include "InputManager.h"

struct getStateCallbackFunctor {
    GameState state;
    std::function<GameState()> getStateCallback;
    bool operator()() const {
        return getStateCallback() == state;
    }
};

void UIManager::addUIContainer(GameState state, std::shared_ptr<UIContainer> container) {
    uiContainers_[state] = std::move(container);
}

void UIManager::drawUI(sf::RenderTarget& target, GameState state) {
    auto it = uiContainers_.find(state);
    if (it != uiContainers_.end() && it->second) {
        it->second->drawAll(target, sf::RenderStates::Default);
    }
}

std::shared_ptr<UIContainer> UIManager::createUI(
    GameState state,
    InputManager& inputManager,
    sf::Font& font,
    std::function<void(GameState)> changeStateCallback,
    std::function<GameState()> getStateCallback)
{
    auto container = std::make_shared<UIContainer>();

    if (state == GameState::MainMenu) {
        container->createButton(
            inputManager,
            {100.f, 100.f},
            font,
            "Play",
            [changeStateCallback]() {
                changeStateCallback(GameState::Playing);
                std::cout << "Playing state" << std::endl;
            },
            getStateCallbackFunctor{state, getStateCallback},
            {200.f, 50.f},
            sf::Color::Green,
            24
        );
        container->createButton(
            inputManager,
            {100.f, 200.f},
            font,
            "Options",
            [changeStateCallback]() {
                changeStateCallback(GameState::Options);
                std::cout << "Options state" << std::endl;
            },
            getStateCallbackFunctor{state, getStateCallback},
            {200.f, 50.f},
            sf::Color::Blue,
            24
        );
        container->createButton(
            inputManager,
            {100.f, 300.f},
            font,
            "Quit",
            []() {
                std::cout << "Quit game!" << std::endl;
            },
            getStateCallbackFunctor{state, getStateCallback},
            {200.f, 50.f},
            sf::Color::Red,
            24
        );
    }
    else if (state == GameState::Options) {
        container->createButton(
            inputManager,
            {720.f, 360.f},
            font,
            "Go back",
            [changeStateCallback]() {
                changeStateCallback(GameState::MainMenu);
                std::cout << "Button in options clicked!" << std::endl;
            },
            getStateCallbackFunctor{state, getStateCallback},
            {200.f, 50.f},
            sf::Color::Yellow,
            24
        );
        container->createButton(
            inputManager,
            {720.f, 460.f},
            font,
            "Smth",
            []() {
                std::cout << "Second options button clicked!" << std::endl;
            },
            getStateCallbackFunctor{state, getStateCallback},
            {200.f, 50.f},
            sf::Color::White,
            24
        );
    }
    // Dodaj kolejne else if dla innych GameState...

    return container;
}

void UIManager::initAllUI(InputManager& inputManager, sf::Font& font,
    std::function<void(GameState)> changeStateCallback,
    std::function<GameState()> getStateCallback)
{
    for (auto state : {GameState::MainMenu, GameState::Options, GameState::Paused}) {
        auto container = createUI(state, inputManager, font, changeStateCallback, getStateCallback);
        addUIContainer(state, container);
    }
}

UIContainer* UIManager::getUIContainer(GameState state) {
    auto it = uiContainers_.find(state);
    if (it != uiContainers_.end()) {
        return it->second.get();
    }
    return nullptr;
}