/*
 * -----------------------------------------------------------------------
 * unittest3.c
 * CS 362_400
 * Antonio Piazza
 * piazzaan
 * 7/15/2108
 * 
 * Unit test 3 for Dominion function endTurn()
 * 
 * Include the following lines in your makefile:
 *
 * unittestresults: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.c rngs.c $(CFLAGS)
 *      ./unittest3 >> unittestresults.out
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
	int player, gameInit, numPlayer;
	int maxPlayer = 4;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState gState;


 
	printf ("\n---------------------------------------------------\nTESTING endTurn():\n---------------------------------------------------");
	
	
	// Loop through edge cases of number of players 2 and 4
	for(numPlayer = 2; numPlayer <= maxPlayer; numPlayer += 2)
	{
		// Loop through players
		for (player = 0; player < numPlayer; player++)
		{
			printf("\n\n---------------------------------------------------\nNumber of players: %d\n", numPlayer);
			printf("Start with Player: %d\n", player + 1);
					
			memset(&gState, 23, sizeof(struct gameState));  // Clear game state
			gameInit = initializeGame(numPlayer, k, seed, &gState);  // Initialize a new game
			
			if (player == 1) 
			{
				endTurn(&gState);
			}
			if (player == 3)
			{
				endTurn(&gState);
				endTurn(&gState);
				endTurn(&gState);
			}
			
			printf("\nInitial:\n");
			printf("Expected: %d\n", player);
			printf("Result: %d\n", gState.whoseTurn);
			assertTrue(gState.whoseTurn, player);
			
			printf("\nEnding Turn\n");
			if (numPlayer == 4)
			{
				
				if (player == 0)
				{
					endTurn(&gState);
					endTurn(&gState);
					endTurn(&gState);
					
					printf("\nAfter Turns ended:\n");
					printf("Expected: %d\n", 3);
					printf("Result: %d\n", gState.whoseTurn);
					assertTrue(gState.whoseTurn, 3);
				}
				else
				{
					endTurn(&gState);
					printf("\nAfter Turns ended(Go Back to first Player):\n");
					printf("Expected: %d\n", 0);
					printf("Result: %d\n", gState.whoseTurn);
					assertTrue(gState.whoseTurn, 0);
				}
			}
			else
			{
				endTurn(&gState);
				if (player == 0)
				{
					printf("\nAfter Turns Ended:\n");
					printf("Expected: %d\n", 1);
					printf("Result: %d\n", gState.whoseTurn);
					assertTrue(gState.whoseTurn, 1);
				}
				else
				{
					printf("\nAfter Turns ended(Go Back to first Player):\n");
					printf("Expected: %d\n", 0);
					printf("Result: %d\n", gState.whoseTurn);
					assertTrue(gState.whoseTurn, 0);
				}
			}
			
			// If Number of players is 4 then to test the upper edge case we 
			// Need to increment player by more than 1 for this for loop
			if (numPlayer == 4) 
			{
				player += 2;
			}
			
			printf("\nOutpostPlayed:\n");
			printf("Expected: %d\n", 0);
			printf("Result: %d\n", gState.outpostPlayed);
			assertTrue(gState.outpostPlayed,0);
			
			printf("\nPhase\n: %d\n", 0);
			printf("Expected: %d\n", 0);
			printf("Result: %d\n", gState.phase);
		    assertTrue(gState.phase,0);
			
			printf("\nNumActions:\n";
			printf("Expected: %d\n", 1);
			printf("Result: %d\n", gState.numActions);
		    assertTrue(gState.numActions,1);
			
			printf("\nCoins:\n";
			printf("Expected: %d\n", 0);
			printf("Result: %d\n", gState.coins);
		    assertTrue(gState.coins,0);
			
			printf("\nNumBuys:\n";
			printf("Expected: %d\n", 1);
			printf("Result: %d\n", gState.numBuys);
		    assertTrue(gState.numBuys,1);
			
			printf("\nPlayedCardCount:\n";
			printf("Expected: %d\n", 0);
			printf("Result: %d\n", gState.playedCardCount);
		    assertTrue(gState.playedCardCount,0);
			
			printf("\nHandCount:\n";
			printf("Expected: %d\n", 0);
			printf("Result: %d\n", gState.handCount[gState.whoseTurn]);
		    assertTrue(gState.handCount[gState.whoseTurn],0);
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
  
