/*
	inputX: the x inputed for the obstacle
	inputY: the y inputed for the obstacle
*/

#include "object.h"
#include <iostream>
using namespace std;

bool PropagateAll(float v, float ang, object obs )
{
	double time = 3.0f;

	object bullet;

	bullet.setX(0.0f);
	bullet.setY(0.0f);
	bullet.setAX(0.0f);
	bullet.setAY(GRAVITY);
	bullet.setVX(v*cos(ang));
	bullet.setVY(v*sin(ang));
	bullet.setDensity(100.0f);
	bullet.setEdgeLength(0.2f);

	if (bullet.update(time, obs, 1))
	{
		return true;
	}
	return false;
}


int main()
{
	object obstacle;

	//Input obstacle's X and Y
	float inputX, inputY; cout << "Input x: "; cin >> inputX; cout << "Input y: "; cin >> inputY;

	//obstacle
	obstacle.setX(inputX);
	obstacle.setY(inputY);
	obstacle.setAX(0.0f);
	obstacle.setAY(0.0f);
	obstacle.setVX(0.0f);
	obstacle.setVY(0.0f);
	obstacle.setEdgeLength(1.0f);
	obstacle.setDensity(HUGE_VAL);

	float v = 0;
	float ang = 0;
	bool collided = false;
	int i = 0, cont = 0;
	while (!collided)
	{
		cont++;
		while (i < 1000 && !collided)
		{
			i++;
			float randomV = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50.0));
			v = randomV;
			float randomAngle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3.141592));
			ang = randomAngle;

			if (PropagateAll(v, ang, obstacle))
			{
				collided = true;
				cout << "Speed: " << v << endl << "Angle: " << ang << endl << "n: "<< i << endl;
			}
		}
		cout << cont << endl;
		if (cont > 1000) {
			PropagateAll(50.0f, 0, obstacle);
			cout << "Speed: 50.0f" << endl << "Angle: 0" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}