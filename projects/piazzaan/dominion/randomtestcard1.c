/*
 * CS362-400
 * Random Test Smithy
 * randomtest1.c
 * 8/5/2018
 * References:
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <time.h>
#include <stdio.h>
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
 
 void testCard(int player, struct gameState *post)
 {
	// Set a new Game State
	struct gameState pre;
	memset(&pre,23,sizeof(struct gameState));	
	int i, r, j, card;
	int treasureNum = 0, treasureNumOrig = 0, bonus = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
	
	
	
	// copy the game state to the copy to preserve the game state
	memcpy(&pre, post, sizeof(struct gameState));
	
	// call card effect function for Adventurer
	r = cardEffect(smithy,0,0,0,post,0,&bonus);
	
	// Test cardEffect
	printf("Testing CardEffect()\n");
	assertTrue(r, 0);
	
	// Check Results
	// Requirement:  Current player should receive exactly 3 cards
	printf("\nPlayer 1 receives exactly 3 cards\n");
	printf("Expected: %d\n", pre.handCount[player1]+2);
	printf("Result: %d\n", post->handCount[player1]);
    assertTrue(post->handCount[player1],pre.handCount[player1]+2);
	
	// Requirement:  The 3 cards should come from player's own pile.
	printf("\nCard's come from Player 1's pile\n");
	printf("Expected: %d\n", pre.deckCount[player1]-3);
	printf("Result: %d\n", post->deckCount[player1]);
    assertTrue(post->deckCount[player1],pre.deckCount[player1]-3);
	
	for (i=0; i < post->numPlayers; i++)
	{
		if(i != player) 
		{
			// Requirement: No state change should occur for other players.
			printf("\nTest Player %d was not effected\n", i);
			// Player 2's hand
			printf("\nPlayer %d hand uneffected\n", i);
			printf("Expected: %d\n", pre.handCount[i]);
			printf("Result: %d\n", post->handCount[i]);
			assertTrue(post->handCount[i],pre.handCount[i]);
			//Player 2's deck
			printf("\nPlayer %d deck uneffected\n", i);
			printf("Expected: %d\n", pre.deckCount[i]);
			printf("Result: %d\n", post->deckCount[i]);
			assertTrue(post->deckCount[i],pre.deckCount[i]);
			
			// Requirement: No state change should occur to the victory card piles and kingdom card piles.
			// Test Victory Piles
			printf("\nTest Victory piles were not effected\n");
			// Test Province Pile
			printf("\nProvince Pile uneffected\n");
			printf("Expected: %d\n", pre.supplyCount[province]);
			printf("Result: %d\n", post->supplyCount[province]);
			assertTrue(post->supplyCount[province],pre.supplyCount[province]);
			// Test Duchy Pile
			printf("\nDuchy Pile uneffected\n");
			printf("Expected: %d\n", pre.supplyCount[duchy]);
			printf("Result: %d\n", post->supplyCount[duchy]);
			assertTrue(post->supplyCount[duchy],pre.supplyCount[duchy]);
			// Test Estate Pile
			printf("\nEstate Pile uneffected\n");
			printf("Expected: %d\n", pre.supplyCount[estate]);
			printf("Result: %d\n", post->supplyCount[estate]);
			assertTrue(post->supplyCount[estate],pre.supplyCount[estate]);
			
			
			// Test Kingdom Cards
			printf("\nTest Kingdom card piles were not effected\n");
			for (j = 0; j < 10; j++) 
			{
				printf("\nchecking card %d pile\n", k[j]);
				printf("Expected: %d\n", pre.supplyCount[k[j]]);
				printf("Result: %d\n", post->supplyCount[k[j]]);
				assertTrue(post->supplyCount[k[j]],pre.supplyCount[k[j]]);
			}
		}
	}
	
 }
 
 
 int main()
 {
	srand(time(0));
	struct gameState gState;
	memset(&gState,23,sizeof(struct gameState));
	int TESTS = 10000;
	int treasures[] = {copper, silver, gold};
	int numTreasures, i, j, playerNum;

	
	printf("\n---------------------------------------------------\nRANDOM ADVENTURER CARD TEST\n---------------------------------------------------");
	// Loop iterates for number of TESTS (Number of tests to be conducted)
	for (i=0; i < TESTS; i++)
	{
		//DEBUG
		printf("\nITERATION NUMBER %d\n", i);
		
		// Randomly initialize the game state
		for (j=0; j < sizeof(struct gameState); j++) 
		{
			((char*)&gState)[j] = (rand() % (256 + 1 - 0 ) )+ 0;
		}
		
		// Change some of the game state properties to meet preconditions
		
		// Randomize the number of players with a minimum of 2 and Max of MAX_PLAYERS
		gState.numPlayers = (rand() % (MAX_PLAYERS + 1 - 2)) + 2;
		
		
		// randomly select player position number
		playerNum = (rand() % (gState.numPlayers - 0)) + 0;
		
		
		// randomly assign player's deck count with at least 3 and no more than the max
		gState.deckCount[playerNum] = (rand() % (MAX_DECK + 1 - 3)) + 3;
		
		
		// randomly assign number of treasure cards in player's deck with a minumum of 3
		numTreasures = (rand() % (gState.deckCount[playerNum] + 1 - 3)) + 3;
		
		
		
		// Add the treasure cards to player's deck (ensures at least 3 cards are treasure cards)
		for (j=0; j < numTreasures; j++)
		{
			gState.deck[playerNum][j] = treasures[(rand() % 3)];  // Pick randomly from the three treasure card types
		}
		
		// set players discard to 0
		gState.discardCount[playerNum] = 0;
		
		// randomly set player's handcount with a minimum of 3
		gState.handCount[playerNum] = (rand() % (MAX_HAND + 1 - 3)) + 3;
	
		
		// Set turn to this player
		gState.whoseTurn = playerNum;
		
		// Call test function
		testCard(playerNum, &gState);
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