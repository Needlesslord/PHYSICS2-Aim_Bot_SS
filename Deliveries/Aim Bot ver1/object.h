#pragma once
#include <iostream>
#include "globals.h"

class object //sphere
{
public:
	void setX(double _x);

	void setY(double _y);

	void setVX(double _vx);

	void setVY(double _vy);

	void setAX(double _ax);

	void setAY(double _ay);

	void setEdgeLength(double _radius);

	void setDensity(double _density);

	double getX();

	double getY();

	double getVX();

	double getVY();

	double getAX();

	double getAY();

	double getRadius();

	double getArea();

	double getVolume();

	double getDensity();

	double getMass();

	double getFX();

	double getFY();

	double distanceTo(object _object);

	bool checkCollission(object _object);

	bool update(double time, object _object, double CR);

private:
	//position
	double x = 0.0;
	double y = 0.0;

	//velocity
	double vx = 0.0;
	double vy = 0.0;

	//acceleration
	double ax = 0.0;
	double ay = 0.0;

	//object dimensions
	double edge_length = 1.0;
	double area = edge_length * edge_length;
	double volume = edge_length * edge_length * edge_length;

	//mass
	double density = 1000.0;
	double mass = volume * density;

	//drag coefficient
	double CD = 1.05;

	//coefficient of friction
	double CF = 0.0;

	//elasticity
	int isElastic = 0;

	//forces
	double fx = 0.0;
	double fy = 0.0;

	//initial force
	double initial_fx = 0.0;
	double initial_fy = 0.0;

	//friction force
	double ff = 0.0;

	//updated data
	double new_x;
	double new_y;
	double new_vx;
	double new_vy;
	double new_ax;
	double new_ay;

	float dt;
};
