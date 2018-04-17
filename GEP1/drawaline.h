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
 
	char *getstring();
	char *getstringpos();
	char *getstringcolor();
 
	void draw();

	float length();
private:
	char *namea;
	char *nameapos;
	char * nameacolor;
	 
	string yidui;
	string yiduipos;
	string yiduicolor;
	 
	float color[3];
	vector333 pos;//start position
	vector333 endpos;//end position
	float position[6];
	vector333 col;//color 
	float width;// width



	~drawaline();
};

