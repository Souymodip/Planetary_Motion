/*
 * initializer.h
 *
 *  Created on: Nov 14, 2015
 *      Author: souy
 */

#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#define G 0.00006354

const float delta =0.05;


//Each celestial object is created by creating a sphere object.
// with first three parameters defining the 3D position of the center of gravity
// 4th parameter is the radius and the fifth parameter is mass.

sphere sun(0.0f,0.0f,0.0f,0.8f,4000000);
sphere earth(0.0f,0.0f,-15.0f,0.09f,50);
sphere jupiter(10.0f,0.0f,0.0f,0.25f,100000);
sphere uranus(-5,0.0f,0.0f,0.2f,100);

// List of celestial objects
std::vector<sphere> solar;


// Give each object an initial velocity vector (velo).
// loads the celestial objects in the list.

inline void load(){
		earth.velo.x=2;
		jupiter.velo.z=5;
		uranus.velo.z=-6;uranus.velo.x=0;

		solar.push_back(earth);
	    solar.push_back(sun);
	    solar.push_back(jupiter);
	    solar.push_back(uranus);


}

#endif /* INITIALIZER_H_ */
