/*
 * fist.cpp
 *
 *  Created on: Oct 31, 2015
 *      Author: souy
 */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include "basic_shape.h"
#include "initializer.h"

/**
 * Buffer used for storing the triggers from the key board
*/
bool* keyStates = new bool[256];

/**
 * The function used for drawing. 
*/
void renderFunction();

/**
 * Global granfather clock.
 * In Newtonian mechanics the determistic nature of the universe is timed by this clock.
 * New values for the positions of the object is calculated by each tick of this clock.
 */
float CLOCK=0;

/**
 	Angular velocity 
 */
float angle =0.02;

/**
 * Defines the camera position or the view port
 */ 
vec3 Camara;
vec3 Pan;

/**
 * Used for bounding the number of objects created on impact.
 */
int lasp=0;


/**
 * Initializing function for setting lighting parameters
 */ 
void init (void) {
	glClearDepth(1);
    glEnable (GL_DEPTH_TEST);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    	GLfloat qaAmbientLight[]	= {0.2, 0.2, 0.2, 1.0};
    	GLfloat qaDiffuseLight[]	= {0.8, 0.8, 0.8, 1.0};
    	GLfloat qaSpecularLight[]	= {1.0, 1.0, 1.0, 1.0};
    	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

    	// Set the light position

}


/**
 * Triggers when a keyboard key is lifted
 */
void keyUp (unsigned char key, int x, int y) {
	keyStates[key] = false;
	if (key == 'a') { // If they ‘a’ key was released
	// Perform action associated with the ‘a’ key
		keyStates[key] = false;
		//renderFunction();
	}
/*	if (key =='0'){
		Camara.x=0;
		Camara.y=0;
		Camara.z=-5;
	}
*/
}



/**
 * Triggers when a keyboard key is pressed
 */
void keyPressed (unsigned char key, int x, int y) {
	keyStates[key] = true;
    if(key == 'a') {
    	Camara.x+=0.05;
    	return;
    }
    if(key == 'd'){
    	Camara.x-=0.05;
    	return;
    }
    if(key == 'w'){
    	Camara.y+=0.05;
    	return;
    }if(key == 's'){
    	Camara.y-=0.05;
    	return;
    }
    if(key == 'i') {
    	Pan.x-=1;
    }
    if(key == 'k') {
        Pan.x+=1;
    }
    if(key == 'c'){
    	Camara.z-=0.05;
    }
    if(key == 'z'){
        Camara.z+=0.05;
    }

    if (key <= '0'+solar.size()-1 && key >= '0')
    {
    	Camara = solar[key-'0'].cog;
    }

    if(key == 'r'){
    	Camara.x=0;
    	Camara.y=0;
    	Camara.z=-5;

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


/**
 * Initialization function called each time  a the window is drawns
 */
inline void initialize(){
			glEnable(GL_BLEND); // Enable the OpenGL Blending functionality
		    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set the blend mode to blend our current RGBA with what is already in the buffer

		    glClearColor(0.5f, 0.5f, 0.5f, 0.5f); // Clear the background of our window to white
		    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
		    glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

		    glTranslatef(Camara.x,Camara.y,Camara.z); // Push eveything 5 units back into the scene, otherwise we won't see the primitive

		    glRotatef(Pan.x, 1.0f, 0.0f, 0.0f);



		   GLfloat qaLightPosition[]	= {solar[0].cog.x,solar[0].cog.y+solar[0].radius,solar[0].cog.z+solar[0].radius, 1.0};
		   glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
}


/**
 * Function defining the effect of collition of two objects pointed by i and j.
 */
inline void disintegrate(std::vector<sphere>::iterator i, std::vector<sphere>::iterator j){
	if (i==solar.end() ||  j == solar.end()) return;

	//Smaller body gets absorbed
	if (i->mass < 0.001*(j->mass) || i->radius <0.08){
		j->mass+= i->mass;
		j->radius+= 0.0008;
		solar.erase(i);
		return;
	}
	if (j->mass < 0.001*(i->mass) || j->radius <0.08){
			i->mass+= j->mass;
			i->radius+= 0.0008;
			solar.erase(j);
			return;
	}



	int n=3;
	float energy=2.0;

	vec3 pos = i->cog;
	pos.x = i->cog.x-i->radius;
	sphere* spi1 = new sphere(pos,i->radius/cbrtf(3*n),i->mass/(energy*n));
	spi1->c=i->c;

	pos.x=i->cog.x;
	pos.y = i->cog.y - i->radius ;
	sphere* spi2 = new sphere(pos,i->radius/cbrtf(3*n),i->mass/(energy*n));
	spi2->c=i->c;

	pos.y=i->cog.y;
	pos.z = i->cog.z - i->radius;
	sphere* spi3 = new sphere(pos,i->radius/cbrtf(3*n),i->mass/(energy*n));
	spi3->c=i->c;

	pos.x = j->cog.x-j->radius;
	sphere* spj1 = new sphere(pos,j->radius/cbrtf(3*n),j->mass/(energy*n));
	spj1->c=j->c;

	pos.x=j->cog.x;
	pos.y = j->cog.y - j->radius;
	sphere* spj2 = new sphere(pos,j->radius/cbrtf(n),j->mass/(energy*n));
	spj2->c=j->c;

	pos.y=j->cog.y;
	pos.z = j->cog.z - j->radius;
	sphere* spj3 = new sphere(pos,j->radius/cbrtf(n),j->mass/(energy*n));
	spj3->c=j->c;

	// --------------------------  x axis ----------------
	// create a random direction;

	srand(time(0));
	float vx = i->velo.x* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	float vy = i->velo.y* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	float vz = i->velo.z* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	vec3 d(vx,vy,vz);
	d*= energy;
	spi1->velo = d;
	d*=(-spi1->mass/spj1->mass);
	spj1->velo = d;

	vx = i->velo.x* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	vy = i->velo.y* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	vz = i->velo.z* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	d.x= vx, d.y=vy, d.z=vz;
	d*= energy;
	spi2->velo = d;
	d*=(-spi1->mass/spj1->mass);
	spj2->velo = d;

	vx = i->velo.x* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	vy = i->velo.y* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	vz = i->velo.z* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	d.x= vx, d.y=vy, d.z=vz;
	d*= energy;
	spi3->velo = d;
	d*=(-spi1->mass/spj1->mass);
	spj3->velo = d;

	solar.erase(i); solar.erase(j);

	solar.push_back(*spi1);
	solar.push_back(*spi2);
	solar.push_back(*spi3);
	
	solar.push_back(*spj1);
	solar.push_back(*spj2);
	solar.push_back(*spj3);

}

/**
 * A simple repel funtion, with perfect coeffcient of restitution
 */
inline void repel2(std::vector<sphere>::iterator i, std::vector<sphere>::iterator j){

		j->velo*=(-1);
		i->velo*=(-1);
		i->acci*=(-1);
		j->acci*=(-1);
}


/**
 * More envloved repel function, with random direction of deflection
 */
inline void repel(std::vector<sphere>::iterator i, std::vector<sphere>::iterator j){
	//if (i==solar.end() ||  j == solar.end()) return;

	srand(time(0));
	float vx = i->velo.x* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	float vy = i->velo.y* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	float vz = i->velo.z* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));

	float vxi = (i->mass*i->velo.x + j->mass*j->velo.x - j->mass*vx)/i->mass;
	float vyi = (i->mass*i->velo.y + j->mass*j->velo.y - j->mass*vy)/i->mass;
	float vzi = (i->mass*i->velo.z + j->mass*j->velo.z - j->mass*vz)/i->mass;

	i->velo.x = vxi, i->velo.y = vyi, i->velo.z=vzi;
	j->velo.x = vx, j->velo.y = vy, j->velo.z =vz;
}


