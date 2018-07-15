/*
 * -----------------------------------------------------------------------
 * cardtest2.c
 * CS 362_400
 * Antonio Piazza
 * piazzaan
 * 7/15/2108
 * 
 * Card test 2 for Dominion Adventurer card
 * 
 * Include the following lines in your makefile:
 *
 * echo "cardtest2.c:" >> unittestresults.out
 * gcc -o cardtest2 -g cardtest2.c dominion.c rngs.c $(CFLAGS)
 * ./cardtest2 >> unittestresults.out
 * gcov cardtest2.c
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
	int i, card;
	int treasureNum = 0, treasureNumOrig = 0;
	int numPlayer = 2;
	int player1 = 0, handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int player2 = 1;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
		
	// Initialize two game states
	struct gameState gState, copyGState;


 
	printf ("\n---------------------------------------------------\nTESTING Adventurer CARD:\n---------------------------------------------------");
	
	// Set Game State
	memset(&gState,23,sizeof(struct gameState));
	memset(&copyGState,23,sizeof(struct gameState));
	
	// Initialize game
	initializeGame(numPlayer, k, seed, &gState);
	
	// copy the game state to the copy to preserve the game state
	 memcpy(&copyGState, &gState, sizeof(struct gameState));
	 
	// call card effect function for Adventurer
	cardEffect(adventurer, choice1, choice2, choice3, &gState, handpos, &bonus);
	
	
	// Check Results
	// Requirement:  Current player should receive exactly 2 treasure cards
	printf("\nPlayer 1 receives exactly 2 treasure cards\n");
	// Check original number of treasure cards in player 1's hand
	for ( i = 0; i < copyGState.handCount[player1]; i++)
	{
		card = copyGState.hand[player1][i];
		if (card == copper || card == silver || card == gold) 
		{
			treasureNumOrig++;
		}
	}
	
	// Check new number of treasure cards in player 1's hand
	for ( i = 0; i < gState.handCount[player1]; i++)
	{
		card = gState.hand[player1][i];
		if (card == copper || card == silver || card == gold) 
		{
			treasureNum++;
		}
	}
	
  
	printf("Expected: %d\n", treasureNumOrig+2);
	printf("Result: %d\n", treasureNum);
	
	// Test and make sure the new number of treasures in the hand is 2 more than the original
	assertTrue(treasureNum, treasureNumOrig+2);
	
	

	// Test hand count of player 1 increased by 2
	printf("\nPlayer 1 hand count increased by exactly 2 \n");
	printf("Expected: %d\n", copyGState.handCount[player1]+2);
	printf("Result: %d\n", gState.handCount[player1]);
    assertTrue(gState.handCount[player1],copyGState.handCount[player1]+2);
	

	
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
  
