#include <GL\glew.h>
#include <glm.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

#include "ShaderWizard.h"
#include "PocketUniverse.h"



int main() {
	
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "Pocket Universe");

	PocketUniverse PKU;
	PKU.createLayer("vertexShader.glsl", "fragmentShader.glsl", glm::vec2(window.getSize().x, window.getSize().y), glm::vec2(8, 8));
	window.display();

	bool running = false;

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
					running = !running;
					std::cout << "epoch " << PKU.UTime << std::endl;
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
		}

		/*if (running) {
			PKU.TimeStep();
			window.display();
		}*/
		
		//std::cout << "space " << PKU.UTime << std::endl;
	}

	return 0;
}