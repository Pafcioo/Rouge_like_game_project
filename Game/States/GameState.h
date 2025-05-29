#include <SFML/Graphics.hpp>
#include "Game/UI/UIManager.h"
#include "Game/Factory/UIFactory.h"

class GameState
{
protected:
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<UIManager> uiManager;
    std::vector<std::pair<UILayer, std::shared_ptr<UIContainer>>> uiContainers;
    GameState(std::shared_ptr<EventBus> eventBus, std::shared_ptr<UIManager> uiManager)
        :eventBus(eventBus),uiManager(uiManager) {}
public:
    virtual ~GameState() = default;
    virtual bool isTransparent() const = 0;
    virtual bool isTranscendent() const = 0;
    virtual void onEnter() = 0;
    virtual void onExit();
    virtual void onPause() = 0;
    virtual void onResume() = 0;
    virtual void update(float deltaTime) const = 0;
    virtual std::vector<std::pair<UILayer, std::shared_ptr<UIContainer>>> getStateUIContainers() const;
};

class InMenu : public GameState
{
public:
    InMenu(std::shared_ptr<EventBus> eventBus, std::shared_ptr<UIManager> uiManager)
        : GameState(eventBus, uiManager) {}
    ~InMenu() = default;
    void onEnter() override;
    void onExit() override;
    void update(float deltaTime) const override;
};

class MapChoosing : public GameState
{
public:
    MapChoosing(std::shared_ptr<EventBus> eventBus, std::shared_ptr<UIManager> uiManager)
        : GameState(eventBus, uiManager) {}
    void onEnter() override;
    void onExit() override;
    void update(float deltaTime) const override;
};

class InGame : public GameState
{
public:
    InGame(std::shared_ptr<EventBus> eventBus, std::shared_ptr<UIManager> uiManager)
        : GameState(eventBus, uiManager) {}
    void onEnter() override;
    void onExit() override;
    void update(float deltaTime) const override;
};

class Paused : public GameState
{
public:
    Paused(std::shared_ptr<EventBus> eventBus, std::shared_ptr<UIManager> uiManager)
        : GameState(eventBus, uiManager) {}
    void onEnter() override;
    void onExit() override;
    void update(float deltaTime) const override;
};

class GameOver: public GameState
{
public:
    GameOver(std::shared_ptr<EventBus> eventBus, std::shared_ptr<UIManager> uiManager)
        : GameState(eventBus, uiManager) {}
    void onEnter() override;
    void onExit() override;
    void update(float deltaTime) const override;   
};
