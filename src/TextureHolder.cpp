#include "TextureHolder.h"

#include <string>
#include <fstream>

#include <SDL_image.h>

std::string SnakeTileFilePath = "SnakeTileMap.png";

TextureHolder::TextureHolder()
{
    this->TileMap = nullptr;
}

TextureHolder::~TextureHolder()
{
    SDL_DestroyTexture(this->TileMap);
}

void TextureHolder::loadTexture(SDL_Renderer* Renderer)
{
    IMG_Init(IMG_INIT_PNG);

    this->TileMap = IMG_LoadTexture(Renderer, SnakeTileFilePath.c_str());

    IMG_Quit();
}

TextureFromTile TextureHolder::getHeadTexture(int Angle)
{
    switch (Angle)
    {
    case 0:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 0, 0, 8, 8} };
    case 90:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 8, 0, 8, 8} };
    case 180:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 16, 0, 8, 8} };
    case 270:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 24, 0, 8, 8} };
    }
}

TextureFromTile TextureHolder::getStraightTexture(int Angle)
{
    switch (Angle)
    {
    case 0:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 0, 16, 8, 8} };
    case 90:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 8, 16, 8, 8} };
    }
}

TextureFromTile TextureHolder::getTailTexture(int Angle)
{
    switch (Angle)
    {
    case 0:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 0, 24, 8, 8} };
    case 90:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 8, 24, 8, 8} };
    case 180:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 16, 24, 8, 8} };
    case 270:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 24, 24, 8, 8} };
    }
}

TextureFromTile TextureHolder::getCornerBodyTexture(int Angle)
{
    switch (Angle)
    {
    case 0:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 0, 8, 8, 8} };
    case 90:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 8, 8, 8, 8} };
    case 180:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 16, 8, 8, 8} };
    case 270:
        return TextureFromTile{ this->TileMap, SDL_Rect{ 24, 8, 8, 8} };
    }
}

TextureFromTile TextureHolder::getTreatTexture()
{
    return TextureFromTile{ this->TileMap, SDL_Rect{ 0, 32, 8, 8} };
}

