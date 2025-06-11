#include <iostream>
#include <SFML/Graphics.hpp>
#include "../inc/GameManager.h"

int main() {
    auto gameManager = std::make_shared<GameManager>();
    gameManager->Play();
    return 0;
}
