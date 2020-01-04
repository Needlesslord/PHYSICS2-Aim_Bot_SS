


***



# AIM BOT


## by Team Vegetta SS: Tomás Carreras, Enric-G. Durán, Núria Lamonja



***

***



## Aim Bot: A quick summary

To code the Aim Bot we are going to use the Montecarlo to implement the Verlet Integrator.

#### Verlet Integration

 - Verlet Integration is a numerical method used to integrate Newton’s equations of motion. It is frequently used to calculate trajectories of particles in molecular dynamics simulations and computer graphics. (https://en.wikipedia.org/wiki/Verlet_integration)

 - The Verlet integrator provides good numerical stability, as well as other properties that are important in physical systems such as time reversibility and preservation of the symplectic form on phase space, at no significant additional computational cost over the simple Euler method. (https://en.wikipedia.org/wiki/Verlet_integration)

#### Montecarlo


***



## Goals


#CHANGE ->

Our goal for this project is to have an interactable integrator that, given an initial data, in our concrete case the initial position x and y, speed vx and vy, acceleration ax and ay, a radius, a density and elapsed time, it computes their values at the end of that given time. 
Our intention is that it will also have a way to test the correct function of the integrator, which will print every frame and it will be able to pause it and a graphic representation. 
In addition, the Newton's Laws will be implemented in order to compare the results of the integrator with the final data and see the accuracy and the standard deviation. 


Our frame rate will be of 60 fps. 
Air density will be implemented, as well as gravity. 
We will have a ground and the ball will be able to collide with it. 
Frame per frame we are going to be calculating each variable to update it.



***



## Aim Bot: The formulas we used

#### Verlet Integration

To see the formulas we used for the Verlet Integrator part of the project, please refer to our provious [Verlet Integrator](https://github.com/Needlesslord/PHYSICS2-Verlet_Integrator).

In addition, you can see in the following web pages more information on the topic and formulas.

[Verlet Integration · GitBook](https://www.algorithm-archive.org/contents/verlet_integration/verlet_integration.html)

[Wikipedia: Verlet Integration](https://en.wikipedia.org/wiki/Verlet_integration)

[A Verlet based approach for 2D game physics](https://www.gamedev.net/articles/programming/math-and-physics/a-verlet-based-approach-for-2d-game-physics-r2714)

#### Montecarlo


#CHANGE ->


***



## Installation


Go to our GitHub repository and download the .zip. Go To the folder "Integrator - console", open the solution and Debug it.

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
This project has been done for CITM-TTC under the MIT License.



***



## Download to the latest release


Here you can go to the release page and download the different versions available. Just click on the release, unzip it once downloaded and you can play clicking the Application.
Instructions can be found in this same web page or in the readme.md file included in the zip.


[Releases](https://github.com/Needlesslord/PHYSICS2-Aim_Bot_SS/releases)



***



## Usage


	CONTROLS:

	COMPUTER KEYBOARD ONLY


In each step, the user will receive instructions of what data or keys they should press. In addition, there is a tutorial at the begining explaining everything.



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


Copyright (c) [2019] [Tomás Carreras, Enric-G. Durán, Núria Lamonja]

Under the MIT License.

All rights reserved to the developers and publishers of the original release (Tomás Carreras, Enric-G. Durán, Núria Lamonja). 
The aim of this project (link to the github project can be found above) and respectively wiki is only educational. 

The content can only be used for non-commercial purposes. 

The copyright of the music and art is used for non-commercial projects and educational purposes.
In case you want to use it for other cases please do contact their rightful owners.

If you want to use this integrator or its content please do ask beforehand (email: needlesslord@gmail.com).

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
