#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Entity.h"
#include "Projectile.h"

class Player;

class UFO : public Entity
{
// Variables
public:
	float movementSpeed = 1;	// How fast the enemy moves
	float attackSpeed = 0.1;	// How fast enemies' projectile move
	bool destroyed = false;		// Flag to check if the projectile is destroyed
	bool dead = false;			// Once true, ufo is completely gone from the game
	int health = 1;				// How many hits it can take before it gets destroyed
	int direction = 1;			// 0 = move left, 1 = move right
	int randomDirectionTime = rand() % 14000 + 3000;	// The UFO will switch direction every 3-14 seconds
	
	std::vector<Projectile> projectileArray;	// Array to keep the UFO's projectiles
	sf::Clock projectileTimer;  // Create time in between shots
	sf::Clock movementTimer;	// Create time in between each move
	sf::Clock directionTimer;	// Create random times between UFO's change in direction
	sf::Clock deathTimer;		// Used as a timer, when UFO dies, explosion is displayed for a brief period of time

// Methods
public:
	UFO(sf::RenderWindow &gameWindow, sf::Texture &UFOTexture);
	void randomDirection();
	void updateMovement();
	void fireProjectile(sf::Texture &projectileTexture);
	void drawProjectile(sf::RenderWindow &gameWindow);
	void checkProjectileCollision(Player &player);
	void deleteDestroyedProjectiles();
	void deleteDestroyedUFO(int &playerScore);
};

