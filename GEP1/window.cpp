#include "window.h"
#include "drawSphere.h"
#include "drawCube.h"
#include <vector>
#include "drawLine.h"
#include "imgui.h"
#include "imgui_impl_glut.h"
#include "drawSpot.h"
#include <thread>
#include "glm\glm.hpp"
#include "QuestManager.h"
#include <string>
/* # include "QuestGUI.h" */
#include "imgui_internal.h"
#include "imconfig.h"
GLuint VBO;
using namespace std;
int		buttonAddedSphereCount = 0;            /* numbers of spheres added through buttons */
int		buttonAddedCubeCount = 0;            /* numbers of cubes added through buttons */
int		buttonAddedLineCount = 0;            /* numbers of lines added through buttons */
int		buttonAddedSpotCount = 0;            /* numbers of spots added through buttons */
string		sphereLabelGeneral = "addsphere";  /* names(without index) for shapes added through buttons */
string		cubeLabelGeneral = "addcube";
string		lineLabelGeneral = "addline";
string		spotLabelGeneral = "addspot";
drawCube	* cb;                                   /* a few debug draw shapes with pre-set values */
drawSphere	*a;
drawSphere	*a1;
drawLine	*ln;
drawSpot	*spt;
MD2Model	* _model;
int		_textureId;
const float	FLOOR_TEXTURE_SIZE = 20.0f;             /* The size of each floor "tile" */
													/* QuestGUI qgui; */
QuestManager	qm;
float		_guyPos = 0;

vector<drawSphere*>	spheres;                        /* vectors of shapes, all debug draw shapes are stored in these vectors */
vector<drawCube*>	cubes;
vector <drawSpot*>	spots;
vector < drawLine*>	lines;
float			debugFlag = 1;            /* Flag if true go through debug  else not */
float			debugKeyRelease = 1;            /* Flag  for detecting the release of the key that toggles on/off debug draw(otherwise its going back and forth til key released) */
int			dbgdkey = 0x76;         /* f7 key used for switch on/off debug */

float	p = 0;                                    /* variables for cube/spheres rotation(currently abandoned) */
float	p2 = 0;
float	p3 = 0;

int	aKey = 0x41;                                 /* virtual key codes for keys controls movements */
int	dKey = 0x44;
int	wKey = 0x53;
int	sKey = 0x57;

float	modelPosition[3] = { 0, 4.5f, -80.0f };         /* model default position */
float	modelRotation = 0;                              /* rotationX of model */
float	startPosX;                                      /* store modelPositionx at start of recording */
float	startPosZ;                                      /* store modelPositionz at start of recording */
float	startRotation;                                  /* store modelRotation at start of recording */

bool	show_test_window = true;
bool	show_another_window = true;
bool	show_qgui = true;
/* choice for tabs in gui */

int stateOfModelMovement = 0;                           /* state/Flag variable that will cause the model move */




void Window::InitRender()
{
	glEnable(GL_DEPTH_TEST);
}


Window::~Window()
{       /* clear memory */
	delete _model;

	for (size_t i = 0; i < cubes.size(); i++)
	{
		delete cubes.at(i);
	}
	for (size_t i = 0; i < spheres.size(); i++)
	{
		delete spheres.at(i);
	}
	for (size_t i = 0; i < lines.size(); i++)
	{
		delete lines.at(i);
	}
	for (size_t i = 0; i < spots.size(); i++)
	{
		delete spots.at(i);
	}

	spots.clear();
	lines.clear();
	spheres.clear();
	cubes.clear();
}


void Window::saveState(int a)
{
	stateOfModelMovement = a; /* statea variable to the state */
}


void Window::cleanUp()
{
	delete _model;
}


/* ***************************All Input Functions for IMGUI are from https://github.com/bitxue/imgui   // */
bool keyboardEvent(unsigned char nChar, int nX, int nY)
{
	ImGuiIO & io = ImGui::GetIO();


	io.AddInputCharacter(nChar);

	if (nChar == 8)
	{
		io.Dpv();
	}


	if (nChar == 27) /* Esc-key */
		glutLeaveMainLoop();

	return(true);
}


