#pragma once
#include <SFML/Graphics.hpp>
#include "Game/UI/UIManager.h"
#include "Game/Factory/UIFactory.h"
#include "Game/UI/UIContainer.h"
#include "Game/GameManager.h"

class GameState
{
protected:
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<UIManager> uiManager;
    std::shared_ptr<GameManager> gameManager;  // Change to shared_ptr
    std::vector<std::pair<UILayer, std::shared_ptr<UIContainer>>> uiContainers;
    GameState() = default;
public:
    virtual ~GameState() = default;
    virtual bool isTransparent() const = 0;
    virtual bool isTranscendent() const = 0;
    virtual void onEnter() = 0;
    virtual void onExit();
    virtual void onPause() = 0;
    virtual void onResume() = 0;
    virtual void update(float deltaTime) const;
    virtual void draw(sf::RenderTarget& target) const;
    virtual void setEventBus(std::shared_ptr<EventBus> newEventBus);
    virtual void setUIManager(std::shared_ptr<UIManager> newUIManager);
    virtual void setGameManager(std::shared_ptr<GameManager> newGameManager);
    virtual std::vector<std::pair<UILayer, std::shared_ptr<UIContainer>>> getStateUIContainers() const;
    std::shared_ptr<UIContainer> getStateContainer() const;
};

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
    void update(float deltaTime) const override;
    void draw(sf::RenderTarget& target) const override;
};

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
    void update(float deltaTime) const override;
    void draw(sf::RenderTarget& target) const override;
};

class InGame : public GameState
{
public:
    InGame() = default;
    ~InGame() = default;
    bool isTransparent() const override;
    bool isTranscendent() const override;
    void onEnter() override;
    void onExit() override;
    void onPause() override;
    void onResume() override;
    void update(float deltaTime) const override;
    void draw(sf::RenderTarget& target) const override;
};

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
    void update(float deltaTime) const override;
    void draw(sf::RenderTarget& target) const override;
};

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
    void update(float deltaTime) const override;
    void draw(sf::RenderTarget& target) const override;
};
