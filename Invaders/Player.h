#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Entity.h"
#include "HealthBar.h"
#include "Bullet.h"

using namespace std;
using namespace sf;

class Player :
	public Entity {

public:

	Texture texture;
	Sprite player;
	string path = "../img/player.png";

	Sound shootSound;
	SoundBuffer buffer;	

	HealthBar healthbar;

	Vector2f pos;

	vector<Bullet> bullets;

	float speed = 7;
	float fireRateMax = 5;
	float fireRate = 1 / fireRateMax;

	float damage = 50;

	Player() {
		if (texture.loadFromFile(path))
		{
			player.setTexture(texture);

			player.setOrigin(
				Vector2f(
					texture.getSize().x / 2,
					texture.getSize().y
				));
		}
		shootSound.setBuffer(buffer);
		shootSound.setVolume(100);
		buffer.loadFromFile("../sounds/shoot.ogg");		
	};

	Vector2f getPosition() {
		return player.getPosition();
	}

	void setPosition(Vector2f pos) {
		player.setPosition(pos);
	}

	void setcurrentHealth(int h) {
		currentHealth = h;
	}

	void setmaximumHealth(int h) {
		maximumHealth = h;
	}

	int getcurrentHealth() {
		return currentHealth;
	}

	int getmaximumHealth() {
		return maximumHealth;
	}
	
	void render(RenderWindow &window) {
		window.draw(player);
	}

	void move() {
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.setPosition(player.getPosition().x - speed, player.getPosition().y);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			player.setPosition(player.getPosition().x + speed, player.getPosition().y);
		}

		if (player.getPosition().x < 0) {
			player.setPosition(Vector2f(540, player.getPosition().y));
		}
		if (player.getPosition().x > 540) {
			player.setPosition(Vector2f(0, player.getPosition().y));
		}
		
		healthbar.setSize(getcurrentHealth(), maximumHealth);
	}
	void shoot() {		
		float bulletX = player.getPosition().x;
		float bulletY = player.getPosition().y;
		Bullet bullet;
		bullet.setPosition(Vector2f(bulletX, bulletY - 60));
		this->bullets.push_back(bullet);
		shootSound.play();
	}
	void takeDamage(float damage) {
		currentHealth -= damage;
	}
	float doDamage() {
		return damage;
	}
};

