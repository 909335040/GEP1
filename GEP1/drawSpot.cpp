#include "drawSpot.h"
#include "GL2/glew.h"
#include "GL\freeglut.h"
#include "drawSphere.h"


drawSpot::drawSpot()
{
}


drawSpot::drawSpot(float r, float g, float b, float posx, float posy, float posz, string name)
{                                                       /* draw 3 lines, around the spot with same color */
	position[0] = posx;                 /* store positions */
	position[1] = posy;
	position[2] = posz;
	color[0] = r;                    /* store colors */
	color[1] = g;
	color[2] = b;
	label = name;                 /* store name(label) of spot */
	labelPos = label + "pos";        /* create & store NAME(LABEL) of spot position */
	labelColor = label + "color";      /* create & store NAME(LABEL) of spot color */
	namePointer = &label[0];            /* make the pointer points to strings(where names(labels) are stored), cuz Imgui requires address of char array as labels */
	namePosPointer = &labelPos[0];
	nameColorPointer = &labelColor[0];
}


void drawSpot::draw()
{
	glBegin(GL_LINES);    /* //line among x pos */
	glLineWidth(2.5f);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(position[0] - .5f, position[1], position[2]);
	glVertex3f(position[0] + .5f, position[1], position[2]);
	glEnd();

	glBegin(GL_LINES);    /* line among y pos */
	glLineWidth(2.5f);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(position[0], position[1] - .5f, position[2]);
	glVertex3f(position[0], position[1] + .5f, position[2]);
	glEnd();

	glBegin(GL_LINES);    /* line among z pos */
	glLineWidth(2.5f);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(position[0], position[1], position[2] - .5f);
	glVertex3f(position[0], position[1], position[2] + .5f);
	glEnd();
}


char * drawSpot::getLabel()
{
	return(namePointer);            /* return label of spot */
}


char * drawSpot::getPosLabel()
{
	return(namePosPointer);         /* return label of spot position */
}


char * drawSpot::getColorLabel()
{
	return(nameColorPointer);       /* return label of spot color */
}


float* drawSpot::getPosition()
{
	return(position);               /* //return position (pointer points to first element of array) */
}


float * drawSpot::getColor()
{
	return(color);                  /* return color (pointer points to first element of array) */
}


drawSpot::~drawSpot()
{
	delete namePointer;
	delete namePosPointer;
	delete nameColorPointer;
}


