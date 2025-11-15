#include "object.h"

static vector_t null_vec = {.x = 0, .y = 0};

object_t object_create(vector_t pos)
{
	object_t a;
	a.accel = null_vec;
	a.cur_pos = pos;
	a.prev_pos = pos;
	a.r = 255;
	a.g = 255;
	a.b = 255;
	a.rad = 30;
	return a;
}

void object_update(object_t* obj, double dt)
{
	// basically means cur_pos = cur_pos + (cur_pos - prev_pos) + accel*dt^2
	const vector_t velocity = vec_sub(obj->cur_pos, obj->prev_pos);
	obj->prev_pos = obj->cur_pos;
	obj->cur_pos = vec_add
	(
		vec_add(obj->cur_pos, velocity),
		vec_mult_scalar(obj->accel, dt*dt)
	);
	obj->accel = null_vec;
}

void object_accelerate(object_t* obj, vector_t acc)
{
	obj->accel = vec_add(obj->accel, acc);
}
