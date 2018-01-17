#include "PocketUniverse.h"


PocketUniverse::PocketUniverse()
{
	glewInit();
	glDisable(GL_DEPTH_TEST);

}

void PocketUniverse::createLayer(const char* vertexShader, const char* fragmentShader, glm::vec2 viewportSize, glm::vec2 pixelScale)
{
	
	this->ComplexityLayers.push_back(UniverseLayer(vertexShader, fragmentShader, viewportSize, pixelScale));
}

void PocketUniverse::TimeStep()
{
	UTime++;
	for each (UniverseLayer u in ComplexityLayers)
	{
		u.Step();
		u.Draw();
	}
}
void PocketUniverse::PokeUniverse(glm::vec2 xy, int value) {
	for each (UniverseLayer u in ComplexityLayers)
	{
		u.Poke(xy, value);
	}
}

PocketUniverse::~PocketUniverse()
{
}
