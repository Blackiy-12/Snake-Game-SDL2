#pragma once

#include <SDL.h>

#include "RenderInfo.h"
#include <memory>

class TextureHolder;

class Render
{
public:

	Render();

	~Render();

	void render(RenderInfo World);

private:

	SDL_Window* Window;

	SDL_Renderer* Renderer;

	std::unique_ptr<TextureHolder> TileMap;

private:

	void renderMap(RenderInfo World);
};

