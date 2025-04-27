#include <iostream>
#include "Command.h"

void MoveCommand::executeCommand()
{
    // Placeholder for move command execution
    std::cout << "Executing move command with direction: (" << entityDirection.x << ", " << entityDirection.y << ")" << std::endl;
}

void DashCommand::executeCommand()
{
    // Placeholder for dash command execution
    std::cout << "Executing dash command with direction: (" << entityDirection.x << ", " << entityDirection.y << ")" << std::endl;
}

void AttackCommand::executeCommand()
{
    // Placeholder for attack command execution
    std::cout << "Executing attack command." << std::endl;
}

void ChangeViewCommand::executeCommand()
{
    // Placeholder for change view command execution
    std::cout << "Executing change view command." << std::endl;
}