#include "drawacube.h"
#include<iostream>;


drawacube::drawacube()
{

}

drawacube::drawacube(float r, float g, float b, float translatex, float translatey, float translatez, float size, float spd,string name)
{
	color[0] = r;//store colors
	color[1] = g;
	color[2] = b;
	position[0] = translatex; // store positions
	position[1] = translatey;
	position[2] = translatez;
	speed = spd;// abanadoned value, used to represent speed
	yidui = name; // name(label) of cube
	yiduipos = yidui + "pos";// create & store NAME(LABEL) of cube position
	yiduicolor = yidui + "color";//create & store NAME(LABEL) of cube color
	yiduisize = yidui + "size";//create & store NAME(LABEL) of cube size
	siz = size; //size of cube
	namea = &yidui[0]; //make the pointer points to strings(where names(labels) are stored), cuz Imgui requires address of char array as labels
	nameapos = &yiduipos[0]; 
	nameacolor = &yiduicolor[0]; 
	nameasize = &yiduisize[0]; 

}

 char *drawacube::getstring()
{
	return namea; // return label of cube
}

 char * drawacube::getstringpos()
 {
	 return  nameapos;// return label of cube pos
 }

 char * drawacube::getstringcolor()
 {
	 return nameacolor;//// return label of cube color
 }

 char * drawacube::getstringsize()
 {
	 return nameasize;//// return label of cube size
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
	return position;//returning float pointer of position array
}

float * drawacube::getcolor()
{
	return color;//returning float pointer of color array
}

 

float *drawacube::getsize()
{
	return &siz;//returning float pointer of size
}


drawacube::~drawacube()
{
}
