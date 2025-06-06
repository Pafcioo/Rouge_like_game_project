#include "Game/States/GameState.h"
#include "Game/Spawner/SpawnManager.h"

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

std::shared_ptr<UIContainer> GameState::getStateContainer() const {
    auto stateContainerIt = std::find_if(uiContainers.begin(), uiContainers.end(),
        [](const auto& pair) { return pair.first == UILayer::State; });

    return (stateContainerIt != uiContainers.end()) ? stateContainerIt->second : nullptr;
}

void GameState::onExit() 
{
    uiContainers.clear();
}

void GameState::update(float deltaTime) const
{
    gameManager->getInputManager().handleInput(deltaTime, eventBus, gameManager->getGameWindow());
    gameManager->getUIManager()->updateAll(deltaTime);    
}

void GameState::draw(sf::RenderTarget& target) const
{
    for (const auto& [layer, container] : uiContainers) {
        if (container) {
            container->draw(target, sf::RenderStates::Default);
        }
    }
}

// InMenu state set up
void InMenu::onEnter()
{
    auto uiFactory = std::make_unique<MainMenuUI>();
    uiContainers.push_back({UILayer::State, uiFactory->createUI(eventBus, gameManager->getFont())});
    
}

void InMenu::onExit() 
{
    GameState::onExit();
    for (auto& handle : subscriptions_)
        eventBus->unsubscribe(handle);
    subscriptions_.clear();
}

void InMenu::onPause() 
{
    getStateContainer()->setIsUIActive(false);
}

void InMenu::onResume() 
{
    getStateContainer()->setIsUIActive(true);
}

void InMenu::update(float deltaTime) const
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

// MapChoosing state set up
void MapChoosing::onEnter() 
{
    auto uiFactory = std::make_unique<MapChoiceUI>();
    uiContainers.push_back({UILayer::State, uiFactory->createUI(eventBus, gameManager->getFont())});
    gameManager->getMapManager().subscribeToEvents(eventBus);
}

void MapChoosing::onExit() 
{
    GameState::onExit();
    for (auto& handle : subscriptions_)
        eventBus->unsubscribe(handle);
    subscriptions_.clear();
}

void MapChoosing::update(float deltaTime) const
{
    GameState::update(deltaTime);
}

void MapChoosing::draw(sf::RenderTarget& target) const
{
    GameState::draw(target);
}

void MapChoosing::onPause()
{
    getStateContainer()->setIsUIActive(false);
}

void MapChoosing::onResume()
{
    getStateContainer()->setIsUIActive(true);
}

bool MapChoosing::isTranscendent() const 
{
    return false;
}

bool MapChoosing::isTransparent() const 
{
    return false;
}

// InGame state set up
void InGame::onEnter() 
{
    auto uiFactory = std::make_unique<InGameUI>();
    uiContainers.push_back({UILayer::State, uiFactory->createUI(eventBus, gameManager->getFont())});
    gameManager->getEntityManager().subscribeToEvents(eventBus);
    gameManager->getEntityManager().setActivity(true);
}

void InGame::onExit() 
{
    GameState::onExit();
    for (auto& handle : subscriptions_)
        eventBus->unsubscribe(handle);
    subscriptions_.clear();
}

void InGame::onPause()
{
    gameManager->getEntityManager().setActivity(false);
}

void InGame::onResume()
{
    gameManager->getEntityManager().setActivity(true);
}

void InGame::update(float deltaTime) const
{
    GameState::update(deltaTime);
    gameManager->getSpawnManager()->update(deltaTime);
    gameManager->getEntityManager().updateEntities(deltaTime);
    gameManager->getEnemyManager()->update(deltaTime);
}

void InGame::draw(sf::RenderTarget& target) const
{
    gameManager->getMapManager().drawMap(target);
    gameManager->getEntityManager().drawEntities(target);
    gameManager->getEnemyManager()->drawEnemies(target);
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

// Paused state set up
void Paused::onEnter() 
{
    auto uiFactory = std::make_unique<PauseUI>();
    auto container = uiFactory->createUI(eventBus, gameManager->getFont());
    container->subscribeToEvents(); // Let it manage itself
    uiContainers.push_back({UILayer::State, container});
}

void Paused::onExit() 
{
    GameState::onExit();
    for (auto& handle : subscriptions_)
        eventBus->unsubscribe(handle);
    subscriptions_.clear();
}

void Paused::onPause() {}
void Paused::onResume() {}

void Paused::update(float deltaTime) const
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

bool Paused::isTransparent() const 
{
    return true;
}

// GameOver state set up
void GameOver::onEnter() 
{
    auto uiFactory = std::make_unique<GameOverUI>();
    uiContainers.push_back({UILayer::State, uiFactory->createUI(eventBus, gameManager->getFont())});
}

void GameOver::onExit() 
{
    GameState::onExit();
    for (auto& handle : subscriptions_)
        eventBus->unsubscribe(handle);
    subscriptions_.clear();
}

void GameOver::onPause() {}
void GameOver::onResume() {}

void GameOver::update(float deltaTime) const
{
    GameState::update(deltaTime);
}

void GameOver::draw(sf::RenderTarget& target) const
{
    GameState::draw(target);
}

bool GameOver::isTranscendent() const 
{
    return true;
}

bool GameOver::isTransparent() const 
{
    return true;
}
