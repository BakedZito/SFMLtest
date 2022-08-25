#include "player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(500.0f, 500.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	velocity.x = 0.0f;
	//or velocity.x *= 0.5f; ---> makes it so you come to a slow stop
		
		//sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;// * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;// * deltaTime;

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += speed * deltaTime;
	*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = false;

		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight); //100SFML units = meter
		//square root (2.0f * gravity *jumpHeight);
	}

	velocity.y += 981.0f * deltaTime;


	if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::onCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//collision of the left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//collision on the right
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//collision on bottom
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//collision with top
		velocity.y = 0.0f;
	}
}
