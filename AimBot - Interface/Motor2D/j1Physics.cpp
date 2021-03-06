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

j1Physics::j1Physics()
{
	name.create("physics");
}

j1Physics::~j1Physics() {}

// Called before render is available
bool j1Physics::Awake(pugi::xml_node& config)
{
	LOG("Loading Physics");

	inputX = config.child("target").child("position").attribute("x").as_float();
	inputY = config.child("target").child("position").attribute("y").as_float();
	inputEdge = config.child("target").child("edge").attribute("length").as_float();
	bullet_position.x = config.child("bullet").child("position").attribute("x").as_float();
	bullet_position.y = config.child("bullet").child("position").attribute("y").as_float();

	return true;
}

// Called before the first frame
bool j1Physics::Start()
{
	bullet_tex = App->tex->Load("textures/dragonBall.png");
	target_tex_boo = App->tex->Load("textures/boo.png");
	origin_tex_vegetta_SS = App->tex->Load("textures/vegetta.png");
	origin_tex_vegetta_SS_kick = App->tex->Load("textures/vegetta_kick.png");

	//Bullet's base Values. Some will get overwritten and some will be definitive
	bullet.setEdgeLength(0.2f);
	bullet.area = bullet.edge_length * bullet.edge_length;
	bullet.volume = bullet.edge_length * bullet.edge_length * bullet.edge_length;
	bullet.setDensity(10000.0f);
	bullet.mass = bullet.volume * bullet.density;
	bullet.CD = 1.05;
	bullet.CF = 0.0f;
	bullet.ff = 0.0f;
	bullet.vx = 0.0f;
	bullet.vy = 0.0f;
	bullet.ax = 0.0f;
	bullet.ay = 0.0f;

	//target's properties inputed
	target.setX(inputX);
	target.setY(inputY);
	target.setEdgeLength(inputEdge);

	//Traget's base Values.Some will get overwritten and some will be definitive
	target.area = target.edge_length * target.edge_length;
	target.mass = target.volume * target.density;
	target.vx = 0.0f;
	target.vy = 0.0f;
	target.ax = 0.0f;
	target.ay = 0.0f;
	target.setDensity(HUGE_VAL);	

	collided = false;
	running = true;
	isElastic = true;
	
	return true;
}

// Called each loop iteration
bool j1Physics::Update(float dt)
{
	//Initial calculations
	if (running && !collided) 
	{
		unsigned int cont = 0;
		while (!collided)
		{
			//Monte Carlo:
			for (unsigned int i = 0; i < 1000 && !collided; i++)
			{
				//we give random values to the velocity and the angle for each attempt
				//the velocity will be a semi-random value from 0 to 50 to avoid straight shots with infinite velocity which would guarantee a hit
				solution_v = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 700.0f));

				//the angle will be a semi-random value from 0 to pi radians to enable the target to be to the left of the bullet's initial position
				solution_ang = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / pi));

				//we try to hit the target with the random values
				if (PropagateAll(solution_v, solution_ang, App->physics->target))
				{
					//we register the hit, which exits the loop
					collided = true;
					running = false;
				}
				
			}
			//in case a result hasn't been found after 10.000 attempts the machine will try the maximum velocity in a straight line as a last try and then end the process
			if (cont > 10) {
				solution_v = 50.0f;
				solution_ang = 0.0f;
				collided = true;
				running = false;
				break;

				miss = true;
			}
			else
				miss = false;
			//we increase the number of Monte Carlo iterations
			cont++;
		}
	}

	//Ready to show the calculated solution graphically
	if (!running && collided)
	{
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			float time = 3.0f;

			//Reset all the base values to start from the same point as before
			bullet.setX(App->physics->bullet_position.x);
			bullet.new_x = bullet.x;
			bullet.setY(App->physics->bullet_position.y);
			bullet.new_y = bullet.y;
			bullet.setAX(0.0f);
			bullet.new_ax = bullet.ax;
			bullet.setAY(GRAVITY);
			bullet.new_y = bullet.y;
			bullet.vx = solution_v*cos(solution_ang);
			bullet.new_vx = bullet.vx;
			bullet.vy = solution_v*sin(solution_ang);
			bullet.new_vy = bullet.vy;
			running = true;

			//this is just to change Vegetta's sprite for a second
			App->scene->kicking = true;
		}
	}
	
	if (running && collided)
	{
		dt = 1.0 / fps;

		//X
		//Updating previous frame variables
		bullet.x = bullet.new_x;
		bullet.vx = bullet.new_vx;

		//Forces
		bullet.fx = 0.5 * AIR_DENSITY *bullet.vx * bullet.vx * bullet.area * bullet.CD;

		if (bullet.new_y == 0) {
			bullet.fx += bullet.ff;
		}

		//Acceleration
		if (bullet.new_vx <= 0.0)
			bullet.new_ax = bullet.fx / bullet.mass;
		else
			bullet.new_ax = -bullet.fx / bullet.mass;

		//Velocity
		bullet.new_vx = bullet.vx + bullet.new_ax * dt;

		//Position
		bullet.new_x = bullet.x + bullet.vx * dt + (bullet.new_ax / 2.0) * dt * dt;

		//Updating previous frame variables
		bullet.y = bullet.new_y;
		bullet.vy = bullet.new_vy;

		//Forces
		bullet.fy = 0.5 * AIR_DENSITY * bullet.new_vy * bullet.new_vy * bullet.area * bullet.CD;

		//Acceleration
		if (bullet.new_vy <= 0.0)
			bullet.new_ay = (GRAVITY + bullet.fy) / bullet.mass;
		else if (bullet.new_vy > 0.0)
			bullet.new_ay = (GRAVITY - bullet.fy) / bullet.mass;

		//Velocity
		bullet.new_vy = bullet.vy + bullet.new_ay * dt;

		//Position
		bullet.new_y = bullet.y + bullet.vy * dt + (bullet.new_ay / 2.0) * dt * dt;

		//Collision with target
		if (bullet.new_x + bullet.getRadius() > target.getX() - target.getRadius() && bullet.new_y - bullet.getRadius() < target.getY() + target.getRadius() &&
			bullet.new_x - bullet.getRadius() < target.getX() + target.getRadius() && bullet.new_y + bullet.getRadius() > target.getY() - target.getRadius())
			running = false;
		App->render->Blit(bullet_tex, bullet.new_x, 600 - bullet.new_y);

		//Print Hit/Miss
		if (!App->physics->miss)
			App->render->Blit(App->scene->hit_tex, 380, 50);
		else
			App->render->Blit(App->scene->miss_tex, 380, 50);
	}
	return true;
}

