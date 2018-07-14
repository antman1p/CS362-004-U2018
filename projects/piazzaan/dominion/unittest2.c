/*
 * -----------------------------------------------------------------------
 * unittest2.c
 * CS 362_400
 * Antonio Piazza
 * piazzaan
 * 7/15/2108
 * 
 * Unit test 1 for Dominion function numHandCards()
 * 
 * Include the following lines in your makefile:
 *
 * unittestresults: unittest1.c unittest2.c dominion.o rngs.o
 *      gcc -o unittestresults -g  unittest1.c unittest2.c dominion.c rngs.c $(CFLAGS)
 *      ./unittestresults &> unittestresults.out
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
	int player, gameInit, numPlayer, intNumHandCards;
	int maxPlayer = 4;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState gState;


 
	printf ("\n---------------------------------------------------\nTESTING numHandCards():\n---------------------------------------------------");
	
	
	// Loop through edge cases of number of players 2 and 4
	for(numPlayer = 2; numPlayer <= maxPlayer; numPlayer += 2)
	{
		// Loop through players
		for (player = 0; player < numPlayer; player++)
		{
			printf("\n\n---------------------------------------------------\nNumber of players: %d\n", numPlayer);
			printf("Player: %d\n", player + 1);
					
			memset(&gState, 23, sizeof(struct gameState));  // Clear game state
			gameInit = initializeGame(numPlayer, k, seed, &gState);  // Initialize a new game
			
			
			gState.whoseTurn = player;  // Set turn to current player
			
			// call the numHandCards function
			intNumHandCards = numHandCards(&gState);
			
			
			printf("NumHandCards: %d\n", intNumHandCards);
			
			if (player == 0)
			{
				assertTrue(intNumHandCards == 5);
			}
			else
			{
				assertTrue(intNumHandCards == 0);
			}
			
			
			// End turns to go to from the first to the last player's turn
			printf("\nEnding turns\n\n");
			
			if (numPlayer == 4)
			{
				endTurn(&gState);
				endTurn(&gState);
				endTurn(&gState);
			}
			else
			{
				endTurn(&gState);
			}
			
			intNumHandCards = numHandCards(&gState);
			
			
			printf("NumHandCards: %d\n", intNumHandCards);
			
			assertTrue(intNumHandCards == 5);
			
			
			// If Number of players is 4 then to test the upper edge case we 
			// Need to increment player by more than 1 for this for loop
			if (numPlayer == 4) 
			{
				player += 2;
			}
		}
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
  
