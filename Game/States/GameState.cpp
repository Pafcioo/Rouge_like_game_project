#include "Game/States/GameState.h"

std::vector<std::pair<UILayer, std::shared_ptr<UIContainer>>> GameState::getStateUIContainers() const
{
    return uiContainers;
}

void GameState::onExit() 
{
    uiContainers.clear();
}

void InMenu::onEnter()
{
    auto uiFactory = std::unique_ptr<MainMenuUI>();
    uiContainers.push_back({UILayer::State, uiFactory->createUI(eventBus)});
}

void InMenu::onExit() 
{
    
}

void InMenu::update(float deltaTime) const
{

}

void MapChoosing::onEnter() 
{
    auto uiFactory = std::unique_ptr<MapChoiceUI>();
    uiContainers.push_back({UILayer::State, uiFactory->createUI(eventBus)});
}

void MapChoosing::onExit() 
{
    
}

void MapChoosing::update(float deltaTime) const
{
    
}

void InGame::onEnter() 
{
    auto uiFactory = std::unique_ptr<InGameUI>();
    uiContainers.push_back({UILayer::State, uiFactory->createUI(eventBus)});
}

void InGame::onExit() 
{
    
}

void InMenu::update(float deltaTime) const
{
    
}

void Paused::onEnter() 
{
    auto uiFactory = std::unique_ptr<PauseUI>();
    uiContainers.push_back({UILayer::State, uiFactory->createUI(eventBus)});
}

void Paused::onExit() 
{
    
}

void Paused::update(float deltaTime) const
{
    
}

void GameOver::onEnter() 
{
    auto uiFactory = std::unique_ptr<GameOverUI>();
    uiContainers.push_back({UILayer::State, uiFactory->createUI(eventBus)});
}

void GameOver::onExit() 
{
    
}

void GameOver::update(float deltaTime) const
{
    
}





