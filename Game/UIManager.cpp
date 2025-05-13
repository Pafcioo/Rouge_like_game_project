#include <iostream>
#include "math.h"
#include "UIManager.h"
#include "GameManager.h"

// In deafault constructor 
// gameManager is needed for changing the game state
UIManager::UIManager(GameManager& gameManager):gameManager_(gameManager){
    backgroundShape_.setFillColor(backgroundColor_);
    backgroundShape_.setSize(sf::Vector2f(1280.f, 720.f));
}

void UIManager::drawBackground(sf::RenderTarget& target, sf::RenderStates states){
    target.draw(backgroundShape_, states);
}

// Based on new state of the game, all previous UIs are deactivated but they could still be drawn in the background
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
// Method for going back to previous UI, so the button don't need the info to where go back, just go to previous one
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

// Method for adding UIs, because UIManager has a map for that, it is used later in createUI method
void UIManager::addUIContainer(GameState state, std::shared_ptr<UIContainer> container) {
    uiContainers_[state] = std::move(container);
}

void UIManager::drawUI(sf::RenderTarget& target, GameState currentState) {
    auto it = uiContainers_.find(currentState);
    if (it != uiContainers_.end() && it->second) {
        // // Draw background UIs if the current UI allows it
        // if (it->second->canHaveBackgroundUI()) {
        //     // Iterate through the stack and draw previous UIs
        //     std::stack<GameState> tempStack = uiHistory_; // Copy the stack
        //     std::vector<GameState> uisToDraw; // Store UIs to draw in order

        //     // Collect UIs to draw
        //     while (!tempStack.empty()) {
        //         GameState prevState = tempStack.top();
        //         tempStack.pop();

        //         // Skip the current state
        //         if (prevState == currentState) continue;

        //         auto prevIt = uiContainers_.find(prevState);
        //         if (prevIt != uiContainers_.end() && prevIt->second) {
        //             uisToDraw.push_back(prevState);
        //         }
        //     }
        //     // Draw only the last one in the background
        //     auto it = uisToDraw.rend();
        //     it--;
        //     auto prevIt = uiContainers_.find(*it);
        //     prevIt ->second->drawAll(target, sf::RenderStates::Default);

        //     // Draw the background for the current UI
        //     drawBackground(target, sf::RenderStates::Default);
        // }

        // Draw the current UI
        it->second->drawAll(target, sf::RenderStates::Default);
    }
}

// It is very important method for creating UIs. For the appropriate game state the elements of UI are created using generic method createUIElement 
std::shared_ptr<UIContainer> UIManager::createUI(EventBus& eventBus, GameState state,sf::Font& font){
    auto container = std::make_shared<UIContainer>(state, eventBus, globalEventCooldownClock_);
    if (state == GameState::MainMenu) {
        container->createUIElement<Text>(
            sf::Vector2f(100.f,30.f), //Position
            font,
            "Main Menu", //Text
            48, //Character size
            sf::Color::White, // Color of font
            "MainMenuTitle" // Label, used later for finding the element
        );
        container->createUIElement<Button>(
            eventBus, // event bus for subscribing and publishing events
            "PlayTheGameButton", //Label
            sf::Vector2f(100.f,50.f), // Position
            sf::Vector2f(100.f,100.f), // Size
            sf::Color::White, // Background color
            "Play", //Text
            font,
            24, //Character size
            [&](){
                gameManager_.changeGameState(GameState::ChooseMap); //Action of the button
            }
        );
        container->createUIElement<Button>(
            eventBus,
            "OptionsButton",
            sf::Vector2f(100.f, 50.f),
            sf::Vector2f(100.f, 200.f),
            sf::Color::White,
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
            "MapChooseButton",
            sf::Vector2f(100.f, 50.f),
            sf::Vector2f(100.f, 300.f),
            sf::Color::White,
            "Choose map",
            font,
            24,
            [&](){
                gameManager_.changeGameState(GameState::ChooseMap);
            }
        );
        container->createUIElement<Button>(
            eventBus,
            "QuitButton",
            sf::Vector2f(100.f, 50.f),
            sf::Vector2f(100.f, 400.f),
            sf::Color::White,
            "Quit",
            font,
            24,
            [](){
                std::cout<<"Button clicked 3";
            }
        );
        container->createUIElement<Image>(
            "PlayerImage", //Label
            0.4, //Scale or target size(sf::Vector2f)
            sf::Vector2f(840.f,360.f), // Position
            sf::degrees(0), // Rotation
            "Assets/player.png" //Path to texture
        );
    }
    if (state == GameState::Options) {
        container->setCanHaveBackgroundUI(true);
        container->createUIElement<GameElement>(
            "BackgroundOption", // Label
            sf::Vector2f(600,300), // Position
            sf::Vector2f(640,360), // Size
            sf::Color::Black, // Background color
            ShapeType::Rectangle, //Type of shape
            true // Centered origin
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
                gameManager_.changeGameState(GameState::Playing);
            },
            true //Centered origin
        );
        container->createUIElement<Button>(
            eventBus,
            "OptionsButton",
            sf::Vector2f(100.f, 100.f),
            sf::Vector2f(640.f, 360.f),
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
            sf::Vector2f(780.f, 360.f),
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
            sf::Vector2f(300.f, 30.f),
            sf::Vector2f(50.f, 600.f),
            sf::Color::Red,
            ShapeType::Rectangle
        );
        container->createUIElement<GameElement>(
            "HealthBar",
            sf::Vector2f(300.f, 30.f),
            sf::Vector2f(50.f, 650.f),
            sf::Color::Red,
            ShapeType::Rectangle
        );
        container->createUIElement<Button>(
            eventBus,
            "OptionsButton",
            sf::Vector2f(100.f, 50.f),
            sf::Vector2f(1100.f, 50.f),
            sf::Color::White,
            "Options",
            font,
            12,
            [&](){
                gameManager_.changeGameState(GameState::Options);
            }
        );
    }
    else if (state == GameState::ChooseMap) {
        container->createUIElement<Button>(
            eventBus,
            "MapButton1",
            sf::Vector2f(100.f, 100.f),
            sf::Vector2f(500.f, 360.f),
            sf::Color::White,
            "Desert Strike",
            font,
            24,
            [&](){
                gameManager_.getMapManager().setMap("Desert Strike");
                gameManager_.changeGameState(GameState::Playing);
            },
            true
        );
        container->createUIElement<Button>(
            eventBus,
            "MapButton1",
            sf::Vector2f(100.f, 100.f),
            sf::Vector2f(640.f, 360.f),
            sf::Color::White,
            "Forest Valley",
            font,
            24,
            [&](){
                gameManager_.getMapManager().setMap("Forest Valley");
                gameManager_.changeGameState(GameState::Playing);
            },
            true
        );
        container->createUIElement<Button>(
            eventBus,
            "MapButton1",
            sf::Vector2f(100.f, 100.f),
            sf::Vector2f(780.f, 360.f),
            sf::Color::White,
            "Castle",
            font,
            24,
            [&](){
                gameManager_.getMapManager().setMap("Castle");
                gameManager_.changeGameState(GameState::Playing);
            },
            true
        );
    }
    // At the end UI subscribe to all events(hover effect, arrow keys, mouse click etc.)
    container->subscribeToEvents();
    return container;
}

void UIManager::initAllUI(EventBus& eventBus, sf::Font& font)
{
    for (auto state : {GameState::MainMenu, GameState::Options, GameState::Paused, GameState::Playing, GameState::ChooseMap}) {
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