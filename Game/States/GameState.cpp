#include "Game/States/GameState.h"
#include "Game/Spawner/SpawnManager.h"
#include "Game/UI/ViewManager.h"
#include "Game/PlayerManager.h"
#include "Game/CollisionManager.h"
#include "Game/ProjectileManager.h"

// Base GameState implementation

void GameState::setEventBus(std::shared_ptr<EventBus> newEventBus) 
{
    eventBus = newEventBus;
}

void GameState::setUIManager(std::shared_ptr<UIManager> newUIManager) 
{
    uiManager = newUIManager;
}

void GameState::setGameManager(std::shared_ptr<GameManager> newGameManager) 
{
    gameManager = newGameManager;
}

std::vector<std::pair<UILayer, std::shared_ptr<UIContainer>>> GameState::getStateUIContainers() const
{
    return uiContainers;
}

// Find and return the main state UI container
std::shared_ptr<UIContainer> GameState::getStateContainer() const {
    auto stateContainerIt = std::find_if(uiContainers.begin(), uiContainers.end(),
        [](const auto& pair) { return pair.first == UILayer::State; });

    return (stateContainerIt != uiContainers.end()) ? stateContainerIt->second : nullptr;
}

// Clean up resources when exiting state
void GameState::onExit() 
{
    uiContainers.clear();
    for (auto& handle : subscriptions_)
        eventBus->unsubscribe(handle);
    subscriptions_.clear();
}

void GameState::onPause()
{
    getStateContainer()->setIsUIActive(false);
}

void GameState::onResume()
{
    getStateContainer()->setIsUIActive(true);
}

// Base update logic - handle input and UI
void GameState::update(float deltaTime)
{
    gameManager->getInputManager()->handleInput(deltaTime);
    // Update all UI containers in the state
    for (const auto& [layer, container] : uiContainers) {
        if (container) {
            container->update(deltaTime);
        }
    }
}

// Draw all UI containers
void GameState::draw(sf::RenderTarget& target) const
{
    for (const auto& [layer, container] : uiContainers) {
        if (container) {
            container->draw(target, sf::RenderStates::Default);
        }
    }
}

// InMenu state - Main menu implementation

void InMenu::onEnter()
{
   auto uiFactory = std::make_unique<MainMenuUI>();
   uiContainers.push_back({UILayer::State, uiFactory->createUI(
       eventBus, 
       gameManager->getFont(),
       gameManager->getGameplayInfoSource())});
}

void InMenu::onExit() 
{
   GameState::onExit();
}

void InMenu::onPause() 
{
   GameState::onPause();
}

void InMenu::onResume() 
{
   GameState::onResume();
}

void InMenu::update(float deltaTime)
{   
   GameState::update(deltaTime);
}

void InMenu::draw(sf::RenderTarget& target) const
{
   GameState::draw(target);
}

bool InMenu::isTranscendent() const 
{
    return false;
}

bool InMenu::isTransparent() const 
{
    return false;
}

// MapChoosing state - Map selection screen

void MapChoosing::onEnter() 
{
    auto uiFactory = std::make_unique<MapChoiceUI>();
    uiContainers.push_back({UILayer::State, uiFactory->createUI(
        eventBus, 
        gameManager->getFont(),
        gameManager->getGameplayInfoSource())});
    gameManager->getMapManager()->subscribeToEvents(eventBus);
}

void MapChoosing::onExit() 
{
    GameState::onExit();
}

void MapChoosing::update(float deltaTime)
{
    GameState::update(deltaTime);
}

void MapChoosing::draw(sf::RenderTarget& target) const
{
    GameState::draw(target);
}

void MapChoosing::onPause()
{
    GameState::onPause();
}

void MapChoosing::onResume()
{
    GameState::onResume();
}

bool MapChoosing::isTranscendent() const 
{
    return false;
}

bool MapChoosing::isTransparent() const 
{
    return false;
}

// InGame state - Active gameplay

