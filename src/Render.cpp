#include "Render.h"

#include "vec2.h"
#include <string>
#include "TextureHolder.h"

Render::Render()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	this->Window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);

	this->Renderer = SDL_CreateRenderer(this->Window, -1, SDL_RENDERER_ACCELERATED);

	this->TileMap = std::make_unique<TextureHolder>();

	this->TileMap->loadTexture(this->Renderer);
}

Render::~Render()
{
	SDL_DestroyRenderer(this->Renderer);

	SDL_DestroyWindow(this->Window);

	SDL_Quit();
}

void Render::render(RenderInfo World)
{
	SDL_SetRenderDrawColor(this->Renderer, 0xff, 0xff, 0xff, 0xff);

	SDL_RenderClear(this->Renderer);

	this->renderMap(World);

	SDL_RenderPresent(this->Renderer);
}


double countAngleForBodyTextureRotation(vec2<int> Prev, vec2<int> Next, vec2<int> Current)
{
	vec2<int> Difrence;
	
	bool Horizotal = false;

	if (Prev.x < Next.x)
	{
		Difrence = Next - Prev;
		
		if (vec2<int>(Current - Prev).x != 0)
			Horizotal = true;
	}
	else
	{
		Difrence = Prev - Next;

		if (vec2<int>(Current - Next).x != 0)
			Horizotal = true;
	}


	if (Difrence.x == 0)
		return 0;

	if (Difrence.y == 0)
		return 90;

	if (Difrence == vec2<int>(1, -1))
	{
		if (Horizotal)
			return 270; 
		else
			return 90;
	}
	else if (Difrence == vec2<int>(1, 1))
	{
		if (Horizotal)
			return 180; 
		else
			return 0; // true
	}
	return 0;
}


double countAngleForHeadTextureRotation(vec2<int> Prev, vec2<int> Head)
{
	vec2<int> Difrence;
	
	Difrence = Head - Prev;

	if (Difrence.x > 0)
		return 90;
	
	else if (Difrence.x < 0)
		return 270;


	if  (Difrence.y > 0)
		return 180;

	else if (Difrence.y < 0)
		return 0;


	return 0;
}

double countAngleForTailTextureRotation(vec2<int> Prev, vec2<int> Tail)
{
	vec2<int> Difrence;

	Difrence = Tail - Prev;

	switch (Difrence.x)
	{

	case 1:
		return 270;

	case -1:
		return 90;

	case 0:
	default:
		break;
	}

	switch (Difrence.y)
	{
	case 1:
		return 0;

	case -1:
		return 180;
	case 0:
	default:
		break;
	}
}

void Render::renderMap(RenderInfo World)
{
	vec2<int> WindowSize;

	SDL_GetWindowSizeInPixels(this->Window, &WindowSize.x, &WindowSize.y);

	SDL_Rect PlayebleMap = { WindowSize.x * 0.05f, WindowSize.y * 0.15f, WindowSize.x - WindowSize.x * 0.1f, WindowSize.y - WindowSize.y * 0.2f };

	SDL_SetRenderDrawColor(this->Renderer, 0x00, 0x00, 0x00, 0xff);

	SDL_Rect TMP = { WindowSize.x * 0.04f, WindowSize.y * 0.14f, WindowSize.x - WindowSize.x * 0.08f, WindowSize.y - WindowSize.y * 0.18f };

	SDL_RenderFillRect(this->Renderer, &TMP);

	vec2<int> SizeOfCellInPixels{ PlayebleMap.w / World.Size.x, PlayebleMap.h / World.Size.y };

	for (int Index = 0; Index < World.SnakeInfo.size(); Index++)
	{
		TextureFromTile Texture;

		vec2<int> PrevBodyPosition(-1, -1);
		vec2<int> NextBodyPosition(-1, -1);
		double AngleOfTextureRotaion = 0;

		if (Index > 0 )
			PrevBodyPosition = World.SnakeInfo[Index - 1].Position;

		if (Index < World.SnakeInfo.size() - 1)
			NextBodyPosition = World.SnakeInfo[Index + 1].Position;

		switch (World.SnakeInfo[Index].Type)
		{
		case ObjectType::HEAD:
			AngleOfTextureRotaion = countAngleForHeadTextureRotation(NextBodyPosition, World.SnakeInfo[Index].Position);
			Texture = this->TileMap->getHeadTexture(AngleOfTextureRotaion);
			break;

		case ObjectType::BODY:
			AngleOfTextureRotaion = countAngleForBodyTextureRotation(PrevBodyPosition, NextBodyPosition, World.SnakeInfo[Index].Position);

			if (PrevBodyPosition.x == NextBodyPosition.x || PrevBodyPosition.y == NextBodyPosition.y)
				Texture = this->TileMap->getStraightTexture(AngleOfTextureRotaion);
			else
				Texture = this->TileMap->getCornerBodyTexture(AngleOfTextureRotaion);

			break;

		case ObjectType::TAIL:
			AngleOfTextureRotaion = countAngleForTailTextureRotation(PrevBodyPosition, World.SnakeInfo[Index].Position);
			Texture = this->TileMap->getTailTexture(AngleOfTextureRotaion);
			break;
		}

		SDL_Rect CellPosition = { PlayebleMap.x + World.SnakeInfo[Index].Position.x * SizeOfCellInPixels.x,	PlayebleMap.y + World.SnakeInfo[Index].Position.y * SizeOfCellInPixels.y,
			SizeOfCellInPixels.x, SizeOfCellInPixels.y };
		
		SDL_RenderCopy(this->Renderer, Texture.TileMap, &Texture.PositionOfTexture, &CellPosition);
	}

	if (World.TreatInfo.Type != ObjectType::NONE)
	{
		TextureFromTile Texture = this->TileMap->getTreatTexture();

		SDL_Rect CellPosition = { PlayebleMap.x + World.TreatInfo.Position.x * SizeOfCellInPixels.x, PlayebleMap.y + World.TreatInfo.Position.y * SizeOfCellInPixels.y, 
			SizeOfCellInPixels.x, SizeOfCellInPixels.y };
	
		SDL_RenderCopy(this->Renderer, Texture.TileMap, &Texture.PositionOfTexture, &CellPosition);
	}
}
