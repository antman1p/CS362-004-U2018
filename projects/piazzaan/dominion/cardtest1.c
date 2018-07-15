/*
 * -----------------------------------------------------------------------
 * cardtest1.c
 * CS 362_400
 * Antonio Piazza
 * piazzaan
 * 7/15/2108
 * 
 * Card test 1 for Dominion Smithy card
 * 
 * Include the following lines in your makefile:
 *
 * echo "cardtest1.c:" >> unittestresults.out
 * gcc -o cardtest1 -g  cardtest1.c dominion.c rngs.c $(CFLAGS)
 * ./cardtest1 >> unittestresults.out
 * gcov cardtest1.c
 *
 * references: 
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include <stdio.h>
#include "dominion_helpers.h"
#include "rngs.h"


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
 
 
 // Main function
 int main()
 {
	int numPlayer = 2;
	int player1 = 0, player2 = 0, handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
		
	// Initialize two game states
	struct gameState gState, copyGState;


 
	printf ("\n---------------------------------------------------\nTESTING SMITHY CARD:\n---------------------------------------------------");
	
	// Set Game State
	memset(&gState,23,sizeof(struct gameState));
	memset(&copyGState,23,sizeof(struct gameState));
	
	// Initialize game
	initializeGame(numbPlayers, k, seed, &gState);
	
	// copy the game state to the copy to preserve the game state
	 memcpy(&scopyGState, &gState, sizeof(struct gameState));
	 
	// call car effect function for Smithy
	cardEffect(smithy, choice1, choice2, choice3, &state, handpos, &bonus);
	
	
	// Check Results
	// Requiment:  Current player should receive exactly 3 cards
	printf("\nPlayer 1 receives exactly 3 cards\n");
	printf("Expected: %d\n", copyGState.handCount[player0]+2);
	printf("Result: %d\n", gState.handCount[player0]);
    assertTrue(state.deckCount[player0],stateOriginal.deckCount[player0]+2);
	
	
 
	/* 
	 * Print “TEST SUCCESSFULLY COMPLETED” If and only if the entire test  
	 * passes, and usually (this isn’t always possible for crashing bugs) print 
	 * "TEST FAILED” for a failure. This makes it easy to  process failing and passing tests. 
	 */
	if (failCnt)  // If the counter is greater than 0 print fail message
	{
		printf("\n---------------------------------------------------\nTEST FAILED\n---------------------------------------------------\n\n");
	}
	else          // Else all tests pass, print pass message
	{
		printf("\n---------------------------------------------------\nTEST SUCCESSFULLY COMPLETED\n---------------------------------------------------\n\n");
	}
	  
	return 0;
}
  
