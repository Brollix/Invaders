#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include "Player.h"
#include "Enemy.h"
#include "HealthBar.h"
#include "Background.h"

using namespace std;
using namespace sf;

int main(){

#pragma region Window

	int width = 540;
	int height = 900;
	RenderWindow window(VideoMode(width, height), "Invaders");
	window.setFramerateLimit(60);

	float vPosX;
	float vPosY;
	View view(FloatRect(vPosX, vPosY, width, height));

#pragma endregion

#pragma region Player

	Player player;

	vector<Enemy> enemies;

	player.setPosition(
		Vector2f(
			width / 2,
			height - 50)
	);

	player.setmaximumHealth(1000);
	player.setcurrentHealth(1000);

#pragma endregion

#pragma region Info

	Font font;
	
	Text cHealth;
	Text mHealth;
	Text pointsText;
	int points = 0;

	font.loadFromFile("../font/retroica.ttf");

	cHealth.setFont(font);
	mHealth.setFont(font);
	pointsText.setFont(font);

	pointsText.setPosition(25, 25);
	cHealth.setPosition(Vector2f(25, 65));
	mHealth.setPosition(Vector2f(25, 100));

	player.healthbar.setPosition(62, 115);
	player.healthbar.barX = 200;

#pragma endregion

#pragma region Clocks

	Clock clock;
	Clock fpsClock;
	Clock shootingClock;
	Clock spawnClock;
	float shootTime = 0;
	float spawnTime = 0;
	float spawnCooldown = 1;	

#pragma endregion

	Background background(width, height);

#pragma region GameLoop

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		float random = 25 + (rand() % width - 25);
		float currentTime = fpsClock.restart().asSeconds();
		float fps = 1 / currentTime;

		shootTime = shootingClock.getElapsedTime().asSeconds();

		spawnTime = spawnClock.getElapsedTime().asSeconds();

		Event e;        
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed){
				window.close();
			}            
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			if (shootTime >= player.fireRate) {
				player.shoot();
				shootingClock.restart();
			}
		}

		for (int i = 0; i < player.bullets.size(); i++) {
			if (player.bullets[i].getPosition().y < 0) {
				player.bullets.erase(player.bullets.begin() + i);
			}
		}

	#pragma region Spawner
		//---------- Spawner ----------
		if (spawnTime >= spawnCooldown) {
			Enemy enemy;
			enemies.push_back(enemy);
			enemy.setPosition(Vector2f(random, -50));
			spawnClock.restart();
		}
	#pragma endregion

	#pragma region Collisions

		bool collision = false;
		if (enemies.size() > 0 && player.bullets.size() > 0) {
			for (int i = 0; i < player.bullets.size(); i++) {
				for (int j = 0; j < enemies.size(); j++) {
					if (player.bullets[i].bullet->getGlobalBounds()
						.intersects(enemies[j].enemy->getGlobalBounds())) {

						collision = true;
						if (collision)
						{
							enemies[j].takeDamage(player.doDamage());

							player.bullets[i].hitSound.play();
						}
						collision = false;
					}
				}
			}
		}

		for (int e = 0; e < enemies.size(); e++) {
			if (enemies[e].currentHealth <= 0 ) {
				enemies.erase(enemies.begin() + e);
				points += 10;
			}
		}

	#pragma endregion

	#pragma region Rendering
		//---------- Render Starts -----------
		window.setView(view);
		window.clear();

		background.update(time);
		background.render(window);

		for (int i = 0; i < player.bullets.size(); i++) {
			player.bullets[i].render(window);
			player.bullets[i].update();
		}		

		player.move();
		player.render(window);

		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].render(window);
			enemies[i].healthbar.render(window);
			enemies[i].move();
		}

		window.draw(cHealth);
		window.draw(mHealth);
		window.draw(pointsText);

		cHealth.setString(
			"Health: " + to_string(player.getcurrentHealth())
		);
		//mHealth.setString(
		//	"Max Health: " + to_string(player.getmaximumHealth())
		//);
		pointsText.setString("Points: " + to_string(points));

		player.healthbar.render(window);

		window.display();
		//----------Render Ends----------
	#pragma endregion
	}
#pragma endregion 
}