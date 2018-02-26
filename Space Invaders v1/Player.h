#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Entity.h"
#include "Projectile.h"
#include "Enemy.h"
#include "UFO.h"

class Player : public Entity
{
// Variables
public:
	float movementSpeed = 0.25;	// how fast the player moves left and right
	bool destroyed = false;		// destroyed once hit by a projectile
	int score = 0;				// keep track of the player's score
	int lives = 3;				// keep track of the player's lives left
	int deathFrame = 0;			// 12 different death frames once the player has been destroyed

	std::vector<Projectile> projectileArray;	// Array to keep the UFO's projectiles
	sf::Clock projectileTimer;					// Create time in between shots
	sf::Clock deathTimer;					

// Methods
public:
	Player(sf::RenderWindow &gameWindow, sf::Texture &spaceshipTexsture);
	void updateMovement();
	void fireProjectiles(sf::Texture &projectileTexture);
	void drawProjectile(sf::RenderWindow &gameWindow);
	void deleteDestroyedProjectiles();
	void checkProjectileCollision(std::vector<Enemy> &enemyArr, UFO &ufo);
	void projectileCollisionInvader(Projectile &projectile, std::vector<Enemy> &enemyArr);
	void deathEvent(sf::Texture &spaceshipTexture, sf::Texture &explosionTexture, bool &game_paused);
};

