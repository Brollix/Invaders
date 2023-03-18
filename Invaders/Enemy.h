#pragma once
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include "HealthBar.h"
#include "Bullet.h"

using namespace std;
using namespace sf;

class Enemy :
	public Entity
{
public:
	Texture* texture = new Texture;
	Sprite* enemy = new Sprite;
	string path = "../img/enemy.png";

	HealthBar healthbar;

	Vector2f pos;

	vector<Bullet> bullets;

	float speed = 1;
	float fireRateMax = 0.5;
	float fireRate = 1 / fireRateMax;

	float damage = 20;	

	Enemy() {
		if (texture->loadFromFile(path))
		{
			enemy->setTexture(*texture);

			enemy->setOrigin(
				Vector2f(
					texture->getSize().x / 2,
					texture->getSize().y / 2
				));
		}
	};

	Vector2f getPosition() {
		return enemy->getPosition();
	}

	void setPosition(Vector2f pos) {
		enemy->setPosition(pos);
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

	void render(RenderWindow& window) {
		window.draw(*enemy);
	}

	void move() {
		pos = enemy->getPosition();
		pos.y += speed;
		enemy->setPosition(pos);
		healthbar.setSize(getcurrentHealth(), maximumHealth);
		
		healthbar.setPosition(			
				enemy->getPosition().x + 12,
				enemy->getPosition().y - 50
		);
	}

	void takeDamage(float damage) {
		if (currentHealth + damage > 0){
			currentHealth -= damage;
		}		
	}

	float doDamage() {
		return damage;
	}
};

