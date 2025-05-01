#include <iostream>
#include "math.h"
#include "UIManager.h"
#include "InputManager.h"

struct getStateCallbackFunctor {
    GameState state;
    std::function<GameState()> getStateCallback;
    bool operator()() const {
        return getStateCallback() == state;
    }
};

struct ImageData {
    int index;
    std::string path;
    sf::Vector2i clipSize; // rozmiar wycinanego fragmentu
};

void UIManager::addUIContainer(GameState state, std::shared_ptr<UIContainer> container) {
    uiContainers_[state] = std::move(container);
}

void UIManager::drawUI(sf::RenderTarget& target, GameState state) {
    auto it = uiContainers_.find(state);
    if (it != uiContainers_.end() && it->second) {
        // Najpierw rysuj overlayStates (może być ich wiele)
        for (GameState overlay : it->second->overlayStates) {
            drawUI(target, overlay);
        }
        if(!it->second->overlayStates.empty()){
            drawBackground(target, sf::RenderStates::Default);
        }
        // Potem rysuj główny container
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
        container->createText(
            font,
            "Main Menu",
            {100.f, 25.f},
            48,
            sf::Color::White
        );
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
        container->createImage(
            "Assets/player.png",
            {1000.f, 300.f},
            {0.3f, 0.3f},
            sf::degrees(0)
        );
    }
    else if (state == GameState::Options) {
        container->createButton(
            inputManager,
            {640.f, 360.f},
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
            {640.f, 460.f},
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
    else if (state == GameState::Playing) {
        container->createText(
            font,
            "Playing",
            {100.f, 25.f},
            48,
            sf::Color::White
        );

        std::vector<ImageData> imagesData = {
            {0, "Assets/ability1.png", {500, 500}},
            {1, "Assets/ability2.png", {2000, 2000}},
            {2, "Assets/ability1.png", {500, 500}},
            {3, "Assets/ability2.png", {2000, 2000}},
            {4, "Assets/ability1.png", {500, 500}},
            {5, "Assets/ability2.png", {2000, 2000}}
            // ...
        };
        float sizeOfImageX = 50.f;
        float scale = 0.7f;
        float offset =sizeOfImageX * sqrt(2.f)* scale;
        sf::Vector2f leftPos = {70.f, 200.f};
        sf::Vector2f rightPos = {leftPos.x + offset, leftPos.y}; // np. 100px odstępu
        sf::Vector2f sizeOfImages = {sizeOfImageX, sizeOfImageX};
        sf::Angle angle = sf::degrees(45);

        for (size_t i = 0; i < imagesData.size(); ++i) {
            sf::Vector2f pos = (i % 2 == 0) ? leftPos : rightPos;
            pos.y += i * offset; // odstęp w pionie
            container->createImageWithSize(
                imagesData[i].path,
                pos,
                sizeOfImages,
                angle
            );
        }
    }
    // Dodaj kolejne else if dla innych GameState...

    return container;
}

void UIManager::initAllUI(InputManager& inputManager, sf::Font& font,
    std::function<void(GameState)> changeStateCallback,
    std::function<GameState()> getStateCallback)
{
    for (auto state : {GameState::MainMenu, GameState::Options, GameState::Paused, GameState::Playing}) {
        auto container = createUI(state, inputManager, font, changeStateCallback, getStateCallback);
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