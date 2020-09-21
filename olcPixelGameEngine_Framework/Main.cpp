#define OLC_PGE_APPLICATION

#include "Raymarching.h"
#include <ctime>

void main()
{
	srand( time(NULL) );

	Raymarching App;

	if (App.Construct(1920, 1080, 1, 1))
		App.Start();
}