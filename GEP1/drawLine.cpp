#include "drawLine.h"
#include "GL2/glew.h"
#include "GL\freeglut.h"
#include "drawSphere.h"
#include <math.h>

drawLine::drawLine()
{
}


drawLine::drawLine(float r, float g, float b, float stx, float sty, float stz, float edx, float edy, float edz, float with, string name)
{
	color[0] = r;                    /* store colors */
	color[1] = g;
	color[2] = b;

	position[0] = stx;                  /* store start and end positions of line */
	position[1] = sty;
	position[2] = stz;
	position[3] = edx;
	position[4] = edy;
	position[5] = edz;
	label = name;                 /* NAME(LABEL) of line */
	labelPos = label + "pos";        /* create & store NAME(LABEL) of line position */
	labelColor = label + "color";      /* create & store NAME(LABEL) of line color */

	namePointer = &label[0];    /* make the pointer points to strings(where names(labels) are stored), cuz Imgui requires address of char array as labels */
	namePosPointer = &labelPos[0];
	nameColorPointer = &labelColor[0];


	/* store parameters in variables */
}


float * drawLine::getPosition()
{
	return(position);                                       /* returning position(pointer points to first element of array) */
}


float * drawLine::getColor()
{
	return(color);                                          /* returning color(pointer points to first element of array) */
}


char * drawLine::getLabel()
{
	return(namePointer);                                    /* return label of line */
}


char * drawLine::getPosLabel()
{
	return(namePosPointer);                                 /* return label of line position */
}


char * drawLine::getColorLabel()
{
	return(nameColorPointer);                               /* return label of line color */
}


void drawLine::draw()
{
	glBegin(GL_LINES);                                    /*  line(primitive) */

	glColor3f(color[0], color[1], color[2]);              /* color */
	glVertex3f(position[0], position[1], position[2]);    /* startposition */
	glVertex3f(position[3], position[4], position[5]);    /* end position */
	glEnd();
}


/* helper methods */


float drawLine::length()
{
	return(sqrt((position[0] - position[3]) * (position[0] - position[3]) + (position[1] - position[4]) * (position[1] - position[4]) + (position[2] - position[5]) * (position[2] - position[5]))); /* length of line */
}


drawLine::~drawLine()
{
	delete namePointer;
	delete namePosPointer;
	delete nameColorPointer;
}


