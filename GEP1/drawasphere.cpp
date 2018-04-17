#include "drawasphere.h"
# include "GL2/glew.h"
# include "GL\freeglut.h"
#include "drawasphere.h"


drawasphere::drawasphere()
{
}

drawasphere::drawasphere(float r, float g, float b, float translatex, float translatey, float translatez, float radius, float spd,string name)
{//constructor
	color[0] = r;
	color[1] = g;
	color[2] = b;
	position[0] = translatex;
	position[1] = translatey;
	position[2] = translatez;
	speed = spd;
	yidui = name;
	namea = &yidui[0];
	yiduipos = yidui + "pos";
	yiduicolor = yidui + "color";
	yiduisize = yidui + "radius";
	radi = radius;
	nameapos = &yiduipos[0];
	nameacolor = &yiduicolor[0];
	nameasize = &yiduisize[0];



}
char * drawasphere::getstring()
{
	return namea;
}
char * drawasphere::getstringpos()
{
	return nameapos;
}
char * drawasphere::getstringcolor()
{
	return nameacolor;
}
char * drawasphere::getstringsize()
{
	return nameasize;
}
void drawasphere::draw()
{
	glPushMatrix();  //push to stack

	glColor3f(color[0], color[1], color[2]); // color
	glTranslatef(position[0], position[1], position[2]);//set position
	glRotatef(90, 1, 0, 0);// rotate 90 degrees along x axis
	glRotatef(speed, 0, 0, 1); // rotate 'spd' degrees along its original z axis after the previous rotation(value of spd(from parameter) is changing , if constant than not rotating)
	glutWireSphere(radi, 20, 50); // sphere. radius is the only thing matters
	glPopMatrix();// pop from stack
}
// helper functions
float* drawasphere::getpos()
{
	return position;//return position
}

float * drawasphere::getcolor()
{
	return color;
}

float * drawasphere::getsize()
{
	return &radi;
}



float drawasphere::getradius()
{
	return radi;//return radius
}




drawasphere::~drawasphere()
{
}
