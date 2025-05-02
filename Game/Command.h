#pragma once
#include <SFML/Graphics.hpp>

class Command
{
public:
    virtual ~Command() = default;
    virtual void executeCommand() = 0;
};

class MoveCommand : public Command
{
private:
    sf::Vector2f entityDirection;
public:
    MoveCommand(sf::Vector2f direction) : entityDirection(direction) {}
    void executeCommand() override;
};

class DashCommand : public Command
{
private:
    sf::Vector2f entityDirection;
public:
    DashCommand(sf::Vector2f direction) : entityDirection(direction) {}
    void executeCommand() override;
};


class AttackCommand : public Command
{
private:
    
public:
    AttackCommand(){}
    void executeCommand() override;
};

class ChangeViewCommand : public Command
{
private:
    
public:
    ChangeViewCommand(){}
    void executeCommand() override;
};
