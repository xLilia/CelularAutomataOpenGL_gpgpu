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
void PocketUniverse::PokeUniverse(int x, int y) {
	for each (UniverseLayer u in ComplexityLayers)
	{
		u.Poke(x,y,1);
	}
}

PocketUniverse::~PocketUniverse()
{
}
