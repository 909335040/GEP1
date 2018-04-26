#pragma once
#include "GL2/glew.h"
#include "GL\freeglut.h"
#include "drawSphere.h"
#include <string>
using namespace std;
class drawSpot
{
public:
	drawSpot();
	drawSpot(float r, float g, float b, float posx, float posy, float posz, string name);
	~drawSpot();
	void draw();


	char *getLabel();               /* name of spot */


	char *getPosLabel();            /* name of spot position */


	char *getColorLabel();          /* name of spot color */


	float *getPosition();           /* helper functions */


	float *getColor();              /* helper functions */


private:
	string	label;                  /* name(label) of spot */
	string	labelPos;               /* name(label) of spot position */
	string	labelColor;             /* name(label) of spot color */
	char	*namePointer;           /* name of spot (character pointer points to the first element of matching string) */
	char	*namePosPointer;        /* name of spot position (character pointer points to the first element of matching string) */
	char	* nameColorPointer;     /* name of color (character pointer points to the first element of matching string) */
	float	position[3];            /* position of object, stored in array because imgui inputfloat3s needs address of arrays to do input */
	float	color[3];               /* color of object, stored in array because imgui inputfloat3s needs address of arrays to do input */
};

