/*
 * auxiliary.h
 *
 *  Created on: Nov 29, 2015
 *      Author: souy
 */

#ifndef AUXILIARY_H_
#define AUXILIARY_H_

extern bool* keyStates;

extern float CLOCK;

extern float angle;

extern vec3 Camara;
extern vec3 Pan_x;
extern vec3 Pan_y;

void detectCollition();

void initialize();

#define BOUND_X 50
#define BOUND_Y 50
#define BOUND_Z 50

GLuint texture; //the array for our texture

/**
*	Parameter used for restricting the number of new objects created in a
*	collision.
*/
extern int lasp;


void keyUp (unsigned char key, int x, int y) {
	keyStates[key] = false;

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
    	Pan_x.x-=1;
    }
    if(key == 'k') {
        Pan_x.x+=1;
    }
    if(key == 'j') {
        	Pan_y.x-=1;
    }
    if(key == 'l') {
            Pan_y.x+=1;
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

    	Pan_x.x=20;
    	Pan_y.x = 0;

    }
}

inline float mod(float y){
	return (y<0?-1*y:y);
}

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
* 	Test mechanics function. hard-coded objects. Replaced by Gravity
*	@see gravity()
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


// This function displays bouncing ball through a cube.
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




//function to load the RAW file

GLuint LoadTexture( const char * filename, int width, int height )
{
    //GLuint texture;
    unsigned char * data;
    FILE * file;

    //The following code will read in our RAW file
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;

    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &texture ); //generate the texture with the loaded data
    glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture to it’s array
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    //Here we are setting the parameter to repeat the texture instead of clamping the texture
    //to the edge of our shape.
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    //Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
 GL_RGB, GL_UNSIGNED_BYTE, data);
    free( data ); //free the texture
    return texture; //return whether it was successfull
}


