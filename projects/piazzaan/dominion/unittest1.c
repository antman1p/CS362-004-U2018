/*
 * -----------------------------------------------------------------------
 * unittest1.c
 * CS 362_400
 * Antonio Piazza
 * piazzaan
 * 7/15/2108
 * 
 * Unit test 1 for Dominion function updateCoins
 * 
 * Include the following lines in your makefile:
 *
 * unittestresults: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 *      ./unittest1 &> unittestresults.out
 *
 * references: https://instructure-uploads.s3.amazonaws.com/account_10020000000097009/attachments/57943997/testUpdateCoins.c?response-content-disposition=inline%3B%20filename%3D%22testUpdateCoins.c%22%3B%20filename%2A%3DUTF-8%27%27testUpdateCoins.c&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAJDW777BLV26JM2MQ%2F20180713%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20180713T230229Z&X-Amz-Expires=86400&X-Amz-SignedHeaders=host&X-Amz-Signature=2214574dced4a3ea9ba53a11edad366aab41c4d203b5efb1df63de53855ed76d
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
	int i, player, bonus, handCount, gameInit, numPlayer;
	int maxPlayer = 4;
	int maxHandCount = 5;
	int maxBonus = 10;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState gState;

	int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
	
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
 
	printf ("\n---------------------------------------------------\nTESTING updateCoins():\n---------------------------------------------------");
	
	// Test the updateCoins function for each treasure, player and with different bonuses
	// and hand counts.
	
	// Loop through edge cases of number of players 2 and 4
	for(numPlayer = 2; numPlayer <= maxPlayer; numPlayer += 2)
	{
		// Loop through players
		for (player = 0; player < numPlayer; player++)
		{
			// Loop through hand count
			for (handCount = 0; handCount <= maxHandCount; handCount+=5)
			{
				// Loop through bonuses
				for (bonus = 1; bonus <= maxBonus; bonus+=9)
				{
					printf("\n\n---------------------------------------------------\nNumber of players: %d\n", numPlayer);
					printf("Player: %d\n", player + 1);
					printf("Hand Count: %d\n", handCount);
					printf("Bonus: %d\n", bonus);
					
					memset(&gState, 23, sizeof(struct gameState));  // Clear game state
					gameInit = initializeGame(numPlayer, k, seed, &gState);  // Initialize a new game
					gState.handCount[player] = handCount;
					
					
					
					// Fill hand with copper
					memcpy(gState.hand[player], coppers, sizeof(int) * handCount);  // Set all cards to copper
					
					// Call updateCoins() function
					updateCoins(player, &gState, bonus);
					
					printf("\nCopper Coin Count\n");
					printf("Expected: %d\n", handCount*1+bonus);
					printf("Result: %d\n", gState.coins);
					
					// Test Results
					assertTrue(gState.coins, handCount*1+bonus);
					
					
					
					// Fill hand with silver
					memcpy(gState.hand[player], silvers, sizeof(int) * handCount);  // Set all cards to silver
					
					// Call updateCoins() function
					updateCoins(player, &gState, bonus);
					
					printf("\nSilver Coin Count\n");
					printf("Expected: %d\n", handCount*2+bonus);
					printf("Result: %d\n", gState.coins);
					
					// Test Results
					assertTrue(gState.coins, handCount*2+bonus);
					
					
					
					// Fill hand with gold
					memcpy(gState.hand[player], golds, sizeof(int) * handCount);  // Set all cards to gold
					
					// Call updateCoins() function
					updateCoins(player, &gState, bonus);
					
					printf("\nGold Coin Count\n");
					printf("Expected: %d\n", handCount*3+bonus);
					printf("Result: %d\n", gState.coins);
					
					// Test Results
					assertTrue(gState.coins, handCount*3+bonus);

				}
			}
			
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
  
