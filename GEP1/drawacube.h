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
    char *getstring();
	char *getstringpos();
	char *getstringcolor();
	char *getstringsize();
	void draw();
	float *getpos();//helper functions
	float *getcolor();
	float *getsize();
private:
	char *namea;
	char *nameapos;
	char * nameacolor;
	char* nameasize;
	string yidui;
	string yiduipos;
	string yiduicolor;
	string yiduisize;
	float color[3];
	float position[3];
	float siz; //size and rotation speed
	float speed;
	~drawacube();
};


