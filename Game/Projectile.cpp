#include <SFML/Graphics.hpp>
#include "Projectile.h"

void Projectile::update(float deltaTime) {
    projectileShape.move(projectileVelocity*deltaTime*projectileSpeed);
}
