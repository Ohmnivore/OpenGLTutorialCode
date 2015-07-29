//Using SDL and standard IO
#include <SDL.h>
#undef main
#include <stdio.h>
#include <Renderer3D.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, const char* args[])
{
	SDL_GLContext maincontext = NULL; /* Our opengl context handle */
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		//Create window
		window = SDL_CreateWindow("LightEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			/* Create our opengl context and attach it to our window */
			maincontext = SDL_GL_CreateContext(window);
			glewExperimental = GL_TRUE;
			glewInit();

			Renderer3D renderer = Renderer3D(maincontext, window);
			renderer.init();

			//Main loop flag
			bool quit = false;
			//Event handler
			SDL_Event e;
			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				renderer.render();
			}
		}
	}
	/* Delete our opengl context */
	SDL_GL_DeleteContext(maincontext);
	//Destroy window
	SDL_DestroyWindow( window );
	//Quit SDL subsystems
	SDL_Quit();
	return 0;
}