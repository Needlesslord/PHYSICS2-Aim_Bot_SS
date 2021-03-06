#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1Physics.h"
#include "globals.h"
#include <iostream>

j1Scene::j1Scene() 
{
	name.create("scene");
}

j1Scene::~j1Scene() {}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");

	return true;
}

// Called before the first frame
bool j1Scene::Start()
{
	bg_tex = App->tex->Load("textures/background.png");
	hit_tex = App->tex->Load("textures/hit.png");
	miss_tex = App->tex->Load("textures/miss.png");
	App->audio->PlayMusic("audio/music/music.ogg");

	kicking = false;
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		App->load = true;

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN && App->audio->volume < 128)
		App->audio->volume += 2;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN && App->audio->volume > 0)
		App->audio->volume -= 2;

	//Rendering background, Vegetta and Boo
	App->render->Blit(bg_tex, -150, 0);
	App->render->Blit(App->physics->target_tex_boo, App->physics->inputX, 550 - App->physics->inputY);

	//Kick
	if (timer > 10) 
	{
		kicking = false;
		timer = 0;
	}
	else if (kicking) 
	{
		App->render->Blit(App->physics->origin_tex_vegetta_SS_kick, App->physics->bullet_position.x - 70, 400 - App->physics->bullet_position.y);
		timer++;
	}
	else
		App->render->Blit(App->physics->origin_tex_vegetta_SS, App->physics->bullet_position.x - 70, 400 - App->physics->bullet_position.y);


	

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}