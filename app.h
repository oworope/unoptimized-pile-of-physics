#pragma once
#include <SDL3/SDL.h>
#include "object_pool.h"
#include "solver.h"

typedef struct ctx_s
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running;

	unsigned int current_time, last_time;
	double dt;
}
ctx_t;

void app_init(ctx_t* context);
void app_quit(ctx_t* context);
double app_handle_events(ctx_t* context, solver_t* solver);
void app_render_present(ctx_t* context);
void app_render_objects(ctx_t* context, object_pool_t* pool);
