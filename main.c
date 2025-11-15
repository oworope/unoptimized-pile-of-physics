#include "app.h"
#include "object_pool.h"
#include "solver.h"
#include "vector.h"

int main()
{
	ctx_t context;
	app_init(&context);

	solver_t solver = {.gravity = vec_create(0, 1000)};
	object_pool_t pool = object_pool_create(4);

	object_pool_add(&pool, object_create(vec_create(400, 220)));
	object_pool_add(&pool, object_create(vec_create(450, 170)));
	object_pool_add(&pool, object_create(vec_create(100, 100)));
	object_pool_add(&pool, object_create(vec_create(250, 50)));

	pool.data[0].object.g = 60;
	pool.data[0].object.b = 60;
	pool.data[0].object.rad = 20;

	// pool.data[1].object.r = 60;
	// pool.data[1].object.g = 60;

	pool.data[2].object.r = 30;
	pool.data[2].object.b = 30;
	pool.data[2].object.rad = 25;

	pool.data[3].object.r = 140;
	pool.data[3].object.g = 140;
	pool.data[3].object.b = 140;
	pool.data[3].object.rad = 40;


	double dt;
	while (context.running)
	{
		dt = app_handle_events(&context);
		solver_update(&solver, &pool, dt);
		app_render_objects(&context, &pool);
		app_render_present(&context);
	}

	object_pool_destroy(&pool);
	app_quit(&context);
	return 0;
}
