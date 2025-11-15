#include <math.h>
#include "solver.h"

void solver_update(solver_t* solver, object_pool_t* pool, double dt)
{
	for (int i = 0; i < pool->size; i++)
	{
		if (!pool->data[i].is_used) { return; }
		object_update(&pool->data[i].object, dt);
		object_accelerate(&pool->data[i].object, solver->gravity);

		// Constraint 300 radius
		float distance = sqrt(
			pow(300 - pool->data[i].object.cur_pos.x, 2) +
			pow(300 - pool->data[i].object.cur_pos.y, 2)
		);

		if (distance > 300 - pool->data[i].object.rad)
		{
			vector_t n = vec_create(
				(300 - pool->data[i].object.cur_pos.x) / distance,
				(300 - pool->data[i].object.cur_pos.y) / distance
			);
			// pool->data[i].object.cur_pos = vec_add(pool->data[i].object.cur_pos, vec_mult_scalar(n, (distance - 30)));
			pool->data[i].object.cur_pos.x = 300 - (n.x * (300 - pool->data[i].object.rad)); // x-component adjustment
			pool->data[i].object.cur_pos.y = 300 - (n.y * (300 - pool->data[i].object.rad)); // y-component adjustment
		}

		// Collisions pain
		for (int j = 0; j < pool->size; j++) // Fix the loop variable to j
		{
			if (j == i || !pool->data[j].is_used) { continue; } // Skip self-collision and unused objects

			// Calculate distance between objects
			float dx = pool->data[i].object.cur_pos.x - pool->data[j].object.cur_pos.x;
			float dy = pool->data[i].object.cur_pos.y - pool->data[j].object.cur_pos.y;
			float distance = sqrt(dx * dx + dy * dy);

			int radsum = pool->data[i].object.rad + pool->data[j].object.rad;

			// Check for collision
			if (distance < radsum)
			{
				// Collision response
				float overlap = pool->data[i].object.rad + pool->data[j].object.rad - distance;

				// Normalize the collision vector
				vector_t collision_normal = vec_create(dx / distance, dy / distance);

				// Resolve positions to prevent objects from sticking
				pool->data[i].object.cur_pos.x += collision_normal.x / 2 * (radsum - distance);
				pool->data[i].object.cur_pos.y += collision_normal.y / 2 * (radsum - distance);
				pool->data[j].object.cur_pos.x -= collision_normal.x / 2 * (radsum - distance);
				pool->data[j].object.cur_pos.y -= collision_normal.y / 2 * (radsum - distance);


				// Optional: Handle velocities, apply impulse, etc.
			}
		}
	}
}
