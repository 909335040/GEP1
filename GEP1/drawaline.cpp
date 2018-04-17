#include "drawaline.h"
# include "GL2/glew.h"
# include "GL\freeglut.h"
#include "drawasphere.h"
#include <math.h>

drawaline::drawaline()
{
}

drawaline::drawaline(float r, float g, float b, float stx, float sty, float stz, float edx, float edy, float edz, float with, string name)
{
 
	color[0] = r;//store colors
	color[1] = g;
	color[2] = b;

	position[0] = stx;// store start and end positions of line
	position[1] = sty;
	position[2] = stz;
	position[3] = edx;
	position[4] = edy;
	position[5] = edz;
	yidui = name; // NAME(LABEL) of line
	yiduipos = yidui + "pos";// create & store NAME(LABEL) of line position
	yiduicolor = yidui + "color";//create & store NAME(LABEL) of line color
 
	namea = &yidui[0];//make the pointer points to strings(where names(labels) are stored), cuz Imgui requires address of char array as labels
	nameapos = &yiduipos[0];
	nameacolor = &yiduicolor[0];
	 
 
	//store parameters in variables
	 
}

float * drawaline::getpos()
{
	return position; //returning float pointer of position array
}

float * drawaline::getcolor()
{
	return color; //returning float pointer of color array
}

 

char * drawaline::getstring()
{
	return namea; // return label of line
}

char * drawaline::getstringpos()
{
	return nameapos;// return label of line position
}

char * drawaline::getstringcolor()
{
	return nameacolor;// return label of line color
}

 

void drawaline::draw()
{ 
	glBegin(GL_LINES);  //  line(primitive)
	 
	glColor3f(color[0], color[1], color[2]); //color
	glVertex3f(position[0], position[1], position[2]); //startposition
	glVertex3f(position[3], position[4], position[5]);//end position
	glEnd();
}

//helper methods

 

float drawaline::length()
{
	
	
	
	
	return sqrt((position[0]-position[3])*(position[0] - position[3]) + (position[1] - position[4])*(position[1] - position[4]) + (position[2] - position[5])*(position[2] - position[5])); //length of line
}







drawaline::~drawaline()
{
}

