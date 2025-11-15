#include "vector.h"

// TODO: maybe copying structs all the
// time is bad for performance.

vector_t vec_create(double x, double y)
{
	vector_t a;
	a.x = x; a.y = y;
	return a;
};

vector_t vec_add(vector_t a, vector_t b)
{
	vector_t o;
	o.x = a.x + b.x;
	o.y = a.y + b.y;
	return o;
};

vector_t vec_sub(vector_t a, vector_t b)
{
	vector_t o;
	o.x = a.x - b.x;
	o.y = a.y - b.y;
	return o;
};

vector_t vec_mult_scalar(vector_t a, double n)
{
	vector_t o;
	o.x = a.x * n;
	o.y = a.y * n;
	return o;
};

vector_t vec_add_scalar(vector_t a, double n)
{
	vector_t o;
	o.x = a.x + n;
	o.y = a.y + n;
	return o;
};
