#include <GL\glew.h>
#include <glm.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

#include "ShaderWizard.h"
#include "PocketUniverse.h"



int main() {
	
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pocket Universe");
	window.create(sf::VideoMode::getFullscreenModes()[0], "Pocket Universe", sf::Style::Fullscreen);
	//window.setFramerateLimit(60);
	//window.setVerticalSyncEnabled(true);
	//window.setMouseCursorVisible(false);
	//window.setMouseCursorGrabbed(true);

	PocketUniverse PKU;
	PKU.createLayer("vertexShader.glsl", "fragmentShader.glsl", 
		glm::vec2(window.getSize().x, window.getSize().y), 
		glm::vec2(8, 8));
	window.display();

	bool running = false;
	int speed = 0;
	int stepcounter = speed;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					PKU.TimeStep();
					window.display();
					std::cout << "epoch " << PKU.UTime << std::endl;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					running = !running;
					if (running) {
						std::cout << "running " << "at speed: " << speed << std::endl;
					}
					else {
						std::cout << "STOPED " << "at speed: " << speed << std::endl;
					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				PKU.PokeUniverse(glm::vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y),1);
				window.display();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				PKU.PokeUniverse(glm::vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y),0);
				window.display();
			}

			if (event.type == sf::Event::MouseWheelScrolled) {
				if (speed >= 0) {
					speed += event.mouseWheelScroll.delta * 100;
				}
				else {
					speed = 0;
				}
				std::cout << "speed " << speed << std::endl;
			}
		}

		stepcounter--;
		if (running && stepcounter <= 0) {
			PKU.TimeStep();
			window.display();
			stepcounter = speed;
		}
	
		
		//std::cout << "space " << PKU.UTime << std::endl;
	}

	return 0;
}