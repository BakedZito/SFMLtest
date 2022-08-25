#pragma once
#include <SFML\Graphics.hpp>
#include "animation.h"
#include "collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Player();

	void update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void onCollision(sf::Vector2f direction);

	sf::Vector2f getPosition() { return body.getPosition(); }
	collider getCollider() { return collider(body); }

private:
	sf::RectangleShape body;
	animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;

};

