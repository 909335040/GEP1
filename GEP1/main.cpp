# include "window.h"
 
#include <vector>
#include <thread>
#include<iostream>
using namespace std;
int starttime;//stores the time that recording keyboard events starts
int recordflag = 2;
int startkey = 0x70;// virtual key code of f1
int playkey = 0x71;//  virtual key code for f2

vector<int> event; // list for recording the event(what key)
vector<int>timea;  // list for recording the time(when is the key event happened)
vector<bool> eq;   //list for recording what is the event(key down or key up)
bool keydownflags[256];// key down flag, each spot for a key(the first 6 are for mouses,  which i have not and not planning to do...the 7th is undifined, 8-255 is for key board)
bool releaseflag = false;//release flag for the recording key(f1),to prevent it to get in the recording
bool donereleaseflag = false;// another release flag still for f1, to prevent it from repeating over and over again(record stop record stop record stop while pressing the key)
Window window; 

void record(int kfrcd) {   //the parameter is the keycode of the key for recording(supposed to be DWORD but i tested that int works fine without warnings while float doesn't,so int it is),for now its just hardcoded to 0x70 which is f1

	if (event.size() <= 0 && releaseflag == false) {// if the f1 key havent been released its not recording

		if (GetAsyncKeyState(kfrcd) == 0) {

			releaseflag = true;//change the release flag to true so can go to the else part
			starttime = GetTickCount(); //save the start time of recording(which is when the key is released)
			window.storeVariables();//store model initial states
			cout << "released";
			
		}

	}
	else {

		if (GetAsyncKeyState(kfrcd) & 0x8000) {
			releaseflag = false;// if the f1 keys pressed again, stop recording
			for (int i = 8; i < 255; i++) { keydownflags[i] = false; } //reset the keydown flags
			recordflag = 0;//change recording flag to 0(ready to playback or record again)
			cout << "stopped recording";
			return;
		}




		for (int i = 8; i < 255; i++) { // 8-255 are keys on keyboard  , didnt use virtual keycodes like 0x30 here simply because i dont have any ideas of how to put that in a loop, but the parameter of 
			//getasynckeystate accepting is an int anyways
			if (GetAsyncKeyState(i) & 0x8000) {// if get the key pressed 
				if (!keydownflags[i] && i != kfrcd) {//if the key wasn't pressed already from previous, and the key isn't f1
					cout << "getkey" << "  " << i << endl << endl;//print the key got
					event.push_back(i);//push the virtual keycode to the list
					timea.push_back(GetTickCount() - starttime);//push the time(has past)since the start of recording to the time list
					eq.push_back(true);// push true to the flags list, which means that this is a key pressed instead of released
					keydownflags[i] = 1;//change the flag to 1 which means this key is pressed now so wont push all the stuff to lists over and over again
				}




			}

			if (GetAsyncKeyState(i) == 0 && i != kfrcd) { //if the key is not pressed and its not f1

				if (keydownflags[i] == 1) {//if the key is pressed(previously)
					cout << "key released" << "  " << i << endl << endl; 

					event.push_back(i);//push the key to list again
					timea.push_back(GetTickCount() - starttime); // push the time (has past since start of recording) to the time list
					eq.push_back(false);// push false to flags list which means this is a key released instead of pressed
					keydownflags[i] = 0; // change the flag to 0 which means this key is now released instead of being pressed



				}




			}



		}






	}





}


void playa() {//playback 

	if (event.size() > 0) { // if any key have been pressed during record, playback
		cout << timea.at(0);
		window.playbackInit();// bring the model back to initial state when start recording
		for (int i = 0; i < event.size(); i++) { //before the last key is pressed
			if (i == 0)
			{// for the first key , sleep for the exact time(pushed in to list.) before simulate the press , sleep is like holding the keys state(if the key is pressed by that time, it'll hold the key until release is called)
				Sleep(timea.at(0));
			}
			else { Sleep(timea.at(i) - timea.at(i - 1)); }//for keys after the first key, sleep for time-previous time
			if (eq.at(i) == true) {//if the matched flags list states that this event is the keys being pressed, simulate it by using keybd_event
				keybd_event(event.at(i),
					event.at(i),
					KEYEVENTF_EXTENDEDKEY | 0,
					0);

			}
			else if (eq.at(i) == false) {// if opposite, simulate keyboard release


				keybd_event(event.at(i),
					event.at(i),
					KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
					0);


			}

			// theres this thing that the keyboard events(from keyboard,not from program) are not disabled while playback is happening, so if you pressed /released the same key included in playback, it'd messup
			// these keyboard events should be replaced in to functions when implementing games


			//this part exits when all events has been gone through
		}


	}
	else { return; }// if theres no keyboard event while recording , simply return, no playback

	for (int i = 8; i < 255; i++) {// after playback has done if there are still any keys not released, release them
		if (GetAsyncKeyState(i) & 0x8000) {
			keybd_event(event.at(i),
				event.at(i),
				KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
				0);
		}
	}
	cout << "daozhele";
	recordflag = 0;// change the record flag to 0 , so its ready to 
}



void check() { // do different things based on value of recordflag, pretty much the "game loop" for the keyboard recording

	while (recordflag == 2) {// while record flag is 2 , which means there haven't been any recording done before. so playback is not available. can only record

		if (GetAsyncKeyState(startkey) & 0x8000) {//if f1 pressed, change record flag to 1

			recordflag = 1;
		 
			cout << "changed flag to 1 " << endl;
		}


	}

	while (recordflag == 1) {
		//record passed the hardcoded f1 in.....
		record(startkey);
	}
	while (recordflag == 0) {//while the record flag is 0 which meant is ready for playback or recording again

		if (GetAsyncKeyState(playkey) & 0x8000) { //if f2(hardcoded as well) is pressed, change it to someother value(5 is just some random value i picked...) so can only go through the playback, not playing, not recording again until playback has end
			recordflag = 5;
			cout << "changed flag to 5 " << endl;
			playa();//playback

		}
		if (GetAsyncKeyState(startkey) & 0x8000) {//if f1 is pressed while recordflag is 0, which meant the user wants to record again

			if (donereleaseflag == true) {// done release flag is true(after the release of f1(after pressing it....))
				recordflag = 1;//change the record flag, clear the data in 3 vectors
				 
				event.clear();
				timea.clear();
				eq.clear();
				donereleaseflag = false;  // reset the flag to false
				cout << "data cleared and recording again" << endl;
			}
		}
		else if (GetAsyncKeyState(startkey) <= 0) {

			donereleaseflag = true;//after the key is pressed, when the key is released, set the release flag to true

		}


	}

}

void gancheck() {

	while (1) {

		check(); //in while loop to go through over and over again

	}

}

int main(int argc, char** argv) {
	thread t(gancheck); // in thread so not contradicting with the game loop of opengl

	window.Create_Window(argc,argv); 


	return 0;
}









