/*
 * -----------------------------------------------------------------------
 * cardtest3.c
 * CS 362_400
 * Antonio Piazza
 * piazzaan
 * 7/15/2108
 * 
 * Card test 3 for Dominion Outpost card
 * 
 * Include the following lines in your makefile:
 *
 * echo "cardtest3.c:" >> unittestresults.out
 * gcc -o cardtest3 -g cardtest3.c dominion.c rngs.c $(CFLAGS)
 * ./cardtest3 >> unittestresults.out
 * gcov cardtest3.c
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
	int i, playerTurn, playerTurnAfterEnd;
	int numPlayer = 2;
	int player1 = 0, handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int player2 = 1;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, outpost, great_hall};
		
	// Initialize two game states
	struct gameState gState, copyGState;


 
	printf ("\n---------------------------------------------------\nTESTING Outpost CARD:\n---------------------------------------------------");
	
	// Set Game State
	memset(&gState,23,sizeof(struct gameState));
	memset(&copyGState,23,sizeof(struct gameState));
	
	// Initialize game
	initializeGame(numPlayer, k, seed, &gState);
	
	// copy the game state to the copy to preserve the game state
	 memcpy(&copyGState, &gState, sizeof(struct gameState));
	 
	// call card effect function for Outpost
	cardEffect(outpost, choice1, choice2, choice3, &gState, handpos, &bonus);
	
	
	
	// Check Results
	// Requirement:  Check that outpostPlayed flag is incremented in the gamestate
	printf("\noutpostPlayed flag should increment\n");
	printf("Expected: %d\n", copyGState.outpostPlayed + 1);
	printf("Result: %d\n", gState.outpostPlayed);
	assertTrue(gState.outpostPlayed, copyGState.outpostPlayed + 1);
	
	
	
	
	
	
	// Requirement: No state change should occur for other players.
	printf("\nTest Player 2 was not effected\n");
	// Player 2's hand
	printf("\nPlayer 2 hand uneffected\n");
	printf("Expected: %d\n", copyGState.handCount[player2]);
	printf("Result: %d\n", gState.handCount[player2]);
    assertTrue(gState.handCount[player2],copyGState.handCount[player2]);
	//Player 2's deck
	printf("\nPlayer 2 deck uneffected\n");
	printf("Expected: %d\n", copyGState.deckCount[player2]);
	printf("Result: %d\n", gState.deckCount[player2]);
    assertTrue(gState.deckCount[player2],copyGState.deckCount[player2]);
	
	// Requirement: No state change should occur to the victory card piles and kingdom card piles.
	// Test Victory Piles
	printf("\nTest Victory piles were not effected\n");
	// Test Province Pile
	printf("\nProvince Pile uneffected\n");
	printf("Expected: %d\n", copyGState.supplyCount[province]);
	printf("Result: %d\n", gState.supplyCount[province]);
	assertTrue(gState.supplyCount[province],copyGState.supplyCount[province]);
	// Test Duchy Pile
	printf("\nDuchy Pile uneffected\n");
	printf("Expected: %d\n", copyGState.supplyCount[duchy]);
	printf("Result: %d\n", gState.supplyCount[duchy]);
	assertTrue(gState.supplyCount[duchy],copyGState.supplyCount[duchy]);
	// Test Estate Pile
	printf("\nEstate Pile uneffected\n");
	printf("Expected: %d\n", copyGState.supplyCount[estate]);
	printf("Result: %d\n", gState.supplyCount[estate]);
	assertTrue(gState.supplyCount[estate],copyGState.supplyCount[estate]);
	
	
	// Test Kingdom Cards
	printf("\nTest Kingdom card piles were not effected\n");
	for (i = 0; i < 10; i++) {
        printf("\nchecking card %d pile\n", k[i]);
		printf("Expected: %d\n", copyGState.supplyCount[k[i]]);
		printf("Result: %d\n", gState.supplyCount[k[i]]);
        assertTrue(gState.supplyCount[k[i]],copyGState.supplyCount[k[i]]);
    }
	
 
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
  