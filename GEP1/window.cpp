# include "window.h"
#include "drawasphere.h"
#include "drawacube.h"
#include <vector>
#include "drawaline.h"
#include "imgui.h"
#include "imgui_impl_glut.h"
#include "drawaspot.h"
#include <thread>
#include"glm\glm.hpp"
# include "QuestManager.h"
#include<string>
//# include "QuestGUI.h"
# include "imgui_internal.h"
# include "imconfig.h"
GLuint VBO;
using namespace std;
int adspheresize=0;
int adcubesize = 0;
int adlinesize = 0;
int adspotsize = 0;
string string1 = "addsphere";
string string11 = "scolor";
string string12 = "spos";
string string2 = "addcube";
string string3 = "addline";
string string4 = "addspot";
drawacube * cb;
drawasphere *a1;
drawaline *ln;
drawaspot *spt;
MD2Model* _model;
int _textureId;
const float FLOOR_TEXTURE_SIZE = 20.0f; //The size of each floor "tile"
//QuestGUI qgui;
QuestManager qm;
float _guyPos = 0;
int sizea = 3;
vector<drawasphere*> spheres;
vector<drawacube*> cubes;
vector <drawaspot*> spots;
vector < drawaline*>lines;
float debug = 1;//flag if true go through debug  else not 
float dbgrls = 1;  //flag  for detecting the release of the key that toggles on/off debug draw(otherwise its going back and forth til key released)
int dbgdkey = 0x76;//f7 key used for switch on/off debug

float p = 0;  //variables for cube/spheres rotation
float p2 = 0;
float p3 = 0;
int lft = 0x41;
int rgt = 0x44;
int  frt = 0x53;
int bac = 0x57;
  
float modpos[3] = { 0,4.5f,-80.0f };
float modrot = 0;  // rotationX of model
float stateposx;  //store modposx at start of recording
float stateposz;  //store modposz at start of recording
float staterot;   //store modrot at start of recording 
drawasphere *a; // a sphere
bool show_test_window = true;
bool show_another_window = true;
bool show_qgui = true;
//choice for tabs in gui
int tabb = 1;
int statea=0;


//variables for bounding box
/*static int xminxx;
static int xmaxxx;
static int yminyy;
static int ymaxyy;
static int zminzz;
static int zmaxzz;*/



void Window::InitRender() { 
	glEnable(GL_DEPTH_TEST);
}
void Window::savestate(int a)
{
	statea = a;
 
}

void Window:: cleanup() {
	delete _model;
}
bool keyboardEvent(unsigned char nChar, int nX, int nY)
{
	ImGuiIO& io = ImGui::GetIO();
	

	io.AddInputCharacter(nChar);
	
	if (nChar == 8) {
		cout << "nmsl";
		io.Dpv();
	 
	}

	
	if (nChar == 27) //Esc-key
		glutLeaveMainLoop();
	
	return true;
}
 

bool mouseEvent(int button, int state, int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	if (state == GLUT_DOWN && (button == GLUT_LEFT_BUTTON))
		io.MouseDown[0] = true;
	else
		io.MouseDown[0] = false;

	if (state == GLUT_DOWN && (button == GLUT_RIGHT_BUTTON))
		io.MouseDown[1] = true;
	else
		io.MouseDown[1] = false;

	return true;
}

void mouseWheel(int button, int dir, int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);
	if (dir > 0)
	{
		// Zoom in
		io.MouseWheel = 1.0;
	}
	else if (dir < 0)
	{
		// Zoom out
		io.MouseWheel = -1.0;
	}
}

 

void keyboardCallback(unsigned char nChar, int x, int y)
{
	if (keyboardEvent(nChar, x, y))
	{
		glutPostRedisplay();
	}
}

void mouseCallback(int button, int state, int x, int y)
{
	if (mouseEvent(button, state, x, y))
	{
		glutPostRedisplay();
	}
}

void mouseDragCallback(int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	glutPostRedisplay();
}

