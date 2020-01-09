#ifndef __j1PHYSICS_H__
#define __j1PHYSICS_H__

#include "j1Module.h"

struct SDL_Texture;
class object //sphere
{
public:
	object();
	~object();
	void setX(float _x);

	void setY(float _y);

	void setVX(float _vx);

	void setVY(float _vy);

	void setAX(float _ax);

	void setAY(float _ay);

	void setEdgeLength(float _radius);

	void setDensity(float _density);

	float getX();

	float getY();

	float getVX();

	float getVY();

	float getAX();

	float getAY();

	float getRadius();

	float getArea();

	float getVolume();

	float getDensity();

	float getMass();

	float getFX();

	float getFY();

	float distanceTo(object _object);

	bool checkCollission(object _object);

	bool update(float time, object _object, float CR, bool draw = false);


	//position
	float x;
	float y;

	//velocity
	float vx;
	float vy;

	//acceleration
	float ax;
	float ay;

	//object dimensions
	float edge_length;
	float area;
	float volume;

	//mass
	float density;
	float mass;

	//drag coefficient
	float CD;

	//coefficient of friction
	float CF;

	//elasticity
	bool isElastic;

	//forces
	float fx;
	float fy;

	//friction force
	float ff;

	//updated data
	float new_x;
	float new_y;
	float new_vx;
	float new_vy;
	float new_ax;
	float new_ay;

	float dt;

	
};

class j1Physics : public j1Module
{
public:

	j1Physics();

	// Destructor
	virtual ~j1Physics();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	//this will be the object we'll aim at
	object target;
	SDL_Texture* target_tex;
	SDL_Texture* bullet_tex;

	//Input target's X and Y
	float inputX;
	float inputY;
	float inputEdge;
};

#endif // __j1PHYSICS_H__