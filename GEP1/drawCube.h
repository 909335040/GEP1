#pragma once
# include "GL2/glew.h"
# include "GL\freeglut.h"
#include "drawSphere.h"
#include <string>
using namespace std;
class drawCube
{
public:
	drawCube();
	drawCube(float r, float g, float b, float translatex, float translatey, float translatez, float size, float spd,string name);
	~drawCube();
	//constructor only stores all the values and create the new strings we need
    char *getLabel(); //name of the cube
	char *getPosLabel();//name of the cube + pos, e.g if the name is cube, this function will return cubepos
	char *getColorLabel();//name of the cube + color, e.g if the name is cube, this function will return cubecolor 
	char *getSizeLabel();//name of the cube + size, e.g if the name is cube, this function will return cubesize 
	void draw();//draws the cube
	float *getPosition();//helper functions,returns pointer points to array(points to first element of array)
	float *getColor();
	float *getSize();
private:
	char *namePointer; //name of cube (character pointer points to the first element of matching string)
	char *namePosPointer; // name of cube position(character pointer points to the first element of matching string)
	char * nameColorPointer;//name of cube color(character pointer points to the first element of matching string)
	char* nameSizePointer;//name of cube size(character pointer points to the first element of matching string)
	string label;// stores the name(label) of cube
	string labelPos;// name(label) of cube position
	string labelColor;// name(label) of cube color
	string labelSize;// name(label) of cube size
	float color[3]; //color of cube, stored in array because imgui inputfloat3s needs address of arrays to do input
	float position[3];// //position of cube, stored in array because imgui inputfloat3s needs address of arrays to do input
	float sizeOfShape; //size  
	float speed;// didn't use this since changed the code

};


