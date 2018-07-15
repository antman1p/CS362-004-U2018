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
	initializeGame(numPlayer, k, seed, &gState);
	
	// copy the game state to the copy to preserve the game state
	 memcpy(&copyGState, &gState, sizeof(struct gameState));
	 
	// call car effect function for Smithy
	cardEffect(smithy, choice1, choice2, choice3, &gState, handpos, &bonus);
	
	
	// Check Results
	// Requirement:  Current player should receive exactly 3 cards
	printf("\nPlayer 1 receives exactly 3 cards\n");
	printf("Expected: %d\n", copyGState.handCount[player1]+2);
	printf("Result: %d\n", gState.handCount[player1]);
    assertTrue(gState.handCount[player1],copyGState.handCount[player1]+2);
	
	// Requirement:  The 3 cards should come from player's own pile.
	printf("\nCard's come from Player 1's pile\n");
	printf("Expected: %d\n", copyGState.deckCount[player1]-3);
	printf("Result: %d\n", gState.deckCount[player1]);
    assertTrue(gState.deckCount[player1],copyGState.deckCount[player1]-3);
	
	// Requirement: No state change should occur for other players.
	printf("\nPlayer 2 was not effected\n");
	// Player 2's hand
	printf("\nPlayer 2 hand uneffected\n");
	printf("Expected: %d\n", copyGState.handCount[player2]);
	printf("Result: %d\n", gState.handCount[player2]);
    assertTrue(gState.handCount[player2],copyGState.handCount[player2]);
	//Player 2's deck
	printf("Expected: %d\n", copyGState.deckCount[player2]);
	printf("Result: %d\n", gState.deckCount[player2]);
    assertTrue(gState.deckCount[player2],copyGState.deckCount[player2]);
	
	// Requirement: No state change should occur to the victory card piles and kingdom card piles.
	
	
 
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
  
