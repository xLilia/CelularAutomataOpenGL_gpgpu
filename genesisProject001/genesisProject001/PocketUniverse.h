#pragma once
#include<GL\glew.h>
#include <glm.hpp>
#include <vector>

#include "UniverseLayer.h"

class PocketUniverse
{
public:
	PocketUniverse(int complexity = 0);
	void createLayer(const char* vertexShader, const char* fragmentShader);
	void TimeStep();
	void PokeUniverse(int x, int y);
	~PocketUniverse();
	GLint UTime = 0;
private:
	std::vector<UniverseLayer> ComplexityLayers;
	
};

