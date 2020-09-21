#include "Circle.h"

Circle::Circle()
{
	this->pos = Vector2( 0.f );
	this->scale = 0;
	this->type = GameObject::TYPE::GO_CIRCLE;
}

Circle::Circle(Vector2 _pos, float _scale)
{
	this->pos = _pos;
	this->scale = _scale;
	this->type = GameObject::TYPE::GO_CIRCLE;
}

Circle::~Circle()
{
}
