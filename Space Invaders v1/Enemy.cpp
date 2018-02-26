#include "Enemy.h"

// Resolution for aliens sprite sheet: 198 x 54 px
// 6 aliens in total, resolution for one alien is 33 x 27 px

Enemy::Enemy(sf::Vector2f position, sf::Texture &invaderTexture, sf::IntRect spritePosition)
{
	sprite.setTexture(invaderTexture);
	sprite.setTextureRect(spritePosition);
	sprite.setOrigin(33 / 2, 27 / 2);
	sprite.setPosition(position.x, position.y);
}

// Function to move the invaders position
void Enemy::updateMovement(int direction)
{
	direction == 0 ? this->sprite.move(-1, 0) : this->sprite.move(1, 0);
}