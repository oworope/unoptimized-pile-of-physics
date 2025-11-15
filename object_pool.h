#pragma once
#include <stdbool.h>
#include "object.h"

typedef struct object_wrap_s
{
	object_t object;
	bool is_used;
}
object_wrap_t;

/// Object pool contains n of objects,
/// where n = size of object pool.
///
/// Replaces std::vector.
typedef struct object_pool_s
{
	unsigned int size;
	unsigned int free_index;
	object_wrap_t* data;
}
object_pool_t;

object_pool_t object_pool_create(int size);
void object_pool_destroy(object_pool_t* pool);
void object_pool_add(object_pool_t* pool, object_t obj);
