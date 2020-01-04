#include "object.h"
#include <iostream>

bool PropagateAll(float v, float ang, object obs )
{
	double time = 3.0f;

	object bullet;

	bullet.setX(0.0f);
	bullet.setY(0.0f);
	bullet.setAX(0.0f);
	bullet.setAY(-9.81);
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

	//obstacle
	obstacle.setX(51.0f);
	obstacle.setY(10.0f);
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
		while (i < 100 && !collided)
		{
			i++;
			v = rand() % 20;
			ang = rand() % 90;		

			if (PropagateAll(v, ang, obstacle))
			{
				collided = true;
				std::cout << "Speed: " << v << std::endl << "Angle: " << ang << std::endl << "n: "<< i << std::endl;
			}
		}
	}
	system("pause");
	return 0;
}