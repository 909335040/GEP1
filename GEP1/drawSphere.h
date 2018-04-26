#pragma once
#include <string>
using namespace std;
struct vector4
{       /* vector with xyz to store position or color or any 3 component stuff....accepting such struct in constructors makes life easier....but ill just keep it as it is....probably for later usage */
	float	x;
	float	y;
	float	z;
	float   rot;
};


class drawSphere
{
public:
	drawSphere();
	drawSphere(float r, float g, float b, float translatex, float translatey, float translatez, float radius, float spd, string name);
	~drawSphere();
	/* constructor only stores all the values and create the new strings we need */
	char *getLabel();               /* name of the sphere */


	char *	getPosLabel();;         /* name of the sphere + pos, e.g if the name is sphere, this function will return spherepos */
	char *	getColorLabel();        /* name of the sphere + color, e.g if the name is sphere, this function will return spherecolor */


	char *getSizeLabel();           /* name of the sphere + size, e.g if the name is sphere, this function will return spheresize */


	void draw();                    /* draws the cube */


	float* getPosition();           /* helper functions,returns pointer points to array(points to first element of array) */


	float *getColor();


	float *getSize();


private:
	char	*namePointer;           /* name of sphere (character pointer points to the first element of matching string) */
	char	*namePosPointer;        /* name of sphere position(character pointer points to the first element of matching string) */
	char	* nameColorPointer;     /* name of sphere color(character pointer points to the first element of matching string) */
	char	* nameSizePointer;      /* name of sphere size(character pointer points to the first element of matching string) */
	string	label;                  /* stores the name(label) of sphere */
	string	labelPos;               /* name(label) of sphere position */
	string	labelColor;             /* name(label) of sphere color */
	string	labelSize;              /* name(label) of sphere size */

	float	color[3];               /* color of sphere, stored in array because imgui inputfloat3s needs address of arrays to do input */
	float	position[3];            /* position of sphere, stored in array because imgui inputfloat3s needs address of arrays to do input */
									/* private variables for storing the position, radius and rotating speed(cuz currently i've set it to only rotating in to one direction.....so only one speed) */
	float	radiusOfSphere;
	float	speed;
};