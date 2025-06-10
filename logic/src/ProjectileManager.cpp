#include "../inc/ProjectileManager.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

std::vector<Projectile*> ProjectileManager::projectiles;

std::vector<Projectile*> ProjectileManager::getProjectiles() {
    return projectiles;
}

void ProjectileManager::updateProjectiles(float deltaTime) {
    for (auto &projectile : projectiles) {
        projectile->update(deltaTime);
        double distance = sqrt(pow(projectile->getShape().getPosition().x - projectile->getInitialPosition().x, 2) + pow(projectile->getShape().getPosition().y - projectile->getInitialPosition().y, 2));
        if (distance > 500) {
            projectile->deactivate();
        }
        projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
                       [](const Projectile* p) { return !p->isActive(); }),
        projectiles.end()
        );
    }
}

void ProjectileManager::drawProjectiles(sf::RenderTarget& target) {
    for (auto &projectile : projectiles) {
        target.draw(*projectile);
    }
}