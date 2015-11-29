/*
 * fist.cpp
 *
 *  Created on: Oct 31, 2015
 *      Author: souy
 */

//#include <omp.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include "basic_shape.h"
#include "initializer.h"
#include "auxiliary.h"



/**
 * Buffer used for storing the triggers from the key board
*/
bool* keyStates = new bool[256];

/**
* 	The main rendering function
*/

float CLOCK=0;

float angle =0.02;

vec3 Camara;
vec3 Pan_x;
vec3 Pan_y;
/*
 * @New_world_parameter:
 */
// currently only two objects can collide at the same time.
// once two object has collided and they disintigrate they are marked for removal
std::vector<sphere>::iterator a;
std::vector<sphere>::iterator b;
// The set of new objects added in each collision is stored in
std::vector<sphere>* new_worlds;




/**
*	Parameter used for restricting the number of new objects created in a 
*	collision.
*/
int lasp=0;



void renderPrimitive(){

	glColor3f(1.0f,0.5f,0.5f);

	if (keyStates['a']){
		//std::cout<<"This was true";
		//drawCircle(0.0f,0.0f,0.0f,2.0f,200);
	}

}







inline void initialize(){
			//glEnable(GL_BLEND); // Enable the OpenGL Blending functionality
		    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set the blend mode to blend our current RGBA with what is already in the buffer

		    glClearColor(0.5f, 0.5f, 0.5f, 0.5f); // Clear the background of our window to white
		    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
		    glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

		    glEnable( GL_TEXTURE_2D); // Enable the OpenGL Blending functionality
		    glTranslatef(Camara.x,Camara.y,Camara.z); // Push eveything 5 units back into the scene, otherwise we won't see the primitive

		    glRotatef(Pan_x.x, 1.0f, 0.0f, 0.0f);
		    glRotatef(Pan_y.x, 0.0f, 1.0f, 0.0f);

		// Light source is the star
		    GLfloat qaLightPosition[] = {0.0,0.0,0.0,1.0};
		 /*   if (solar.empty()){
		    	qaLightPosition[0]	= 0.0;
		    	qaLightPosition[1]	= 0.0;
		    	qaLightPosition[2]	= 0.0;
		    	qaLightPosition[3]	= 1.0;
		    }
		    else{
		    	qaLightPosition[0]	= solar[0].cog.x;
		    			    	qaLightPosition[1]	= solar[0].cog.y+solar[0].radius;
		    			    	qaLightPosition[2]	= solar[0].cog.z+solar[0].radius;
		    			    	qaLightPosition[3]	= 1.0;
		    }
*/

		// Light source is some point in space.
		// GLfloat qaLightPosition[] = {0,0,5.0,1.0};
		glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);


}

void disintegrate(std::vector<sphere>::iterator i, std::vector<sphere>::iterator j){
	// Initializing the new worlds parameters
	new_worlds->clear();
	a = solar.end();
	b = solar.end();


	if (i==solar.end() ||  j == solar.end() || solar.size() >= MAX_OBJ) return;

	//Smaller body gets absorbed
	if (i->mass < 0.01*(j->mass) || i->radius <0.1){
		j->mass+= i->mass;
		j->radius+= 0.0008;
		//a =i;
		i->cog.x=BOUND_X+1;
		return;
	}
	if (j->mass < 0.001*(i->mass) || j->radius <0.1){
			i->mass+= j->mass;
			i->radius+= 0.0008;
			//b=j;
			j->cog.x=BOUND_X+1;
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

	//Marked for deletion.
	//a = i;
	//b = j;
	new_worlds->push_back(*spi1);
	new_worlds->push_back(*spi2);
	new_worlds->push_back(*spi3);
	
	new_worlds->push_back(*spj1);
	new_worlds->push_back(*spj2);
	new_worlds->push_back(*spj3);

	return;

}


inline void repel2(std::vector<sphere>::iterator i, std::vector<sphere>::iterator j){

		j->velo*=(-1);
		i->velo*=(-1);
		i->acci*=(-1);
		j->acci*=(-1);
}




inline void detectCollition(){

	for (std::vector<sphere>::iterator i = solar.begin();i!=solar.end();i++){

		if (outside_the_OU(*i)){
				continue;
		}

		for(std::vector<sphere>::iterator j = (i+1);j!=solar.end();j++){
			if (outside_the_OU(*i)){
							continue;
			}
			vec3 dis = i->cog-j->cog;
			float scal_dis =dis.dot(dis)*SCALE*SCALE;

			if (scal_dis <= (i->radius+j->radius + ERROR)*SCALE*(i->radius+j->radius + ERROR)*SCALE ){
				//repel2(i,j);

					int number_of_objects = solar.size();
					std::cout<<"number "<<number_of_objects<<"\n";
					if (number_of_objects < MAX_OBJ)
					{
						disintegrate(i,j);
						//repel2(i,j);
						return;
					}
					else{
						repel2(i,j);
						//lasp++;
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

	// Initialize force vector for each object in the universe.
	for(unsigned int i=0;i< N;i++){
		vec3 c;
		forc.push_back(c);
	}
	for(unsigned int j =0;j<solar.size();j++){
		//vec3 forci;
		if (outside_the_OU(solar[j]) == false){
			for(unsigned int k = (j+1); k<solar.size(); k++){
				if (outside_the_OU(solar[j]) == false){

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

						forc[k]+=d;
						forc[j]-=d;
					}
				}
			}
		}

		solar[j].force(forc[j]);
		solar[j].move(delta);

	}
	detectCollition();
	
	forc.swap(forc);
}


inline void Render_obj(){
	//std::vector<sphere *> to_be_del;
	std::vector<sphere>::iterator i = solar.begin();
			//	glPushMatrix();
					glScalef(0.25,0.25,0.25);
		/*			for (;i!=solar.end();i++){
						i->draw();
					}
*/			//		glPopMatrix();

					while(i!=solar.end()){
						if(outside_the_OU(*i)){
							i++;
							//to_be_del.push_back(i);
							//i->draw();
						}
						else{
							i->draw();
							i++;
						}

					}

}



// Solar system with N-bodies, the size of the solar system.
void renderstatic3(){



			initialize();

			Render_background();

			Render_obj();

			glutSwapBuffers();

			gravity();
//			if(a!=solar.end())
//								solar.erase(a);
//							if(b!=solar.end())
//								solar.erase(b);

			for (auto it = new_worlds->begin();it!=new_worlds->end();it++){
							solar.push_back(*it);
			}

			new_worlds->clear();





}


// SOLAR systems with three bodies.





void reshape (int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}


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


/* Main method - main entry point of application
the freeglut library does the window creation work for us,
regardless of the platform. */
int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1000,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Newtonian Gravity Simulator!!");
    init();

    Camara.z= -5.0f;
    Pan_x.x = 20;
    load();
    new_worlds = new std::vector<sphere>();
    a = solar.end();
    b = solar.end();

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



