


***



# AIM BOT


## by Team Vegetta SS: Tomás Carreras, Enric-G. Durán, Núria Lamonja



***

***



## Aim Bot: A quick summary

To code the Aim Bot we are going to use the Montecarlo to implement the Verlet Integrator.

#### Verlet Integration

Verlet Integration is a numerical method used to integrate Newton’s equations of motion. It is frequently used to calculate trajectories of particles in molecular dynamics simulations and computer graphics. 

The Verlet integrator provides good numerical stability, as well as other properties that are important in physical systems such as time reversibility and preservation of the symplectic form on phase space, at no significant additional computational cost over the simple Euler method. 

[Wikipedia: Verlet Integration](https://en.wikipedia.org/wiki/Verlet_integration)

#### Montecarlo

The Montecarlo method uses a loop inside a loop. In the internal loop, the function runs for X times a random angle and velocity and computes for each one if the projectile reached the objective using a function, which in our case it will be called “PropagateAll()”, and the Verlet Integrator. In the external loop, this loop is limited to frames so the screen doesn’t freeze. This is the concrete case for video games. 

Basically, in general, the MC relies on a repeated random sampling (we require a sequence of numbers which are random, independent, real and uniformly distributed in the range zero to one) when it’s difficult to impossible to use other more deterministic approaches. It is used in optimization, integration and probability distribution.

[Wikipedia: Monte Carlo Method](https://en.wikipedia.org/wiki/Monte_Carlo_method)
[Arxiv](https://arxiv.org/pdf/cond-mat/0104167.pdf)
[Barkema FPSPXIII](http://itf.fys.kuleuven.be/~fpspXIII/material/Barkema_FPSPXIII.pdf)
[Rummukai: Montecarlo](https://www.mv.helsinki.fi/home/rummukai/lectures/montecarlo_oulu/lectures/mc_notes1.pdf)
[Towards data science](https://towardsdatascience.com/the-house-always-wins-monte-carlo-simulation-eb82787da2a3)
[Palisade: Montecarlo Simulation](https://www.palisade.com/risk/monte_carlo_simulation.asp)
[Science Direct: Montecarlo Method](https://www.sciencedirect.com/topics/neuroscience/monte-carlo-method)



***



## Goals


Therefore, our main goal for this project is to get a Montecarlo well implemented in the Aim Bot with an interface. The user will be able to change the the input through an .xml file. The input is going to be the position of the bullet, the position of the target, if the collision is elastic or completely inelastic and the mass of the bullet. The program is not intended to have a rerun option, but if there is time, it will be considered. The Aim Bot won’t freeze the screen, so if the target is not found it will throw the bullet at a set speed and angle and notify the user the object has not been found.



***



## Aim Bot: The formulas we used

#### Verlet Integration

To see the formulas we used for the Verlet Integrator part of the project, please refer to our provious [Verlet Integrator](https://github.com/Needlesslord/PHYSICS2-Verlet_Integrator).

In addition, you can see in the following web pages more information on the topic and formulas.

[Verlet Integration · GitBook](https://www.algorithm-archive.org/contents/verlet_integration/verlet_integration.html)

[Wikipedia: Verlet Integration](https://en.wikipedia.org/wiki/Verlet_integration)

[A Verlet based approach for 2D game physics](https://www.gamedev.net/articles/programming/math-and-physics/a-verlet-based-approach-for-2d-game-physics-r2714)

#### Montecarlo

The Montecarlo, since it is a method, it does not use formulas. What it does is set the velocity and the angle randomly in between some parameters to later implement the Verlet Method to calculate if the bullet hits the objective or not.



***



## Installation


Go to our GitHub repository and download the .zip. Decompress the .zip and start the app.

Enjoy!



***



## Team members:


**Co-Team Leader and progammer:** Tomás Carreras Ugarte

	GitHub: tomascarreras1000

**Co-Team Leader and progammer:** Enric-G. Durán

	GitHub: EnricGDV

**Co-Team Leader and progammer:** Núria Lamonja

	GitHub:	 needlesslord



***



## Credits:


Design and Development (co-team leaders): 

		Tomás Carreras
		
		Enric-G. Durán
	
		Núria Lamonja


We would like to thank David de la Torre, who has helped with this project and given us kind advice.
This project has been done for CITM-TTC under the MIT License with .



***



## Download to the latest release


Here you can go to the release page and download the different versions available. Just click on the release, unzip it once downloaded and you can play clicking the Application.
Instructions can be found in this same web page or in the readme.md file included in the zip.


[Releases](https://github.com/Needlesslord/PHYSICS2-Aim_Bot_SS/releases)



***



## Usage


	CONTROLS:

	COMPUTER KEYBOARD ONLY

	[R]			Restart the simulation with the data updated from the .xml
	[ENTER]/[RETURN]	Start the simulation. It can be restarted as many times as you want.
	[ESC]			Exit the app

To input the data open the "input.xml" file and change the variables. 

(*) Note that you can run the app, change the values and press [R] to reload the new data and continue using it without closing the app.



***



## Content


In this integrator you are shown a welcome message at first and a small tutorial. 

After that, you input the data and all the frames will be displayed on the screen afterwards.

In the final results, it will also be displayed in case you want to the results of calculating everything with the Newton's Laws.



***



## Disclosure


This is an integrator made by second year students of the Videogame Design and Development degree taught at CITM-TTC.

The integrator has been made using C++, using SDL libraries.



***



## Links


[Github](https://github.com/Needlesslord/PHYSICS2-Aim_Bot_SS): https://github.com/Needlesslord/PHYSICS2-Aim_Bot_SS

[Releases of this integrator](https://github.com/Needlesslord/PHYSICS2-Aim_Bot_SS/releases): https://github.com/Needlesslord/PHYSICS2-Aim_Bot_SS/releases

[Our web page](https://needlesslord.github.io/PHYSICS2-Aim_Bot_SS/): https://needlesslord.github.io/PHYSICS2-Aim_Bot_SS/



***



## License


Copyright (c) [2020] [Tomás Carreras, Enric-G. Durán, Núria Lamonja]

Under the MIT License.

All rights reserved to the developers and publishers of the original release (Tomás Carreras, Enric-G. Durán, Núria Lamonja). 
The aim of this project (link to the github project can be found above) and respectively wiki is only educational. 

The content can only be used for non-commercial purposes. 

The copyright of the music and art is used for non-commercial projects and educational purposes.
In case you want to use it for other cases please do contact their rightful owners.

If you want to use this integrator or its content please do ask beforehand (email: needlesslord@gmail.com).

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
