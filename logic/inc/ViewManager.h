#pragma once
#include <SFML/Graphics.hpp>
#include "../../core/inc/GameManager.h"

// Manages different camera views for UI and gameplay rendering
class ViewManager {
private:
    sf::View defaultView;   // Fixed view for UI elements
    sf::View gameplayView;  // Dynamic view that follows player

public:
    ViewManager();
    ~ViewManager() = default;
    
    // View getters
    const sf::View& getDefaultView() const;
    const sf::View& getGameplayView() const;
    
    // Apply views to the game window
    void setDefaultView(std::shared_ptr<GameManager> gameManager);
    void setGameplayView(std::shared_ptr<GameManager> gameManager);
};