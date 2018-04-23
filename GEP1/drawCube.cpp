#include "drawCube.h"
#include<iostream>


drawCube::drawCube()
{

}

drawCube::drawCube(float r, float g, float b, float translatex, float translatey, float translatez, float size, float spd,string name)
{
	color[0] = r;//store colors
	color[1] = g;
	color[2] = b;
	position[0] = translatex; // store positions
	position[1] = translatey;
	position[2] = translatez;
	speed = spd;// abanadoned value, used to represent speed
	label = name; // name(label) of cube
	labelPos = label + "pos";// create & store NAME(LABEL) of cube position
	labelColor = label + "color";//create & store NAME(LABEL) of cube color
	labelSize = label + "size";//create & store NAME(LABEL) of cube size
	sizeOfShape = size; //size of cube
	namePointer = &label[0]; //make the pointer points to strings(where names(labels) are stored), cuz Imgui requires address of char array as labels
	namePosPointer = &labelPos[0]; 
	nameColorPointer = &labelColor[0]; 
	nameSizePointer = &labelSize[0]; 

}

 char *drawCube::getLabel()
{
	return namePointer; // return label of cube
}

 char * drawCube::getPosLabel()
 {
	 return  namePosPointer;// return label of cube pos
 }

 char * drawCube::getColorLabel()
 {
	 return nameColorPointer;//// return label of cube color
 }

 char * drawCube::getSizeLabel()
 {
	 return nameSizePointer;//// return label of cube size
 }

void drawCube::draw()
{	//transformations 
	glPushMatrix();//push matrix to stack 

	glColor3f(color[0], color[1], color[2]);//color 

	glTranslatef(position[0], position[1], position[2]);//position
	glRotatef(speed, 0, 1, 0);//rotate along z axis
	glutWireCube(sizeOfShape); // cube
	glPopMatrix(); //pop from stack
}

float *drawCube::getPosition()
{
	return position;//return position pointer(pointer points to first element of array)
}

float * drawCube::getColor()
{
	return color;//return color pointer(pointer points to first element of array)
}

 

float *drawCube::getSize()
{
	return &sizeOfShape;//returning float pointer of size
}


drawCube::~drawCube()
{
	delete namePointer;
	delete namePosPointer;
	delete nameColorPointer;
	delete nameSizePointer;
}