bool mouseEvent(int button, int state, int x, int y)
{
	ImGuiIO & io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	if (state == GLUT_DOWN && (button == GLUT_LEFT_BUTTON))
		io.MouseDown[0] = true;
	else
		io.MouseDown[0] = false;

	if (state == GLUT_DOWN && (button == GLUT_RIGHT_BUTTON))
		io.MouseDown[1] = true;
	else
		io.MouseDown[1] = false;

	return(true);
}


void mouseWheel(int button, int dir, int x, int y)
{
	ImGuiIO & io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);
	if (dir > 0)
	{
		/* Zoom in */
		io.MouseWheel = 1.0;
	}
	else if (dir < 0)
	{
		/* Zoom out */
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
	ImGuiIO & io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	glutPostRedisplay();
}


void mouseMoveCallback(int x, int y)
{
	ImGuiIO & io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	glutPostRedisplay();
}


/* above all imgui input function from git are over. */

void Window::drawGui()
{
	ImGui_ImplGLUT_NewFrame(1600, 900);                                                                                                           /* resolution of imgui window should be same with the glut window size or else the input will not be accurate */


																																				  /*
																																				  * 1. Show a simple window
																																				  * Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
																																				  */
	{
		{
			ImGui::Begin("Debug Draw", &show_another_window);                                                                             /* begin this window, show another window is a bool value, when this value is true its showing this window, when its false the window hides */
			ImGui::SetWindowSize(ImVec2(600, 400));                                                                                     /* hardcoded window size */


			ImGui::Text("                          DebugDraws");                                                                          /* some hardcoded text to make the context in window look neat */
			ImGui::Text("========================================================");
			ImGui::Text("      Xpos                Ypos                Zpos");
			ImGui::InputFloat3("modelPosition", &modelPosition[0]);                                                                       /* create blanks to change the model position, modelpos is the hardcoded label, modelposition is the array that storing the models position */
			ImGui::Text("      Xpos                Ypos                Zpos");
			ImGui::InputFloat("modelRotation", &modelRotation);
			ImGui::Text("========================================================");                                                      /* some hardcoded text to make the context in window look neat */
			ImGui::Text("========================================================");
			ImGui::NewLine();                                                                                                               /* 3 lines of nothing(white spaces) before going to next set of shapes */
			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::Text("                          Cubes");                                                                               /* some hardcoded text to make the context in window look neat */
			ImGui::Text("========================================================");
			ImGui::Text("========================================================");
			for (size_t i = 0; i < cubes.size(); i++)                                                                                     /* looping through the cubes array */
			{
				ImGui::Text("                         ");                                                                             /* hardcoded spaces before the name of cube, to make it look neat */
				ImGui::SameLine();                                                                                                      /* to make whatever context after the previous ones(hardcoded spaces) displayed on the same line with the previous text */
				ImGui::Text(cubes.at(i)->getLabel());                                                                               /* label/name of cubes */
				ImGui::Text("      Xpos                Ypos                Zpos");                                                    /* some hardcoded text to make the context in window look neat */
				ImGui::InputFloat3(cubes.at(i)->getPosLabel(), cubes.at(i)->getPosition());                                       /* create blanks to change the position of cubes,labels are "cubename+index+pos", array are from the classes, was storing the cube positions */
				ImGui::Text("      Red                 Green               Blue");                                                    /* some hardcoded text to make the context in window look neat */
				ImGui::InputFloat3(cubes.at(i)->getColorLabel(), cubes.at(i)->getColor());;                                       /* create blanks to change the position of cubes,labels are "cubename+index+color", array are from the classes, was storing the cube colors */
				ImGui::Text("                          Size ");                                                                       /* some hardcoded text to make the context in window look neat */
				ImGui::InputFloat(cubes.at(i)->getSizeLabel(), cubes.at(i)->getSize());;                                          /* create blanks to change the position of cubes,labels are "cubename+index+size", input value are from the class, was storing the cubes size */

				ImGui::Text("========================================================");                                              /* some hardcoded text to make the context in window look neat */
				ImGui::Text("========================================================");
			}

			ImGui::NewLine();                                                                                                               /* 3 lines of nothing(white spaces) before going to next set of shapes */
			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::Text("                          Spheres");                                                                             /* some hardcoded text to make the context in window look neat,big seperatation from previous shapes */
			ImGui::Text("========================================================");
			ImGui::Text("========================================================");
			for (size_t i = 0; i < spheres.size(); i++)
			{
				ImGui::Text("                         ");                                                                             /* hardcoded spaces before the name of sphere, to make it look neat */
				ImGui::SameLine();                                                                                                      /* to make whatever context after the previous ones(hardcoded spaces) displayed on the same line with the previous text */
				ImGui::Text(spheres.at(i)->getLabel());                                                                             /* label/name of spheres */
				ImGui::Text("      Xpos                Ypos                Zpos");                                                    /* some hardcoded text to make the context in window look neat */
				ImGui::InputFloat3(spheres.at(i)->getPosLabel(), spheres.at(i)->getPosition());                                   /* create blanks to change the position of spheres,labels are "spherename+index+pos", array are from the classes, was storing the  position of sphere */
				ImGui::Text("      Red                 Green               Blue");                                                    /* some hardcoded text to make the context in window look neat */
				ImGui::InputFloat3(spheres.at(i)->getColorLabel(), spheres.at(i)->getColor());                                    /* create blanks to change the color of spheres,labels are "spherename+index+color", array are from the classes,was storing the color of sphere */
				ImGui::Text("                          Radius ");                                                                     /* some hardcoded text to make the context in window look neat */
				ImGui::InputFloat(spheres.at(i)->getSizeLabel(), spheres.at(i)->getSize());                                       /* create blanks to change the size of spheres,labels are "spherename+index+size", array are from the classes, was storing the size of sphere */

				ImGui::Text("========================================================");                                              /* some hardcoded text to make the context in window look neat */
				ImGui::Text("========================================================");
			}
			ImGui::NewLine();                                                                                                               /* 3 lines of nothing(white spaces) before going to next set of shapes */
			ImGui::NewLine();
			ImGui::NewLine();

			ImGui::Text("                          Lines");                                                                               /* some hardcoded text to make the context in window look neat,big seperatation from previous shapes */
			ImGui::Text("========================================================");
			ImGui::Text("========================================================");
			for (size_t i = 0; i < lines.size(); i++)
			{
				ImGui::Text("                         ");                                                                             /* hardcoded spaces before the name of sphere, to make it look neat */
				ImGui::SameLine();                                                                                                      /* to make whatever context after the previous ones(hardcoded spaces) displayed on the same line with the previous text */
				ImGui::Text(lines.at(i)->getLabel());                                                                               /* label/name of lines */
				ImGui::Text("  StartX   StartY   StartZ    EndX      EndY      EndZ");                                                /* /some hardcoded text to make the context in window look neat */
				ImGui::InputFloat6(lines.at(i)->getPosLabel(), lines.at(i)->getPosition());                                       /* create blanks to change the position of lines,labels are "linename+index+position", array are from the classes, was storing the starting and ending positions(basically 2 spots) of line */
				ImGui::Text("      Red                 Green               Blue");                                                    /* some hardcoded text to make the context in window look neat */
				ImGui::InputFloat3(lines.at(i)->getColorLabel(), lines.at(i)->getColor());                                        /* create blanks to change the color of lines,labels are "linename+index+color", array are from the classes, was storing the color of line */


				ImGui::Text("========================================================");                                              /* some hardcoded text to make the context in window look neat */
				ImGui::Text("========================================================");
			}
			ImGui::NewLine();                                                                                                               /* 3 lines of nothing(white spaces) before going to next set of shapes */
			ImGui::NewLine();
			ImGui::NewLine();

			ImGui::Text("                          Spots");                                                                               /* some hardcoded text to make the context in window look neat,big seperatation from previous shapes */
			ImGui::Text("========================================================");
			ImGui::Text("========================================================");
			for (size_t i = 0; i < spots.size(); i++)
			{
				ImGui::Text("                         ");                                                                             /* hardcoded spaces before the name of sphere, to make it look neat */
				ImGui::SameLine();                                                                                                      /* to make whatever context after the previous ones(hardcoded spaces) displayed on the same line with the previous text */
				ImGui::Text(spots.at(i)->getLabel());                                                                               /* label/name of spots */
				ImGui::Text("      Xpos                Ypos                Zpos");                                                    /* some hardcoded text to make the context in window look neat */
				ImGui::InputFloat3(spots.at(i)->getPosLabel(), spots.at(i)->getPosition());                                       /* create blanks to change the position of spots,labels are "spotname+index+pos", array are from the classes, was storing the  position of spot */
				ImGui::Text("      Red                 Green               Blue");                                                    /* some hardcoded text to make the context in window look neat */
				ImGui::InputFloat3(spots.at(i)->getColorLabel(), spots.at(i)->getColor());                                        /* create blanks to change the color of spots,labels are "spotname+index+color", array are from the classes, was storing the color of spot */
				ImGui::Text("========================================================");                                              /* some hardcoded text to make the context in window look neat */
				ImGui::Text("========================================================");
			}


			if (ImGui::Button("Add Sphere"))                                                                                            /* button for add another sphere, the code in brackets only runs (once) when the imgui button is pressed */
			{
				++buttonAddedSphereCount;                                                                                               /* add 1 to the integer counting numbers of spheres added through button,use this as the index */
				string indexNumber = to_string(buttonAddedSphereCount);                                                               /* cast the integer to string */
				sphereLabelGeneral += indexNumber;                                                                                      /* add the string and the hardcoded string"addsphere", make it addsphere+index */
				drawSphere *s = new drawSphere(.8f, .1f, .1f, 0, 0, -20, 1, 0, sphereLabelGeneral);                                   /* create new shape with these default values */
				spheres.push_back(s);                                                                                                 /* push the shape to the vector */
				sphereLabelGeneral = "addsphere";                                                                                       /* change the string with index back to the original string */
			}
			ImGui::SameLine();                                                                                                              /* make the next button to stay on same line */
			if (ImGui::Button("Add Cube"))                                                                                              /* button for add another cube, the code in brackets only runs (once) when the imgui button is pressed */
			{
				++buttonAddedCubeCount;                                                                                                 /* add 1 to the integer counting numbers of cubes added through button,use this as the index */
				string indexNumber = to_string(buttonAddedCubeCount);                                                                 /* cast the integer to string */
				cubeLabelGeneral += indexNumber;                                                                                        /* add the string and the hardcoded string"addcube", make it addcube+index */
				drawCube *s = new drawCube(.8f, .1f, .1f, 0, 0, -20, 1, 0, cubeLabelGeneral);                                         /* create new shape with these default values */
				cubes.push_back(s);                                                                                                   /* push the shape to the vector */
				cubeLabelGeneral = "addcube";                                                                                           /* change the string with index back to the original string */
			}
			ImGui::SameLine();
			if (ImGui::Button("Add Lines"))
			{
				++buttonAddedLineCount;                                                                                                 /* add 1 to the integer counting numbers of lines added through button,use this as the index */
				string indexNumber = to_string(buttonAddedLineCount);                                                                 /* cast the integer to string */
				lineLabelGeneral += indexNumber;                                                                                        /* add the string and the hardcoded string"addline", make it addline+index */
				drawLine *s = new drawLine(.8f, 0, 0, 0, 1, -10, 10, 0, -10, 5.5, lineLabelGeneral);                                  /* create new shape with these default values */
				lines.push_back(s);                                                                                                   /* push the shape to the vector */
				lineLabelGeneral = "addline";                                                                                           /* change the string with index back to the original string */
			}
			ImGui::SameLine();
			if (ImGui::Button("Add Spot"))
			{
				++buttonAddedSpotCount;                                                                                                 /* add 1 to the integer counting numbers of spots added through button,use this as the index */
				string indexNumber = to_string(buttonAddedSpotCount);                                                                 /* cast the integer to string */
				spotLabelGeneral += indexNumber;                                                                                        /* add the string and the hardcoded string"addspot", make it addspot+index */
				drawSpot *s = new drawSpot(.8f, .1f, .1f, -3, -1, -15, spotLabelGeneral);                                             /* create new shape with these default values */
				spots.push_back(s);                                                                                                   /* push the shape to the vector */
				spotLabelGeneral = "addspot";                                                                                           /* change the string with index back to the original string */
			}
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);    /* frame rate of window, this line is still original from bitxues git, didnt delete this */


			ImGui::End();                                                                                                                   /* end of this window, another window can begin from here */

			ImGui::Begin("Quest Manager window", &show_qgui);
			qm.QuestGUI();
			qm.AddTask();
			ImGui::End();
		}
	}


	ImGui::Render();
}


