#include "Game/States/GameState.h"

UIFactory::UIFactory()
{
    if (!font.openFromFile("Assets/Roboto_Condensed-Black.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
}

void InMenu::onEnter() const
{
    auto uiFactory = std::unique_ptr<MainMenuUI>();
    uiManager.addLayer(UILayer::State, uiFactory->createUI(eventBus));
}

void InMenu::onExit() const
{
    uiManager.removeLayer(UILayer::State);
}

void InMenu::update(float deltaTime) const
{

}

void MapChoosing::onEnter() const
{
    auto uiFactory = std::unique_ptr<MapChoiceUI>();
    uiManager.addLayer(UILayer::State, uiFactory->createUI(eventBus));
}

void MapChoosing::onExit() const
{
    uiManager.removeLayer(UILayer::State);
}

void MapChoosing::update(float deltaTime) const
{
    
}

void InGame::onEnter() const
{
    auto uiFactory = std::unique_ptr<InGameUI>();
    uiManager.addLayer(UILayer::State, uiFactory->createUI(eventBus));
}

void InGame::onExit() const
{
    uiManager.removeLayer(UILayer::State);
}

void InMenu::update(float deltaTime) const
{
    
}

void Paused::onEnter() const
{
    auto uiFactory = std::unique_ptr<PauseUI>();
    uiManager.addLayer(UILayer::State, uiFactory->createUI(eventBus));
}

void Paused::onExit() const
{
    uiManager.removeLayer(UILayer::State);
}

void Paused::update(float deltaTime) const
{
    
}

void GameOver::onEnter() const
{
    auto uiFactory = std::unique_ptr<GameOverUI>();
    uiManager.addLayer(UILayer::State, uiFactory->createUI(eventBus));
}

void GameOver::onExit() const
{
    uiManager.removeLayer(UILayer::State);
}

void GameOver::update(float deltaTime) const
{
    
}





