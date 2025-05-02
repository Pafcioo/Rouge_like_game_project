#include <iostream>
#include "Command.h"

void MoveCommand::executeCommand(Entity* player, float deltaTime)
{
    player->move(entityDirection*deltaTime*player->getEntitySpeed());
    //std::cout << "Executing move command with direction: (" << entityDirection.x << ", " << entityDirection.y << ")" << std::endl;
}

void DashCommand::executeCommand(Entity* player, float deltaTime)
{
    // Placeholder for dash command execution
    //std::cout << "Executing dash command with direction: (" << entityDirection.x << ", " << entityDirection.y << ")" << std::endl;
}

void AttackCommand::executeCommand(Entity* player, float deltaTime)
{
    player->attack(entityDirection);
    //std::cout << "Executing attack command." << std::endl;
}

void ChangeViewCommand::executeCommand(Entity* player, float deltaTime)
{
    // Placeholder for change view command execution
    //std::cout << "Executing change view command." << std::endl;
}