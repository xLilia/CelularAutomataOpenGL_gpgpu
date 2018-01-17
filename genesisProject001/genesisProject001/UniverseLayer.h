#pragma once
#include "ShaderWizard.h"
#include "GLError.h"
#include <glm.hpp>

struct VertexData {
	GLubyte color[4];
	GLfloat texCoords[4];
	GLfloat position[4];
};

class UniverseLayer
{
public:
	UniverseLayer(const char* vertexShader, const char* fragmentShader, glm::vec2 viewportSize, glm::vec2 pixelScale);
	void genTex(GLuint &id);
	void genframeBuf(GLuint &fid, GLuint &rid);
	void Swap(GLuint * a, GLuint * b);
	void SwapTex();
	void Step();
	void Draw();
	void Poke(GLint x, GLint y, GLint value);

	glm::vec2 stateSize, viewportSize;
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