// Called before quitting
bool j1Physics::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

//////// VARIABLES LIST ////////
/*

dt = time between 2 frames

new_x = value of x in the current frame
x = initial x, when used in a formula x = previous frame x position

new_y = value of y in the current frame
y = initial y, when used in a formula y = previous frame y position

new_vx = value of vx in the current frame
vx = initial vx, when used in a formula vx = previous frame x velocity

new_vy = value of vy in the current frame
vy = initial vy, when used in a formula vy = previous frame y velocity

new_ax = value of ax in the current frame
ax = initial ax, when used in a formula ax = previous frame x acceleration

new_ay = value of ay in the current frame
ay = initial ay, when used in a formula ay = previous frame a acceleration

fx = resultant force on x axis
fy = resultant force on y axis

initial_fx= initial force on x axis
initial_fy= initial force on y axis

CF = coefficient of friction with the ground
ff = friction force of the object


bool checkCollision() compares two object positions, if their distance is less than the sum of their radius, returns true

*/

void object::setX(float _x)
{
	x = _x;
}

void object::setY(float _y)
{
	y = _y;
}

void object::setVX(float _vx)
{
	vx = _vx;
}

void object::setVY(float _vy)
{
	vy = _vy;
}

void object::setAX(float _ax)
{
	ax = _ax;
}

void object::setAY(float _ay)
{
	ay = _ay;
}

void object::setEdgeLength(float _edgeLength)
{
	edge_length = _edgeLength;
}

void object::setDensity(float _density)
{
	density = _density;
}

//get
float object::getX()
{
	return x;
}

float object::getY()
{
	return y;
}

float object::getVX()
{
	return vx;
}

float object::getVY()
{
	return vy;
}

float object::getAX()
{
	return ax;
}

float object::getAY()
{
	return ay;
}

float object::getRadius()
{
	return edge_length;
}

float object::getArea()
{
	return area;
}

float object::getVolume()
{
	return volume;
}

float object::getDensity()
{
	return density;
}

float object::getMass()
{
	return mass;
}

float object::getFX()
{
	return fx;
}

float object::getFY()
{
	return fy;
}

float object::distanceTo(object _object)
{
	float distanceX = abs(new_x - _object.x) - (edge_length / 2 - _object.edge_length / 2);
	float distanceY = abs(new_y - _object.y) - (edge_length / 2 - _object.edge_length / 2);

	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

	return distance;
}

bool object::checkCollission(object _object)
{
	float distanceX = abs(new_x - _object.x);
	float distanceY = abs(new_y - _object.y);

	if (distanceX <= 0.0 || distanceY <= 0.0)
		return true;
	else
		return false;
}

