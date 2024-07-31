#include <iostream>
#include <string>
#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "../imgui.h"
#include <tinyxml2.h>

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Hello, World!", 100, 100, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
	
	if (!glewInit())
	{
		printf("glewInit Error: %s\n", glewGetErrorString(glewInit()));
		return 1;
	}

	SDL_GL_CreateContext(window);

	printf("ImGui Version: %s\n", (IMGUI_VERSION));

	printf("tinyxml2 Version: %i\n", (TINYXML2_MAJOR_VERSION));

	printf("SDL Version: %i\n", SDL_GetVersion());

	printf("OpenGL Version: %s\n", (const char*)glGetString(GL_VERSION));

	system("PAUSE");
}