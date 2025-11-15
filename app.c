#include <stdio.h>
#include "app.h"

void SDL_draw_filled_circle(SDL_Renderer* renderer, int center_x, int center_y, int radius)
{
	const int diameter = (radius * 2);

	int x = (radius - 1);
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = (tx - diameter);

	while (x >= y)
	{
		// Each of the following renders an octant of the circle
		SDL_RenderLine(renderer, center_x - y, center_y + x, center_x + y, center_y + x);
		SDL_RenderLine(renderer, center_x - x, center_y + y, center_x + x, center_y + y);
		SDL_RenderLine(renderer, center_x - x, center_y - y, center_x + x, center_y - y);
		SDL_RenderLine(renderer, center_x - y, center_y - x, center_x + y, center_y - x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void app_init(ctx_t* context)
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL_Init failed: %s", SDL_GetError());
	}

	context->window = SDL_CreateWindow("physics-engine", 600, 600, 0);
	if (!context->window) {
		printf("SDL_CreateWindow failed: %s", SDL_GetError());
	} else { printf("window created;\n"); }

	context->renderer = SDL_CreateRenderer(context->window, NULL);
	if (!context->renderer) {
		printf("SDL_CreateRenderer failed: %s", SDL_GetError());
	} else { printf("renderer created;\n"); }

	context->running = true;
	context->last_time = SDL_GetTicks();
	context->current_time = context->last_time;
	context->dt = 0;
};

void app_quit(ctx_t *context)
{
	SDL_DestroyRenderer(context->renderer);
	SDL_DestroyWindow(context->window);
	SDL_Quit();
}

double app_handle_events(ctx_t* context)
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_EVENT_QUIT ||
		(e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE)) {
			context->running = false;
		}
	}
	context->current_time = SDL_GetTicks();
	// Calculate delta time in seconds (converted to double)
	context->dt = (context->current_time - context->last_time) / 1000.0; // Convert ms to seconds
	context->last_time = context->current_time;

	SDL_SetRenderDrawColor(context->renderer, 50, 50, 50, 255);
	SDL_RenderClear(context->renderer);

	return context->dt;
}

void app_render_present(ctx_t* context)
{
	SDL_RenderPresent(context->renderer);
	SDL_Delay(16); // ~60 FPS i hope
}

void app_render_objects(ctx_t* context, object_pool_t* pool)
{
	// Draw arena
	SDL_SetRenderDrawColor(context->renderer, 100, 100, 100, 255);
	SDL_draw_filled_circle(context->renderer, 300, 300, 300);

	for (int i = 0; i < pool->size; i++)
	{
		if (pool->data[i].is_used)
		{
    		SDL_SetRenderDrawColor
    		(
    			context->renderer,
    			pool->data[i].object.r,
    			pool->data[i].object.g,
    			pool->data[i].object.b,
    			255
    		);
			SDL_draw_filled_circle
			(
				context->renderer,
				pool->data[i].object.cur_pos.x,
				pool->data[i].object.cur_pos.y,
				pool->data[i].object.rad
			);
		}
	}
}
