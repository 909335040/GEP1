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

#include "imageloader.h"
#include "md2model.h"
class Window {

	
public:
	static void cleanup();
	static void drawgui();
	static void storeVariables();
	static void playbackInit();
	static void handleKeypress(unsigned char key, int x, int y);
	static GLuint loadTexture(Image *image);
	static void initRendering();
	static void handleResize(int w, int h);
	static void update();	
	static void initshapes();
	static void debugdraw();
	static void Draw_Floor();
	static void drawScene();
    
	static void Create_Window(int argv,char** argc);
 
	static void InitRender();
 


};