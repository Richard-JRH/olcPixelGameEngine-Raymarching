#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Vector2.h"

class Player
{
private:
	Vector2 pos;

	float rotation;	
	float size;
public:
	Player();
	~Player();

	// Getters/Setters
	void SetPos( Vector2 _pos );
	void SetPos( float _x, float _y );
	Vector2 GetPos();

	void SetRotation(float _rotation);
	float GetRotation();

	void SetSize(float _size);
	float GetSize();

	void Move( Vector2 _translation );
};

#endif

