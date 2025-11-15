#include <stdlib.h>
#include <stdio.h>
#include "object_pool.h"

object_pool_t object_pool_create(int size)
{
	object_pool_t t;
	t.size = size;
	printf("allocating %ld of bytes\n", sizeof(object_wrap_t) * t.size);
	t.data = (object_wrap_t*)malloc(sizeof(object_wrap_t) * t.size);
	t.free_index = 0;

	for (int i = 0; i < size; i++)
	{
		t.data[i].is_used = false;
	}

	return t;
}

void object_pool_destroy(object_pool_t* pool)
{
	free(pool->data);
}

void object_pool_add(object_pool_t *pool, object_t obj)
{
	if (pool->free_index == pool->size)
	{
		// TODO: realloc, now should crash.
		printf("todo: reallocating, not crashing\n");
	}
	pool->data[pool->free_index].is_used = true;
	pool->data[pool->free_index].object = obj;
	pool->free_index += 1;
}
