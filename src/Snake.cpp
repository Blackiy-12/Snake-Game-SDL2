#include "Snake.h"

#include "Game.h"

Snake::Snake(Game* World, vec2<int> HeadPosition, vec2<int> TailPosition) :
	World(World)
{
	this->Head = std::make_unique<Object>(HeadPosition);

	this->Body.push_back(std::make_unique<Object>(TailPosition));

	this->HitItself = false;
}

Snake::~Snake()
{
}

void Snake::move(MoveDirection Direction)
{
	if (this->HitItself == true)
		return;

	auto NewHeadLoaction = this->Head->getPosition();

	switch (Direction)
	{
	case MoveDirection::UP:
		NewHeadLoaction = NewHeadLoaction + vec2<int>(0, -1);
		break;
	case MoveDirection::DOWN:
		NewHeadLoaction = NewHeadLoaction + vec2<int>(0, 1);
		break;
	case MoveDirection::LEFT:
		NewHeadLoaction = NewHeadLoaction + vec2<int>(-1, 0);
		break;
	case MoveDirection::RIGHT:
		NewHeadLoaction = NewHeadLoaction + vec2<int>(1, 0);
		break;
	}

	auto WorldSize = this->World->getWorldSize();

	if (NewHeadLoaction.x >= WorldSize.x)
		NewHeadLoaction.x = 0;

	else if (NewHeadLoaction.x < 0)
		NewHeadLoaction.x = WorldSize.x - 1;

	if (NewHeadLoaction.y >= WorldSize.y)
		NewHeadLoaction.y = 0;

	else if (NewHeadLoaction.y < 0)
		NewHeadLoaction.y = WorldSize.y - 1;


	auto Object = this->World->getTypeOfObject(NewHeadLoaction);

	switch (Object)
	{
	case ObjectType::NONE:
		this->slideHead(NewHeadLoaction, false);
		break;
	case ObjectType::TREAT:
		this->slideHead(NewHeadLoaction, true);
		this->World->eatTreat();
		break;
	case ObjectType::HEAD:
	case ObjectType::BODY:
	case ObjectType::TAIL:
		this->HitItself = true;
	}
}

ObjectType Snake::getObjectType(vec2<int> Coordinate)
{
	if (this->Head->getPosition() == Coordinate)
		return ObjectType::HEAD;

	for (int Index = 0; Index < this->Body.size(); Index++)
	{
		if (this->Body[Index]->getPosition() == Coordinate)
		{
			if (this->Body.size() - 1 == Index)
				return ObjectType::TAIL;

			return ObjectType::BODY;
		}
	}

	return ObjectType::NONE;
}

std::vector<Entity> Snake::getRenderInfo()
{
	std::vector<Entity> Result = { { ObjectType::HEAD, this->Head->getPosition() } };

	for (int Index = 0; Index < this->Body.size() - 1; Index++)
	{
		Result.push_back({ ObjectType::BODY, this->Body[Index]->getPosition()});
	}

	Result.push_back({ ObjectType::TAIL, this->Body[this->Body.size() -  1]->getPosition()});

	return Result;
}

bool Snake::isHitItself()
{
	return this->HitItself;
}

void Snake::slideHead(vec2<int> NewHeadLocation, bool EatTreat)
{
	vec2<int> LocationForCurentBodyCell = this->Head->getPosition();

	this->Head->setNewPosition(NewHeadLocation);

	for (int Index = 0; Index < this->Body.size(); Index++)
	{
		vec2<int> LocationForNextBodyCell = this->Body[Index]->getPosition();

		this->Body[Index]->setNewPosition(LocationForCurentBodyCell);

		LocationForCurentBodyCell = LocationForNextBodyCell;
	}

	if (EatTreat)
	{
		this->Body.push_back(std::make_unique<Object>(LocationForCurentBodyCell));
	}
}
