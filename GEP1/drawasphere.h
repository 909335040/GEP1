#pragma once
#include <string>
using namespace std;
struct vector333
{    // vector with xyz to store position or color or any 3 component stuff....accepting such struct in constructors makes life easier....but ill just keep it as it is....probably for later usage
	float x;
	float y;
	float z;

};




class drawasphere
{
public:
	drawasphere();
	drawasphere(float r, float g, float b, float translatex, float translatey, float translatez, float radius, float spd,string name);
	char *getstring();
	char *getstringpos();
	char *getstringcolor();
	char *getstringsize();
	void draw();
	float* getpos(); // return 
	float *getcolor();
	float *getsize();
	float getradius(); // return the radius of sphere


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
	vector333 pos;  //private variables for storing the position, radius and rotating speed(cuz currently i've set it to only rotating in to one direction.....so only one speed)
	float radi;
	float speed;

	~drawasphere();
};

