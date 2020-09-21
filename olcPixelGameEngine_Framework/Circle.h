#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "GameObject.h"

class Circle : public GameObject
{
public:
	Circle();
	Circle(Vector2 _pos, float _scale);
	~Circle();
};

#endif

