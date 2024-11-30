#include "Renderer.h"

int windowWidth = 1280;
int windowHeight = 800;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

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

void DestroyWindow()
{
	free(colorBufferRGBA);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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

void DrawFillRect(int x, int y, int w, int h, uint32_t fillColor)
{
	for (int i = y; i < (y + h); i++)
	{
		for (int j = x; j < (x + w); j++)
		{
			colorBufferRGBA[(windowWidth * i) + j] = fillColor;
		}
	}
}
