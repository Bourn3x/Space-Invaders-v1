#include "Projectile.h"

// Resolution of projectile's png image: 9 x 22 px

Projectile::Projectile(sf::Vector2f position, sf::Texture &projectileTexture)
{
	sprite.setTexture(projectileTexture);
	sprite.setScale(0.7, 0.7);
	sprite.setOrigin(sf::Vector2f(9 / 2, 22 / 2));
	sprite.setPosition(position.x, position.y);
}

// Move the projectile upwards or downwards depending on who shot it
// Argument type = 0 when shot by player, type = 1 when shot by UFO
void Projectile::updateProjectileMovement(int type)
{
	type == 0 ? this->sprite.move(0, -this->movementSpeed) : this->sprite.move(0, this->movementSpeed);
}