void mouseMoveCallback(int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	glutPostRedisplay();
}
void Window::drawgui()
{
	ImGui_ImplGLUT_NewFrame(1600, 900);

	
	
	
	
	// 1. Show a simple window
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
	{
		

		{
			
			
			static float f = 0.0f;

			ImGui::Begin("Debug Draw", &show_another_window);
			ImGui::SetWindowSize(ImVec2(600, 400));
			

			
				ImGui::Text("                          DebugDraws");
				ImGui::Text("========================================================");
				ImGui::Text("      Xpos                Ypos                Zpos");
				ImGui::InputFloat3("modelpos", modpos);

				ImGui::Text("                          Cubes");
				ImGui::Text("========================================================");
				ImGui::Text("========================================================");
				for (int i = 0; i < cubes.size(); i++) {
					ImGui::Text("                         "); ImGui::SameLine();
					ImGui::Text(cubes.at(i)->getstring());
					ImGui::Text("      Xpos                Ypos                Zpos");
					ImGui::InputFloat3(cubes.at(i)->getstringpos(), cubes.at(i)->getpos());
					ImGui::Text("      Red                 Green               Blue");
					ImGui::InputFloat3(cubes.at(i)->getstringcolor(), cubes.at(i)->getcolor());
					ImGui::Text("                          Size ");
					ImGui::InputFloat(cubes.at(i)->getstringsize(), cubes.at(i)->getsize());

					ImGui::Text("========================================================");
					ImGui::Text("========================================================");
				}

				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::Text("                          Spheres");
				ImGui::Text("========================================================");
				ImGui::Text("========================================================");
				for (int i = 0; i < spheres.size(); i++) {
					ImGui::Text("                         "); ImGui::SameLine();
					ImGui::Text(spheres.at(i)->getstring());
					ImGui::Text("      Xpos                Ypos                Zpos");
					ImGui::InputFloat3(spheres.at(i)->getstringpos(), spheres.at(i)->getpos());
					ImGui::Text("      Red                 Green               Blue");
					ImGui::InputFloat3(spheres.at(i)->getstringcolor(), spheres.at(i)->getcolor());
					ImGui::Text("                          Radius ");
					ImGui::InputFloat(spheres.at(i)->getstringsize(), spheres.at(i)->getsize());

					ImGui::Text("========================================================");
					ImGui::Text("========================================================");
				}
				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::NewLine();

				ImGui::Text("                          Lines");
				ImGui::Text("========================================================");
				ImGui::Text("========================================================");
				for (int i = 0; i < lines.size(); i++) {
					ImGui::Text("                         ");
					ImGui::SameLine();
					ImGui::Text(lines.at(i)->getstring());
					ImGui::Text("  StartX   StartY   StartZ    EndX      EndY      EndZ");
					ImGui::InputFloat6(lines.at(i)->getstringpos(), lines.at(i)->getpos());
					ImGui::Text("      Red                 Green               Blue");
					ImGui::InputFloat3(lines.at(i)->getstringcolor(), lines.at(i)->getcolor());


					ImGui::Text("========================================================");
					ImGui::Text("========================================================");
				}
				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::NewLine();

				ImGui::Text("                          Spots");
				ImGui::Text("========================================================");
				ImGui::Text("========================================================");
				for (int i = 0; i < spots.size(); i++) {
					ImGui::Text("                         ");
					ImGui::SameLine();
					ImGui::Text(spots.at(i)->getstring());
					ImGui::Text("      Xpos                Ypos                Zpos");
					ImGui::InputFloat3(spots.at(i)->getstringpos(), spots.at(i)->getpos());
					ImGui::Text("      Red                 Green               Blue");
					ImGui::InputFloat3(spots.at(i)->getstringcolor(), spots.at(i)->getcolor());
					ImGui::Text("========================================================");
					ImGui::Text("========================================================");
				}




				if (ImGui::Button("Add Sphere")) {
					++adspheresize;
					string namba = to_string(adspheresize);
					string1 += namba;
					drawasphere *s = new drawasphere(.8f, .1f, .1f, 0, 0, -20, 1, 0, string1);
					spheres.push_back(s);
					string1 = "addsphere";

				}
				ImGui::SameLine();
				if (ImGui::Button("Add Cube")) {
					++adcubesize;
					string namba = to_string(adcubesize);
					string2 += namba;
					drawacube *s = new drawacube(.8f, .1f, .1f, 0, 0, -20, 1, 0, string2);
					cubes.push_back(s);
					string2 = "addcube";

				}		ImGui::SameLine();
				if (ImGui::Button("Add Lines")) {
					++adlinesize;
					string namba = to_string(adlinesize);
					string3 += namba;
					drawaline *s = new drawaline(.8f, 0, 0, 0, 1, -10, 10, 0, -10, 5.5, string3);
					lines.push_back(s);
					string3 = "addline";

				}
				ImGui::SameLine();
				if (ImGui::Button("Add Spot")) {
					++adspotsize;
					string namba = to_string(adspotsize);
					string4 += namba;
					drawaspot *s = new drawaspot(.8f, .1f, .1f, -3, -1, -15, string4);
					spots.push_back(s);
					string4 = "addspot";

				}
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			
			

		
			
			ImGui::End();

			ImGui::Begin("Quest Manager window",&show_qgui);
			qm.QuestGUI();
			qm.AddTask();
			ImGui::End();
		}
		

		
		
	}

 

	ImGui::Render();
}

