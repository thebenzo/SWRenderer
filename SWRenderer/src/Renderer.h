#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include <SDL.h>

extern int windowWidth;
extern int windowHeight;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern uint32_t* colorBufferRGBA;
extern SDL_Texture* colorBufferTexture;

bool InitializeWindow();
void DestroyWindow();

void RenderColorBuffer();
void ClearColorBuffer(uint32_t color);

void DrawGrid(int size);
void DrawDotGrid(int size);

void DrawFillRect(int x, int y, int w, int h, uint32_t fillColor);

#endif // !RENDERER_H
