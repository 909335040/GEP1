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
	//constructor only stores all the values and create the new strings we need
	char *getstring(); //name of the sphere
	char *getstringpos();;//name of the sphere + pos, e.g if the name is sphere, this function will return spherepos
	char *getstringcolor();//name of the sphere + color, e.g if the name is sphere, this function will return spherecolor 
	char *getstringsize();//name of the sphere + size, e.g if the name is sphere, this function will return spheresize 
	void draw();//draws the cube

	float* getpos(); //helper functions,returns pointer points to array(points to first element of array)
	float *getcolor();
	float *getsize();
	float getradius(); // return the radius of sphere


private:
	char *namea; //name of sphere (character array points to the first element of matching string)
	char *nameapos; // name of sphere position(character array points to the first element of matching string)
	char * nameacolor;//name of sphere color(character array points to the first element of matching string)
	char* nameasize;//name of sphere size(character array points to the first element of matching string)
	string yidui;// stores the name(label) of sphere
	string yiduipos;// name(label) of sphere position
	string yiduicolor;// name(label) of sphere color
	string yiduisize;// name(label) of sphere size
	 
	float color[3];//color of sphere, stored in array because imgui inputfloat3s needs address of arrays to do input
	float position[3];//position of sphere, stored in array because imgui inputfloat3s needs address of arrays to do input
	vector333 pos;  //private variables for storing the position, radius and rotating speed(cuz currently i've set it to only rotating in to one direction.....so only one speed)
	float radi;
	float speed;

	~drawasphere();
};

