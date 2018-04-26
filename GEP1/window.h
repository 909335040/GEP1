#pragma once

# include "GL2/glew.h"
# include "GL\freeglut.h"
# include "glm/vec3.hpp"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
# include<math.h>
# include <vector>
 
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "drawSphere.h"
#include "imageloader.h"
#include "md2model.h"
class Window {

	
public:
	static void saveState(int a);
	 
	static void cleanUp();
	static void drawGui();
	static void storeVariables();
	static void playbackInit();
	static void handleKeypress(unsigned char key, int x, int y);
	static GLuint loadTexture(Image *image);
	static void initRendering();
	static void handleResize(int w, int h);
	static void update();	
	static void initShapes();
	static void debugDraw();
	static void Draw_Floor();
	static void drawScene();
	static vector4 returnModelData();
	static void writeModelData(vector4 modData);
	static void Create_Window(int argv,char** argc);
 
	static void InitRender();
 
 
	  ~Window();
};

static float xminxx;
static float xmaxxx;
static float yminyy;
static float ymaxyy;
static float zminzz;
static float zmaxzz;

float getxminxx();
float getxmaxxx();
float getyminyy();
float getymaxyy();
float getzminzz();
float getzmaxzz();

