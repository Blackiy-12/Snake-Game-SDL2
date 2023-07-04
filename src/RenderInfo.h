#pragma once

#include <vector>
#include "vec2.h"

enum class ObjectType
{
	NONE,
	TREAT,
	HEAD,
	BODY,
	TAIL
};

struct Entity
{
	ObjectType Type;

	vec2<int> Position;
};

struct RenderInfo
{
	std::vector<Entity> SnakeInfo;

	Entity TreatInfo;

	vec2<int> Size;
};