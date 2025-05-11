#pragma once
#include <SFML/Graphics.hpp>
#include "UIContainer.h"
#include <unordered_map>
#include <memory>
#include <stack>

class GameManager;

enum class GameState
{
    MainMenu,
    Playing,
    Paused,
    Options,
    GameOver
};

class UIManager {
public:
    UIManager(GameManager& gameManager);
    ~UIManager() = default;
    // Method for adding a UI to unordered map of UIs
    void addUIContainer(GameState state, std::shared_ptr<UIContainer> container);
    // Method for initializaing all of the created UIs
    void initAllUI(EventBus& eventBus, sf::Font& font);
    // Method for creating a UI
    std::shared_ptr<UIContainer> createUI(EventBus& eventBus, GameState state, sf::Font& font);
    // Getter for UI
    std::shared_ptr<UIContainer> getUIContainer(GameState state);
    // Draw methods for UIs
    void drawUI(sf::RenderTarget& target, GameState state);
    void drawBackground(sf::RenderTarget& target, sf::RenderStates states);
    // Update methods for UI
    void updateActiveUI(GameState newGameState);
    void goBackToPreviousUI();
private:
    GameManager& gameManager_;
    std::unordered_map<GameState, std::shared_ptr<UIContainer>> uiContainers_;
    sf::RectangleShape backgroundShape_;
    sf::Color backgroundColor_ = sf::Color(0, 0, 0, 150);
    std::stack<GameState> uiHistory_; // Stack to track the history of opened UIs
    sf::Clock globalEventCooldownClock_; // Global clock to track event cooldown
    sf::Time globalEventCooldown_ = sf::milliseconds(200);
};
