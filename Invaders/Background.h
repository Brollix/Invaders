#include "SFML/Graphics.hpp"
using namespace std;
using namespace sf;

#pragma once
class Background
{
private:
	Texture texture;
	Sprite sprite;
	Shader shader;
public:
	Background(int width, int height) {
		if (!shader.loadFromFile("../shaders/backgroundFragment.shader", "../shaders/backgroundVertex.shader")) {};

		texture.create(width, height);
		sprite.setTexture(texture);

		float tx = texture.getSize().x;
		float ty = texture.getSize().y;

		shader.setUniform("u_resolution", Vector2f(tx, ty));
	}

	void render(RenderWindow &window) {
		window.draw(sprite, &shader);
	}
	void update(float time) {
		shader.setUniform("u_time", time);
	}	
};

