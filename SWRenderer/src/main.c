#include "Renderer.h"

bool isRunning = false;

void ProcessInputs()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}

void Render()
{
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);

	DrawDotGrid(10);
	DrawFillRect(100, 200, 500, 300, 0x4F7942FF);

	RenderColorBuffer();
	ClearColorBuffer(0xFFFFFFFF);

	SDL_RenderPresent(renderer);
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
		ProcessInputs();
		// Update
		Render();
	}

	DestroyWindow();

	return 0;
}