void Window::storeVariables()
{
	startPosX = modelPosition[0]; /* store variables(currently only model position and rotation), this function is used when recording just starts */
	startPosZ = modelPosition[2];
	startRotation = modelRotation;
}


void Window::playbackInit()
{
	modelPosition[0] = startPosX; /* store variables back, this function is used when playback just starts */
	modelPosition[2] = startPosZ;
	modelRotation = startRotation;
}


void Window::handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: /* Escape key */
		cleanUp();
		exit(0);
	}
}


GLuint Window::loadTexture(Image *image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return(textureId);
}


void Window::initRendering()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);


	ImGui_ImplGLUT_Init();
	/* Load the model */

	_model = MD2Model::load("tallguy.md2");
	if (_model != NULL)
	{
		_model->setAnimation("run");

		xminxx = getxminx();

		xmaxxx = getxmaxx();
		yminyy = getyminy();
		ymaxyy = getymaxy();
		zminzz = getzminz();
		zmaxzz = getzmaxz();
	}

	/*
	* Renders the floor(a sample grass image with certain values for width)
	* Draw_Floor();
	*/
}


void Window::handleResize(int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(20, (GLdouble)x / (GLdouble)y, .5f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
}


void Window::initShapes()
{
	/* pre made shapes, these shapes are in green, create these shapes and push them to the vectors */
	cb = new drawCube(0, .8f, 0, 0, 0, -20, 1, p3, "cube1");
	cubes.push_back(cb);
	a = new drawSphere(.1f, .8f, .1f, 1.5f, 0, -10, .5f, p, "sphere1");
	spheres.push_back(a);
	a1 = new drawSphere(.1f, .8f, .1f, -1.5, 0, -10, .5f, p2, "sphere2");
	spheres.push_back(a1);
	ln = new drawLine(.8f, .8f, .1f, 0, 0, -10, 5, 0, -10, 5.5, "line1");
	lines.push_back(ln);
	spt = new drawSpot(.8f, .8f, .1f, -2, 1, -15, "spot1");
	spots.push_back(spt);
}


void Window::debugDraw()
{
	for (size_t i = 0; i < spheres.size(); i++)
	{
		spheres.at(i)->draw();
	}                                                              /* loop through the vectors and draw all the shapes */
	for (size_t i = 0; i < cubes.size(); i++)
	{
		cubes.at(i)->draw();
	}
	for (size_t i = 0; i < lines.size(); i++)
	{
		lines.at(i)->draw();
	}
	for (size_t i = 0; i < spots.size(); i++)
	{
		spots.at(i)->draw();
	}
}


void Window::drawScene()
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	ImGuiIO &io = ImGui::GetIO();


	/* Draw the guy */
	if (_model != NULL)
	{
		/* model transforms */


		glPushMatrix();
		glTranslatef(modelPosition[0], modelPosition[1], modelPosition[2]); /* model translation from origin point(0,0,0 in this case, so basically its the position) */
		glScalef(0.5f, 0.5f, 0.5f);
		glRotatef(-90.0f, 0.0f, 0, 1.0f);
		glRotatef(modelRotation, 1.0f, 0.0, 0.0f);
		glClearColor(0, 0, 0, 0);
		_model->draw();

		glPopMatrix();
	}

	if (debugFlag > 0)
	{
		debugDraw();
		drawGui();
	}
	glutSwapBuffers();
}

