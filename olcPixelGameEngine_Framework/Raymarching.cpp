#include "Raymarching.h"

Raymarching::Raymarching()
{
}

Raymarching::~Raymarching()
{
}

bool Raymarching::OnUserCreate()
{
	// Init player
	player = new Player;
	player->SetPos( Vector2(ScreenWidth() / 2, ScreenHeight() / 2) );
	player->SetRotation( 0.f );
	player->SetSize( PLAYER_SIZE );

	// Init GameObjects
	Circle* go1 = new Circle( Vector2( 376, 312 ), 85.f );
	Circle* go2 = new Circle( Vector2( 317, 980 ), 120.f);
	Circle* go3 = new Circle( Vector2( 913, 922 ), 45.f );
	Circle* go4 = new Circle( Vector2( 1983, 1122 ), 155.f);
	Circle* go5 = new Circle( Vector2( 1842, 572 ), 68.f);
	Circle* go6 = new Circle( Vector2( 109, 96 ), 55.f);
	goList = { go1, go2, go3, go4, go5, go6 };

	// Misc
	selectedGO = nullptr;

	return true;
}

bool Raymarching::OnUserUpdate(float dt)
{
	Render( dt );
	InputHandler( dt );
	CollisionHandler( dt );
	ConstrainPlayer();

	// Update selected GameObject position
	if (selectedGO != nullptr)
		selectedGO->SetPos( GetMouseX(), GetMouseY() );

	// DEBUG
	// std::cout << player->GetRotation() << std::endl;
	// std::cout << GetMouseX() << ", " << GetMouseY() << std::endl;
	// std::cout << GetMouseWheel() << std::endl;

	return true;
}

void Raymarching::Render(const float& dt)
{
	Clear( BACKGROUND_COLOUR );

	// Render GameObjects
	for (GameObject* &go : goList)
	{
		switch ( go->GetType() )
		{
			case GameObject::TYPE::GO_CIRCLE:
			{
				FillCircle(go->GetPos().x, go->GetPos().y,
						   go->GetScale(), olc::BLACK);
				break;
			}
			case GameObject::TYPE::GO_SQUARE:
			{

				break;
			}
			default:
			{
				throw ("GameObject has invalid type");
				break;
			}
		}
	}

	// Render Player 
	FillCircle( player->GetPos().x, player->GetPos().y, player->GetSize(), PLAYER_COLOUR );

	// Render circles
	float playerAngle = DegreeToRadian( player->GetRotation() );
	Vector2 pos = player->GetPos();
	Vector2 dir(cosf( playerAngle ), sinf( playerAngle ));

	for (int i = 0; i < MAX_ITR; ++i)
	{
		GameObject* nearestGO = nullptr;
		float minDist = FLT_MAX;

		GetNearestGO( pos, nearestGO, minDist );

		if (minDist > 3000.f)
		{
			/*DrawLine(player->GetPos().x, player->GetPos().y,
					 player->GetPos().x * LINE_LENGTH, player->GetPos().y * LINE_LENGTH,
					 olc::WHITE);*/
			break;
		}

		if (minDist < 3.f)
		{
			Vector2 endPoint = pos + (dir * minDist);
			DrawLine( player->GetPos().x, player->GetPos().y, endPoint.x, endPoint.y, olc::WHITE );
			break;
		}

		DrawCircle( pos.x, pos.y, minDist, olc::GREY );
		FillCircle( pos.x, pos.y, 3, olc::WHITE );
		pos += ( dir * minDist );
	}
}

