// First attempt on creating a game using c++ and sfml :)
// To run program, run Local Windows Debugger in debug mode

#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>

#include "Entity.h"
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "UFO.h"
#include "Horde.h"

using namespace std;

// Functions
void loadTextures(sf::Font &font, sf::Texture &background, sf::Texture &lives, sf::Texture &spaceship, sf::Texture &projectile, sf::Texture &invader, sf::Texture &invaderProjectile, sf::Texture &explosionTexture);
void displayHeader(sf::RenderWindow &gameWindow, sf::Texture &backgroundTexture, sf::Font &fontTexture, sf::Texture livesTexture, int currentScore, int currentLives);
void drawWorld(sf::RenderWindow &gameWindow, Player &player, UFO &ufo, Horde &horde);

void updatePlayer(Player &player, sf::Texture &projectileTexture, vector<Enemy> &enemyArr, UFO &ufo);
void updateUFO(Player &player, sf::Texture &projectileTexture, UFO &ufo, int &playerScore);
void updateHorde(Horde &horde, int &playerScore);

int main() {

	// Edit window attributes
	sf::RenderWindow window(sf::VideoMode(800, 675), "Pew Pew Invaders", sf::Style::Close);

	// Variables
	bool game_paused = false;

	// Textures
	sf::Font fontTexture;
	sf::Texture backgroundTexture;
	sf::Texture livesTexture;
	sf::Texture spaceshipTexture;
	sf::Texture projectileTexture;
	sf::Texture invaderTexture;
	sf::Texture UFOTexture;
	sf::Texture explosionTexture;

	// Load Textures
	loadTextures(fontTexture, backgroundTexture, livesTexture, spaceshipTexture, projectileTexture, invaderTexture, UFOTexture, explosionTexture);

	Player mainPlayer(window, spaceshipTexture); // Create the player
	UFO ufo(window, UFOTexture);				 // Create the UFO
	Horde horde(invaderTexture);				 // Create Enemy Horde

	/*
	cout << horde.enemyArray[0].sprite.getPosition().x << " - " << horde.enemyArray[0].sprite.getPosition().y << endl;
	cout << horde.enemyArray[12].sprite.getPosition().x << " - " << horde.enemyArray[12].sprite.getPosition().y << endl;
	cout << horde.enemyArray[24].sprite.getPosition().x << " - " << horde.enemyArray[24].sprite.getPosition().y << endl;
	cout << horde.enemyArray[36].sprite.getPosition().x << " - " << horde.enemyArray[36].sprite.getPosition().y << endl;
	cout << horde.enemyArray[48].sprite.getPosition().x << " - " << horde.enemyArray[48].sprite.getPosition().y << endl;
	cout << horde.enemyArray[60].sprite.getPosition().x << " - " << horde.enemyArray[60].sprite.getPosition().y << endl;
	cout << ufo.sprite.getPosition().x << " - " << ufo.sprite.getPosition().y << endl;
	*/

	while (window.isOpen()) {

		sf::Event evnt;
		// Option to close the windows
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Clear the screen
		window.clear();

		// Display background and header
		displayHeader(window, backgroundTexture, fontTexture, livesTexture, mainPlayer.score, mainPlayer.lives);	
		
		// Display player, projectiles, enemies, ufo
		drawWorld(window, mainPlayer, ufo, horde);

		// Trigger an event when the player gets shot by a projectile 
		mainPlayer.deathEvent(spaceshipTexture, explosionTexture, game_paused);

		if (!game_paused)
		{
			updatePlayer(mainPlayer, projectileTexture, horde.enemyArray, ufo);	// Update Player's gameplay
			updateUFO(mainPlayer, projectileTexture, ufo, mainPlayer.score);	// Update UFO's gameplay
			updateHorde(horde, mainPlayer.score);								// Update invaders' gameplay
		}

		// Update the window
		window.display();
	}
	return 0;
}

// Load textures
void loadTextures(sf::Font &font, sf::Texture &background, sf::Texture &lives, sf::Texture &spaceship, sf::Texture &projectile, sf::Texture &invader, sf::Texture &UFO, sf::Texture &explosion)
{
	if (!font.loadFromFile("Fonts/GALACTIC VANGUARDIAN NCV.ttf")) {
		exit(1);
	}
	if (!background.loadFromFile("Textures/background.png")) {
		exit(1);
	}
	if (!lives.loadFromFile("Textures/lives.png")) {
		exit(1);
	}
	if (!spaceship.loadFromFile("Textures/spaceship.png")) {
		exit(1);
	}
	if (!projectile.loadFromFile("Textures/projectiles.png")) {
		exit(1);
	}
	if (!invader.loadFromFile("Textures/aliens_final.png")) {
		exit(1);
	}
	if (!UFO.loadFromFile("Textures/UFO.png")) {
		exit(1);
	}
	if (!explosion.loadFromFile("Textures/spaceship_explosion.png")) {
		exit(1);
	}
}

// Function to display the background and header (scores and lives left)
void displayHeader(sf::RenderWindow &gameWindow, sf::Texture &backgroundTexture, sf::Font &fontTexture, sf::Texture livesTexture, int currentScore, int currentLives)
{
	// Display background
	static sf::Sprite background(backgroundTexture);
	gameWindow.draw(background);

	// Display header text
	sf::String score = "SCORE\t" + to_string(currentScore);
	sf::Text drawScore(score, fontTexture, 22);
	drawScore.setPosition(20, 10);

	static sf::String lives = "LIVES";
	static sf::Text drawLives(lives, fontTexture, 22);
	drawLives.setPosition(550, 10);

	gameWindow.draw(drawScore);
	gameWindow.draw(drawLives);

	// Display lives left
	sf::Sprite livesDisplay;
	livesDisplay.setTexture(livesTexture);
	livesDisplay.setTextureRect(sf::IntRect(0, 0, 80 * currentLives, 80));
	livesDisplay.setScale(0.5, 0.5);
	livesDisplay.setPosition(630, 5);

	gameWindow.draw(livesDisplay);
}

// Function to draw the player, ufo, invaders, and projectiles
void drawWorld(sf::RenderWindow &gameWindow, Player &player, UFO &ufo, Horde &horde)
{
	gameWindow.draw(player.sprite);		// Draw player
	player.drawProjectile(gameWindow);	// Draw player's projectiles

	gameWindow.draw(ufo.sprite);		// Draw UFO
	ufo.drawProjectile(gameWindow);		// Draw UFO's projectiles

	horde.drawEnemiesToScreen(gameWindow);	// Draw invaders
}

void updatePlayer(Player &player, sf::Texture &projectileTexture, vector<Enemy> &enemyArr, UFO &ufo)
{
	player.updateMovement();
	player.fireProjectiles(projectileTexture);
	player.checkProjectileCollision(enemyArr, ufo);
	player.deleteDestroyedProjectiles();
}

// Function that draws, moves, and fire projectiles out the ufo
void updateUFO(Player &player, sf::Texture &projectileTexture, UFO &ufo, int &playerScore)
{
	if (!ufo.dead)
	{
		ufo.updateMovement();
		ufo.fireProjectile(projectileTexture);
		ufo.checkProjectileCollision(player);
		ufo.deleteDestroyedProjectiles();	
	}
	ufo.deleteDestroyedUFO(playerScore);
}

void updateHorde(Horde &horde, int &playerScore)
{
	horde.moveHorde();
	horde.deleteDestroyedEnemies(playerScore);
}