#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Vector2.h"

class GameObject
{
public:
	enum class TYPE
	{
		GO_CIRCLE,
		GO_SQUARE,

		NUM_TYPES
	};
protected:
	TYPE type;
	Vector2 pos;
	float scale;
public:
	GameObject();
	~GameObject();

	// Getters/Setters
	void SetPos( Vector2 _pos );
	void SetPos( float _x, float _y );
	Vector2 GetPos();

	void SetScale( float _scale );
	float GetScale();

	void SetType( GameObject::TYPE _type );
	GameObject::TYPE GetType();
};

#endif

