#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool isRunning = false;

bool InitializeWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Failed to initialize SDL. Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Tiny Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 800, SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "Failed to create SDL Window. Error: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Failed to create SDL Renderer. Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

int main(int argc, char* args[])
{
	isRunning = InitializeWindow();

	// Game Loop
	while (isRunning)
	{
		// Process Inputs
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}

		// Render
		SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
	}

	return 0;
}