void Raymarching::InputHandler(const float& dt)
{
	// W - Move forward
	if (GetKey(olc::Key::W).bHeld)
	{
		float playerAngle = DegreeToRadian( player->GetRotation() );
		Vector2 dir(cosf( playerAngle ), sinf( playerAngle ));

		player->Move( dir * PLAYER_SPEED * dt );
	}
	// A - Rotate left
	if (GetKey(olc::Key::A).bHeld)
	{
		player->SetRotation( player->GetRotation() - PLAYER_ROTATE_SPEED * dt );

		if (player->GetRotation() < 0.f)
			player->SetRotation( player->GetRotation() + 360.f );
	}
	// S - Move backward
	if (GetKey(olc::Key::S).bHeld)
	{
		float playerAngle = DegreeToRadian( player->GetRotation() );
		Vector2 dir(cosf( playerAngle ), sinf( playerAngle ));

		player->Move( -dir * PLAYER_SPEED * dt );
	}
	// D - Rotate right
	if (GetKey(olc::Key::D).bHeld)
	{
		player->SetRotation( player->GetRotation() + PLAYER_ROTATE_SPEED * dt );

		if (player->GetRotation() > 360.f)
			player->SetRotation( player->GetRotation() - 360.f );
	}
	// LMB - Select GameObject
	if (GetMouse(0).bHeld)
	{
		Vector2 mousePos( GetMouseX(), GetMouseY() );

		for (GameObject* &go : goList)
		{
			Circle* goCircle = static_cast<Circle*>( go );
			Vector2 displacement = goCircle->GetPos() - mousePos;

			if (displacement.Magnitude() < goCircle->GetScale())
			{
				selectedGO = goCircle;
				break;
			}
		}
	}
	// LMB - Create new GameObject
	if (GetMouse(0).bPressed)
	{
		if (selectedGO == nullptr)
		{
			float randScale = 30 + (rand() % 250);
			Circle* goCircle = new Circle(Vector2(GetMouseX(), GetMouseY()), randScale);
			goList.push_back(goCircle);
		}
	}
	if (GetMouse(0).bReleased)
	{
		if (selectedGO != nullptr)
			selectedGO = nullptr;
	}
	// RMB - Delete object
	if (GetMouse(1).bPressed)
	{
		if (selectedGO != nullptr)
			selectedGO = nullptr;
	}
	// Scroll up, increase GameObject scale
	if (GetMouseWheel() > 0.f)
	{
		if (selectedGO != nullptr)
		{
			selectedGO->SetScale( selectedGO->GetScale() + SCALE_SPEED * dt );
			ClampScale( selectedGO );
		}
	}
	// Scroll down, decrease GameObject scale
	if (GetMouseWheel() < 0.f)
	{
		if (selectedGO != nullptr)
		{
			if (selectedGO != nullptr)
			{
				selectedGO->SetScale( selectedGO->GetScale() - SCALE_SPEED * dt );
				ClampScale( selectedGO );
			}
		}
	}
}

void Raymarching::ConstrainPlayer()
{
	if (player->GetPos().x < player->GetSize()) 
	{
		player->SetPos( player->GetSize(), player->GetPos().y );
	}
	if (player->GetPos().y < player->GetSize())
	{
		player->SetPos( player->GetPos().x, player->GetSize() );
	}
	if (player->GetPos().x > ScreenWidth() - player->GetSize())
	{
		player->SetPos( ScreenWidth() - player->GetSize(), player->GetPos().y );
	}
	if (player->GetPos().y > ScreenHeight() - player->GetSize())
	{
		player->SetPos( player->GetPos().x, ScreenHeight() - player->GetSize() );
	}
}

void Raymarching::CollisionHandler(const float& dt)
{
	if (CheckForCollision( dt ) == true)
		CollisionResponse( dt );
}

/*
	Helper Functions
*/
float Raymarching::DegreeToRadian( const float &theta )
{
	return theta * (PI / 180.f);
}

void Raymarching::Clamp(float &val, const float &min, const float &max)
{
	if (val < min) val = min;
	if (val > max) val = max;
}

void Raymarching::ClampScale(GameObject* &go)
{
	if (go->GetScale() < MIN_SCALE) go->SetScale( MIN_SCALE );
	if (go->GetScale() > MAX_SCALE) go->SetScale( MAX_SCALE );
}

GameObject* Raymarching::GetNearestGO(GameObject* ptr)
{
	float minDist = FLT_MAX;
	GameObject* nearestGO = nullptr;

	for (GameObject* &go : goList)
	{
		Vector2 displacement = ptr->GetPos() - go->GetPos();
		float dist = displacement.Magnitude();

		if (dist < minDist)
		{
			minDist = dist;
			nearestGO = go;
		}
	}

	return nearestGO;
}

GameObject* Raymarching::GetNearestGO(Vector2 pos)
{
	float minDist = FLT_MAX;
	GameObject* nearestGO = nullptr;

	for (GameObject* &go : goList)
	{
		Vector2 displacement = pos - go->GetPos();
		float dist = displacement.Magnitude();

		if (dist < minDist)
		{
			minDist = dist;
			nearestGO = go;
		}
	}

	return nearestGO;
}

void Raymarching::GetNearestGO(Vector2 pos, GameObject*& retGO, float& retDist)
{
	float minDist = FLT_MAX;

	for (GameObject* &go : goList)
	{
		Vector2 displacement = go->GetPos() - pos;
		float distance = displacement.Magnitude() - go->GetScale();

		if (distance < minDist)
		{
			minDist = distance;
			retGO = go;
		}
	}

	retDist = minDist;
}

bool Raymarching::CheckForCollision(const float& dt)
{
	return false;
}

void Raymarching::CollisionResponse(const float& dt)
{
}
