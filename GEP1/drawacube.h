#pragma once
# include "GL2/glew.h"
# include "GL\freeglut.h"
#include "drawasphere.h"
#include <string>
using namespace std;
class drawacube
{
public:
	drawacube();
	drawacube(float r, float g, float b, float translatex, float translatey, float translatez, float size, float spd,string name);
	//constructor only stores all the values and create the new strings we need
    char *getstring(); //name of the cube
	char *getstringpos();//name of the cube + pos, e.g if the name is cube, this function will return cubepos
	char *getstringcolor();//name of the cube + color, e.g if the name is cube, this function will return cubecolor 
	char *getstringsize();//name of the cube + size, e.g if the name is cube, this function will return cubesize 
	void draw();//draws the cube
	float *getpos();//helper functions,returns pointer points to array(points to first element of array)
	float *getcolor();
	float *getsize();
private:
	char *namea; //name of cube (character array points to the first element of matching string)
	char *nameapos; // name of cube position(character array points to the first element of matching string)
	char * nameacolor;//name of cube color(character array points to the first element of matching string)
	char* nameasize;//name of cube size(character array points to the first element of matching string)
	string yidui;// stores the name(label) of cube
	string yiduipos;// name(label) of cube position
	string yiduicolor;// name(label) of cube color
	string yiduisize;// name(label) of cube size
	float color[3]; //color of cube, stored in array because imgui inputfloat3s needs address of arrays to do input
	float position[3];// //position of cube, stored in array because imgui inputfloat3s needs address of arrays to do input
	float siz; //size  
	float speed;// didn't use this since changed the code
	~drawacube();
};


