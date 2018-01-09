#include "PocketUniverse.h"


PocketUniverse::PocketUniverse(int complexity)
{
	glewInit();

}

void PocketUniverse::createLayer(const char* vertexShader, const char* fragmentShader)
{
	
	this->ComplexityLayers.push_back(UniverseLayer(vertexShader, fragmentShader));
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
