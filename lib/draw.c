#include "draw.h"

void draw_point(Vector2 point)
{
	DrawCircle(point.x, point.y, RADIUS, COLOR);
}

void draw_line(Vector2 point1, Vector2 point2)
{
	DrawLine(point1.x, point1.y, point2.x, point2.y, COLOR);
}
//_DRAW
void draw_object(Object object)
{
	for (size_t i = 0; i < object.nr_edges; i++)
	{
		Vector2 p1 = display(project(object.edges[i]->a));
		Vector2 p2 = display(project(object.edges[i]->b));
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

//_TRANSLATE
void translate(Object object, float dx, float dy, float dz)
{
	for (int i = 0; i < object.nr_points; i++)
	{
		object.points[i]->x += dx;
		object.points[i]->y += dy;
		object.points[i]->z += dz;
	}
}

//_ROTATIONS
void rotate(Object object, float phi_x, float phi_y, float phi_z)
{
	rotate_x(object, phi_x);
	rotate_y(object, phi_y);
	rotate_z(object, phi_z);
}

void rotate_x(Object object, float phi)
{
	Vector3 center = get_center(object);
	for (int i = 0; i < object.nr_points; i++)
	{
		float y_prime = object.points[i]->y - center.y;
		float z_prime = object.points[i]->z - center.z;
		object.points[i]->y = center.y + y_prime*cos(phi) - z_prime*sin(phi);
		object.points[i]->z = center.z + y_prime*sin(phi) + z_prime*cos(phi);
	}
}

void rotate_y(Object object, float phi)
{
	Vector3 center = get_center(object);
	for (int i = 0; i < object.nr_points; i++)
	{
		float x_prime = object.points[i]->x - center.x;
		float z_prime = object.points[i]->z - center.z;
		object.points[i]->x = center.x + x_prime*cos(phi) + z_prime*sin(phi);
		object.points[i]->z = center.z - x_prime*sin(phi) + z_prime*cos(phi);
	}
}

void rotate_z(Object object, float phi)
{
	Vector3 center = get_center(object);
	for (int i = 0; i < object.nr_points; i++)
	{
		float x_prime = object.points[i]->x - center.x;
		float y_prime = object.points[i]->y - center.y;
		object.points[i]->x = center.x + x_prime*cos(phi) - y_prime*sin(phi);
		object.points[i]->y = center.y + x_prime*sin(phi) + y_prime*cos(phi);
	}
}

Vector3 get_center(Object object)
{
	float x = 0;
	float y = 0;
	float z = 0;
	for (int i = 0; i < object.nr_points; i++)
	{
		x += object.points[i]->x;
		y += object.points[i]->y;
		z += object.points[i]->z;
	}
	Vector3 center = {x/object.nr_points, y/object.nr_points, z/object.nr_points};
	return center;
}

Object cube(float length, Vector3 center)
{
	length = length/2;
    Object object;

    object.nr_points = 8;
    object.nr_edges  = 12;

    object.points = malloc(object.nr_points * sizeof *object.points);
    object.edges  = malloc(object.nr_edges  * sizeof *object.edges);

    Vector3 *p0 = malloc(sizeof *p0); *p0 = (Vector3){center.x + length, center.y + length, center.z - length};
    Vector3 *p1 = malloc(sizeof *p1); *p1 = (Vector3){center.x + length, center.y - length, center.z - length};
    Vector3 *p2 = malloc(sizeof *p2); *p2 = (Vector3){center.x - length, center.y - length, center.z - length};
    Vector3 *p3 = malloc(sizeof *p3); *p3 = (Vector3){center.x - length, center.y + length, center.z - length};
    Vector3 *p4 = malloc(sizeof *p4); *p4 = (Vector3){center.x + length, center.y + length, center.z + length};
    Vector3 *p5 = malloc(sizeof *p5); *p5 = (Vector3){center.x + length, center.y - length, center.z + length};
    Vector3 *p6 = malloc(sizeof *p6); *p6 = (Vector3){center.x - length, center.y - length, center.z + length};
    Vector3 *p7 = malloc(sizeof *p7); *p7 = (Vector3){center.x - length, center.y + length, center.z + length};

    object.points[0] = p0; object.points[1] = p1;
    object.points[2] = p2; object.points[3] = p3;
    object.points[4] = p4; object.points[5] = p5;
    object.points[6] = p6; object.points[7] = p7;

    object.edges[0]  = malloc(sizeof(Edge)); *object.edges[0]  = (Edge){p0,p1};
    object.edges[1]  = malloc(sizeof(Edge)); *object.edges[1]  = (Edge){p1,p2};
    object.edges[2]  = malloc(sizeof(Edge)); *object.edges[2]  = (Edge){p2,p3};
    object.edges[3]  = malloc(sizeof(Edge)); *object.edges[3]  = (Edge){p3,p0};
    object.edges[4]  = malloc(sizeof(Edge)); *object.edges[4]  = (Edge){p4,p5};
    object.edges[5]  = malloc(sizeof(Edge)); *object.edges[5]  = (Edge){p5,p6};
    object.edges[6]  = malloc(sizeof(Edge)); *object.edges[6]  = (Edge){p6,p7};
    object.edges[7]  = malloc(sizeof(Edge)); *object.edges[7]  = (Edge){p7,p4};
    object.edges[8]  = malloc(sizeof(Edge)); *object.edges[8]  = (Edge){p0,p4};
    object.edges[9]  = malloc(sizeof(Edge)); *object.edges[9]  = (Edge){p1,p5};
    object.edges[10] = malloc(sizeof(Edge)); *object.edges[10] = (Edge){p2,p6};
    object.edges[11] = malloc(sizeof(Edge)); *object.edges[11] = (Edge){p3,p7};

    return object;
}
