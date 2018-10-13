#include "ModuleFadeToBack.h"
#include "j1App.h"
#include "j1Render.h"
#include "p2Log.h"


ModuleFadeToBlack::~ModuleFadeToBlack()
{

}

// Load assets
bool ModuleFadeToBlack::Start()
{
	screen = { 0, 0, App->render->camera.w , App->render->camera.h };
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

// Update: draw background
bool  ModuleFadeToBlack::Update(float dt)
{
	if (current_step == fade_step::none)
		return true;

	Uint32 now = SDL_GetTicks() - start_time;
	normalized = MIN(1.0f, (float)now / (float)total_time);

	switch (current_step)
	{
	case fade_step::fade_to_black:
	{
		if (now >= total_time)
		{
			// TODO 3: enable / disable the modules received when FadeToBlacks() gets called

			to_disable->Disable();
			to_enable->Enable();

			to_disable = nullptr;
			to_enable = nullptr;
			// ---

			total_time += total_time;
			start_time = SDL_GetTicks();
			current_step = fade_step::fade_from_black;
		}
	} break;

	case fade_step::fade_from_black:
	{

		normalized = 1.0f - normalized;

		if (now >= total_time)
			current_step = fade_step::none;
	} break;
	}


	return true;
}
bool ModuleFadeToBlack::Draw()
{
	// Finally render the black square with alpha on the screen
	App->render->DrawQuad(screen, 0, 0, 0, (Uint8)(normalized * 255.0f));
	return true;
}
bool ModuleFadeToBlack:: FadeToBlack(j1Module* module_off, j1Module* module_on, float time) {
	bool ret = false;

	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		to_enable = module_on;
		to_disable = module_off;
		ret = true;
	}

	return ret;
}
