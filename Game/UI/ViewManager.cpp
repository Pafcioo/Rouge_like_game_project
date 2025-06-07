#include "Game/UI/ViewManager.h"
#include "Game/GameManager.h"

// Initialize both views with standard 1280x720 resolution
ViewManager::ViewManager() {
    defaultView = sf::View(sf::FloatRect({0, 0}, {1280, 720}));
    gameplayView = sf::View(sf::FloatRect({0, 0}, {1280, 720}));
}

const sf::View& ViewManager::getDefaultView() const {
    return defaultView;
}

const sf::View& ViewManager::getGameplayView() const {
    return gameplayView;
}

// Set fixed default view for UI elements
void ViewManager::setDefaultView(std::shared_ptr<GameManager> gameManager)
{
    gameManager->getGameWindow().setView(defaultView);
}

// Set gameplay view that follows player with map boundary clamping
void ViewManager::setGameplayView(std::shared_ptr<GameManager> gameManager) {
    Entity* player = gameManager->getEntityManager().getPlayer();
    if (!player) return;

    sf::Vector2f playerPosition = player->getPosition();

    // If map exists, clamp camera to stay within map boundaries
    if (!gameManager->getMapManager().getCurrentMapLabel().empty()) {
        sf::Vector2f halfMapSize = gameManager->getMapManager().getCurrentMap().getSize() / 2.f;
        sf::Vector2f viewSize = gameplayView.getSize();
        sf::Vector2f halfViewSize = viewSize / 2.f;

        float clampedX = playerPosition.x;
        float clampedY = playerPosition.y;

        // Clamp X: prevent camera from showing beyond map edges
        clampedX = std::max(-halfMapSize.x + halfViewSize.x,
                            std::min(clampedX, halfMapSize.x - halfViewSize.x));

        // Clamp Y: prevent camera from showing beyond map edges
        clampedY = std::max(-halfMapSize.y + halfViewSize.y,
                            std::min(clampedY, halfMapSize.y - halfViewSize.y));

        gameplayView.setCenter({clampedX, clampedY});
    } else {
        // No map boundaries - freely follow player
        gameplayView.setCenter(playerPosition);
    }
    gameManager->getGameWindow().setView(gameplayView);
}