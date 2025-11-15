#pragma once
#include "vector.h"
#include "object_pool.h"

typedef struct solver_s
{
	vector_t gravity;
}
solver_t;

void solver_update(solver_t* solver, object_pool_t* pool, double dt);
