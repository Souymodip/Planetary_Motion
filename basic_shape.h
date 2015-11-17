/*
 * basic_shape.h
 *
 *  Created on: Nov 1, 2015
 *      Author: souy
 */

#ifndef BASIC_SHAPE_H_
#define BASIC_SHAPE_H_

#include "GL/freeglut.h"
#include "GL/gl.h"
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265

int MY_INDEX=0;

inline void drawCircle(const float x, const float y, const float z, float r,int al){
	glBegin(GL_LINE_LOOP);
	/*
		x' = x*cos q - y*sin q
		y' = x*sin q + y*cos q
		z' = z
	*/
	al = (al < 1? 1:al);
	for(int i=0;i< al; i++){
		float angle = 2*PI*((float)i/al);
		float x1 = (r)*cos(angle) ;
		float y1 = (r)*sin(angle) ;
		//std::cout<<"("<<x1<<","<<y1<<","<<z<<") :"<<"angle "<<angle<<" ";
		glVertex3f(x1+x,y1+y,z);
	}
	glEnd();
}

inline void drawSphere(float radius, int prec){
    int numSlices = prec;
    int numStacks = prec;

    glColor3f(1.0f,0.5f,0.5f);
    drawCircle(0.0f,0.0f,0.0f,radius+0.2,200);
    GLUquadricObj* pQuadric = gluNewQuadric();
    //assert(pQuadric!=NULL);

    glColor3f(0.0f,0.5f,0.5f);
    gluSphere(pQuadric,radius,numSlices,numStacks);

    //glRotatef(-0.5f,0.0f,0.1f,0.0f);
}


inline void drawSphere2(float radius, int prec=200){

	for(int i=0;i<prec;i++){
		float rad_i = radius*sin(PI*(float)i/(float)prec);
		glBegin(GL_LINE_LOOP);
		for(int j=0;j<prec;j++){
			float angle = 2*PI*((float)j/(float)prec);
			glVertex3f(rad_i*cos(angle),rad_i*sin(angle),2*radius*(float)i/(float)prec-radius);
		}
		glEnd();
	}

}


inline void mySphere(float radius,int prec){
	glPushMatrix();
	glRotatef(30,1.0f,1.0f,0.0f);
/*	for(int i=0;i<prec;i++){
		glPushMatrix();
			glRotatef((float)360/prec*(float)i,0.0f,1.0f,0.0f);
			drawCircle(0.0f,0.0f,0.0f,radius,200);
		glPopMatrix();
	}
*/
	glPopMatrix();
}

inline void myCube(float length, float width, float height){
	glLineWidth(2.5);
	glBegin(GL_LINE_STRIP);
		glVertex3f(-length/2, -width/2, 0.0);
		glVertex3f(length/2, -width/2, 0.0);
		glVertex3f(length/2, width/2, 0.0);
		glVertex3f(-length/2, width/2, 0.0);
		glVertex3f(-length/2, -width/2, 0.0);
		glVertex3f(-length/2, -width/2, height);
		glVertex3f(length/2, -width/2, height);
		glVertex3f(length/2, width/2, height);
		glVertex3f(-length/2, width/2, height);
		glVertex3f(-length/2, -width/2, height);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(-length/2, width/2, 0.0);
		glVertex3f(-length/2, width/2, height);
	glEnd();

	glBegin(GL_LINES);
			glVertex3f(length/2, width/2, 0.0);
			glVertex3f(length/2, width/2, height);
	glEnd();

	glBegin(GL_LINES);
			glVertex3f(length/2, -width/2, 0.0);
			glVertex3f(length/2,-width/2, height);
	glEnd();
}


class vec3{
private:

public:
	float x;
		float y;
		float z;

	vec3(float x=0,float y=0,float z=0):x(x),y(y),z(z){}
	vec3(const vec3& v):x(v.x),y(v.y),z(v.z){}

	void set(float x, float y, float z){
		this->x=x; this->y=y, this->z=z;
	}

	vec3& operator=(const vec3& v){
		x= v.x,y=v.y,z=v.z;
		return *this;
	}
	vec3& operator-=(const vec3& v){
		x-=v.x,y-=v.y,z-=v.z;
		return *this;
	}

	vec3& operator+=(const vec3& v){
			x+=v.x,y+=v.y,z+=v.z;
			return *this;
	}
	vec3& operator-(const vec3& v){
			vec3* v1= new vec3(x- v.x,y- v.y,z- v.z);
			return *v1;
	}
	vec3& operator*=(float c){
		x*=c; y*=c; z*=c;
		return *this;
	}

