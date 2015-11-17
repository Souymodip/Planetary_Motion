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


bool* keyStates = new bool[256];

void renderFunction();

float CLOCK=0;

float angle =0.02;

vec3 Camara;
vec3 Pan;

int lasp=0;

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





void keyPressed (unsigned char key, int x, int y) {
	keyStates[key] = true;
    if(key == 'a') {
    	Camara.x-=0.01;
    	return;
    }
    if(key == 'd'){
    	Camara.x+=0.01;
    	return;
    }
    if(key == 'w'){
    	Camara.y+=0.01;
    	return;
    }if(key == 's'){
    	Camara.y-=0.01;
    	return;
    }
    if(key == 'i') {
    	Pan.x-=1;
    }
    if(key == 'k') {
        Pan.x+=1;
    }
    if(key == 'c'){
    	Camara.z-=0.01;
    }
    if(key == 'z'){
        Camara.z+=0.01;
    }

    if (key <= '0'+solar.size()-1 && key >= '0')
    {
    	Camara = solar[key-'0']->cog;
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

inline void initialize(){
			glEnable(GL_BLEND); // Enable the OpenGL Blending functionality
		    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set the blend mode to blend our current RGBA with what is already in the buffer

		    glClearColor(0.5f, 0.5f, 0.5f, 0.5f); // Clear the background of our window to white
		    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
		    glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

		    glTranslatef(Camara.x,Camara.y,Camara.z); // Push eveything 5 units back into the scene, otherwise we won't see the primitive

		    glRotatef(Pan.x, 1.0f, 0.0f, 0.0f);



		   GLfloat qaLightPosition[]	= {solar[0]->cog.x,solar[0]->cog.y+solar[0]->radius,solar[0]->cog.z+solar[0]->radius, 1.0};
		   glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
}

inline void disintegrate(std::vector<sphere *>::iterator i, std::vector<sphere *>::iterator j){
	if (i==solar.end() ||  j == solar.end()) return;

	//Smaller body gets absorbed
	if ((*i)->mass < 0.001*(*j)->mass){
		(*j)->mass+= (*i)->mass;
		solar.erase(i);
		return;
	}
	if ((*j)->mass < 0.001*(*i)->mass){
			(*i)->mass+= (*j)->mass;
			solar.erase(j);
			return;
	}


	int n=3;

	vec3 pos = (*i)->cog;
	pos.x = (*i)->cog.x-(*i)->radius;
	sphere* spi1 = new sphere(pos,(*i)->radius/cbrtf(2*n),(*i)->mass/n);
	spi1->c=(*i)->c;
	spi1->velo.x = -1*n*(*i)->velo.x;

	pos.x=(*i)->cog.x;
	pos.y = (*i)->cog.y - (*i)->radius;
	sphere* spi2 = new sphere(pos,(*i)->radius/cbrtf(2*n),(*i)->mass/n);
	spi2->c=(*i)->c;
	spi2->velo.y = -1*n*(*i)->velo.y;

	pos.y=(*i)->cog.y;
	pos.z = (*i)->cog.z - (*i)->radius;
	sphere* spi3 = new sphere(pos,(*i)->radius/cbrtf(2*n),(*i)->mass/n);
	spi3->c=(*i)->c;
	spi3->velo.z = -1*n*(*i)->velo.z;


	pos.x = (*j)->cog.x-(*j)->radius;
	sphere* spj1 = new sphere(pos,(*j)->radius/cbrtf(2*n),(*j)->mass/n);
	spj1->c=(*j)->c;
	spj1->velo.x = -1*n*(*j)->velo.x;

	pos.x=(*j)->cog.x;
	pos.y = (*j)->cog.y - (*j)->radius;
	sphere* spj2 = new sphere(pos,(*j)->radius/cbrtf(2*n),(*j)->mass/n);
	spj2->c=(*j)->c;
	spj2->velo.y = -1*n*(*j)->velo.y;

	pos.y=(*j)->cog.y;
	pos.z = (*j)->cog.z - (*j)->radius;
	sphere* spj3 = new sphere(pos,(*j)->radius/cbrtf(2*n),(*j)->mass/cbrtf(n));
	spj3->c=(*j)->c;
	spj3->velo.z = -1*n*(*j)->velo.z;

	// --------------------------  x axis ----------------
	// create a random direction;
	srand(time(0));
	float vx = (*i)->velo.x* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	float vy = (*i)->velo.y* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	float vz = (*i)->velo.z* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	vec3 d(vx,vy,vz);
	spi1->velo = d;
	d*=(-1*spi1->mass/spj1->mass);
	spj1->velo = d;

	vx = (*i)->velo.x* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	vy = (*i)->velo.y* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	vz = (*i)->velo.z* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	d.x= vx, d.y=vy, d.z=vz;
	spi2->velo = d;
	d*=(-1*spi1->mass/spj1->mass);
	spj2->velo = d;

	vx = (*i)->velo.x* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	vy = (*i)->velo.y* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	vz = (*i)->velo.z* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	d.x= vx, d.y=vy, d.z=vz;
	spi3->velo = d;
	d*=(-1*spi1->mass/spj1->mass);
	spj3->velo = d;

	solar.erase(i); solar.erase(j);

	solar.push_back(spi1);
	solar.push_back(spi2);
	solar.push_back(spi3);
	solar.push_back(spj1);
	solar.push_back(spj2);
	solar.push_back(spj3);
}


inline void repel2(std::vector<sphere*>::iterator i, std::vector<sphere*>::iterator j){


		(*j)->velo*=(-1);
		(*i)->velo*=(-1);

}

inline void repel(std::vector<sphere*>::iterator i, std::vector<sphere*>::iterator j){
	//if (i==solar.end() ||  j == solar.end()) return;

	srand(time(0));
	float vx = (*i)->velo.x* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	float vy = (*i)->velo.y* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	float vz = (*i)->velo.z* (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));

	float vxi = ((*i)->mass*(*i)->velo.x + (*j)->mass*(*j)->velo.x - (*j)->mass*vx)/(*i)->mass;
	float vyi = ((*i)->mass*(*i)->velo.y + (*j)->mass*(*j)->velo.y - (*j)->mass*vy)/(*i)->mass;
	float vzi = ((*i)->mass*(*i)->velo.z + (*j)->mass*(*j)->velo.z - (*j)->mass*vz)/(*i)->mass;

	(*i)->velo.x = vxi, (*i)->velo.y = vyi, (*i)->velo.z=vzi;
	(*j)->velo.x = vx, (*j)->velo.y = vy, (*j)->velo.z =vz;
}

inline void detectCollition(){

	for (std::vector<sphere*>::iterator i = solar.begin();i!=solar.end();i++){
		for(std::vector<sphere*>::iterator j = (i+1);j!=solar.end();j++){
			vec3 dis = (*i)->cog-(*j)->cog;
			float mag = sqrt(dis.dot(dis));
			if (mag + ERROR <= (*i)->radius+(*j)->radius){

					//std::cout<<"BANG!\n";
					repel2(i,j);
					if (lasp <= 0)
					{	lasp ++;
						disintegrate(i,j);
					}
					else{
						lasp++;
						repel(i,j);
						if(lasp>=15){
							lasp =0;

						}
					}
					return;

			}
		}
	}

}


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
			vec3 d = solar[j]->cog - solar[k]->cog;

			float dis = (d.dot(d));

			if (dis <= ERROR ) return;

			float mag;

			dis = sqrt(dis) - (solar[j]->radius+solar[k]->radius);
			if (dis <= -ERROR){
				mag = G*(solar[j]->mass)*(solar[k]->mass)*dis/0.0001;
			}

			mag = G*(solar[j]->mass)*(solar[k]->mass)/dis;
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

		solar[j]->force(forc[j]);
		solar[j]->move(delta);

	//	solar[1].force(forc[1]);
	//	solar[1].move(delta);
	}
	detectCollition();
	//for(std::vector<sphere>::iterator i = solar.begin(); i!= solar.end();i++){
	//	i->move(delta);
	//}
	forc.swap(forc);
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

	std::vector<sphere*>::iterator i = solar.begin();
	glPushMatrix();
			glScalef(0.25,0.25,0.25);
	for (;i!=solar.end();i++){
		(*i)->draw();
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

    Camara.z= -5.0f;
    Pan.x = 20;
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


