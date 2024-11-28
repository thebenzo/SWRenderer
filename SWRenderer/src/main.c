#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include <SDL.h>

const int windowWidth = 1280;
const int windowHeight = 800;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool isRunning = false;

uint32_t* colorBufferRGBA = NULL;
SDL_Texture* colorBufferTexture = NULL;

bool InitializeWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Failed to initialize SDL. Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Tiny Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
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

void RenderColorBuffer()
{
	SDL_UpdateTexture(colorBufferTexture, NULL, colorBufferRGBA, (int)(sizeof(uint32_t) * windowWidth));
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void ClearColorBuffer(uint32_t color)
{
	for (int y = 0; y < windowHeight; y++)
	{
		for (int x = 0; x < windowWidth; x++)
		{
			colorBufferRGBA[(windowWidth * y) + x] = color;
		}
	}
}

void DrawGrid(int size)
{
	for (int y = 0; y < windowHeight; y++)
	{
		for (int x = 0; x < windowWidth; x++)
		{
			if (x % size == 0 || y % size == 0)
			{
				colorBufferRGBA[(windowWidth * y) + x] = 0x000000FF;
			}
		}
	}
}

void DrawDotGrid(int size)
{
	for (int y = 1; y <= windowHeight; y += 10)
	{
		for (int x = 1; x <= windowWidth; x += 10)
		{
			colorBufferRGBA[(windowWidth * y) + x] = 0x000000FF;
		}
	}
}

int main(int argc, char* args[])
{
	isRunning = InitializeWindow();

	// Allocate and setup colorBuffer in the memory
	colorBufferRGBA = (uint32_t*) malloc(sizeof(uint32_t) * windowWidth * windowHeight);
	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);

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

		DrawDotGrid(10);

		RenderColorBuffer();
		ClearColorBuffer(0xFFFFFFFF);

		SDL_RenderPresent(renderer);
	}

	// Cleanup allocated resources
	free(colorBufferRGBA);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
