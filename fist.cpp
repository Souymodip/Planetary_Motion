/*
 * fist.cpp
 *
 *  Created on: Oct 31, 2015
 *      Author: souy
 */

#include <iostream>
#include <vector>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include "basic_shape.h"
#include "initializer.h"


bool* keyStates = new bool[256];

void renderFunction();

float CLOCK=0;

float angle =0.02;



void init (void) {
	glClearDepth(1);
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void keyUp (unsigned char key, int x, int y) {
	keyStates[key] = false;
	if (key == 'a') { // If they ‘a’ key was released
	// Perform action associated with the ‘a’ key
		keyStates[key] = false;
		//renderFunction();
	}
}





void keyPressed (unsigned char key, int x, int y) {
	keyStates[key] = true;
    if(key == 'a') {
    	//std::cout<<"Key pressed "<<keyStates[key]<<"\n";
    	//renderFunction();
    }
}
void renderPrimitive(){

	glColor3f(1.0f,0.5f,0.5f);

	if (keyStates['a']){
		//std::cout<<"This was true";
		//drawCircle(0.0f,0.0f,0.0f,2.0f,200);
	}

}

void keyOperations (void) {
	if (keyStates['a']) { // If the 'a' key has been pressed
		// Perform 'a' key operations
		drawCircle(0.0f,0.0f,0.0f,2.0f,200);
	}
}




inline float mod(float y){
	return (y<0?-1*y:y);
}

inline void initialize(){
	glEnable(GL_BLEND); // Enable the OpenGL Blending functionality
		    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set the blend mode to blend our current RGBA with what is already in the buffer

		    glClearColor(0.5f, 0.5f, 0.5f, 0.5f); // Clear the background of our window to white
		    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
		    glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

		    glTranslatef(0.0f, 0.0f, -5.0f); // Push eveything 5 units back into the scene, otherwise we won't see the primitive
		    glRotatef(20, 1.0f, 0.0f, 0.0f);
}

void detectCollition(){

	for (std::vector<sphere>::iterator i = solar.begin();i!=solar.end();i++){
		for(std::vector<sphere>::iterator j = (i+1);j!=solar.end();j++){
			vec3 dis = i->cog-j->cog;
			float mag = sqrt(dis.dot(dis));
			if (mag <= i->radius+j->radius){
					std::cout<<"BANG!\n";
			}
		}
	}

}


void gravity(){
	std::vector<sphere>::iterator i= solar.begin();
	std::vector<vec3> forc;
	for(;i!=solar.end();i++){
		vec3 c;
		forc.push_back(c);
	}
	for(unsigned int j =0;j<solar.size();j++){
		//vec3 forci;
		for(unsigned int k = (j+1); k<solar.size(); k++){
			vec3 d = solar[j].cog - solar[k].cog;
			float dis = (d.dot(d));

			if (dis<=0 ) return;

			float mag = G*(solar[j].mass)*(solar[k].mass)/dis;
			d.normal();
			d*=mag;
			forc[k]+=d;
			forc[j]-=d;
		}

		solar[j].force(forc[j]);
		solar[j].move(delta);

	//	solar[1].force(forc[1]);
	//	solar[1].move(delta);
	}
	detectCollition();
}


inline void mechanics(){
	CLOCK += delta;

	vec3 forc1 = sun.cog-earth.cog;
	float gravity1 = G*sun.mass*earth.mass/(forc1.dot(forc1));
	forc1.normal();
	forc1*=gravity1;
	vec3 forcse = forc1;

	forc1 = jupiter.cog-earth.cog;
	gravity1 = G*jupiter.mass*earth.mass/(forc1.dot(forc1));
	forc1.normal();
	forc1*=gravity1;
	vec3 forcje = forc1;


	vec3 forc2 = earth.cog-sun.cog;
	float gravity2 = G*sun.mass*earth.mass/(forc2.dot(forc2));
	forc2.normal();
	forc2*=gravity2;
	vec3 forces = forc2;


	forc2 = jupiter.cog-sun.cog;
	gravity2 = G*jupiter.mass*sun.mass/(forc2.dot(forc2));
	forc2.normal();
	forc2*=gravity2;
	vec3 forsj = forc2;


	vec3 forcE = forcje+forcse;
	vec3 forcJ = forcje + forsj;
	forcJ *=(-1);
	vec3 forcS = forces + forsj;

	earth.force(forcE);
	sun.force(forcS);
	jupiter.force(forcJ);

	earth.move(delta);
	sun.move(delta);
	jupiter.move(delta);

	detectCollition();
}

// Solar system with N-bodies, the size of the solar system.
void renderstatic3(){
	initialize();

	std::vector<sphere>::iterator i = solar.begin();
	glPushMatrix();
			glScalef(0.25,0.25,0.25);
	for (;i!=solar.end();i++){
		i->draw();
	}
	glPopMatrix();

	glutSwapBuffers();

	gravity();
}


// SOLAR systems with three bodies.
void renderstatic2(){
	initialize();


	angle+= 0.5;



	glPushMatrix();
		glScalef(0.25,0.25,0.25);
		glPushMatrix();
					glColor4f(0.2,0.2,0,1);
					jupiter.draw(angle);
		glPopMatrix();
		glPushMatrix();
			glColor4f(0,0,1,0.8);
			earth.draw(0);
		glPopMatrix();
		glPushMatrix();
			glColor4f(1,0.2,0,1);
			sun.draw(angle);
		glPopMatrix();
	glPopMatrix();


	glutSwapBuffers();

	mechanics();
}


// Thi function displays bouning ball through a cube.
void renderFunction()
{
	static bool Up = true;
	static float yLocation = -2.0f; // Keep track of our position on the y axis.
	static float yRotationAngle = 180.0f;
	//static float sf = 0.0;
	const float alpha = 0.2;
	const float beta = 0.05;
	static float velo = 1.0;

		static sphere sp(2.0f,2.0f,1.0f,0.5f,2);

		initialize();
	    sp.draw();

	    glPushMatrix();
	    	glTranslatef(0.0f, yLocation, 0.0f); // Translate our object along the y axis

	     // Rotate our object around the y axis


	    	glPushMatrix();
	    		glColor4f(1.0f, 0.0f, 0.0f, 0.5f); // Set the colour to red and 50% transparent
	    		float k=0;
	    		if (yLocation >=2-0.1 || yLocation <=-2+0.1)
	    			k= 5*(mod(yLocation)-1.9)/2.01;
	    		glScalef(1+k,1-k,1);
	    		//drawSphere2(0.5f,150);
	    	glPopMatrix();

	    glPopMatrix();

	    glPushMatrix();
	    	    	glRotatef(-30,0.0f,1.0f,0.0f);
	    	    	glColor4f(0.0f, 1.0f, 0.0f, 0.3f); // Set the colour to green and fully opaque
	    	    	glutSolidCube(1.3f); // Render the primitive
	    glPopMatrix();

	    float **bulg = new float*[2];
	    bulg[0] = new float[2];
	    bulg[1] = new float[2];

	    bulg[0][0] = 1.0; bulg[0][1] = 1.0;
	    bulg[1][0] = 2.0; bulg[1][1] = 1.0;



	    glutSwapBuffers(); // Swap our buffers


	if(Up){
		velo += (-1)*alpha*beta;
		yLocation += velo*beta;
	}else{
		velo += alpha*beta;
		yLocation += (-1)*velo*beta;
	}
	if (velo<=0){
		Up=false;
	}
	if (yLocation < -2.0f){
		Up=true;
		velo = 1.0;
	}


    yRotationAngle = 180.0f; // Increment our rotation value
    if (yRotationAngle > 360.0f){ // If we have rotated beyond 360 degrees (a full rotation)
    	yRotationAngle = 0.05f;
    }
    delete [] bulg;
    //glutSwapBuffers(); // Flush the OpenGL buffers to the window
}


void reshape (int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

/* Main method - main entry point of application
the freeglut library does the window creation work for us,
regardless of the platform. */
int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1000,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - First window demo");
    init();




    load();
    //std::cout<<d.x<<","<<d.y<<","<<d.z<<std::endl;

    glutDisplayFunc(renderstatic3);
    glutIdleFunc(renderstatic3);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);




    glutMainLoop();
    return 0;
}


