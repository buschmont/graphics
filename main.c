#include <stdio.h>
#include "lib/draw.h"

#define FPS 60

int main()
{
	float delta_x = 0.0;
	float delta_y = 0.0;
	float delta_z = 0.00;
	float phi_x = 0.01;
	float phi_y = 0.04;
	float phi_z = 0.01;

	Vector3 center0 = {-1.0, 0.0, 5.0};
	Vector3 center1 = {5.0, 2.0, 10.0};
	Object cube0 = cube(2.5, center0);
	Object cube1 = cube(1.5, center1);

	InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Scene");
	SetTargetFPS(FPS);

	//_LOOP
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		draw_object(cube0);
		draw_object(cube1);
		translate(cube0, delta_x, delta_y, delta_z);
		translate(cube1, delta_x, delta_y, delta_z);
		rotate(cube0, -phi_x, phi_y, -phi_z); 
		rotate(cube1, phi_x, phi_y, phi_z); 

		EndDrawing();
	}

	CloseWindow();
}
