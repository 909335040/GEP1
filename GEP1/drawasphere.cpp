#include "drawasphere.h"
# include "GL2/glew.h"
# include "GL\freeglut.h"
#include "drawasphere.h"


drawasphere::drawasphere()
{
}

drawasphere::drawasphere(float r, float g, float b, float translatex, float translatey, float translatez, float radius, float spd,string name)
{//constructor
	color[0] = r; //store colors
	color[1] = g;
	color[2] = b;
	position[0] = translatex;// store positions
	position[1] = translatey;
	position[2] = translatez;
	speed = spd;
	yidui = name;// name(label) of sphere
	namea = &yidui[0];
	yiduipos = yidui + "pos";// create & store NAME(LABEL) of sphere position
	yiduicolor = yidui + "color";//create & store NAME(LABEL) of sphere color
	yiduisize = yidui + "size";//create & store NAME(LABEL) of sphere size
	radi = radius;//radius of sphere
	nameapos = &yiduipos[0];//make the pointer points to strings(where names(labels) are stored), cuz Imgui requires address of char array as labels
	nameacolor = &yiduicolor[0];
	nameasize = &yiduisize[0];



}
char * drawasphere::getstring()
{
	return namea;// return label of sphere
}
char * drawasphere::getstringpos()
{
	return nameapos;// return label of sphere pos
}
char * drawasphere::getstringcolor()
{
	return nameacolor;// return label of sphere color
}
char * drawasphere::getstringsize()
{
	return nameasize;// return label of sphere size
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
	return color;//return color
}

float * drawasphere::getsize()
{
	return &radi;//return radius pointer
}



float drawasphere::getradius()
{
	return radi;//return radius, abandoned function
}




drawasphere::~drawasphere()
{
}