bool object::update(float time, object _target, float CR)
{
	unsigned int second = 0;
	unsigned int frame = 0;
	unsigned int secondFrame = 0;
	bool checkCollisionAgain = true;


	new_x = x;
	new_y = y;
	new_vx = vx;
	new_vy = vy;
	

	for (frame = 0; frame < time * fps; frame++)
	{
		dt = 1.0 / fps;

		//X
		//Updating previous frame variables
		x = new_x;
		vx = new_vx;

		//Forces
		fx = 0.5 * AIR_DENSITY * vx * vx * area * CD;

		if (new_y == 0) {
			fx += ff;
		}

		//Acceleration
		if (new_vx <= 0.0)
			new_ax = fx / mass;
		else
			new_ax = -fx / mass;

		//Velocity
		new_vx = vx + new_ax * dt;

		//Position
		new_x = x + vx * dt + (new_ax / 2.0) * dt * dt;

		//Updating previous frame variables
		y = new_y;
		vy = new_vy;

		//Forces
		fy = 0.5 * AIR_DENSITY * new_vy * new_vy * area * CD;

		//Acceleration
		if (new_vy <= 0.0)
			new_ay = (GRAVITY + fy) / mass;
		else if (new_vy > 0.0)
			new_ay = (GRAVITY - fy) / mass;

		//Velocity
		new_vy = vy + new_ay * dt;

		//Position
		new_y = y + vy * dt + (new_ay / 2.0) * dt * dt;

		//Collision with target
		if (new_x + this->getRadius() > _target.getX() - _target.getRadius() && new_y - getRadius() < _target.getY() + _target.getRadius() &&
			new_x - this->getRadius() < _target.getX() + _target.getRadius() && new_y + getRadius() > _target.getY() - _target.getRadius())
			return true;
		else if (new_y < 0)
			return false;
	}
	return false;
}


//Called when Aiming (AimBot)
bool j1Physics::PropagateAll(float v, float ang, object target)
{
	float time = 3.0f;

	bullet.setX(App->physics->bullet_position.x);
	bullet.setY(App->physics->bullet_position.y);
	bullet.setAX(0.0f);
	bullet.setAY(GRAVITY);
	bullet.setVX(v*cos(ang));
	bullet.setVY(v*sin(ang));
	
	if (bullet.update(time, target, 1))
	{
		return true;
	}
	return false;
}


bool j1Physics::Load(pugi::xml_node& saved)
{
	//Load Target Position within Window
	inputX = saved.child("target").child("position").attribute("x").as_float();
	inputY = saved.child("target").child("position").attribute("y").as_float();
	if (inputX > 900)
		inputX = 900;
	if(inputX < 70)
		inputX = 70;
	if (inputY > 600)
		inputY = 600;
	if (inputY < 0)
		inputY = 0;
	target.setX(inputX);
	target.setY(inputY);
	//Load Target Radius
	if(saved.child("target").child("edge").attribute("length").as_float() < 0)
		target.setEdgeLength(saved.child("target").child("edge").attribute("length").as_float());

	//Load Bullet Initial Position within Window
	bullet.x = saved.child("bullet").child("position").attribute("x").as_float();
	bullet.y = saved.child("bullet").child("position").attribute("y").as_float();
	if (bullet.x > 900)
		bullet.x = 900;
	if (bullet.x < 70)
		bullet.x = 70;
	if (bullet.y > 500)
		bullet.y = 500;
	if (bullet.y < 0)
		bullet.y = 0;
	bullet_position.x = bullet.x;
	bullet_position.y = bullet.y;
	//Load Bullet Radius
	if(saved.child("bullet").child("edge").attribute("length").as_float() < 0)
		bullet.setEdgeLength(saved.child("bullet").child("edge").attribute("length").as_float());
	//Load Bullet Density
	if (saved.child("bullet").child("density").attribute("value").as_float() < 0)
		bullet.setDensity(saved.child("bullet").child("density").attribute("value").as_float());


	//APPLY MONTECARLO AGAIN

	collided = false;
	unsigned int cont = 0;
	while (!collided)
	{
		//Monte Carlo:
		for (unsigned int i = 0; i < 1000 && !collided; i++)
		{
			//we give random values to the velocity and the angle for each attempt
			//the velocity will be a semi-random value from 0 to 50 to avoid straight shots with infinite velocity which would guarantee a hit
			solution_v = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 700.0f));

			//the angle will be a semi-random value from 0 to pi radians to enable the target to be to the left of the bullet's initial position
			solution_ang = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / pi));

			//we try to hit the target with the random values
			if (PropagateAll(solution_v, solution_ang, App->physics->target))
			{
				//we register the hit, which exits the loop
				collided = true;
				running = false;
			}

		}
		//in case a result hasn't been found after 10.000 attempts the machine will try the maximum velocity in a straight line as a last try and then end the process
		if (cont > 10) {
			solution_v = 50.0f;
			solution_ang = 0.0f;
			collided = true;
			running = false;

			miss = true;
			break;
		}
		else
			miss = false;
		//we increase the number of Monte Carlo iterations
		cont++;
	}
		return true;
}
