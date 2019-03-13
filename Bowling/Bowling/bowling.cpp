/*Chido Nguyen
Bowling Score App
*/
#include <iostream>
#include "bowlinghelp.h"
#include "testbowling.h"

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

	cout << "Press enter to exit." << endl;
	cin.ignore();
}
