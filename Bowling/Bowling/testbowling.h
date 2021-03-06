#ifndef TESTBOWLING_H
#define TESTBOWLING_H
#include <iostream>
#include "bowlinghelp.h"

using std::cout;
using std::cin;
using std::endl;

/*
testInput: testing(processInput)
-Testing to see if throws are added appropriately to our frame structure of ballone and balltwo
-Testing to see if our frames register and stores where strikes and spares are achieved
-Testing frame 10 input to see if third attempts are documented correctly
*/
void testInput() {
	int roundCount = 1;
	frame* gameFrames = new frame[10];


	char score1[3] = { '0','/', '\0' };
	char score2[2] = { 'X', '\0' };
	char score3[3] = { '1','8', '\0' };
	char score4[3] = { '2','7', '\0' };
	char score5[3] = { '3','5' , '\0' };
	char score6[3] = { '4','3', '\0' };
	char score7[3] = { '5','1', '\0' };
	char score8[3] = { '6','3', '\0' };
	char score9[3] = { '7','0', '\0' };
	char score10[3] = { '8','1', '\0' };
	char score11[3] = { '9','/', '\0' };
	char score12[4] = { '9','/', '1', '\0' };
	char score13[4] = { 'X','8', '1', '\0' };
	char score14[4] = { 'X','X', 'X', '\0' };
	char *arrayScore[14] = {score1, score2,score3,score4,score5,score6,score7,score8,score9,score10,score11, score12, score13, score14 };

	//Test Case 1 all valid inputs//
	int testcase1_pass = 0;
	int testcase1_fail = 0;
	for (int x = 0; x < 11; x++) {

		char * arr = arrayScore[x];
		processInput(arr, gameFrames, roundCount);

		int first = arrayScore[x][0];
		int second = arrayScore[x][1];
		if (first == gameFrames[roundCount - 1].ballOne && first == 88)
			testcase1_pass++;
		else if (first == gameFrames[roundCount - 1].ballOne && second == gameFrames[roundCount - 1].ballTwo)
			testcase1_pass++;
		else
			testcase1_fail++;
			
	}
	cout << "Test Case 1: Inputting valid inputs" << endl;
	cout << testcase1_pass << " of 11 tests PASSED." << endl << endl;

	////////////////////////////////////////////////////////
	delete gameFrames;
	gameFrames = new frame[10];

	//Test Case 2: checking for strike/spares//

	int test2_p = 0;
	for (int x = 0; x < 3; x++) {
		char * arr = arrayScore[x];
		processInput(arr, gameFrames, x+1);
	}
	for (int x = 0; x < 3; x++) {
		if (x == 0 && gameFrames[x].spare == true)
			test2_p++;

		if (x == 1 && gameFrames[x].strike == true)
			test2_p++;

		if (x == 2 && gameFrames[x].spare == false)
			if(gameFrames[x].strike == false)
				test2_p++;

	}
	cout << "Test Case 2: Strike and Spares Registered Properly in frames" << endl;
	cout << test2_p << " of 3 tests PASSED." << endl << endl;

	////////////////////////////////////////////////////////
	delete gameFrames;
	gameFrames = new frame[10];
	///////////////////////////////////////////////////////

	//test case 3: testing for input of frame 10 which has "3" potential attempts;

	int round10 = 10;
	int test3p = 0;
	for (int x = 11; x < 14; x++) {
		char * arr = arrayScore[x];
		processInput(arr, gameFrames, round10);
		int first = arrayScore[x][0];
		int second = arrayScore[x][1];
		int third = arrayScore[x][2];
		if (first == gameFrames[9].ballOne)
			if (second == gameFrames[9].ballTwo)
				if (third == gameFrames[9].ballThree)
					test3p++;
	}
	cout << "Test Case 3: Frame 10 input check for third attempt" << endl;
	cout << test3p << " of 3 tests PASSED." << endl << endl;
	delete gameFrames;

}
/*
testScore: Testing (process_Score)
-Generated own potential game score card
-Used generated score as userInput to fill our gameFrames
-Key test is to document if our process_score calculates each frame score correctly for open frames / strikes and spares.
-Test checks calculated score against expectedFrameScore[]
*/
void testScore() {

	int roundCount = 1;
	frame* gameFrames = new frame[10];


	char score1[3] = { '0','/', '\0' };
	char score2[2] = { 'X', '\0' };
	//
	char score3[3] = { '1','8', '\0' };
	char score4[3] = { '2','7', '\0' };
	char score5[3] = { '3','5' , '\0' };
	char score6[3] = { '4','3', '\0' };
	char score7[3] = { '5','1', '\0' };
	char score8[3] = { '6','3', '\0' };
	char score9[3] = { '7','0', '\0' };
	char score10[3] = { '8','1', '\0' };
	char score11[3] = { '9','/', '\0' };
	char score12[4] = { '9','/', '1', '\0' };
	//
	char score13[4] = { 'X','8', '1', '\0' };
	char score14[4] = { 'X','X', 'X', '\0' };
	char *arrayScore[14] = { score1, score2,score3,score4,score5,score6,score7,score8,score9,score10,score11, score12, score13, score14 };
	//from score3 -> score 12 game test//
	int expectedFrameScore[10] = { 9,9,8,7,6,9,7,9,19,11 };
	/////////
	char * arr;
	int round = 1;
	int testpass = 0;
	for (int x = 2; x < 12; x++) {
		arr = arrayScore[x];
		processInput(arrayScore[x], gameFrames, round);
		process_Score(gameFrames, round);
		round++;
	}
	for (int x = 0; x < 10; x++) {
		int scoreArrayIndex = x + 2;
		arr = arrayScore[scoreArrayIndex];
		int inputSize = strlen(arr);
		if (expectedFrameScore[x] == gameFrames[x].score)
			testpass++;

	}
	cout << "Test Case Frame Scores: Correct Frame Scores are recorded." << endl;
	cout << testpass << " out of 10 frames test PASSED." << endl << endl;
	delete gameFrames;
}
/*
testScore: testing(printScore)
-Testing to see if strikes and spares are ignored properly until the correct frames have been played
-Expected Final Score output 300 perfect game / conditions 2 = 159 / c3 = 84
*/
void testPrint() {
	frame * gameFrames = new frame[10];
	/*char score1[2] = { 'X','\0' };
	char score2[2] = { 'X','\0' };
	char score3[2] = { 'X','\0' };
	char score4[2] = { 'X','\0' };
	char score5[2] = { 'X','\0' };
	char score6[2] = { 'X','\0' };
	char score7[2] = { 'X','\0' };
	char score8[2] = { 'X','\0' };
	char score9[2] = { 'X','\0' };
	char score10[4] = { 'X','X','X','\0' };*/
	
	char score1[3] = { '1','/','\0' };
	char score2[3] = { '1','/','\0' };
	char score3[2] = { 'X','\0' };
	char score4[3] = { '1','3','\0' };
	char score5[2] = { 'X','\0' };
	char score6[3] = { '1','8','\0' };
	char score7[2] = { 'X','\0' };
	char score8[3] = { '1','5','\0' };
	char score9[2] = { 'X','\0' };
	char score10[4] ={ 'X','X','X','\0' };

	/*char score1[3] = { '1','5','\0' };
	char score2[3] = { '1','5','\0' };
	char score3[3] = { '1','5','\0' };
	char score4[3] = { '1','5','\0' };
	char score5[3] = { '1','5','\0' };
	char score6[3] = { '1','5','\0' };
	char score7[3] = { '1','5','\0' };
	char score8[3] = { '1','5','\0' };
	char score9[3] = { '1','5','\0' };
	char score10[4] = { 'X','X','X','\0' };*/
	
	char *arrayScore[14] = { score1, score2,score3,score4,score5,score6,score7,score8,score9,score10 };
	int round = 1;
	int testpass = 0;
	cout << "Test Case: No Scores printed if first three throws are strikes" << endl;
	for (int x = 0; x < 10; x++) {
		processInput(arrayScore[x], gameFrames, round);
		process_Score(gameFrames, round);
		printScore(gameFrames, round);
		round++;
	}

	cout << "Over all correctness and printed info testing" << endl;
	cout << "To edit comment in/out different sets of generated data in the test function." << endl;
	cout << "Expected results are either 300/159/84" << endl;

	delete gameFrames;
}
#endif