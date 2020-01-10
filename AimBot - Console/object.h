#pragma once
#include <iostream>
#include "globals.h"

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

	bool update(float time, object _object, float CR, bool console = false);
private:
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
