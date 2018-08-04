/*
 * CS362-400
 * Random Test Adventurer
 * randomtestadventurer.c
 * 8/5/2018
 * References:
 */
 
 #include "dominion.h"
 #include "rngs.h"
 #include <stdlib.h>
 #include <time.h>
 #include <math.h>
 
 // Variable to keep count of test fails
int failCnt = 0;

 
 
 /*
 * To avoid making it hard to collect coverage when a test fails, 
 * using my own asserttrue function instead of the standard C assert 
 * (which basically crashes the code and fails to collect coverage). 
 * My assert also prints whether the test passes or fails.  If the test   
 * fails the fail counter int variable will increment by 1.
 */
 void assertTrue(int int1, int int2) 
 {
	if (int1 == int2) 
	{
		printf("Test Passed\n");
	} 
	else
	{
		printf("Test Failed\n");
		failCnt++;
	}
 }
 
 void testCard()
 {
	 
 }
 
 
 int main()
 {
	srand(time(0));
	struct gameState gState;
	int MAX_TESTS = 1000;
	int treasures[] = {copper, silver, gold};
	int numTreasures, i, j, playerNum;
	
	
	// randomly select player position number
	playerNum = rand() % (MAX_PLAYERS + 1 - 1) + 1;
	
	//debug
	printf("playerNum = %d\n", playerNum);
	
	
	printf("RANDOM ADVENTURER CARD TEST\n");
	
	
	
	
	 
	return 0;
 }