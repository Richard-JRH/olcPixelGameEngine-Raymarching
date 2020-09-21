#include "Player.h"

Player::Player()
{
	pos = Vector2( 0.f );

	rotation = 0.f;
	size = 0.f;
}

Player::~Player()
{
}

void Player::SetPos( Vector2 _pos )
{
	this->pos = _pos;
}

void Player::SetPos(float _x, float _y)
{
	this->pos.x = _x;
	this->pos.y = _y;
}

Vector2 Player::GetPos()
{
	return this->pos;
}

void Player::SetRotation(float _rotation)
{
	this->rotation = _rotation;
}

float Player::GetRotation()
{
	return this->rotation;
}

void Player::SetSize(float _size)
{
	this->size = _size;
}

float Player::GetSize()
{
	return this->size;
}

void Player::Move(Vector2 _translation)
{
	pos += _translation;
}


