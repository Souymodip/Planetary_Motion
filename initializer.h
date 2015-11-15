/*
 * initializer.h
 *
 *  Created on: Nov 14, 2015
 *      Author: souy
 */

#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#define G 0.000006354			// Gravitational constant
#define SMALL 10000000  		// Stickiness of collations.

const float delta =0.1;


//Each celestial object is created by creating a sphere object.
// with first three parameters defining the 3D position of the center of gravity
// 4th parameter is the radius and the fifth parameter is mass.

sphere sun(0.0f,0.0f,0.0f,1.0f,4000000);
sphere earth(0.0f,0.0f,-5.0f,0.2f,50);
sphere jupiter(-8.0f,0.0f,0.0f,0.25f,50000);
sphere uranus(-10.0,0.0f,0.0f,0.5f,1000);

sphere sun2(8.0f,0.0f,0.0f,1.0f,400000);
// List of celestial objects
std::vector<sphere> solar;


// Give each object an initial velocity vector (velo).
// loads the celestial objects in the list.

inline void load(){
		earth.velo.x=2;
		jupiter.velo.z=2;
		uranus.velo.z=-2;uranus.velo.x=0;
		sun2.velo.y=2;  sun2.c=0;

		solar.push_back(earth);
	    solar.push_back(sun);
	   solar.push_back(jupiter);
	   solar.push_back(uranus);
	   solar.push_back(sun2);


}

#endif /* INITIALIZER_H_ */
