#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include "raylib.h"

#define SCREEN_SIZE 1000
#define FPS 60

#define RADIUS 5
#define COLOR RED

typedef struct Edge
{
	Vector3 *a;
	Vector3 *b;
} Edge;

void draw_point(Vector2 point);
void draw_line(Vector2 point1, Vector2 point2);
void draw_object(Edge *object[], size_t nr_points);

Vector2 project(Vector3 *point);
Vector2 display(Vector2 point);

void translate(Vector3 *object[], size_t nr_points,  float dx, float dy, float dz);
void rotate(Vector3 **object, size_t nr_points, float phi_x, float phi_y, float phi_z);
void rotate_x(Vector3 *object[], size_t nr_points, float phi);
void rotate_y(Vector3 *object[], size_t nr_points, float phi);
void rotate_z(Vector3 *object[], size_t nr_points, float phi);

Vector3 get_center(Vector3 **object_points, size_t nr_points);


int main()
{
	//define scene
	Vector3 p0 = {1.0, 1.0, 4.0};
	Vector3 p1 = {1.0, -1.0, 4.0};
	Vector3 p2 = {-1.0, -1.0, 4.0};
	Vector3 p3 = {-1.0, 1.0, 4.0};
	Vector3 p4 = {1.0, 1.0, 6.0};
	Vector3 p5 = {1.0, -1.0, 6.0};
	Vector3 p6 = {-1.0, -1.0, 6.0};
	Vector3 p7 = {-1.0, 1.0, 6.0};

	Edge e0 = {&p0, &p1};
	Edge e1 = {&p1, &p2};
	Edge e2 = {&p2, &p3};
	Edge e3 = {&p3, &p0};
	Edge e4 = {&p4, &p5};
	Edge e5 = {&p5, &p6};
	Edge e6 = {&p6, &p7};
	Edge e7 = {&p7, &p4};
	Edge e8 = {&p0, &p4};
	Edge e9 = {&p1, &p5};
	Edge e10 = {&p2, &p6};
	Edge e11 = {&p3, &p7};

	Vector3 *cube_points[] = {&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7};
	Edge *cube_edges[] = {&e0, &e1, &e2, &e3, &e4, &e5, &e6, &e7, &e8, &e9, &e10, &e11};

	size_t nr_points_cube = sizeof(cube_points) / sizeof(cube_points[0]);
	size_t nr_edges_cube = sizeof(cube_edges) / sizeof(cube_edges[0]);

	float x_center_cube = 0.0;
	float y_center_cube = 0.0;
	float z_center_cube = 5.0;
	
	float delta_x = 0.001;
	float delta_y = 0.002;
	float delta_z = 0.01;
	float phi_x = 0.01;
	float phi_y = 0.04;
	float phi_z = 0.01;

	InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Scene");
	SetTargetFPS(FPS);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		draw_object(cube_edges, nr_edges_cube);

		translate(cube_points, nr_points_cube, delta_x, delta_y, delta_z);
		rotate(cube_points, nr_points_cube, phi_x, phi_y, phi_z); 

		EndDrawing();
	}

	CloseWindow();
}


void draw_point(Vector2 point)
{
	DrawCircle(point.x, point.y, RADIUS, COLOR);
}

void draw_line(Vector2 point1, Vector2 point2)
{
	DrawLine(point1.x, point1.y, point2.x, point2.y, COLOR);
}

void draw_object(Edge **object, size_t nr_edges)
{
	for (size_t i = 0; i < nr_edges; i++)
	{
		Vector2 p1 = display(project(object[i]->a));
		Vector2 p2 = display(project(object[i]->b));
		draw_line(p1, p2);
	}
}

Vector2 display(Vector2 point)
{
	point.x = SCREEN_SIZE/2 * (point.x + 1);
	point.y = SCREEN_SIZE/2 * (point.y + 1);
	return point;
}

Vector2 project(Vector3 *point)
{
	Vector2 vec = {point->x/point->z, point->y/point->z};
	return vec;
}

void translate(Vector3 **object, size_t nr_points, float dx, float dy, float dz)
{
	for (int i = 0; i < nr_points; i++)
	{
		object[i]->x += dx;
		object[i]->y += dy;
		object[i]->z += dz;
	}
}

void rotate(Vector3 **object, size_t nr_points, float phi_x, float phi_y, float phi_z)
{
	rotate_x(object, nr_points, phi_x);
	rotate_y(object, nr_points, phi_y);
	rotate_z(object, nr_points, phi_z);
}

void rotate_x(Vector3 **object, size_t nr_points, float phi)
{
	Vector3 center = get_center(object, nr_points);
	for (int i = 0; i < nr_points; i++)
	{
		float y_prime = object[i]->y - center.y;
		float z_prime = object[i]->z - center.z;
		object[i]->y = center.y + y_prime*cos(phi) - z_prime*sin(phi);
		object[i]->z = center.z + y_prime*sin(phi) + z_prime*cos(phi);
	}
}

void rotate_y(Vector3 **object, size_t nr_points, float phi)
{
	Vector3 center = get_center(object, nr_points);
	for (int i = 0; i < nr_points; i++)
	{
		float x_prime = object[i]->x - center.x;
		float z_prime = object[i]->z - center.z;
		object[i]->x = center.x + x_prime*cos(phi) + z_prime*sin(phi);
		object[i]->z = center.z - x_prime*sin(phi) + z_prime*cos(phi);
	}
}

void rotate_z(Vector3 **object, size_t nr_points, float phi)
{
	Vector3 center = get_center(object, nr_points);
	for (int i = 0; i < nr_points; i++)
	{
		float x_prime = object[i]->x - center.x;
		float y_prime = object[i]->y - center.y;
		object[i]->x = center.x + x_prime*cos(phi) - y_prime*sin(phi);
		object[i]->y = center.y + x_prime*sin(phi) + y_prime*cos(phi);
	}
}

Vector3 get_center(Vector3 **object_points, size_t nr_points)
{
	float x = 0;
	float y = 0;
	float z = 0;
	for (int i = 0; i < nr_points; i++)
	{
		x += object_points[i]->x;
		y += object_points[i]->y;
		z += object_points[i]->z;
	}
	Vector3 center = {x/nr_points, y/nr_points, z/nr_points};
	return center;
}

