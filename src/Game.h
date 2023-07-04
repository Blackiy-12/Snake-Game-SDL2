#pragma once

#include "RenderInfo.h"
#include "Snake.h"
#include "Object.h"
#include "Render.h"
#include <memory>
#include "vec2.h"

class Game
{
public:

	Game(vec2<int> SizeOfWorld = vec2<int>(20,20));

	~Game();

	void play();

	ObjectType getTypeOfObject(vec2<int> Coordinate);

	vec2<int> getWorldSize();

	void eatTreat();

private:

	std::unique_ptr<Render> RenderPtr;

	std::unique_ptr<Object> Treat;

	std::unique_ptr<Snake> SnakePtr;

	vec2<int> Size;

private:

	void spawnNewTreat();

	RenderInfo getRednderInfo();

	void initEntities();
};

