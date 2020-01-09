#include "object.h"


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

object::object()
{
	edge_length = 1.0f;
	area = edge_length * edge_length;
	mass = volume * density;
	vx = 0.0f;
	vy = 0.0f;
	ax = 0.0f;
	ay = 0.0f;
	isElastic = false;
}

object::~object() {}

//set

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
		fx = 0.5 * AIR_DENSITY * new_vx * vx * area * CD;
		
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

		//ground collisions
		if (new_y - edge_length <= 0)
		{
			new_y = edge_length;
			if(isElastic) new_vy *= -1;
			else new_vy = 0.0;
		}

		//left wall collisions
		if (new_x - edge_length <= 0)
		{
			new_x = edge_length;
			if (isElastic) new_vx *= -1;
			else new_vx = 0.0;
		}

		//right wall collisions
		if (new_x + edge_length >= 100)
		{
			new_x = 100 - edge_length;
			if (isElastic) new_vx *= -1;
			else new_vx = 0.0;
		}

		//Collision with target
		if (x + this->getRadius() > _target.getX() - _target.getRadius() && y - getRadius() < _target.getY() + _target.getRadius() &&
			x - this->getRadius() < _target.getX() + _target.getRadius() && y + getRadius() > _target.getY() - _target.getRadius())
		return true;
		else if (y < 0)
			return false;
	}
	return false;
}