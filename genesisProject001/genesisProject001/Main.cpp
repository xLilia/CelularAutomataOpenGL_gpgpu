#include <GL\glew.h>
#include <glm.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

#include "ShaderWizard.h"
#include "PocketUniverse.h"



int main() {
	
	sf::RenderWindow window(sf::VideoMode(512, 512), "Pocket Universe");

	PocketUniverse PKU;
	PKU.createLayer("vertexShader.glsl", "fragmentShader.glsl", glm::vec2(window.getSize().x, window.getSize().y), glm::vec2(12, 12));
	window.display();

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
					std::cout << "space " << PKU.UTime << std::endl;
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				PKU.PokeUniverse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			}
		}

		//window.clear();
		
		
	}

	return 0;
}