vector4 Window::returnModelData()
{
	vector4 modelData;
	modelData.x = startPosX;
	modelData.z = startPosZ;
	modelData.rot = startRotation;
	return modelData;

}

void Window::writeModelData(vector4 modData)
{
	startPosX=modData.x;
	startPosZ = modData.z;
	startRotation = modData.rot;
}


void Window::Draw_Floor()
{
	glTranslatef(0.0f, -5.4f, 0.0f); /* starting point of drawing */
									 /* binding the texture for loading */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* drawing the plane between the glbegin and glend */
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


void Window::update()
{
	if (GetAsyncKeyState(dbgdkey) & 0x8000 && debugKeyRelease > 0)
	{
		/* key f7 as the key to toggle debug draw on/off */
		debugFlag = -debugFlag;                                           /* change the debug Flag to opposite */
		debugKeyRelease = -1;                                                   /* set the Flag for f7 release to -1 until release so no repeating */
	}
	else if (GetAsyncKeyState(dbgdkey) == 0)
	{
		debugKeyRelease = 1;                                                    /*  */
	}
	/* Advance the animation */
	if (_model != NULL)
	{
		if (GetAsyncKeyState(aKey) || stateOfModelMovement == 3)            /* if keys(wasd) pressed, or received keypressed message from server, change following rotation and position */
		{
			_model->advance(.015f);                                       /* for playing for animation, controls time value in md2model(controls the play of animation...i didn't look in to how is it done originally was .025f, slowed it for a bit) */
			modelPosition[0] -= 0.1f;                                /* move position(to left by 0.1f) */
			xminxx -= 0.1f;
			xmaxxx -= 0.1f;
			modelRotation = 90.0f;                                /* x rotation value */
		}
		else if (GetAsyncKeyState(dKey) || stateOfModelMovement == 4)      /* right */
		{
			_model->advance(.015f);
			modelPosition[0] += 0.1f;
			xminxx += 0.1f;
			xmaxxx += 0.1f;
			modelRotation = -90.0f;
		}
		else if (GetAsyncKeyState(wKey) || stateOfModelMovement == 2)      /* s, backwards */
		{
			_model->advance(.015f);
			modelPosition[2] += 0.1f;
			zminzz += 0.1f;
			zmaxzz += 0.1f;
			modelRotation = 0.0f;
		}
		else if (GetAsyncKeyState(sKey) || stateOfModelMovement == 1)      /* w, forward */
		{
			_model->advance(.015f);
			modelPosition[2] -= 0.1f;
			zminzz -= 0.1f;
			zmaxzz -= 0.1f;
			modelRotation = 180.0f;
		}
		else {
			_model->setfm();
		}
	}


	p += .5f;         /* rotation value change for sphere on left */
	p2 -= 0.8f;        /* rotation value change for sphere on right */
	p3 += .8f;         /* rotation value change for cube */


	glutPostRedisplay();
}


void Window::Create_Window(int argv, char** argc)
{
	initShapes();
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
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


float getxminxx()
{
	return(xminxx);
}


float getxmaxxx()
{
	return(xmaxxx);
}


float getyminyy()
{
	return(yminyy);
}


float getymaxyy()
{
	return(ymaxyy);
}


float getzminzz()
{
	return(zminzz);
}


float getzmaxzz()
{
	return(zmaxzz);
}


