#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Enemy.h"

class Horde
{
// Variables
public:
	std::vector<Enemy> enemyArray;
	sf::Clock enemyMovementTimer;			// Used to create time in between enemies' movement
	sf::Clock enemyDeathTimer;				// Used as a timer, when invader dies, explosion is displayed for a brief period of time
	int currentHordeDirection = 0;			// To signal where the horde will be moving, 0 = horde moving left, 1 = horde moving right
	signed int currentHordePosition = 0;	// To keep track of the invaders' position as a whole

// Methods
public:
	Horde(sf::Texture &invaderTexture);
	void spawnEnemies(sf::Texture &texture);
	void drawEnemiesToScreen(sf::RenderWindow &gameWindow);
	void deleteDestroyedEnemies(int &playerScore);
	void moveHorde();
};

