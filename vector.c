#include "vector.h"

// TODO: maybe copying structs all the
// time is bad for performance.

vector_t vec_create(double x, double y)
{
	vector_t a;
	a.x = x; a.y = y;
	return a;
};

void vec_add(vector_t* a, vector_t* b)
{
	a->x += b->x;
	a->y += b->y;
};

void vec_sub(vector_t* a, vector_t* b)
{
	a->x -= b->x;
	a->y -= b->y;
};

void vec_mult_scalar(vector_t* a, double n)
{
	a->x *= n;
	a->y *= n;
};

void vec_add_scalar(vector_t* a, double n)
{
	a->x += n;
	a->y += n;
};