void Window::storeVariables()
{
	stateposx = modpos[0];//store variables, this function is used when recording just starts
	stateposz = modpos[2];
	staterot = modrot;
}

void Window::playbackInit()
{

	modpos[0]=stateposx; //store variables, this function is used when recording just starts
		modpos[2] = stateposz;
	  modrot = staterot;
}

void Window::handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		cleanup();
		exit(0);
	}
}

GLuint Window::loadTexture(Image *image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width, image->height,0,GL_RGB,GL_UNSIGNED_BYTE,image->pixels);
	return textureId;
}

void Window::initRendering() {
	glEnable(GL_DEPTH_TEST);
	 
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	 
 
	ImGui_ImplGLUT_Init();
	//Load the model
 
	_model = MD2Model::load("tallguy.md2");
	if (_model != NULL) {
		_model->setAnimation("run");

		xminxx = getxminx();

		xmaxxx = getxmaxx();
		yminyy = getyminy();
		ymaxyy = getymaxy();
		zminzz = getzminz();
		zmaxzz = getzmaxz();
		
	}
 
	//Renders the floor(a sample grass image with certain values for width)
	//Draw_Floor();

	

}
 

void Window::handleResize(int x, int y) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(20, (GLdouble)x / (GLdouble)y, .5f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
}
void Window::initshapes()
{
	
	cb = new drawacube(0, .8f, 0, 0, 0, -20, 1, p3,"cube1");  // draw cube 
	cubes.push_back(cb);
	a = new drawasphere(.1f, .8f, .1f, 1.5f, 0, -10, .5f, p,"sphere1");
	spheres.push_back(a);
    a1= new drawasphere(.1f, .8f, .1f, -1.5, 0, -10, .5f, p2, "sphere2");
	spheres.push_back(a1);
	ln = new drawaline(.8f, .8f, .1f, 0, 0, -10, 5, 0, -10, 5.5, "line1");//draw line
	lines.push_back(ln);
	spt = new drawaspot(.8f, .8f, .1f, -2, 1, -15, "spot1");//draw spot(lines)
	spots.push_back(spt);
}

