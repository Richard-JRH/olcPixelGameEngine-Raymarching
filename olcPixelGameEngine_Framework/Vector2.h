#ifndef _VECTOR_2_H
#define _VECTOR_2_H

#include <math.h>

class Vector2
{
public:
	float x;
	float y;
public:
	Vector2();
	Vector2(float _val);
	Vector2(float _x, float _y);
	~Vector2();

	void SetX(float _x);
	void SetY(float _y);
	void SetXY(float _x, float _y);

	Vector2 UpLeft()   const;
	Vector2 Up()	   const;
	Vector2 UpRight()  const;
	Vector2 Right()	   const;
	Vector2 BotRight() const;
	Vector2 Down()	   const;
	Vector2 BotLeft()  const;
	Vector2 Left()	   const;
	Vector2 Zero()	   const;

	Vector2 operator+(const Vector2 &rhs) const;
	void operator+=(const Vector2& rhs);

	Vector2 operator-(const Vector2& rhs) const;

	Vector2 operator-(void) const;
	Vector2 operator*(const float &scalar) const;

	float Magnitude();
	Vector2 Normalized();
};

#endif

