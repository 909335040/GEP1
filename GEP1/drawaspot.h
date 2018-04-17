#pragma once
# include "GL2/glew.h"
# include "GL\freeglut.h"
#include "drawasphere.h"
#include <string>
using namespace std;
class drawaspot
{
public:
	drawaspot();
	drawaspot(float r, float g, float b, float posx, float posy, float posz, string name);
	void draw();
	char *getstring();
	char *getstringpos();
	char *getstringcolor();
 
	float *getpos();//helper functions
	float *getcolor();
	 


private:
	string yidui;
	string yiduipos;
	string yiduicolor;
	char *namea;
	char *nameapos;
	char * nameacolor;
	float position[3];
	float color[3];



	~drawaspot();
};