/**
 * Detect whether a colition has occured.
 * Calls the disintegrate function and repel function 
 * @see disintegrate
 * @see repel
 * @see repel2
 */ 
inline void detectCollition(){

	for (std::vector<sphere>::iterator i = solar.begin();i!=solar.end();i++){
		for(std::vector<sphere>::iterator j = (i+1);j!=solar.end();j++){
			vec3 dis = i->cog-j->cog;
			float mag = sqrt(dis.dot(dis));
			if (mag <= i->radius+j->radius + ERROR ){

//					std::cout<<"BANG!\n";
//					repel2(i,j);
					if (lasp <= 0 && solar.size() <=100)
					{	lasp ++;
						disintegrate(i,j);
						return;
					}
					else{
						repel2(i,j);
						lasp++;
						if(lasp>=5){
							lasp =0;

						}
					}
					return;

			}
		}
	}

}

/**
 	Newtons theory of gravitation at work 
 * 	Newtons laws of motions are used in generating forces on each object in the current universe
 */ 
 void gravity(){
	//std::vector<sphere>::iterator i= solar.begin();
	std::vector<vec3> forc;
	unsigned int N = solar.size();
	for(unsigned int i=0;i< N;i++){
		vec3 c;
		forc.push_back(c);
	}
	for(unsigned int j =0;j<solar.size();j++){
		//vec3 forci;
		for(unsigned int k = (j+1); k<solar.size(); k++){
			vec3 d = solar[j].cog - solar[k].cog;

			float dis_sq = (d.dot(d));

			//if (dis <= ERROR ) return;

			float mag;
			float dis = sqrt(dis_sq);
			
			if (dis <= ERROR + solar[j].radius+solar[k].radius){
				mag = G*(solar[j].mass)*(solar[k].mass)*dis;
			}
			else{
				mag = G*(solar[j].mass)*(solar[k].mass)/dis_sq;	
			
				d.normal();
				d*=mag;

	/*		if	(sqrt(d.dot(d)) >= SMALL){
				//std::cout<<"HERE!";
				d.set(0,0,0);
				//return;
			}
	*/
				forc[k]+=d;
				forc[j]-=d;
			}
		}

		solar[j].force(forc[j]);
		solar[j].move(delta);

	//	solar[1].force(forc[1]);
	//	solar[1].move(delta);
	}
	detectCollition();
	
	forc.swap(forc);
}

/**
 * Implements newtonian mechanics for the universe containing Sun earth and Jupiter
 * Used only for testing purpose.
 * Replaced by gravity
 * @see gravity
 */ 
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


// Thi function displays bouncing ball through a cube.
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

		// Squashing effect on the ball
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

    Camara.z= -5.0f;
    Pan.x = 20;
    load();

    if (solar.size()<=0) return 0;
    //std::cout<<d.x<<","<<d.y<<","<<d.z<<std::endl;

    glutDisplayFunc(renderstatic3);
    glutIdleFunc(renderstatic3);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop();
    return 0;
}



