#pragma once
#include "SFML/Graphics.hpp"
using namespace std;
using namespace sf;

class Bullet
{
public:
	Texture* texture = new Texture;
	Sprite* bullet = new Sprite;
	string path = "../img/bullet.png";

	Vector2f pos;
	float speed = 15;

	Sound hitSound;
	SoundBuffer buffer;	

	Bullet() {
		if (texture->loadFromFile(path)){
			bullet->setTexture(*texture);

			bullet->setOrigin(
				Vector2f(
					texture->getSize().x / 2,
					texture->getSize().y / 2
				));
		}
		buffer.loadFromFile("../sounds/hit.ogg");
		hitSound.setBuffer(buffer);
	}
	Vector2f getPosition(){
		return bullet->getPosition();
	}
	void setPosition(Vector2f pos) {
		bullet->setPosition(pos);
	}
	void update() {		
		pos = bullet->getPosition();
		pos.y -= speed;
		bullet->setPosition(pos);
	}
	void render(RenderWindow &window) {
		window.draw(*bullet);
	}
};

