#pragma once
#include "GL2/glew.h"
#include "GL\freeglut.h"
#include "drawSphere.h"
#include <string>
using namespace std;
class drawLine
{
public:
	drawLine();
	drawLine(float r, float g, float b, float stx, float sty, float stz, float edx, float edy, float edz, float width, string name);
	~drawLine();
	float*getPosition();


	float *getColor();


	char *getLabel();               /* name of the line */


	char *getPosLabel();            /* name of the line + pos, e.g if the name is cube, this function will return cubepos */


	char *getColorLabel();          /* name of the line + color, e.g if the name is cube, this function will return cubecolor */


	void draw();                    /* draws the line */


	float length();                 /* returns length */


private:
	char	*namePointer;           /* name of line (character pointer points to the first element of matching string) */
	char	*namePosPointer;        /* name of line position(character pointer points to the first element of matching string) */
	char	* nameColorPointer;     /* name of line color(character pointer points to the first element of matching string) */

	string	label;                  /* stores the name(label) of line */
	string	labelPos;               /* name(label) of line position */
	string	labelColor;             /* name(label) of line color */

	float color[3];                 /* color of object, stored in array because imgui inputfloat3s needs address of arrays to do input */

	float position[6];              /* color of object, stored in array because imgui inputfloat6s(function i changed inputfloat3 into made tho) needs address of arrays to do input, first 3 are start pos of line, rest are end pos */
};

