#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UIElement : public sf::Drawable {
private:
    std::string label_;
public:
    UIElement(const std::string& label = "") : label_(label) {}
    virtual ~UIElement() = 0;
    virtual void update(float deltaTime) = 0;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
    void setLabel(const std::string& label) { label_ = label; }
    const std::string& getLabel() const { return label_; }
};