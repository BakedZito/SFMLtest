#pragma once
#include <SFML\Graphics.hpp>
#include "collider.h"

class platform
{
public:
	platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~platform();

	void draw(sf::RenderWindow& window);
	collider getCollider() { return collider(body); }

private:
	sf::RectangleShape body;

};

