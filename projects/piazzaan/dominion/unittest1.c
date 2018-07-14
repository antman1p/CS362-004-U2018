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
 *      gcc -o unittestresults -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 *      ./unittestresults &> unittestresults.out
 *
 * references: https://instructure-uploads.s3.amazonaws.com/account_10020000000097009/attachments/57943997/testUpdateCoins.c?response-content-disposition=inline%3B%20filename%3D%22testUpdateCoins.c%22%3B%20filename%2A%3DUTF-8%27%27testUpdateCoins.c&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAJDW777BLV26JM2MQ%2F20180713%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20180713T230229Z&X-Amz-Expires=86400&X-Amz-SignedHeaders=host&X-Amz-Signature=2214574dced4a3ea9ba53a11edad366aab41c4d203b5efb1df63de53855ed76d
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include <string.h>


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
	int i, j, player, bonus, handCount, gameInit;
	int maxHandCount = 5;
	int maxBonus = 10;
	int seed = 1000;
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	struct gameState gState;
	
	char treasures[8];

	int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
	
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
 
	printf ("TESTING updateCoins():\n");
	
	// Test the updateCoins function for each treasure, player and with different bonuses
	// and hand counts.
	// Loop through players
	for (player = 1; player <= numPlayer; player++)
	{
		// Loop through hand count
		for (handCount = 1; handCount <= maxHandCount; handCount++)
		{
			// Loop through bonuses
			for (bonus = 0; bonus <= maxBonus; bonus++)
			{
				// Loop for each of the 3 treasure types
				for (j =0; j < 3; j++)
				{
					// Set treasures char array to NULL
					memset(&treasures[0], 0, sizeof(treasures));
					
					// Change treasure type based of loop iteration
					if (j = 0)
					{
						stpcpy(treasures, "coppers");
					}
					else if (j = 1)
					{
						stpcpy(treasures, "silvers");
					}
					else
					{
						stpcpy(treasures, "golds");
					}
					
					printf("\nPlayer: %d\n", player);
					printf("Hand Count: %d\n", handCount);
					printf("Bonus: %d\n", bonus);
					
					memset(&gState, 23, sizeof(struct gameState));  // Clear game state
					gameInit = initializeGame(numPlayer, k, seed, &gState);  // Initialize a new game
					memcpy(gState.hand[player], treasures, sizeof(int) * handCount);  // Set all cards to copper
					
					// Call updateCoins() function
					updateCoins(player, &gState, bonus);
					
					printf("\nCoin Count minus %s\n", treasures);
					printf("Expected: %d\n", handCount * 1 + bonus);
					printf("Result: %d\n", gState.coins);
					
					// Test Results
					assertTrue(gState.coins, handCount * 1 + bonus);
				}

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
		printf("\nTEST FAILED\n");
	}
	else          // Else all tests pass, print pass message
	{
		printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
	}
	  
	return 0;
	  
 }
  
