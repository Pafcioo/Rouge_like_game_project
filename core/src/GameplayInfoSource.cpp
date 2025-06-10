#include <utility>
#include "../inc/GameplayInfoSource.h"

bool GameplayInfoSource::hasInfo(const std::string& key) const
{
    return gameplayInfo.find(key) != gameplayInfo.end();
}

void GameplayInfoSource::setGameplayInfo(std::unordered_map<std::string, std::any> gameplayInfoSource) {
    gameplayInfo = std::move(gameplayInfoSource);
}

std::unordered_map<std::string, std::any> GameplayInfoSource::getGameplayInfo() {
    return gameplayInfo;
}