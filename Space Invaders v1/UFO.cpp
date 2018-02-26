#include "UFO.h"
#include "Player.h"

// Resolution for the UFO's png image : 172 x 160 px
// UFO = sf::IntRect(0, 0, 172, 80)
// UFO Explosion = sf::IntRect(0, 80, 172, 80)

UFO::UFO(sf::RenderWindow &gameWindow, sf::Texture &UFOTexture)
{
	sprite.setTexture(UFOTexture);
	sprite.setTextureRect(sf::IntRect(0, 0, 172, 80));
	sprite.setScale(0.3, 0.3);
	sprite.setOrigin(172 / 2, 80 / 2);
	sprite.setPosition(gameWindow.getSize().x / 2, gameWindow.getSize().y * 0.1);
}

// Function that will change the direction of the UFO every 3-14 seconds
// this->randomDirectionTime is a randomly generated time
// this->directionTimer is a timer, once this has gone above the randomDirectionTime, 
// the UFO changes direction, this timer restarts, randomDirectionTime get a new random time
void UFO::randomDirection()
{
	if (this->directionTimer.getElapsedTime().asMilliseconds() >= this->randomDirectionTime)
	{
		this->randomDirectionTime = rand() % 7000 + 2000;
		this->directionTimer.restart();
		this->direction == 0 ? this->direction = 1 : this->direction = 0;
	}
}

// Function to move the UFO's position
void UFO::updateMovement()
{
	this->randomDirection();
	if (this->movementTimer.getElapsedTime().asMilliseconds() >= 5)
	{
		this->movementTimer.restart();
		if (this->direction == 0)
		{
			this->sprite.move(-this->movementSpeed, 0);
			if (this->sprite.getPosition().x <= 25)
			{
				this->direction = 1;
			}
		}
		else
		{
			this->sprite.move(this->movementSpeed, 0);
			if (this->sprite.getPosition().x >= 775)
			{
				this->direction = 0;
			}
		}
	}
}

// The UFO fires a projectile every 750 to 1500 miliseconds
void UFO::fireProjectile(sf::Texture &projectileTexture)
{
	if (this->projectileTimer.getElapsedTime().asMilliseconds() >= (rand() % 2500 + 1000))
	{
		this->projectileTimer.restart();
		Projectile projectile(sprite.getPosition(), projectileTexture);
		projectile.sprite.setTextureRect(sf::IntRect(9, 0, 9, 22));
		projectile.movementSpeed = 0.2;
		this->projectileArray.push_back(projectile);
	}
}

// Draw UFO's projectiles onto the screen
void UFO::drawProjectile(sf::RenderWindow &gameWindow)
{
	static std::vector<Projectile>::const_iterator projectileIter;
	int counter = 0;
	for (projectileIter = this->projectileArray.begin(); projectileIter != this->projectileArray.end(); projectileIter++)
	{
		gameWindow.draw(this->projectileArray[counter].sprite);
		this->projectileArray[counter].updateProjectileMovement(1);
		counter++;
	}
}

// Check whether the UFO's projectiles has hit the player
void UFO::checkProjectileCollision(Player &player)
{
	static std::vector<Projectile>::const_iterator projectileIter;
	int counter = 0;
	for (projectileIter = this->projectileArray.begin(); projectileIter != this->projectileArray.end(); projectileIter++)
	{
		if (this->projectileArray[counter].sprite.getPosition().y > 675)
		{
			this->projectileArray[counter].destroyed = true;
		}
		else if (this->projectileArray[counter].sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds()))
		{
			player.lives -= 1;
			player.destroyed = true;
			this->projectileArray[counter].destroyed = true;
		}
		counter++;
	}
}

// Once the projectiles have hit the player or gone out of bounds, it is destroyed and deleted
void UFO::deleteDestroyedProjectiles()
{
	static std::vector<Projectile>::const_iterator projectileIter;
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

// Function to delete the UFO once the UFO has run out of health
void UFO::deleteDestroyedUFO(int &playerScore)
{
	if (this->health <= 0 && this->destroyed == false)
	{
		this->deathTimer.restart();
		this->destroyed = true;
		this->dead = true;
		this->sprite.setTextureRect(sf::IntRect(0, 80, 172, 80));
		playerScore += 120;
	}
	else if (this->destroyed && this->deathTimer.getElapsedTime().asMilliseconds() >= 750) // Explosion lasts for 750 miliseconds
	{
		this->sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
	}
}