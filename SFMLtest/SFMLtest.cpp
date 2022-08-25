#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>
#include "player.h"
#include "platform.h"

static const float VIEW_HEIGHT = 1000.0f;

void resizeView(sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}



int main()
{
	
	/* basic movement code
	
	sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Tutorial", sf::Style::Close | sf::Style::Resize); // creates window, its size, name, style(minimize, close button
	sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));																										   // title bar button
	player.setFillColor(sf::Color::Red);
	player.setOrigin(50.0f, 50.0f); //sets the origin of the square to the middle of mouse

	while (window.isOpen()) //opens window
	{
		sf::Event evnt; //creates an event
		while (window.pollEvent(evnt)) 
		{

			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				//std::cout << "New Window Width: " << poop.size.width << " New Window Height: "<< poop.size.height << std::endl;
				printf("New Window Width: %i New Window Height: %i\n", evnt.size.width, evnt.size.height);
				break; 
			case sf::Event::TextEntered:
				if (evnt.text.unicode < 128)
				{
					printf("%c", evnt.text.unicode);
				}
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			player.move(-0.1f, 0.0f);
		}
		/* keyboard movement of cube
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			player.move(0.1f, 0.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			player.move(0.0f, -0.1f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			player.move(0.0f, 0.1f);
		}
		

		//mouse movement of cube
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player.setPosition((float)mousePos.x, (float)mousePos.y);
		}

		window.clear();
		window.draw(player);
		window.display();
	
	}
	*/
	
	//texture 
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Tutorial", sf::Style::Close | sf::Style::Resize); // creates window, its size, name, style(minimize, close button
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	
	/* music
	sf::SoundBuffer buffer;
	buffer.loadFromFile("demo2.wav");

	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	*/

	//also music
	sf::Music music;
	music.openFromFile("retro.wav");
	music.setVolume(20);
	std::cout << "volume: " << music.getVolume() <<  std::endl;
	music.setLoop(true);
	std::cout << "loop: " << music.getLoop() << std::endl;
	music.play();

	sf::Texture playerTexture;
	playerTexture.loadFromFile("TuxClassic.png");
	
	//sf::Sprite sprite(playerTexture,sf::IntRect(0,0,200,200));

	Player player(&playerTexture, sf::Vector2u(6, 5), 0.3, 200.0f, 200);

	std::vector<platform> platforms;

	platforms.push_back(platform(nullptr, sf::Vector2f(500.0f, 150.0f), sf::Vector2f(1000.0f, 300.0f)));
	platforms.push_back(platform(nullptr, sf::Vector2f(500.0f, 100.0f), sf::Vector2f(1500.0f, 150.0f)));
	platforms.push_back(platform(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));


	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen()) //opens window
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;
		//std::cout << deltaTime * 100000 <<  std::endl;

		sf::Event evnt; //creates an event
		while (window.pollEvent(evnt))
		{

			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				resizeView(window, view);
				break;
			}
		}
		
		player.update(deltaTime);

		sf::Vector2f direction;

		/*for loop does the same as
				for(int i = 0; i < platforms.size(); i++)
				{
					platform& platform = platforms[i];
				}
			*/
		for (platform& platform : platforms)
			if (platform.getCollider().checkCollision(player.getCollider(), direction, 1.0f))
				player.onCollision(direction);
		
		view.setCenter(player.getPosition());

		window.clear(sf::Color::Green);
		window.setView(view);
	//	window.draw(sprite);
		player.Draw(window);

		for (platform& platform : platforms)
			platform.draw(window);
		
		
		window.display();

	}

	return 0;
}