#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"

#define RADIUS 5
#define COLOR RED
#define SCREEN_SIZE 1000

typedef struct Edge
{
	Vector3 *a;
	Vector3 *b;
} Edge;

typedef struct Object
{
	Vector3 **points;
	Edge **edges;
	size_t nr_points;
	size_t nr_edges;
} Object;

Object cube(float length, Vector3 center);

void draw_point(Vector2 point);
void draw_line(Vector2 point1, Vector2 point2);
void draw_object(Object object);

Vector2 project(Vector3 *point);
Vector2 display(Vector2 point);

void translate(Object object, float dx, float dy, float dz);
void rotate   (Object object, float phi_x, float phi_y, float phi_z);
void rotate_x (Object object, float phi);
void rotate_y (Object object, float phi);
void rotate_z (Object object, float phi);

Vector3 get_center(Object object);
