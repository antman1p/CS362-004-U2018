/*
 * CS362-400
 * Random Test Adventurer
 * randomtestadventurer.c
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
	int i, r, card;
	int treasureNum = 0, treasureNumOrig = 0, bonus = 0;
	
	
	
	// copy the game state to the copy to preserve the game state
	memcpy(&pre, post, sizeof(struct gameState));
	
	// call card effect function for Adventurer
	r = cardEffect(adventurer,0,0,0,post,0,&bonus);
	
	assertTrue(r, 0);
	assertTrue(memcmp(&pre, post, sizeof(struct gameState)), 0);
	
	
	// // Check Results
	// //
	// // Requirement:  Current player should receive exactly 2 treasure cards
	// printf("\nPlayer %d receives exactly 2 treasure cards\n", player);
	// // Check original number of treasure cards in player's hand
	// for ( i = 0; i < pre.handCount[player]; i++)
	// {
		// card = pre.hand[player][i];
		// if (card == copper || card == silver || card == gold) 
		// {
			// treasureNumOrig++;
		// }
	// }
	
	// // Check new number of treasure cards in player's hand
	// for ( i = 0; i < post->handCount[player]; i++)
	// {
		// card = post->hand[player][i];
		// if (card == copper || card == silver || card == gold) 
		// {
			// treasureNum++;
		// }
	// }
	
	// printf("Expected: %d\n", treasureNumOrig+2);
	// printf("Result: %d\n", treasureNum);
	
	// // Test and make sure the new number of treasures in the hand is 2 more than the original
	// assertTrue(treasureNum, treasureNumOrig+2);
	
 }
 
 
 int main()
 {
	srand(time(0));
	struct gameState gState;
	memset(&gState,23,sizeof(struct gameState));
	int TESTS = 1000;
	int treasures[] = {copper, silver, gold};
	int numTreasures, i, j, playerNum;

	
	printf("\n---------------------------------------------------\nRANDOM ADVENTURER CARD TEST\n---------------------------------------------------");
	// Loop iterates for number of TESTS (Number of tests to be conducted)
	for (i=0; i < TESTS; i++)
	{
		// Randomly initialize the game state
		for (j=0; j < sizeof(struct gameState); j++) 
		{
			((char*)&gState)[j] = rand() % (256 + 1 - 0 ) + 0;
		}
		
		// Change some of the game state properties to meet preconditions
		
		// Randomize the number of players with a minimum of 2 and Max of MAX_PLAYERS
		gState.numPlayers = rand() % (MAX_PLAYERS + 1 - 2) + 2;
		
		// randomly select player position number
		playerNum = rand() % (gState.numPlayers + 1 - 0) + 0;
		
		// randomly assign player's deck count with at least 3 and no more than the max
		gState.deckCount[playerNum] = rand() % (MAX_DECK + 1 - 3) + 3;
		
		// randomly assign number of treasure cards in player's deck with a minumum of 3
		numTreasures = rand() % (gState.deckCount[playerNum] + 1 - 3) + 3;
		
		// Add the treasure cards to player's deck (ensures at least 3 cards are treasure cards)
		for (j=0; j < numTreasures; j++)
		{
			gState.deck[playerNum][j] = treasures[rand() % 3];  // Pick randomly from the three treasure card types
		}
		
		// set players discard to 0
		gState.discardCount[playerNum] = 0;
		
		// randomly set player's handcount with a minimum of 3
		gState.handCount[playerNum] = rand() % (MAX_HAND + 1 - 3) + 3;
		
		// Set turn to this player
		gState.whoseTurn = playerNum;
		
		// Call test function
		testCard(playerNum, &gState);
	
	}	 
	return 0;
 }