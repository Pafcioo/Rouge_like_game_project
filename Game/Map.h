#include "SFML/Graphics.hpp"

class Map: public sf::Drawable
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f size;
public:
    Map(const std::string& texturePath, const sf::Vector2f& position, const sf::Vector2f& size)
        : position(position), size(size), texture(texturePath), sprite(texture)
    {
        sprite.setOrigin({texture.getSize().x / 2.f, texture.getSize().y / 2.f});
        sprite.setPosition(position);
        sprite.setScale({size.x / texture.getSize().x, size.y / texture.getSize().y});
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override
    {
        target.draw(sprite, states);
    }
    const sf::Vector2f& getPosition() const { return position; }
    const sf::Vector2f& getSize() const { return size; }
};