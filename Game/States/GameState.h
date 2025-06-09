#pragma once
#include <SFML/Graphics.hpp>
#include "Game/UI/UIManager.h"
#include "Game/Factory/UIFactory.h"
#include "Game/UI/UIContainer.h"
#include "Game/GameManager.h"

// Base class for all game states with UI management and event handling
class GameState
{
protected:
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<UIManager> uiManager;
    std::shared_ptr<GameManager> gameManager;
    std::vector<std::pair<UILayer, std::shared_ptr<UIContainer>>> uiContainers;
    std::vector<SubscriptionHandle> subscriptions_;
    GameState() = default;

public:
    virtual ~GameState() = default;
    
    // State behavior properties
    virtual bool isTransparent() const = 0;  // Can see through to underlying states
    virtual bool isTranscendent() const = 0; // Other states can be updated
    
    // State lifecycle methods
    virtual void onEnter() = 0;
    virtual void onExit();
    virtual void onPause();
    virtual void onResume();
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderTarget& target) const;
    
    // Dependency injection
    virtual void setEventBus(std::shared_ptr<EventBus> newEventBus);
    virtual void setUIManager(std::shared_ptr<UIManager> newUIManager);
    virtual void setGameManager(std::shared_ptr<GameManager> newGameManager);
    
    // UI container access
    virtual std::vector<std::pair<UILayer, std::shared_ptr<UIContainer>>> getStateUIContainers() const;
    std::shared_ptr<UIContainer> getStateContainer() const;
};

// Main menu state - Entry point of the game
class InMenu : public GameState
{
public:
    InMenu() = default;
    ~InMenu() = default;
    bool isTransparent() const override;
    bool isTranscendent() const override;
    void onEnter() override;
    void onExit() override;
    void onPause() override;
    void onResume() override;
    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target) const override;
};

// Map selection state - Choose game level
class MapChoosing : public GameState
{
public:
    MapChoosing() = default;
    ~MapChoosing() = default;
    bool isTransparent() const override;
    bool isTranscendent() const override;
    void onEnter() override;
    void onExit() override;
    void onPause() override;
    void onResume() override;
    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target) const override;
};

// Active gameplay state - Main game loop
class InGame : public GameState
{
private:
    float gameTime;
public:
    InGame();
    ~InGame() = default;
    bool isTransparent() const override;
    bool isTranscendent() const override;
    void onEnter() override;
    void onExit() override;
    void onPause() override;
    void onResume() override;
    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target) const override;
};

// Pause overlay state - Game suspension with resume options
class Paused : public GameState
{
public:
    Paused() = default;
    ~Paused() = default;
    bool isTransparent() const override;
    bool isTranscendent() const override;
    void onEnter() override;
    void onExit() override;
    void onPause() override;
    void onResume() override;
    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target) const override;
};

// Game over state - End game results and options
class GameOver: public GameState
{
public:
    GameOver() = default;
    ~GameOver() = default;
    bool isTransparent() const override;
    bool isTranscendent() const override;
    void onEnter() override;
    void onExit() override;
    void onPause() override;
    void onResume() override;
    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target) const override;
};