/*
 * CS362-400
 * Random Tester Quiz
 * testme.cabs
 * 7/22/2018
 * References:  https://www.asciitable.com/
 */


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// Returns random ASCII characters in integer form from cahracters "space" to "~" (32 to 126)
char inputChar()
{
    int minChar = 32;          // Space
	int maxChar = 126;         // ~
	return (minChar + rand() % (maxChar - minChar));
}


// Returns a 6 character array consisting of 5 random characters from lower case a to 
// lower case z (97 to 122) and a null character at the end
char *inputString()
{
    char* stringArr[6];
	int i;
	int minChar = 97;          // a
	int maxChar = 122;         // z
	
	for (i = 0; i < 5; i++) 
	{
		stringArr[i] = minChar + rand() % (maxChar - minChar);
	}
	
    return *stringArr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
