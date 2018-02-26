#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Entity.h"

class Enemy : public Entity
{
//Variables
public:
	float movementSpeed = 0.1;	// How fast the enemy moves
	float attackSpeed = 0.1;	// How fast enemies' projectile move
	int health = 1;				// How many hits it can take before it gets destroyed
	int color = 0;				// Colors 0-5 to differentiate the color of the enemy
	bool destroyed = false;		// Flag to check if the enemy is destroyed 

// Methods
public:
	Enemy(sf::Vector2f position, sf::Texture &invaderTexture, sf::IntRect spritePosition);
	void updateMovement(int direction);
};