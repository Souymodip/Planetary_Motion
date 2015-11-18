/*
 * initializer.h
 *
 *  Created on: Nov 14, 2015
 *      Author: souy
 */


#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#define G 0.00006354			// Gravitational constant
#define SMALL 10000000  		// Stickiness of collations.
#define ERROR 0.001
const float delta =0.01;


//Each celestial object is created by creating a sphere object.
// with first three parameters defining the 3D position of the center of gravity
// 4th parameter is the radius and the fifth parameter is mass.



sphere sun(0.0f,0.0f,0.0f,2.30f,4000000);
sphere earth(0.0f,2.0f,-8.0f,0.3f,10);
//sphere jupiter(12.0f,0.0f,0.0f,0.5f,50000);
sphere jupiter(0.0f,0.0f,0.0f,0.5f,50000);
sphere europa(8.0f,0,0,0.3,10);
sphere uranus(-8.0,0.0f,4.0f,0.4f,1000);

sphere helly1(5.0f,0.0f,0.0f,0.1f,0.01);
sphere helly2(5.0f,0.0f,0.0f,0.1f,0.01);
sphere helly3(5.0f,0.0f,0.0f,0.1f,0.01);
sphere helly4(5.0f,0.0f,0.0f,0.1f,0.01);
sphere helly5(5.0f,0.0f,0.0f,0.1f,0.01);

sphere sun2(8.0f,0.0f,0.0f,1.0f,400000);
// List of celestial objects
std::vector<sphere> solar;


// Give each object an initial velocity vector (velo).
// Else the will just fall into each other.
// loads the celestial objects in the list.

inline void load(){
/*		
	earth.velo.x=5;
		jupiter.velo.z=5;
		uranus.velo.z=-7;uranus.velo.x=0;
		//sun2.velo.y=2;  sun2.c=0;



		helly1.velo.z =-10;
		helly2.velo.z = 8;
		helly3.velo.y = -8;
		helly4.velo.z =-8; helly4.velo.x =-8;
		helly5.velo.z =-8; helly4.velo.y =-8;
*/

  //     solar.push_back(sun);
  //     solar.push_back(earth);
	   solar.push_back(jupiter);
	   solar.push_back(uranus);
/*	   solar.push_back(helly1);
	   solar.push_back(helly2);
	   solar.push_back(helly3);
	   solar.push_back(helly4);
	   solar.push_back(helly5);
	   //solar.push_back(europa);
	   //solar.push_back(sun2);
*/

}

#endif /* INITIALIZER_H_ */
