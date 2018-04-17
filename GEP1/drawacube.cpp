#include "drawacube.h"
#include<iostream>;


drawacube::drawacube()
{

}

drawacube::drawacube(float r, float g, float b, float translatex, float translatey, float translatez, float size, float spd,string name)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
	position[0] = translatex;
	position[1] = translatey;
	position[2] = translatez;
	speed = spd;
	yidui = name;
	yiduipos = yidui + "pos";
	yiduicolor = yidui + "color";
	yiduisize = yidui + "size";
	siz = size;
	namea = &yidui[0];
	nameapos = &yiduipos[0];
	nameacolor = &yiduicolor[0];
	nameasize = &yiduisize[0];

}

 char *drawacube::getstring()
{
	return namea;
}

 char * drawacube::getstringpos()
 {
	 return  nameapos;
 }

 char * drawacube::getstringcolor()
 {
	 return nameacolor;
 }

 char * drawacube::getstringsize()
 {
	 return nameasize;
 }

void drawacube::draw()
{	//transformations 
	glPushMatrix();//push matrix to stack 

	glColor3f(color[0], color[1], color[2]);//color 

	glTranslatef(position[0], position[1], position[2]);//position
	glRotatef(speed, 0, 1, 0);//rotate along z axis
	glutWireCube(siz); // cube
	glPopMatrix(); //pop from stack
}

float *drawacube::getpos()
{
	return position;
}

float * drawacube::getcolor()
{
	return color;
}

 

float *drawacube::getsize()
{
	return &siz;
}


drawacube::~drawacube()
{
}