void Window::debugdraw()
{
	 
	for (int i = 0; i < spheres.size(); i++) { spheres.at(i)->draw(); }
	for (int i = 0; i < cubes.size(); i++) { cubes.at(i)->draw(); }
	for (int i = 0; i < lines.size(); i++) { lines.at(i)->draw(); }
	for (int i = 0; i < spots.size(); i++) { spots.at(i)->draw(); }
 
}
void Window::drawScene() {
	 
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
 
	ImGuiIO&io = ImGui::GetIO();


 
	//Draw the guy
	if (_model != NULL) {
		 // model transforms
	 

 



 

 
		glPushMatrix();
		glTranslatef(modpos[0], modpos[1],modpos[2]);
		glScalef(0.5f, 0.5f, 0.5f);
		glRotatef(-90.0f, 0.0f, 0, 1.0f);
		glRotatef(modrot, 1.0f, 0.0, 0.0f);
		glClearColor(0, 0, 0, 0);
		_model->draw();
		
		glPopMatrix();
	}

	if (debug>0) {
		debugdraw();
		drawgui();
	}
	glutSwapBuffers();
}
void Window::Draw_Floor() {



	glTranslatef(0.0f, -5.4f, 0.0f);	//starting point of drawing
										//binding the texture for loading 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//drawing the plane between the glbegin and glend
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(60 / FLOOR_TEXTURE_SIZE, _guyPos / FLOOR_TEXTURE_SIZE);
	glVertex3f(-30.0f, 0.0f, -30.0f);
	glTexCoord2f(60 / FLOOR_TEXTURE_SIZE, (60 + _guyPos) / FLOOR_TEXTURE_SIZE);
	glVertex3f(-30.0f, 0.0f, 30.0f);
	glTexCoord2f(0.0f, (60 + _guyPos) / FLOOR_TEXTURE_SIZE);
	glVertex3f(30.0f, 0.0f, 30.0f);
	glTexCoord2f(0.0f, _guyPos / FLOOR_TEXTURE_SIZE);
	glVertex3f(30.0f, 0.0f, -30.0f);

	glEnd();


}

void Window::update() {
	 
	 if (GetAsyncKeyState(dbgdkey)&0x8000 &&dbgrls>0) {
	
		//key f7 as the key to toggle debug draw on/off
		debug = -debug; //change the debug flag to opposite
		dbgrls =-1;// set the flag for f7 release to -1 until release so no repeating

	}
	 else if (GetAsyncKeyState(dbgdkey) == 0) {
	 
		 dbgrls = 1; //

	 }
	//Advance the animation
	if (_model != NULL) {

		

		if (GetAsyncKeyState(lft)||statea==3) { //if keys(wasd) pressed, change following rotation and position
			_model->advance(.015f); // for playing for animation, controls time value in md2model(controls the play of animation...i didn't look in to how is it done originally was .025f, slowed it for a bit)
			modpos[0] -= 0.1f;//move position(to left by 0.1f)
			xminxx -= 0.1f;
			xmaxxx -= 0.1f;
			modrot = 90.0f; //x rotation value
		 
		}
		else if (GetAsyncKeyState(rgt)||statea==4) { // right
			_model->advance(.015f);
			modpos[0] += 0.1f;
			xminxx += 0.1f;
			xmaxxx += 0.1f;
			modrot = -90.0f;
 

		}
		else if (GetAsyncKeyState(frt)||statea==2) {//s, backwards
			_model->advance(.015f);
			modpos[2] += 0.1f;
			zminzz += 0.1f;
			zmaxzz += 0.1f;
			modrot = 0.0f;
	 
		}
		else if (GetAsyncKeyState(bac)||statea==1) {//w, forward
			_model->advance(.015f);
			modpos[2] -= 0.1f;
			zminzz -= 0.1f;
			zmaxzz -= 0.1f;
			modrot = 180.0f;	 
		}
		else  {
			_model->setfm();
		}
	}
 
 
	p += .5f;  //rotation value change for sphere on left
	p2 -= 0.8f;//rotation value change for sphere on right
	p3 += .8f;//rotation value change for cube


	glutPostRedisplay();
 
}



 


void Window::Create_Window(int argv, char** argc ) {
	initshapes();
	glutInit(&argv, argc);
	glutInitDisplayMode(  GLUT_DEPTH| GLUT_DOUBLE);
	glutInitWindowSize(1600, 900);
	 
	glutCreateWindow("Alpha Engine");
	initRendering();

	glutDisplayFunc(drawScene);
 
	glutReshapeFunc(handleResize);
	glutKeyboardFunc(keyboardCallback);
 
	glutMouseFunc(mouseCallback);
	glutMouseWheelFunc(mouseWheel);
	glutMotionFunc(mouseDragCallback);
	glutPassiveMotionFunc(mouseMoveCallback);
	glutIdleFunc(update);
	glutMainLoop();
	
}


float getxminxx() {
	return xminxx;
}

float getxmaxxx() {
	return xmaxxx;
}

float getyminyy() {
	return yminyy;
}

float getymaxyy() {
	return ymaxyy;
}

float getzminzz() {
	return zminzz;
}

float getzmaxzz() {
	return zmaxzz;
}

