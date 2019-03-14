#ifndef BOWLINGHELP_H
#define BOWLINGHELP_H

#include <string.h>
#include <queue>
#include <iostream>
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
void process_Score(frame*game, int round);
void printScore(frame*game, int round);
int BowlingAsciiToInt(int ascii);


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
	//Add our throws into a queue FIFO
	int inputSize = strlen(user);
	for (int charIndex = 0; charIndex < inputSize; charIndex++) {
		int asciiValue = user[charIndex];
		if (asciiValue >= 47 && asciiValue <= 57) {
			balls.push(asciiValue);
		}
		else if (asciiValue == 88) {
			balls.push(asciiValue);
		}
	}

	//round 10 and 3 attempts
	if (round == 10 && balls.size() ==3 ) {
		int ballsize = balls.size();
		game[roundIndex].ballOne = balls.front();
		if (balls.front() == 88) {
			game[roundIndex].strike = true;
		}
		balls.pop();
		game[roundIndex].ballTwo = balls.front();
		if (balls.front() == 47) {
			game[roundIndex].spare = true;
		}
		balls.pop();
		if(ballsize == 3)
			game[roundIndex].ballThree = balls.front();
		balls.pop();
	}
	// normal 2 attempt frames
	else if(balls.size() == 2) {
		game[roundIndex].ballOne = balls.front();
		balls.pop();
		game[roundIndex].ballTwo = balls.front();
		if (balls.front() == 47) {
			game[roundIndex].spare = true;
		}
		balls.pop();
	}
	//strikes 
	else {
		game[roundIndex].ballOne = balls.front();
		balls.pop();
		game[roundIndex].strike = true;
	}
}
/*
Function: process_Score
Job: Iterates through played frames and checks for spares/strikes and updates scores accordingly
Parameters: frame struct array and round count
Returns: Void/None
*/
void process_Score(frame*game, int round) {

	for (int x = 0; x < round; x++) {
		//round 10 requires some extra manipulation for third attempt and checks
		if (x+1 == 10 && game[x].strike) {
			int score = 0;
			//first ball strike
			if (game[x].strike) {
				score = 10;
				score += BowlingAsciiToInt(game[x].ballTwo);
				if (game[x].ballThree == 47) {
					score += BowlingAsciiToInt(game[x].ballThree) - BowlingAsciiToInt(game[x].ballTwo);
				}
				else
					score += BowlingAsciiToInt(game[x].ballThree);
				game[x].score = score;
				game[x].strike = false;
			}
			// open frame or spare
			else {
				score += BowlingAsciiToInt(game[x].ballOne);
				if (game[x].ballTwo == 47) {
					score = 10;
					score += BowlingAsciiToInt(game[x].ballThree);
				}
				else
					score += BowlingAsciiToInt(game[x].ballTwo);

				game[x].score = score;
			}
		}
		//strike
		else if (game[x].strike) { //&& x+1 != round) {
			int strikeScore = 10;
			//2 strike frames
			if (game[x + 1].strike && game[x + 2].strike) {
				game[x].score = 30;
				game[x].strike = false;
			}
			//round 9 2 strike frames
			else if (x == 8 && round == 10) {
				strikeScore += BowlingAsciiToInt(game[x + 1].ballOne);
				strikeScore += BowlingAsciiToInt(game[x + 1].ballTwo);
				game[x].score = strikeScore;
				game[x].strike = false;
			}
			//spare frame
			else if (x + 1 < round && game[x + 1].spare) {
				strikeScore += BowlingAsciiToInt(game[x + 1].ballOne);
				strikeScore += BowlingAsciiToInt(game[x + 1].ballTwo) - BowlingAsciiToInt(game[x + 1].ballOne); //registered as spare but needs to be adjusted for what was actually thrown for scoring i.e. 7,/ = ball 1 7 , ball 2 3
				game[x].score = strikeScore;
				game[x].strike = false;
			}
			// 1 strike + open frame following
			else if (game[x + 1].strike && game[x + 2].score != -1) {
				strikeScore += BowlingAsciiToInt(game[x + 1].ballOne);
				strikeScore += BowlingAsciiToInt(game[x + 2].ballOne);
				game[x].score = strikeScore;
				game[x].strike = false;
			}
			else if (game[x+1].score != -1){
				strikeScore += BowlingAsciiToInt(game[x + 1].ballOne);
				strikeScore += BowlingAsciiToInt(game[x + 1].ballTwo);
				game[x].score = strikeScore;
				game[x].strike = false;
			}

		}
		//spare
		else if (game[x].spare && x + 1 < round) {
			int spareScore = 10;
			spareScore += BowlingAsciiToInt(game[x + 1].ballOne);
			game[x].score = spareScore;
			game[x].strike = false;
		}
		// all else
		else if( game[x].ballOne != 88 && game[x].ballTwo != 47) {
			int frameScore = 0;
			frameScore += BowlingAsciiToInt(game[x].ballOne);
			frameScore += BowlingAsciiToInt(game[x].ballTwo);
			game[x].score = frameScore;

		}
	}
}

/*
Function: PrintScore
Job: Prints the score of the bowling game after each frame as needed
Parameters: game frame structure and round number
Returns: Nothing/Void except screen printout
*/
void printScore(frame*game, int round) {
	process_Score(game, round);
	int scoreSum = 0;
	for (int x = 0; x < round; x++) {
		if (x + 1 == round)
			cout << "Recent ";
		cout << "Frame " << (x + 1) << " : ";
		if (game[x].score != -1) {
			scoreSum += game[x].score;
			cout << scoreSum;
		}
		cout << endl;
	}
	cout << endl << endl;
}
/*
Function: BowlingAsciiToInt
Job: Convert ascii integer decimal values to 0-9 values or 10
Parameters: Ascii Decimal Value
Returns: Int
*/
int BowlingAsciiToInt(int ascii) {
	if (ascii == 47 || ascii == 88)
		return 10;
	else
		return ascii - 48;
}
#endif