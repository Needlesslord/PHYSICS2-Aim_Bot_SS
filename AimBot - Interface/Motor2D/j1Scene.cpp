#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "object.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	img = App->tex->Load("textures/test.png");
	App->audio->PlayMusic("audio/music/music_sadpiano.ogg");
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
	// TODO 1: Request Load / Save on application when pressing L/S
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->load = true;

	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN && App->audio->volume < 128)
		App->audio->volume += 2;

	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN && App->audio->volume > 0)
		App->audio->volume -= 2;


	///////////////////////////
	// AIMBOT IMPLEMENTATION //
	///////////////////////////
	
	//this will be the object we'll aim at
	object target;

	//Input target's X and Y
	float inputX = 0;
	float inputY = 0;

	//target's properties
	target.setX(inputX);
	target.setY(inputY);
	target.setAX(0.0f);
	target.setAY(0.0f);
	target.setVX(0.0f);
	target.setVY(0.0f);
	target.setEdgeLength(1.0f);
	target.setDensity(HUGE_VAL);


	bool collided = false;
	unsigned int cont = 0;
	while (!collided)
	{
		//Monte Carlo:
		for (unsigned int i = 0; i < 1000 && !collided; i++)
		{
			//we give random values to the velocity and the angle for each attempt
			//the velocity will be a semi-random value from 0 to 50 to avoid straight shots with infinite velocity which would guarantee a hit
			float v = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50.0f));

			//the angle will be a semi-random value from 0 to pi radians to enable the target to be to the left of the bullet's initial position
			float ang = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / pi));

			//we try to hit the target with the random values
			if (PropagateAll(v, ang, target))
			{
				//we register the hit, which exits the loop
				collided = true;
				//angles will be expressed in degrees so we make the conversion
				ang *= 360 / (2 * pi);
				//we output the results found
				//cout << "Speed: " << v << endl << "Angle: " << ang << " degrees" << endl << "Number of attempts: " << i << endl;
			}
		}
		//in case a result hasn't been found after 10.000 attempts the machine will try the maximum velocity in a straight line as a last try and then end the process
		if (cont > 10) {
			PropagateAll(50.0f, 0, target);
			//cout << "Speed: 50.0f" << endl << "Angle: 0" << endl;
			break;
		}
		//we increase the number of Monte Carlo iterations
		cont++;
	}


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

//Called when Aiming (AimBot)
bool j1Scene::PropagateAll(float v, float ang, object target)
{
	float time = 3.0f;

	object bullet;
	bullet.setX(0.0f);
	bullet.setY(0.0f);
	bullet.setAX(0.0f);
	bullet.setAY(GRAVITY);
	bullet.setVX(v*cos(ang));
	bullet.setVY(v*sin(ang));
	bullet.setDensity(100.0f);
	bullet.setEdgeLength(0.2f);

	if (bullet.update(time, target, 1))
	{
		return true;
	}
	return false;
}
