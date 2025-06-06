#pragma once
#include <SFML/Graphics.hpp>

class ViewManager {
private:
    sf::View defaultView;
    sf::View gameplayView;
public:
    ViewManager();
    ~ViewManager() = default;
    const sf::View& getDefaultView() const;
    const sf::View& getGameplayView() const;
    void setGameplayView(const sf::Vector2f& center, const sf::Vector2f& size);
};
