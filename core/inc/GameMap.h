#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class GameMap: public sf::Drawable
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f size;
public:
    GameMap(const std::string& texturePath, const sf::Vector2f& position, const sf::Vector2f& size)
        : texture(texturePath), sprite(texture), position(position), size(size)
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
    void setPosition(const sf::Vector2f& newPosition) { position = newPosition; }
    void setSize(const sf::Vector2f& newSize) { size = newSize; }
    void setTexture(const std::string& texturePath)
    {
        std::cout<< "Loading texture from: " << texturePath << std::endl;
        if (!texture.loadFromFile(texturePath))
        {
            throw std::runtime_error("Failed to load texture");
        }
        else
        {
            std::cout<< "Texture loaded successfully" << std::endl;
        }
        sprite.setTexture(texture, true);
    }
    void setScale(const sf::Vector2f& scale)
    {
        sprite.setScale(scale);
    }
};