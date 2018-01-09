#pragma once
#include "ShaderWizard.h"

class UniverseLayer
{
public:
	UniverseLayer(const char* vertexShader, const char* fragmentShader);
	void genTex(GLuint &id);
	void Swap(GLuint * a, GLuint * b);
	void SwapTex();
	void Step();
	void Draw();
	void Poke(int x, int y, int value);
	~UniverseLayer();
private:
	/*GLuint frameBuffer;
	GLuint TexFront;
	GLuint TexBack;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	ShaderWizard SW;
	GLuint posAttrib;
	GLuint texAttrib;
	GLuint colAttrib;
	GLuint scale;*/
};

