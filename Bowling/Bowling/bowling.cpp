/*Chido Nguyen
Bowling Score App
*/
#include <iostream>
#include "bowlinghelp.h"
#include "testbowling.h"
#include <math.h>
#include <limits.h>



using std::cin;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
	// Test Section //
	//testInput();
	//testScore();
	//testPrint();
	////////////////////

	 //Game Flow //
	cout << "10-pin bowling scoring application." << endl;
	cout << "Enter scores for each frame X for strike , / for spare, 0-9 with commas in between. i.e. '7,/' or 'X'" << endl;
	//char array to store user inputs + memset to clear out the array//
	char scoreInput[128];
	memset(scoreInput, '\0', 128);
	int roundCount = 1;
	frame* gameFrames = new frame[10];
	while (roundCount <= 10) {
		cout << "Enter Score:" << endl;
		cin >> scoreInput;

		processInput(scoreInput, gameFrames, roundCount);
		process_Score(gameFrames, roundCount);
		printScore(gameFrames, roundCount);
		roundCount++;
	}

	///////////////////////////////////*/
	//https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
	
	cout << "Press enter to close." << endl;
	cin.ignore(INT_MAX, '\n');
	cin.get();
	delete gameFrames;
	return 0;
}
