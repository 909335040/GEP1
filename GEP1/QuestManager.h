#pragma once

# include "GL2\glew.h"
# include "GL\freeglut.h"
# include "imgui.h"
# include "imgui_impl_glut.h"

# include <stdio.h>
# include <string.h>
# include <iostream>
# include <fstream>
# include <stdlib.h>

using namespace std;
 static int choice_tab = 1;
 static int choice_key ;
 static bool z,j;
 //for the purpose of passing it to the engine through user input.
static  char key_press[100];

//for the purpose of passing it to the code.
static char ke , lv;
static bool key_pressed;
static bool startQuest;
static char level_count[5];

 static bool taskadd = false;

 // file details
static  FILE *qc , *ql;
 static int ch;
 static char input[10000];
 static ofstream compfile;
 static bool compdocd = true;

 //Level quest variables
 static int level = 1;
 static int level_to_reach;

 //Quest completed count (for xp)
 static bool levelquestcompleted;
 static bool questcompleted;
 static int questcount = 0;
 static int experience = 0;

class QuestManager {

private:
	


public:

	
	static void AddKeyQuestLine(char);				//gui display for the quest to be completed
	static void AddKeyQuestCompletedLine(char);		//gui display for quest completed 
	static void QuestsManager();
	static void QuestGUI();
	static void AddTask();				//contains the add task code
	static void LevelLogic();			//contains the level up code and logic
	
	
	static void keyboardCallback(unsigned char key, int x, int y);
	 static bool KeyBoardFunction(unsigned char key,int x,int y);
};