InGame::InGame()
{
    gameTime = 0.f;
}

void InGame::onEnter() 
{
    auto uiFactory = std::make_unique<InGameUI>();
    uiContainers.push_back({UILayer::State, uiFactory->createUI(
        eventBus, 
        gameManager->getFont(),
        gameManager->getGameplayInfoSource())});
    gameManager->getPlayerManager()->subscribeToEvents();
    gameManager->getSpawnManager()->setUpStrategies(gameManager->getGameplayInfoSource(),gameManager->getEnemyManager(),gameManager->getMapManager());
}

void InGame::onExit() 
{
    GameState::onExit();
    gameManager->getPlayerManager()->unsubscribeToEvents();
}

void InGame::onPause()
{
    GameState::onPause();
    gameManager->getPlayerManager()->unsubscribeToEvents();
}

void InGame::onResume()
{
    GameState::onResume();
    gameManager->getPlayerManager()->subscribeToEvents();
}

// Update all game systems
void InGame::update(float deltaTime)
{
    GameState::update(deltaTime);
    gameTime+=deltaTime;
    gameManager->getGameplayInfoSource()->setInfo<float>("gameTime",gameTime);
    gameManager->getSpawnManager()->update(deltaTime);
    gameManager->getPlayerManager()->update(deltaTime);
    gameManager->getEnemyManager()->update(deltaTime);
    gameManager->getCollisionManager()->manageCollisions(gameManager, deltaTime);
    gameManager->getProjectileManager()->updateProjectiles(deltaTime);
}

void InGame::draw(sf::RenderTarget& target) const
{
    // Draw world elements with gameplay view (follows player)
    gameManager->getViewManager()->setGameplayView(gameManager);
    gameManager->getMapManager()->drawMap(target);
    gameManager->getProjectileManager()->drawProjectiles(target);
    gameManager->getPlayerManager()->draw(target);
    gameManager->getEnemyManager()->draw(target);
    
    // Draw UI elements with default view (fixed position)
    gameManager->getViewManager()->setDefaultView(gameManager);
    GameState::draw(target);
}

bool InGame::isTranscendent() const 
{
    return false;
}

bool InGame::isTransparent() const 
{
    return false;
}

// Paused state - Game pause overlay

void Paused::onEnter() 
{
    auto uiFactory = std::make_unique<PauseUI>();
    auto container = uiFactory->createUI(
        eventBus, 
        gameManager->getFont(),
        gameManager->getGameplayInfoSource());
    container->subscribeToEvents();
    uiContainers.push_back({UILayer::State, container});
}

void Paused::onExit() 
{
    GameState::onExit();
}

void Paused::onPause() 
{
    GameState::onPause();
}

void Paused::onResume() 
{
    GameState::onResume();
}

void Paused::update(float deltaTime)
{
    GameState::update(deltaTime);
}

void Paused::draw(sf::RenderTarget& target) const
{
    GameState::draw(target);
}

bool Paused::isTranscendent() const 
{
    return false;
}

// Transparent - shows underlying game state
bool Paused::isTransparent() const 
{
    return true;
}

// GameOver state - End game screen

void GameOver::onEnter() 
{
    auto uiFactory = std::make_unique<GameOverUI>();
    uiContainers.push_back({UILayer::State, uiFactory->createUI(
        eventBus, 
        gameManager->getFont(),
        gameManager->getGameplayInfoSource())});
}

void GameOver::onExit() 
{
    GameState::onExit();
}

void GameOver::onPause() 
{
    GameState::onPause();
}

void GameOver::onResume() 
{
    GameState::onResume();
}

void GameOver::update(float deltaTime)
{
    GameState::update(deltaTime);
}

void GameOver::draw(sf::RenderTarget& target) const
{
    GameState::draw(target);
}

// Transcendent - can be drawn over other states
bool GameOver::isTranscendent() const 
{
    return false;
}

bool GameOver::isTransparent() const 
{
    return true;
}