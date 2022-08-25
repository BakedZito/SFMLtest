#include "platform.h"

platform::platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size/2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

platform::~platform()
{
}

void platform::draw(sf::RenderWindow& window)
{
	window.draw(body);
}
