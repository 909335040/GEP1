#include "drawaspot.h"
# include "GL2/glew.h"
# include "GL\freeglut.h"
#include "drawasphere.h"


drawaspot::drawaspot()
{
}

drawaspot::drawaspot(float r, float g, float b, float posx, float posy, float posz , string name)
{  // draw 3 lines, around the spot with same color 
 
	position[0] = posx;
	position[1] = posy;
	position[2] = posz;
	color[0] = r;
	color[1] = g;
	color[2] = b;
	yidui = name;
	yiduipos = yidui + "pos";
	yiduicolor = yidui + "color";
	namea = &yidui[0];
	nameapos = &yiduipos[0];
	nameacolor = &yiduicolor[0];
 

}

void drawaspot::draw()
{
	glBegin(GL_LINES);////line among x pos
	glLineWidth(2.5f);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(position[0] - .5f, position[1], position[2]);
	glVertex3f(position[0] + .5f, position[1], position[2]);
	glEnd();

	glBegin(GL_LINES);//line among y pos
	glLineWidth(2.5f);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(position[0], position[1] - .5f, position[2]);
	glVertex3f(position[0], position[1] + .5f, position[2]);
	glEnd();

	glBegin(GL_LINES);// line among z pos
	glLineWidth(2.5f);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(position[0], position[1], position[2] - .5f);
	glVertex3f(position[0], position[1], position[2] + .5f);
	glEnd();
}

char * drawaspot::getstring()
{
	return namea;
}

char * drawaspot::getstringpos()
{
	return nameapos;
}

char * drawaspot::getstringcolor()
{
	return nameacolor;
}

 

float* drawaspot::getpos()
{
	return position;
}

float * drawaspot::getcolor()
{
	return color;
}



drawaspot::~drawaspot()
{
}

