#include "Horde.h"

Horde::Horde(sf::Texture &invaderTexture)
{
	this->spawnEnemies(invaderTexture);
}

// Function that creates the enemies and pushes it into the enemyArray
void Horde::spawnEnemies(sf::Texture &texture)
{
	// Create an array(alienCoordinatesArray) to store the coordinates of the aliens on the sprite sheet that will be used
	// Total of 72 aliens
	// alienArray[0-23] shooters, 1-12 yellow(0), 13-24 pink(1)
	// alienArray[24-47] tankers, 25-36 red(2), 37-48 purple(3)
	// alienArray[48-71] shielders, 49-60 blue(4), 61-72 green(5)

	std::vector<sf::IntRect> alienCoordinatesArray;	// To store the coordinates of each invader on the sprite sheet
	int arrayCounter = 0;		// Used to point into the enemyArray

	for (int y = 0; y <= 5; y++)
	{
		for (int x = 1; x <= 12; x++)
		{
			alienCoordinatesArray.push_back(sf::IntRect(33 * (y), 0, 33, 27));

			float xCoordinate = (float(float(x) / float(13)) * 700) + 50;
			float yCoordinate = (y * 35) + 105;

			// Create enemy object
			Enemy enemyObj(sf::Vector2f(xCoordinate, yCoordinate), texture, alienCoordinatesArray[arrayCounter]);

			// set the attributes accordingly
			if (y <= 1)
			{
				enemyObj.color = y;
				enemyObj.health = 2;
			}
			else if (y <= 3)
			{
				enemyObj.color = y;
				enemyObj.health = 3;
			}
			else
			{
				enemyObj.color = y;
				enemyObj.health = 2;
			}

			arrayCounter++;
			this->enemyArray.push_back(enemyObj);
		}
	}
}

// Function to draw existing enemies onto the windows
void Horde::drawEnemiesToScreen(sf::RenderWindow &gameWindow)
{
	static std::vector<Enemy>::const_iterator enemyIter;	// Used to iterate through the enemyArray
	int enemyArrCounter = 0;		// Used as a pointer to point into the EnemyArray

	// Iterate through the enemy array and draw all enemies
	for (enemyIter = this->enemyArray.begin(); enemyIter != this->enemyArray.end(); enemyIter++)
	{
		gameWindow.draw(this->enemyArray[enemyArrCounter].sprite);
		enemyArrCounter++;
	}
}

// Function to draw an explosion when invader dies and deleted invader from the enemyArray
void Horde::deleteDestroyedEnemies(int &playerScore)
{
	static std::vector<Enemy>::const_iterator enemyIter;	// Used to iterate through the enemyArray
	int enemyArrCounter = 0;				// Used as a pointer to point into the EnemyArray

	// Iterate through the enemy array
	for (enemyIter = this->enemyArray.begin(); enemyIter != this->enemyArray.end(); enemyIter++)
	{
		// If enemy health <= 0, set property destroyed to true
		if (this->enemyArray[enemyArrCounter].health <= 0 && this->enemyArray[enemyArrCounter].destroyed == false)
		{
			this->enemyDeathTimer.restart();
			this->enemyArray[enemyArrCounter].destroyed = true;
			this->enemyArray[enemyArrCounter].sprite.setTextureRect(sf::IntRect(33 * this->enemyArray[enemyArrCounter].color, 27, 33, 27));
			playerScore += 30;
		}
		// Enemies' death animation lasts for 250 miliseconds
		else if (this->enemyArray[enemyArrCounter].destroyed && this->enemyDeathTimer.getElapsedTime().asMilliseconds() >= 250) // Explosion lasts for 250 miliseconds
		{
			this->enemyArray.erase(enemyIter);
			break;
		}
		enemyArrCounter++;
	}
}

// Function to move the horde
void Horde::moveHorde()
{
	static std::vector<Enemy>::const_iterator enemyIter;		// Used to iterate through the enemyArray
	int enemyArrCounter = 0;					// Used to point into the enemyArray

	if (this->enemyMovementTimer.getElapsedTime().asMilliseconds() >= 15)	// Move the invaders every 15 miliseconds
	{
		this->enemyMovementTimer.restart();
		if (this->currentHordeDirection == 0)	// If hordeDirection == 0, horde moves left
		{
			for (enemyIter = this->enemyArray.begin(); enemyIter != this->enemyArray.end(); enemyIter++)
			{
				this->enemyArray[enemyArrCounter].updateMovement(this->currentHordeDirection);
				enemyArrCounter++;
			}

			this->currentHordePosition -= 1;			// Keep moving the horde's position LEFT until it reaches the end
			if (this->currentHordePosition <= -(103 - (33 / 2)))	// position of the upmost left invader = 103, size of invader = 33
			{
				this->currentHordeDirection = 1;
			}
		}
		else	// If hordeDirection == 1, horde moves right
		{
			for (enemyIter = this->enemyArray.begin(); enemyIter != this->enemyArray.end(); enemyIter++)
			{
				this->enemyArray[enemyArrCounter].updateMovement(this->currentHordeDirection);
				enemyArrCounter++;
			}

			this->currentHordePosition += 1;			// Keep moving the horde's position RIGHT until it reaches the end
			if (this->currentHordePosition >= (103 - (33 / 2)))	// position of the upmost right invader = 800-103, size of invader = 33
			{
				this->currentHordeDirection = 0;
			}
		}
	}
}