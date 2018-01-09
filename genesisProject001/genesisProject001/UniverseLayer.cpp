#include "UniverseLayer.h"

GLuint frameBuffer;
GLuint TexFront;
GLuint TexBack;
GLuint vao;
GLuint vbo;
GLuint ebo;
ShaderWizard SW;
GLuint posAttrib;
GLuint texAttrib;
GLuint colAttrib;
GLuint scale;

UniverseLayer::UniverseLayer(const char* vertexShader, const char* fragmentShader)
{
	
	//Shader Program Information
	SW.installShaders(vertexShader, fragmentShader);
	SW.installShaders(vertexShader,"copyfragshader.glsl");
	glUseProgram(SW.InstlledProgramIDs[0]);

	//Generate Textures
	genTex(TexFront);
	genTex(TexBack);

	glCreateFramebuffers(1, &frameBuffer);

	//glGenFramebuffers(1, &frameBuffer);

	GLfloat space[] = {
		//POS		  //TEXcord	  //COLOR
		-1.0f, +1.0f, 0.0f, 1.0f, +1.0f, +1.0f, +1.0f,// Vertex 1 (X, Y)
		-1.0f, -1.0f, 0.0f, 0.0f, +1.0f, +1.0f, +0.0f,// Vertex 2 (X, Y)
		+1.0f, -1.0f, 1.0f, 0.0f, +1.0f, +0.0f, +1.0f,// Vertex 3 (X, Y)
		+1.0f, +1.0f, 1.0f, 1.0f, +0.0f, +1.0f, +1.0f // Vertex 4 (X, Y)
	};
	
	GLuint elements[] = {
		0,1,2,
		2,3,0
	};

	//Vertex Array Object
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);
	
	//Vertex Buffer Object
	glGenBuffers(1, &vbo); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(space), space, GL_STATIC_DRAW);
	
	//Element Buffer Object
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	posAttrib = glGetAttribLocation(SW.InstlledProgramIDs[0], "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(posAttrib);

	texAttrib = glGetAttribLocation(SW.InstlledProgramIDs[0], "texCoords");
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)(2 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(texAttrib);

	colAttrib = glGetAttribLocation(SW.InstlledProgramIDs[0], "colors");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)(4 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(colAttrib);
	
	scale = glGetUniformLocation(SW.InstlledProgramIDs[1], "scale");
	glUniform2f(scale, 16, 16);
	std::cout << TexFront << " " << TexBack << std::endl;
	//Step();
	//Draw();
}

void UniverseLayer::genTex(GLuint &id)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	//2D TEX PROPERTIES
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	
	// Black/white checkerboard
	/*if (id ==1) {
		float pixels[] = {
			0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
		};
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_FLOAT, pixels);
	}*/
	
}

void UniverseLayer::SwapTex()
 {
	GLuint tmp;
	tmp = TexFront;
	TexFront = TexBack;
	TexBack = tmp;
}

void UniverseLayer::Swap(GLuint *a, GLuint *b)
{
	GLuint aux = *a;
	*a = *b;
	*b = aux;
}

void UniverseLayer::Step()
{
	//Bind hidden Drawing Target 
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TexBack, 0);
	glViewport(0, 0, 512, 512);
	glBindTexture(GL_TEXTURE_2D, TexFront);
	glUseProgram(SW.InstlledProgramIDs[0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	SwapTex();
	std::cout << TexFront << " " << TexBack << std::endl;
}

void UniverseLayer::Draw() {
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
	glViewport(0, 0, 512, 512);
	glBindTexture(GL_TEXTURE_2D, TexFront);
	glUseProgram(SW.InstlledProgramIDs[1]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void UniverseLayer::Poke(int x, int y, int value) {
	int v = value * 255;
	glBindTexture(GL_TEXTURE_2D,TexFront);
	glTexSubImage2D(GL_TEXTURE_2D,0,x,y,1,1,GL_RGBA,GL_UNSIGNED_BYTE, (new uint8_t[v, v, v, 255]));
}


UniverseLayer::~UniverseLayer()
{
	//glDeleteFramebuffers(1, &frameBuffer);
	/*glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteTextures(1, &TexFront);
	glDeleteTextures(1, &TexBack);*/
}
