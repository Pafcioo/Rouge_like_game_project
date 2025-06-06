#include "Game/UI/ViewManager.h"

ViewManager::ViewManager() {
    // Initialize default view with a size of 1280x720
    defaultView = sf::View(sf::FloatRect({0, 0}, {1280, 720}));
    // Initialize gameplay view with the same size
    gameplayView = sf::View(sf::FloatRect({0, 0}, {1280, 720}));
}

const sf::View& ViewManager::getDefaultView() const {
    return defaultView;
}

const sf::View& ViewManager::getGameplayView() const {
    return gameplayView;
}

void ViewManager::setGameplayView(const sf::Vector2f& center, const sf::Vector2f& size) {
    gameplayView.setCenter(center);
    gameplayView.setSize(size);
}