#include "Platform/Platform.hpp"
#include <cmath>

int main()
{

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window", sf::Style::Titlebar | sf::Style::Close);
	const float fps {60};
	window.setFramerateLimit(fps);
		// variables

	const float g { 9.81f };
	const float l {400};
	const float pi {3.14f};
	const float theta_0 {pi/3};
	const float dt {10 / fps};
	float time = {};
	float theta {theta_0};
	float x {l * std::sin(theta_0)};
	float y {l * std::cos(theta_0)};
	const sf::Vector2f origin = sf::Vector2f(400, 50);
	sf::Vector2f bob_position = sf::Vector2f(x + 400, y + 50);


	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		time += dt;

		theta = theta_0 * std::cos(std::sqrt(g/l)*time);

		std::cout << theta << "\n";

		x = l * std::sin(theta);
		y = l * std::cos(theta);
		bob_position = sf::Vector2f(x + 400, y + 50);

		sf::CircleShape bob = sf::CircleShape(10.f);
		bob.setOrigin(10.f, 10.f);
		bob.setPosition(bob_position);

		sf::Vertex line[] = {
			origin,
			bob_position
		};

		// draw everything here...
		// window.draw(...);
		window.draw(line, 2, sf::Lines);
		window.draw(bob);

		// end the current frame
		window.display();
	}

	return 0;
}

