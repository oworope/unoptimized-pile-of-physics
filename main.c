#include <stdlib.h>
#include <time.h>

#include "app.h"
#include "solver.h"

int main()
{
	ctx_t context;
	app_init(&context);

	solver_t solver = {.gravity = vec_create(0, 1000)};
	object_pool_t pool = object_pool_create(250);

	srand(time(NULL));


	for (int i = 0; i < 250; i++)
	{
		object_pool_add(&pool, object_create(vec_create(50 + i * 10, 50 + i * 10)));
		pool.data[i].object.r = 10;
		pool.data[i].object.g = 10;
		pool.data[i].object.b = rand() % 255;
		pool.data[i].object.rad = 10 + rand() % 10;
	}

	double dt;
	while (context.running)
	{
		dt = app_handle_events(&context);
		const int substeps = 16;
		double subdt = dt / substeps;
		for (int i = 0; i < substeps; i++)
		{
			solver_update(&solver, &pool, subdt);
		}
		app_render_objects(&context, &pool);
		app_render_present(&context);
	}

	object_pool_destroy(&pool);
	app_quit(&context);
	return 0;
}
