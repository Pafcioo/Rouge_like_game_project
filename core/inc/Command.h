#pragma once
#include <SFML/Graphics.hpp>
#include "../../entity/inc/Entity.h"

class Command
{
public:
    virtual ~Command() = default;
    virtual void executeCommand(Entity* player, float deltaTime) = 0;
};

class MoveCommand : public Command
{
private:
    sf::Vector2f entityDirection;
public:
    MoveCommand(sf::Vector2f direction) : entityDirection(direction) {}
    void executeCommand(Entity* player, float deltaTime) override;
};

class DashCommand : public Command
{
private:
    sf::Vector2f entityDirection;
public:
    DashCommand(sf::Vector2f direction) : entityDirection(direction) {}
    void executeCommand(Entity* player, float deltaTime) override;
};


class AttackCommand : public Command
{
private:
    sf::Vector2f entityDirection;
public:
    AttackCommand(sf::Vector2f direction) : entityDirection(direction){}
    void executeCommand(Entity* player, float deltaTime) override;
};

class ChangeViewCommand : public Command
{
private:
    
public:
    ChangeViewCommand(){}
    void executeCommand(Entity* player, float deltaTime) override;
};
