#pragma once
#include "vector.h"

typedef struct object_s
{
	vector_t prev_pos, cur_pos, accel;
	unsigned short r, g, b, rad;
}
object_t;

object_t object_create(vector_t pos);
void object_update(object_t* obj, double dt);
void object_accelerate(object_t* obj, vector_t acc);