	vec3& operator+(const vec3& v){
				vec3* v1= new vec3(x+ v.x,y+ v.y,z+ v.z);
				return *v1;
		}

	float dot(const vec3& v){
		return x*v.x + y*v.y + z*v.z;
	}

	void normal(){
		float mag = sqrt(x*x+y*y+z*z);
		if(mag<=0) return;
		x=x/mag; y= y/mag; z= z/mag;
	}

};

enum colour{
	red,yellow,blue,green,black,white
};

inline void colourIt(int c){
	switch(c){
	case black:
			glColor4f(0,0,0,1);
			break;
	case	green:
			glColor4f(0,1,0,1);
			break;
	case	blue:
			glColor4f(0,0,1,1);;
			break;
	case	red:
			glColor4f(1,0.2,0,1);
			break;
	case	yellow:
			glColor4f(0.2,0.2,0,1);
			break;
	case 	white:
			glColor4f(1,1,1,0);
			break;
	}
}

class shape{

public:
	vec3 cog;
		vec3 velo;
		vec3 acci;

		float mass;
		vec3 colour;

		float spin;
	void move(float time){
		velo.x = velo.x + acci.x*time;
		velo.y = velo.y + acci.y*time;
		velo.z = velo.z + acci.z*time;

		cog.x = cog.x + velo.x*time;
				cog.y = cog.y + velo.y*time;
				cog.z = cog.z + velo.z*time;
	}

	void force(vec3 f){
		acci.x = f.x/mass;
		acci.y = f.y/mass;
		acci.z = f.z/mass;
	}

	virtual void draw(float angle=0)=0;
};

class sphere : public shape{
	int prec;
public:

	float radius;
	int c;
	sphere(float x,float y,float z, float r, float m, int p =200)
	:prec(p),radius(r){
		this->c = (MY_INDEX++)%6;
		cog.x=x; cog.y =y; cog.z =z;
		velo.x=0; velo.y=0; velo.z=0;
		acci.x=0; acci.y=0; acci.z=0;

		mass = m;

		spin =1;
	}

	sphere(vec3 pos, float r, float m, int p =200)
		:prec(p),radius(r){
			this->c = (MY_INDEX++)%5;
			cog.x=pos.x; cog.y =pos.y; cog.z =pos.z;
			velo.x=0; velo.y=0; velo.z=0;
			acci.x=0; acci.y=0; acci.z=0;

			mass = m;
	}
	virtual void draw(float angle=0){
		spin+=0.05;
		if (spin >360)
			spin =1;
		//glPushMatrix();
			//glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
		glPushMatrix();
			glTranslatef(cog.x,cog.y,cog.z);

//			glPushMatrix();

			glRotatef(spin,1.0f,1.0f,0.0f);

				glPushMatrix();
					colourIt(c);
					glutSolidSphere(radius,15,15);
					//glRotatef((float)360/prec*(float)i,0.0f,1.0f,0.0f);
					//drawCircle(0.0f,0.0f,0.0f,radius,prec);
				glPopMatrix();


//			glPopMatrix();
		glPopMatrix();
		//glPopMatrix();
	}

	void draw2(){
		for(int i=0;i<prec;i++){
				float rad_i = radius*sin(PI*(float)i/(float)prec);
				glBegin(GL_LINE_LOOP);
				for(int j=0;j<prec;j++){
					float angle = 2*PI*((float)j/(float)prec);
					glVertex3f(rad_i*cos(angle),rad_i*sin(angle),2*radius*(float)i/(float)prec-radius);
				}
				glEnd();
			}
	}
};


class astroid : public sphere{
public:
	astroid(float x,float y,float z, float r, float m, int p =200)
		:sphere(x,y,z,r,m,p){}

	astroid(vec3 pos, float r, float m, int p =200):sphere(pos,r,m,p){}

	void draw(float angle=0){
			spin+=1;
			if (spin >360)
				spin =1;

			glPushMatrix();
				glTranslatef(cog.x,cog.y,cog.z);

	//			glPushMatrix();

				srand(time(0));

				static int A= rand()%5+2;
				static int B= rand()%5+2;

				glRotatef(spin,1.0f,1.0f,0.0f);
					glPushMatrix();
						colourIt(c);
						glutSolidSphere(radius,A,B);
						//glRotatef((float)360/prec*(float)i,0.0f,1.0f,0.0f);
						//drawCircle(0.0f,0.0f,0.0f,radius,prec);
					glPopMatrix();
	//			glPopMatrix();
			glPopMatrix();
			//glPopMatrix();
		}
};

#endif /* BASIC_SHAPE_H_ */
