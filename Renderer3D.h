#pragma once
#include <SDL.h>
#undef main
#include <stdio.h>
#include <GL\glew.h>

class Renderer3D
{
public:
	Renderer3D(SDL_GLContext, SDL_Window*);
	~Renderer3D();
	void init();
	void render();

	SDL_GLContext glcontext;
	SDL_Window* window;

private:
	void apply();
};

