#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

using namespace sf;
using namespace std;

class HealthBar
{
public:

	RectangleShape bar;

	Vector2f pos;
	float barX = 50;
	float barY = 10;	

	HealthBar() {
		bar.setFillColor(Color(200,50,50));
		bar.setOrigin(Vector2f(37, 0));
	}

	void setPosition(float x, float y) {
		bar.setPosition(Vector2f(x, y));
	}

	void setSize(float currentHealth, float maximumHealth) {
		float percentage = currentHealth / maximumHealth;
		bar.setSize(Vector2f(barX * percentage, barY));
	}

	void render(RenderWindow& window) {
		window.draw(bar);
	}
};

