#include "UniverseLayer.h"

GLuint frameBuffer;
GLuint renderBuffer;
GLuint TexFront;
GLuint TexBack;
GLuint vao;
GLuint vbo;
GLuint ebo;
GLuint posAttrib;
GLuint texAttrib;
GLuint colAttrib;
GLuint scaleLoc0 , scaleLoc1;
ShaderWizard SW;

UniverseLayer::UniverseLayer(const char * vertexShader, const char * fragmentShader, glm::vec2 viewportSize, glm::vec2 pixelScale)
{
	this->viewportSize = viewportSize;
	this->stateSize = viewportSize / pixelScale;

	//Shader Program Information
	SW.installShaders(vertexShader, fragmentShader);
	SW.installShaders(vertexShader,"copyfragshader.glsl");
		//check_gl_error();
	
	//Generate Textures
	genTex(TexFront);
	genTex(TexBack);
	genframeBuf(frameBuffer, renderBuffer);
		//check_gl_error();
	
	/*VertexData space[4] = {
		{{255, 255, 255, 255},{},{}}
	}*/

	GLfloat space[] = {
		//POS		  //TEXcord	  //COLOR
		-1.0f, +1.0f, 0.0f, 1.0f, +1.0f, +1.0f, +1.0f,// Vertex 1 (X, Y, S, T, R, G, B)
		-1.0f, -1.0f, 0.0f, 0.0f, +1.0f, +1.0f, +0.0f,// Vertex 2 (X, Y, S, T, R, G, B)
		+1.0f, -1.0f, 1.0f, 0.0f, +1.0f, +0.0f, +1.0f,// Vertex 3 (X, Y, S, T, R, G, B)
		+1.0f, +1.0f, 1.0f, 1.0f, +0.0f, +1.0f, +1.0f // Vertex 4 (X, Y, S, T, R, G, B)
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

	/*colAttrib = glGetAttribLocation(SW.InstlledProgramIDs[0], "colors");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)(4 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(colAttrib);
	check_gl_error();*/ //- ERROR

	scaleLoc0 = glGetUniformLocation(SW.InstlledProgramIDs[0], "scale0");
	glUniform2f(scaleLoc0, 1, 1);
	scaleLoc1 = glGetUniformLocation(SW.InstlledProgramIDs[1], "scale1");
	glUniform2f(scaleLoc1, 1, 1);
	
	std::cout << TexFront << " " << TexBack << std::endl;
	Step();
	//Draw();
	
}

void UniverseLayer::genTex(GLuint &id)
{
	//glCreateTextures(GL_TEXTURE_2D, 1, &id);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	//2D TEX PROPERTIES
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, stateSize.x, stateSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

}

void UniverseLayer::genframeBuf(GLuint & fid, GLuint & rid)
{
	glCreateFramebuffers(1, &fid);
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
	glViewport(0, 0, stateSize.x, stateSize.y);
	glBindTexture(GL_TEXTURE_2D, TexFront);
	glUseProgram(SW.InstlledProgramIDs[0]);
	glUniform2f(scaleLoc0, stateSize.x, stateSize.y);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	SwapTex();//put backtex -> up
	//std::cout << TexFront << " " << TexBack << std::endl;
	
}

void UniverseLayer::Draw() {
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
	glViewport(0, 0, viewportSize.x, viewportSize.y);
	glBindTexture(GL_TEXTURE_2D, TexFront);//bind back tex/last rendered/now up to draw
	glUseProgram(SW.InstlledProgramIDs[1]);//copy from binded tex 
	glUniform2f(scaleLoc1, viewportSize.x, viewportSize.y);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void UniverseLayer::screenCoordToTex(glm::vec2 &coord) {
	coord.x = -(((viewportSize.x - coord.x) * stateSize.x) / viewportSize.x) + stateSize.x;
	coord.y = -((coord.y * stateSize.y) / viewportSize.y) + stateSize.y;
}

void UniverseLayer::Poke(glm::vec2 Mouse_xy, GLint value) {
	screenCoordToTex(Mouse_xy);
	std::cout << "poked! " << Mouse_xy.x << " " << Mouse_xy.y << std::endl;
	GLint v = value * 255; 
	GLubyte pixel[] = { v, v, v, 255 };
	glBindTexture(GL_TEXTURE_2D,TexFront);
	if (value == 1) {
		glTexSubImage2D(GL_TEXTURE_2D, 0, Mouse_xy.x - .5f, Mouse_xy.y - .5f, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
	}
	else {
		glTexSubImage2D(GL_TEXTURE_2D, 0, Mouse_xy.x - .5f, Mouse_xy.y - .5f, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
	}
	
	Draw();
	check_gl_error();
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
