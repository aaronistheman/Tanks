#include <Tanks/Game.hpp>
#include <Tanks/ResourceHolder.hpp>
#include <Tanks/ResourceIdentifiers.hpp>
#include <Tanks/Utility.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
    // Game game;
    // game.run();
  sf::RenderWindow window(sf::VideoMode(640, 480), "Resources");
	window.setFramerateLimit(20);

	// Try to load resources
	ResourceHolder<sf::Texture, Textures::ID> textures;
	try
	{
		textures.load(Textures::Landscape, "Media/Textures/Metal.bmp");
		textures.load(Textures::Tank, "Media/Textures/Tank.gif");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		return 1;
	}

	// Access resources
	sf::Sprite landscape(textures.get(Textures::Landscape));
	sf::Sprite tank(textures.get(Textures::Tank));
	tank.setPosition(200.f, 200.f);

  setSize(landscape, sf::Vector2f(window.getSize()));
  setSize(tank, sf::Vector2f(80.0f, 37.0f));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::Closed)
				return 0;
		}

		window.clear();
		window.draw(landscape);
		window.draw(tank);
		window.display();
	}
}
