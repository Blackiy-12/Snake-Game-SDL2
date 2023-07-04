#pragma once

#include "vec2.h"

class Object
{
public:

	Object(vec2<int> StartPosition);

	~Object();

	void setNewPosition(vec2<int> NewPosition);

	vec2<int> getPosition();

private:

	vec2<int> Position;

};

