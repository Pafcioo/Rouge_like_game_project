#pragma once
#include <SFML/Graphics.hpp>

class UIElement : public sf::Drawable {

public:
    UIElement(){};
    virtual ~UIElement() = 0;
    virtual void update(float deltaTime) = 0;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};