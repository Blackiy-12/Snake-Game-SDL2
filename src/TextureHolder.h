#pragma once

#include <SDL.h>

struct TextureFromTile
{
	SDL_Texture* TileMap;

	SDL_Rect PositionOfTexture;
};

class TextureHolder
{
public:

	TextureHolder();

	~TextureHolder();

	void loadTexture(SDL_Renderer* Renderer);

	TextureFromTile getHeadTexture(int Angle);

	TextureFromTile getStraightTexture(int Angle);

	TextureFromTile getTailTexture(int Angle);

	TextureFromTile getCornerBodyTexture(int Angle);

	TextureFromTile getTreatTexture();

private:

	SDL_Texture* TileMap;
};

