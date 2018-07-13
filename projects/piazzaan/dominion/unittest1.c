/*
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
	int i;
	int seed = 1000;
	int numPlayer = 2;
	int bonus;
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
 
	printf ("TESTING updateCoins():\n");
 
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
  
