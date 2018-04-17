# include "QuestManager.h"


bool QuestManager::KeyBoardFunction(unsigned char key, int x, int y) {

	ImGuiIO& io = ImGui::GetIO();


	io.AddInputCharacter(key);

	if (key == 'z') {
		
		//cout << "Z is pressed";
		z = true;
	}

	if (key == 'j') {

		j = true;
	}
	if (key == ke) {

		key_pressed = true;
	}

	return true;
}
void QuestManager::keyboardCallback(unsigned char key, int x, int y)
{
	if (KeyBoardFunction(key, x, y))
	{
		glutPostRedisplay();
	}
}
void QuestManager::QuestsManager() {

	

	
	
}

void QuestManager::AddTask() {

	//adding of tasks

	if (taskadd == true) {

		ImGui::Begin("Add a Task");
		ImGui::SetWindowSize(ImVec2(400, 400));
		ImGui::Text("This is task window");
		ImGui::Combo("Type of Quest", &choice_key, "None\0Kill\0Reach\0Level Up\0Key Pressed");

		//choice key = 3 selects the 3rd option from the type of quest.(Level up)
		if (choice_key == 3) {
			key_pressed = false;

			ImGui::Text("Level up selected");
			ImGui::InputText("Level",level_count,10);

			lv = level_count[0];
			//conert char to int value;
			lv = (int)lv - (int)48;
		
		}
		
		//choice key = 4 selects the 4th option from the type of quest.(Key pressed)
		if (choice_key == 4) {
			key_pressed = false;
		ImGui::InputText("Key To Press",key_press,10);


		ke = key_press[0];


			
		}
		
		if (ImGui::Button("Add", ImVec2(50, 25))) {

			//add code for key pressed
			if(choice_key == 4){
				key_press[0] = (char)0;
				if (ke) {
					startQuest = true;
				}

				choice_key == 0;
				taskadd = false;
			}

			//add code for level up

			if (choice_key == 3) {
				level_count[0] = (char)0;

				if (lv) {
					startQuest = true;
				}

				choice_key = 0;
				taskadd = false;
			}
			
		}
		if (ImGui::Button("Close", ImVec2(50, 25))) {
			taskadd = false;
		}
		
		ImGui::End();
		
	}
}

void QuestManager::AddKeyQuestLine(char a) {

	ImGui::Text("Quest: Press Button %c", a);
}

void QuestManager::AddKeyQuestCompletedLine(char a) {
	
	ImGui::Text("Quest is completed. Button %c is pressed.", a);
}

void QuestManager::LevelLogic() {

	//level up logic
	//each quest completed will earn 25 exp
	//100 experience will earn one level up. . i.e 4 quests need to be completed.

	printf("\nExperience: %d", experience);
	if (questcompleted && (!levelquestcompleted)) {

		questcount = questcount + 1;

		experience = experience + 25;

		if (experience == 100) {
			
			level = level + 1;
			printf("\nLevel : %d", level);
			experience = 0;
		}

		if (level == level_to_reach) {
			//questcompleted = true;
			levelquestcompleted = true;
			printf("\nLevel to reached:%d , \t Player has reached level: %d", level_to_reach, level);
		}
		questcompleted = false;
	}

}
void QuestManager::QuestGUI() {

	// creation of gui of quest manager
	//level up
	
	// three types of quests: Kill 1. Reach a point 2. Interact with something 3. Level up(chain of many quests)
	//Line 1
	ImGui::SetWindowSize(ImVec2(600, 600));
	ImGui::Button("Quests", ImVec2(100, 25));
	//Line 2
	if (ImGui::Button("In Progress", ImVec2(100, 25))) {
		choice_tab = 1;
	}
	ImGui::SameLine();
	if (ImGui::Button("Completed", ImVec2(100, 25))) {
		choice_tab = 2;
	}
	ImGui::SameLine();

	//button 3 to add task
	if (ImGui::Button("Add Quest", ImVec2(100, 25))) {
		
		taskadd = true;
		
	}
	ImGui::SameLine();
	//Quests COmpleted log
	if (ImGui::Button("Quest Log", ImVec2(100, 25))) {
		choice_tab = 4;
		

	}



	switch (choice_tab) {
	case 1:
		

		if (startQuest&&(!key_pressed)&&(!lv)) {

			AddKeyQuestLine(ke);
		}

		if (startQuest && lv) {
			//for now just print the number
			startQuest = true;
			level_to_reach = (int)lv;
			ImGui::Text("Level to reach: %d", level_to_reach);
		}

		if (ke) {
			if (key_pressed) {


				if (compdocd) {

					qc = fopen("QuestCompleted.txt", "a+");


					fprintf(qc, "Quest Completed.Button %c is pressed\n", ke);



					fclose(qc);
				}
			
				compdocd = false;

			}


		}

		if (levelquestcompleted) {

			ql = fopen("QuestCompleted.txt", "a+");
			fprintf(ql, "Quest completed.Player has reached level %d", level);
			levelquestcompleted = false;
		}
	
		
		break;
	case 2:
		
		if (ke) {
			if (key_pressed) {

				//quest has been completed.

				AddKeyQuestCompletedLine(ke);
				
				if(lv){

					questcompleted = true;
					LevelLogic();
				}
				
				

				if (compdocd) {

					qc = fopen("QuestCompleted.txt", "a+");


					fprintf(qc, "Quest Completed.Button %c is pressed\n", ke);

				

					fclose(qc);
					compdocd = false;
				}

				key_pressed = false;
				
			}
			//key_pressed = false;
		
		}
		
		if (levelquestcompleted) {

			ql = fopen("QuestCompleted.txt", "a+");
			fprintf(ql, "Quest completed.Player has reached level %d", level);
			levelquestcompleted = false;
			
		}
		break;

	case 4:

		//prints all the completed quests till now
		ql = fopen("QuestCompleted.txt", "r");
		//fgets(input, 100, ql);
		while (fgets(input, 10000, ql)) {
			//printf("%s", input);
			ImGui::Text(input);
		}

		//printf("\n\nEnd of file");
		fclose(ql);

		break;
	}

	

	
	glutKeyboardFunc(keyboardCallback);
}