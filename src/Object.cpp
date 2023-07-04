#include "Object.h"

Object::Object(vec2<int> StartPosition) :
    Position(StartPosition)
{
}

Object::~Object()
{
}

void Object::setNewPosition(vec2<int> NewPosition)
{
    this->Position = NewPosition;
}

vec2<int> Object::getPosition()
{
    return this->Position;
}
