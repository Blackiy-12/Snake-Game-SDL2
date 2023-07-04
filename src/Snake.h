#pragma once

#include "Object.h"
#include "RenderInfo.h"

#include <memory>
#include <vector>

class Game;

enum class MoveDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Snake
{
public:
	
	Snake(Game* World, vec2<int> HeadPosition, vec2<int> TailPosition);

	~Snake();

	void move(MoveDirection Direction);

	ObjectType getObjectType(vec2<int> Coordinate);

	std::vector<Entity> getRenderInfo();

	bool isHitItself();

private:

	bool HitItself;

	Game* World;

	std::unique_ptr<Object> Head;

	std::vector<std::unique_ptr<Object>> Body;

private:

	void slideHead(vec2<int> NewHeadLocation, bool EatTreat);
};

