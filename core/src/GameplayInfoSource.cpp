#include <utility>
#include "../inc/GameplayInfoSource.h"

bool GameplayInfoSource::hasInfo(const std::string& key) const
{
    return gameplayInfo.find(key) != gameplayInfo.end();
}
