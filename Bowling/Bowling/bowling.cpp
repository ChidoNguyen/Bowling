#include <iostream>
#include <string.h>
#include <queue>
#include <assert.h>

using std::cin;
using std::cout;
using std::endl;
using std::queue;

struct frame {
	int ballOne = -1;
	int ballTwo = -1;
	int ballThree = -1;
	int score = -1;
	bool spare = false;
	bool strike = false;
};

void processInput(char user[], frame * game, int round);

int main(int argc, char** argv) {

	cout << "10-pin bowling scoring application." << endl;
	//char array to store user inputs + memset to clear out the array//
	char scoreInput[128];
	memset(scoreInput, '\0', 128);
	int roundCount = 1;
	frame* gameFrames = new frame[10];


	processInput(scoreInput, gameFrames,roundCount);


}

/*
Function:	processInput
Job : Takes the user input and processes the equivalent score for the appropriate frame.
Parameters : Character array storing user input, frame structure and round count
Returns : Void / None
*/
void processInput(char user[], frame * game, int round) {
	int roundIndex = round - 1;
	queue<int> balls;
	//ascii / 0-9 and X 
	//		47, 48-57, 88
	int inputSize = strlen(user);
	for(int charIndex = 0; charIndex <inputSize; charIndex++){
		int asciiValue = user[charIndex];
		if (asciiValue >= 48 && asciiValue <= 57) {
			balls.push(asciiValue);
		}
		else if (asciiValue == 88) {
			balls.push(asciiValue);
		}
	}
	
	if (balls.front() == 88) {
		game[roundIndex].ballOne = balls.front();
		balls.pop();
		game[roundIndex].strike = true;
	}
	else {
		game[roundIndex].ballOne = balls.front();
		balls.pop();
		game[roundIndex].ballTwo = balls.front();
		if (balls.front() == 47) {
			game[roundIndex].spare = true;
		}
		balls.pop();
	}
	
}