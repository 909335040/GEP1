#pragma once
# include "GL2/glew.h"
# include "GL\freeglut.h"
#include "drawasphere.h"
#include <string>
using namespace std;
class drawaline
{
public:
	drawaline();
	drawaline(float r, float g, float b, float stx, float sty, float stz, float edx, float edy, float edz, float width,string name);
	float*getpos();
	float *getcolor();
 
	char *getstring(); //name of the line
	char *getstringpos();//name of the line + pos, e.g if the name is cube, this function will return cubepos
	char *getstringcolor();//name of the line + color, e.g if the name is cube, this function will return cubecolor 
 
	void draw();//draws the line

	float length(); //returns length
private:
	char *namea; //name of line (character array points to the first element of matching string)
	char *nameapos; // name of line position(character array points to the first element of matching string)
	char * nameacolor;//name of line color(character array points to the first element of matching string)
	 
	string yidui;// stores the name(label) of line
	string yiduipos;// name(label) of line position
	string yiduicolor;// name(label) of line color
	
	float color[3];//color of object, stored in array because imgui inputfloat3s needs address of arrays to do input
	vector333 pos;//start position
	vector333 endpos;//end position
	float position[6];//color of object, stored in array because imgui inputfloat6s(function i changed inputfloat3 into made tho) needs address of arrays to do input, first 3 are start pos of line, rest are end pos
	vector333 col;//color 
	float width;// width



	~drawaline();
};

