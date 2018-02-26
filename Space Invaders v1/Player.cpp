#include "Player.h"

using namespace std;

// Resolution of player's spaceship png image: 64 x 64 px

Player::Player(sf::RenderWindow &gameWindow, sf::Texture &spaceshipTexture)
{
	sprite.setTexture(spaceshipTexture);
	sprite.setOrigin(sf::Vector2f(64 / 2, 64 / 2));
	sprite.setPosition(gameWindow.getSize().x / 2, gameWindow.getSize().y - 40);
}

// Function to move the player left and right
void Player::updateMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->sprite.getPosition().x > 32)
	{
		this->sprite.move(-this->movementSpeed, 0);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->sprite.getPosition().x < 800 - 32)
	{
		this->sprite.move(this->movementSpeed, 0);
	}
}

void Player::fireProjectiles(sf::Texture &projectileTexture)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (this->projectileTimer.getElapsedTime().asMilliseconds() >= 600)	// To provide time in between shots(no rapid fire)
		{
			this->projectileTimer.restart();
			Projectile projectile(sprite.getPosition(), projectileTexture);
			projectile.sprite.setTextureRect(sf::IntRect(0, 0, 9, 22));
			this->projectileArray.push_back(projectile);
		}
	}
}

void Player::drawProjectile(sf::RenderWindow &gameWindow)
{
	static vector<Projectile>::const_iterator projectileIter;
	int counter = 0;
	for (projectileIter = this->projectileArray.begin(); projectileIter != this->projectileArray.end(); projectileIter++)
	{
		gameWindow.draw(this->projectileArray[counter].sprite);
		this->projectileArray[counter].updateProjectileMovement(0);
		counter++;
	}
}

// Function that deletes projectiles that have been destroyed
void Player::deleteDestroyedProjectiles()
{
	static vector<Projectile>::const_iterator projectileIter;
	int counter = 0;
	for (projectileIter = this->projectileArray.begin(); projectileIter != this->projectileArray.end(); projectileIter++)
	{
		if (this->projectileArray[counter].destroyed)
		{
			this->projectileArray.erase(projectileIter);
			break;
		}
		counter++;
	}
}

void Player::checkProjectileCollision(vector<Enemy> &enemyArr, UFO &ufo)
{
	static vector<Projectile>::const_iterator projectileIter;
	int counter = 0;
	for (projectileIter = this->projectileArray.begin(); projectileIter != this->projectileArray.end(); projectileIter++)
	{
		if (this->projectileArray[counter].sprite.getPosition().y < 0)
		{
			projectileArray[counter].destroyed = true;
		}
		else if (this->projectileArray[counter].sprite.getPosition().y <= 67.5)
		{
			if (projectileArray[counter].sprite.getGlobalBounds().intersects(ufo.sprite.getGlobalBounds()))
			{
				ufo.health -= 1;
				projectileArray[counter].destroyed = true;
				break;
			}
		}
		else if (this->projectileArray[counter].sprite.getPosition().y <= 300)
		{
			projectileCollisionInvader(projectileArray[counter], enemyArr);
		}
	}
}

void Player::projectileCollisionInvader(Projectile &projectile, vector<Enemy> &enemyArr)
{
	vector<Enemy>::const_iterator enemyIter;
	int counter = 0;
	for (enemyIter = enemyArr.begin(); enemyIter != enemyArr.end(); enemyIter++)
	{
		if (projectile.sprite.getGlobalBounds().intersects(enemyArr[counter].sprite.getGlobalBounds()))
		{
			projectile.destroyed = true;
			enemyArr[counter].health -= 1;
			break;
		}
		counter++;
	}
}

// Function that triggers when the players get hit by a projectile
void Player::deathEvent(sf::Texture &spaceshipTexture, sf::Texture &explosionTexture, bool &game_paused)
{
	if (this->destroyed)
	{
		game_paused = true;
		this->sprite.setTexture(explosionTexture);
		if (this->deathTimer.getElapsedTime().asMilliseconds() >= 150)
		{
			this->deathTimer.restart();
			this->sprite.setTextureRect(sf::IntRect(this->deathFrame * 64, 0, 64, 64));
			this->deathFrame++;
		}
		if (this->deathFrame >= 15)
		{
			this->deathFrame = 0;
			this->destroyed = false;
			this->sprite.setTexture(spaceshipTexture);
			this->sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
			game_paused = false;
		}
	}
}

