#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Entity.h"

class Projectile : public Entity
{
// Variables
public:
	float movementSpeed = 0.6;	// Speed at which the projectile travels
	bool destroyed = false;		// Flag to check if the projectile is destroyed 

// Methods
public:
	Projectile(sf::Vector2f position, sf::Texture &projectileTexture);
	void updateProjectileMovement(int type);
};

