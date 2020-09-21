#ifndef _RAYMARCHING_H_
#define _RAYMARCHING_H_

#include "olcPixelGameEngine.h"

#include "Player.h"
#include "Circle.h"
#include "Square.h";

class Raymarching : public olc::PixelGameEngine
{
public:
	const float		 PLAYER_SPEED = 180.f;
	const float		 PLAYER_SIZE = 25.f;
	const float		 PLAYER_ROTATE_SPEED = 45.f;
	const olc::Pixel PLAYER_COLOUR = olc::WHITE;

	const float		 MIN_SCALE = 30.f;
	const float		 MAX_SCALE = 300.f;
	const float		 SCALE_SPEED = 450.f;

	const float		 LINE_LENGTH = 3500.f;
	const float		 PI = 3.141592653589793f;
	static const int MAX_ITR = 20;
	const olc::Pixel BACKGROUND_COLOUR = olc::Pixel(50, 50, 50);
private:
	Player	   *player;
	GameObject *selectedGO;

	std::vector<GameObject*> goList;
public:
	Raymarching();
	~Raymarching();

	bool OnUserCreate();
	bool OnUserUpdate(float dt);
	void Render(const float &dt);
	void InputHandler(const float &dt);
	void ConstrainPlayer();

	void CollisionHandler(const float &dt);
	bool CheckForCollision(const float &dt);
	void CollisionResponse(const float &dt);

	// Helper funcs
	GameObject* GetNearestGO( GameObject* ptr );
	GameObject* GetNearestGO( Vector2 pos );
	void GetNearestGO( Vector2 pos, GameObject* &retGO, float &retDist );

	float DegreeToRadian( const float &theta ); 
	void Clamp( float &val, const float &min, const float &max );
	void ClampScale( GameObject* &go );
};

#endif

