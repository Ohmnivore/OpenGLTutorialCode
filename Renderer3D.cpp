#include <Renderer3D.h>
#include <iostream>
#include <fstream>

Renderer3D::Renderer3D(SDL_GLContext glcontext, SDL_Window* window)
{
	this->glcontext = glcontext;
	this->window = window;
	init();
}


Renderer3D::~Renderer3D()
{
}

void sendDataToOpenGL()
{
	const GLfloat TOP_Z = -0.5f;
	const GLfloat BOT_Z = 0.5f;
	GLfloat verts[] =
	{
		//x, y, z, r, g, b
		+0.0f, +0.0f, TOP_Z, +0.0f, +1.0f, +0.0f,
		+1.0f, +1.0f, TOP_Z, +0.0f, +0.0f, +1.0f,
		-1.0f, +1.0f, TOP_Z, +1.0f, +0.0f, +0.0f,

		-1.0f, -1.0f, BOT_Z, + 1.0f, +0.0f, +0.0f,
		+1.0f, -1.0f, BOT_Z, +0.0f, +0.0f, +1.0f,
		+0.0f, +1.0f, -1.0f, +0.0f, +1.0f, +0.0f,
	};
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

	GLushort indices[] = { 0, 1, 2, 3, 4, 5, };
	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

bool checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC propertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC logGetterFunc,
	GLenum statusType)
{
	GLint status;
	propertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint logLength;
		propertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &logLength);
		GLchar* buffer = new GLchar[logLength];

		GLsizei bufferSize;
		logGetterFunc(objectID, logLength, &bufferSize, buffer);
		std::cout << buffer << std::endl;

		delete[] buffer;
		return false;
	}
	return true;
}
bool checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}
bool checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

std::string readFile(const char* relPath)
{
	std::ifstream input(relPath);
	if (!input.good())
	{
		std::cout << "Couldn't find file: " << relPath << std::endl;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(input),
		std::istreambuf_iterator<char>());
}

void installShaders()
{
	GLuint vShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	std::string temp = readFile("vertexSimple.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vShaderID, 1, adapter, 0);
	temp = readFile("fragmentSimple.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fShaderID, 1, adapter, 0);

	glCompileShader(vShaderID);
	glCompileShader(fShaderID);

	if (!checkShaderStatus(vShaderID) || !checkShaderStatus(fShaderID))
		return;

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vShaderID);
	glAttachShader(programID, fShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
		return;

	glUseProgram(programID);
}

void Renderer3D::init()
{
	glEnable(GL_DEPTH_TEST);

	/* Clear our buffer with a green background */
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	apply();

	sendDataToOpenGL();
	installShaders();
}

void Renderer3D::render()
{
	glClear(GL_DEPTH_BUFFER_BIT);

	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	apply();
}

void Renderer3D::apply()
{
	/* Swap our back buffer to the front */
	SDL_GL_SwapWindow(window);
}