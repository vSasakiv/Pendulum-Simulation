#include "Platform/Platform.hpp"
#include <cmath>


float omegaDot(float theta, float g, float l);
float thetaDot(float omega);

int main()
{

	sf::Font font;
	font.loadFromFile("src/Fonts/Roboto-Regular.ttf");
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window", sf::Style::Titlebar | sf::Style::Close);
	const float fps { 60 };
	window.setFramerateLimit(fps);
	// variables

	const float g { 9.81f };
	const float l { 400 };
	const float pi { 3.14f };
	const float theta_0 { pi / 3 };
	const float omega_0 { -0.5 };
	const float dt { 10 / fps };
	float time = {};
	float theta { theta_0 };
	float omega { omega_0 };
	float x { l * std::sin(theta_0) };
	float y { l * std::cos(theta_0) };
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

		// Do the heavy calculations
		// We increment the time by dt, so we can step the pendulum
		time += dt;

		// we apply runge-kutta so that we can determinate theta in terms of time.

		float k1omega, k2omega, k3omega, k4omega, k1theta, k2theta, k3theta, k4theta;

		k1omega = omegaDot(theta, g, l);
		k1theta = thetaDot(omega);
		k2omega = omegaDot(theta + dt*k1theta/2, g, l);
		k2theta = thetaDot(omega + dt*k1omega/2);
		k3omega = omegaDot(theta + dt*k2theta/3, g, l);
		k3theta = thetaDot(omega + dt*k2omega/2);
		k4omega = omegaDot(theta + dt*k3theta, g, l);
		k4theta = thetaDot(omega + dt*k3omega);

		omega = omega + (dt/6) * (k1omega + 2*k2omega + 2*k3omega + k4omega);
		theta = theta + (dt / 6) * (k1theta + 2 * k2theta + 2 * k3theta + k4theta);

		//std::cout << theta << "\n";

		// we set x and y according to the angle and set that as the bob position
		x = l * std::sin(theta);
		y = l * std::cos(theta);
		bob_position = sf::Vector2f(x + 400, y + 50);

		// we draw the bob and set its position
		sf::CircleShape bob = sf::CircleShape(10.f);
		bob.setOrigin(10.f, 10.f);
		bob.setPosition(bob_position);

		// and here we declare the line vertex array
		sf::Vertex line[] = {
			origin,
			bob_position
		};

		// and here we add the little top text
		sf::Text theta_display;
		theta_display.setFont(font);
		theta_display.setString("Angle = " + std::to_string(static_cast<int>((theta * 180 / pi)) % 360) + " graus");
		theta_display.setCharacterSize(24);

		// draw everything here.
		window.draw(line, 2, sf::Lines);
		window.draw(bob);
		window.draw(theta_display);

		// end the current frame
		window.display();
	}

	return 0;
}

float omegaDot(float theta, float g, float l)
{
	return -1 * g * std::sin(theta) / l;
}

float thetaDot(float omega){
	return omega;
}