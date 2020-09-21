#include "Vector2.h"

Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(float _val)
{
	this->x = _val;
	this->y = _val;
}

Vector2::Vector2(float _x, float _y)
{
	this->x = _x;
	this->y = _y;
}

Vector2::~Vector2()
{
}

void Vector2::SetX(float _x)
{
	this->x = _x;
}

void Vector2::SetY(float _y)
{
	this->y = _y;
}

void Vector2::SetXY(float _x, float _y)
{
	this->x = _x;
	this->y = _y;
}

Vector2 Vector2::UpLeft() const
{
	return Vector2(-1, -1);
}

Vector2 Vector2::Up() const
{
	return Vector2(0, -1);
}

Vector2 Vector2::UpRight() const
{
	return Vector2(1, -1);
}

Vector2 Vector2::Right() const
{
	return Vector2(1, 0);
}

Vector2 Vector2::BotRight() const
{
	return Vector2(1, 1);
}

Vector2 Vector2::Down() const
{
	return Vector2(0, 1);
}

Vector2 Vector2::BotLeft() const
{
	return Vector2(-1, 1);
}

Vector2 Vector2::Left() const
{
	return Vector2(-1, 0);
}

Vector2 Vector2::Zero() const
{
	return Vector2( 0.f );
}


Vector2 Vector2::operator+(const Vector2 &rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

void Vector2::operator+=(const Vector2& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator-(void) const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator*(const float& scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

float Vector2::Magnitude()
{
	return sqrtf((x * x) + (y * y));
}

Vector2 Vector2::Normalized()
{
	float length = this->Magnitude();

	if (length != 0.0f)
		return Vector2( x / length, y / length);
}


