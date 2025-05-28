#include <SFML/Graphics.hpp>
#include "Game/UI/UIManager.h"
#include "Game/Factory/UIFactory.h"

class GameState
{
protected:
    std::shared_ptr<EventBus> eventBus;
    UIManager& uiManager;
    GameState(UIManager& uiManager, std::shared_ptr<EventBus> eventBus)
        : uiManager(uiManager), eventBus(eventBus) {}
public:
    virtual ~GameState() = default;
    virtual void onEnter() const = 0;
    virtual void onExit() const = 0;
    virtual void update(float deltaTime) const = 0;
};

class InMenu : public GameState
{
public:
    InMenu(UIManager& uiManager, std::shared_ptr<EventBus> eventBus)
        : GameState(uiManager, eventBus) {}
    ~InMenu() = default;
    void onEnter() const override;
    void onExit() const override;
    void update(float deltaTime) const override;
};

class MapChoosing : public GameState
{
public:
    MapChoosing(UIManager& uiManager, std::shared_ptr<EventBus> eventBus)
        : GameState(uiManager, eventBus) {}
    void onEnter() const override;
    void onExit() const override;
    void update(float deltaTime) const override;
};

class InGame : public GameState
{
public:
    InGame(UIManager& uiManager, std::shared_ptr<EventBus> eventBus)
        : GameState(uiManager, eventBus) {}
    void onEnter() const override;
    void onExit() const override;
    void update(float deltaTime) const override;
};

class Paused : public GameState
{
public:
    Paused(UIManager& uiManager, std::shared_ptr<EventBus> eventBus)
        : GameState(uiManager, eventBus) {}
    void onEnter() const override;
    void onExit() const override;
    void update(float deltaTime) const override;
};

class GameOver: public GameState
{
public:
    GameOver(UIManager& uiManager, std::shared_ptr<EventBus> eventBus)
        : GameState(uiManager, eventBus) {}
    void onEnter() const override;
    void onExit() const override;
    void update(float deltaTime) const override;   
};
