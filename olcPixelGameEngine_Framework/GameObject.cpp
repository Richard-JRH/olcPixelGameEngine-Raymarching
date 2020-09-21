#include "GameObject.h"

GameObject::GameObject()
{
	pos = Vector2( 0.f );
	type = GameObject::TYPE::GO_CIRCLE;
	scale = 0.f;
}

GameObject::~GameObject()
{
}

void GameObject::SetPos(Vector2 _pos)
{
	this->pos = _pos;
}

void GameObject::SetPos(float _x, float _y)
{
	this->pos.x = _x;
	this->pos.y = _y;
}

Vector2 GameObject::GetPos()
{
	return this->pos;
}

void GameObject::SetScale(float _scale)
{
	this->scale = _scale;
}

float GameObject::GetScale()
{
	return this->scale;
}

void GameObject::SetType(GameObject::TYPE _type)
{
	this->type = _type;
}

GameObject::TYPE GameObject::GetType()
{
	return this->type;
}