void Render_background(){
	texture = LoadTexture( "./OU/pur2.tga", 512,512 );
    glBindTexture( GL_TEXTURE_2D, texture ); //bind our texture to our shape
    glRotatef( 0, 1.0f, 1.0f, 1.0f );


    glBegin (GL_QUADS);
    glTexCoord3d(0.0,0.0,0.0); glVertex3d(-50.0+Camara.x,-50.0+Camara.y,-50.0+Camara.z); //with our vertices we have to assign a texcoord
    glTexCoord3d(1.0,0.0,0.0); glVertex3d(+50.0+Camara.x,-50.0+Camara.y,-50.0+Camara.z); //so that our texture has some points to draw to
    glTexCoord3d(1.0,1.0,0.0); glVertex3d(+50.0+Camara.x,+50.0+Camara.y,-50.0+Camara.z);
    glTexCoord3d(0.0,1.0,0.0); glVertex3d(-50.0+Camara.x,+50.0+Camara.y,-50.0+Camara.z);
    glEnd();
	glDeleteTextures(1, &texture);

	texture = LoadTexture( "./OU/pur.tga", 512,512 );
	glBindTexture( GL_TEXTURE_2D, texture ); //bind our texture to our shape
	glBegin (GL_QUADS);
    glTexCoord3d(0.0,0.0,0.0); glVertex3d(-50.0+Camara.x,-50.0+Camara.y,50.0+Camara.z); //with our vertices we have to assign a texcoord
    glTexCoord3d(0.0,1.0,0.0); glVertex3d(-50.0+Camara.x,+50.0+Camara.y,50.0+Camara.z); //so that our texture has some points to draw to
    glTexCoord3d(1.0,1.0,0.0); glVertex3d(-50.0+Camara.x,+50.0+Camara.y,-50.0+Camara.z);
    glTexCoord3d(1.0,0.0,0.0); glVertex3d(-50.0+Camara.x,-50.0+Camara.y,-50.0+Camara.z);
    glEnd();
	glDeleteTextures(1, &texture);

	texture = LoadTexture( "./OU/pur3.tga", 512,512 );
	glBindTexture( GL_TEXTURE_2D, texture ); //bind our texture to our shape
	glBegin (GL_QUADS);
    glTexCoord3d(0.0,0.0,0.0); glVertex3d(+50.0+Camara.x,-50.0+Camara.y,50.0+Camara.z); //with our vertices we have to assign a texcoord
    glTexCoord3d(0.0,1.0,0.0); glVertex3d(+50.0+Camara.x,+50.0+Camara.y,50.0+Camara.z); //so that our texture has some points to draw to
    glTexCoord3d(1.0,1.0,0.0); glVertex3d(+50.0+Camara.x,+50.0+Camara.y,-50.0+Camara.z);
    glTexCoord3d(1.0,0.0,0.0); glVertex3d(+50.0+Camara.x,-50.0+Camara.y,-50.0+Camara.z);
    glEnd();
	glDeleteTextures(1, &texture);


	texture = LoadTexture( "./OU/pur4.tga", 512,512 );
	glBindTexture( GL_TEXTURE_2D, texture ); //bind our texture to our shape
	glBegin (GL_QUADS);
    glTexCoord3d(0.0,0.0,0.0); glVertex3d(-50.0+Camara.x,-50.0+Camara.y,+50.0+Camara.z); //with our vertices we have to assign a texcoord
    glTexCoord3d(0.0,1.0,0.0); glVertex3d(-50.0+Camara.x,-50.0+Camara.y,-50.0+Camara.z); //so that our texture has some points to draw to
    glTexCoord3d(1.0,1.0,0.0); glVertex3d(+50.0+Camara.x,-50.0+Camara.y,-50.0+Camara.z);
    glTexCoord3d(1.0,0.0,0.0); glVertex3d(+50.0+Camara.x,-50.0+Camara.y,+50.0+Camara.z);
    glEnd();
	glDeleteTextures(1, &texture);

	texture = LoadTexture( "./OU/pur5.tga", 512,512 );
	glBindTexture( GL_TEXTURE_2D, texture ); //bind our texture to our shape
	glBegin (GL_QUADS);
       glTexCoord3d(0.0,0.0,0.0); glVertex3d(-50.0+Camara.x,+50.0+Camara.y,50.0+Camara.z); //with our vertices we have to assign a texcoord
    glTexCoord3d(0.0,1.0,0.0); glVertex3d(-50.0+Camara.x,+50.0+Camara.y,-50.0+Camara.z); //so that our texture has some points to draw to
    glTexCoord3d(1.0,1.0,0.0); glVertex3d(+50.0+Camara.x,+50.0+Camara.y,-50.0+Camara.z);
    glTexCoord3d(1.0,0.0,0.0); glVertex3d(+50.0+Camara.x,+50.0+Camara.y,50.0+Camara.z);
    glEnd();
	glDeleteTextures(1, &texture);


	texture = LoadTexture( "./OU/pur6.tga", 512,512 );
	glBindTexture( GL_TEXTURE_2D, texture ); //bind our texture to our shape
	  glBegin (GL_QUADS);
    glTexCoord3d(0.0,0.0,0.0); glVertex3d(-50.0+Camara.x,-50.0+Camara.y,50.0+Camara.z); //with our vertices we have to assign a texcoord
    glTexCoord3d(1.0,0.0,0.0); glVertex3d(+50.0 +Camara.x,-50.0+Camara.y,50.0+Camara.z); //so that our texture has some points to draw to
    glTexCoord3d(1.0,1.0,0.0); glVertex3d(+50.0+Camara.x,+50.0+Camara.y,50.0 +Camara.z);
    glTexCoord3d(0.0,1.0,0.0); glVertex3d(-50.0+Camara.x,+50.0+Camara.y,50.0+Camara.z);
    glEnd();
	glDeleteTextures(1, &texture);


}


inline bool outside_the_OU(const sphere& s){
	return (s.cog.x > BOUND_X) || (s.cog.y > BOUND_Y) || (s.cog.z > BOUND_Z) ||
			(s.cog.x < -BOUND_X) || (s.cog.y < -BOUND_Y) || (s.cog.z < -BOUND_Z);
}



#endif /* AUXILIARY_H_ */
