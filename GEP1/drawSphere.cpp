#include "drawSphere.h"
#include "GL2/glew.h"
#include "GL\freeglut.h"
#include "drawSphere.h"


drawSphere::drawSphere()
{
}


drawSphere::drawSphere(float r, float g, float b, float translatex, float translatey, float translatez, float radius, float spd, string name)
{                                                       /* constructor */
	color[0] = r;                    /* store colors */
	color[1] = g;
	color[2] = b;
	position[0] = translatex;           /* store positions */
	position[1] = translatey;
	position[2] = translatez;
	speed = spd;
	label = name;                 /* name(label) of sphere */
	namePointer = &label[0];
	labelPos = label + "pos";        /* create & store NAME(LABEL) of sphere position */
	labelColor = label + "color";      /* create & store NAME(LABEL) of sphere color */
	labelSize = label + "size";       /* create & store NAME(LABEL) of sphere size */
	radiusOfSphere = radius;               /* radius of sphere */
	namePosPointer = &labelPos[0];         /* make the pointer points to strings(where names(labels) are stored), cuz Imgui requires address of char array as labels */
	nameColorPointer = &labelColor[0];
	nameSizePointer = &labelSize[0];
}


char * drawSphere::getLabel()
{
	return(namePointer);                                    /* return label of sphere */
}


char * drawSphere::getPosLabel()
{
	return(namePosPointer);                                 /* return label of sphere pos */
}


char * drawSphere::getColorLabel()
{
	return(nameColorPointer);                               /* return label of sphere color */
}


char * drawSphere::getSizeLabel()
{
	return(nameSizePointer);                                /* return label of sphere size */
}


void drawSphere::draw()
{
	glPushMatrix();                                         /* push to stack */

	glColor3f(color[0], color[1], color[2]);              /* color */
	glTranslatef(position[0], position[1], position[2]);  /* set position */
	glRotatef(90, 1, 0, 0);                               /* rotate 90 degrees along x axis */
	glRotatef(speed, 0, 0, 1);                            /* rotate 'spd' degrees along its original z axis after the previous rotation(value of spd(from parameter) is changing , if constant than not rotating) */
	glutWireSphere(radiusOfSphere, 20, 50);               /* sphere. radius is the only thing matters */
	glPopMatrix();                                          /* pop from stack */
}


/* helper functions */
float* drawSphere::getPosition()
{
	return(position);                                       /* return position(pointer points to first element of array) */
}


float * drawSphere::getColor()
{
	return(color);                                          /* return color(pointer points to first element of array) */
}


float * drawSphere::getSize()
{
	return(&radiusOfSphere);                                /* return radius pointer(pointer points to first element of array) */
}


drawSphere::~drawSphere()
{
	delete namePointer;
	delete namePosPointer;
	delete nameColorPointer;
	delete nameSizePointer;
}


