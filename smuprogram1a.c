/* John M. Medellin SMU Lyle CSE 7346 Fall 2017, Program 1 a computational exhaustion */

/* Program name is program1a.c compiled using gcc smuprogram1a.c -o smuprogram1a.out */
/* Define Includes */
/* ----------------*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>

/* Define counter…number of modulo multiples to find before the program finishes
randum number, modulus operator to determine if it's a valid number
______________________________________________________________________ */

        long long int count = 0;
	int maxcount = 3;
	long long int randnum = 1;
	int powerof = 1;
	long long int modoper = 1;
	long long int numtries = 0;
	long long int totnumtries = 0;
	
	
        


int main (void)
{

/* Accept input from the key board to drive the number of modular compliant numbers
the modulo operator to be used and the elevation of rand to a power of 10

THE CODE DEFAULTS TO THE FOLLOWING:

100 MULTIPLES OF THE ROUND NUMBER TO FIND
2^34TH MODULO OPERATOR
2^10TH IS USED TO MULTIPLY TIMES ROUND NUMBER TO COMPARE TOT THE 2^34TH MODULO

THE CODE CAN ALSO BE MADE AS INPUT FROM THE KEYBOARD BY MAKING THE PRINTF/SCAN LINES ACTIVE

------------------------------------------------------------------------------------------- */

	

//	printf("Enter the number of modulars to find (default is 3) \n");
//	scanf ("%i",&maxcount);
	maxcount = 100;

//	printf("Enter the modulo operator in power of 2 (10 = 1024) \n");
//	scanf ("%lli",&modoper);
	modoper = 34;

	modoper = ldexp(1,modoper);
	// 1 X 2 ^ 34 == 17179869184
//	printf("%lli \n",modoper);
//	printf("Enter the power of 2 that we are to elevate the random number \n");
//	scanf ("%i",&powerof);
	powerof = 10;

//	printf("Rand^pwr \t Modulo \t [rand^pwr]/Modulo \t #Iter \n");
//	printf("------------------------------------------------- \n");

// BEGIN LOOP TO FIND THE NUMBER OF OCCURRENCES WHERE THE RANDOM IS A FUNCTION OF THE MODULO

	while (count < maxcount) 
{
        	
/* Fetch a random number, elevate it to the power, increase the number of tries counter
_______________________________________________________________________________________ */

		randnum = rand() * ldexp(1,powerof); 
		numtries ++;

/* If it is modulo that we want, report it with the number of tries, increase counter
 and zero out the number of tries so we can report the variable again
_____________________________________________________________________________________ */
		
		if (randnum % modoper == 0){ 
		
		printf("%lli \t %lli \t %lli \t %lli \n",randnum,modoper,(randnum/modoper),numtries);
		count ++; 
		totnumtries = totnumtries + numtries;
		numtries = 0;}
}

// ADD UP THE NUMBER OF TRIES IT TOOK TO GET TO THE NUMBER OF OCCURRENCES AND PRINT IT

printf("Total number of tries %lli \n",totnumtries);

// SYSTEM COMMAND TO ISSUE THE STATISTICS OF THE RUN

system("ps aux");

// PRINT THE PROCESS ID SO IT CAN BE USED TO DETERMINE THE USAGE STATISTICS

printf("process id %d \n",getpid());

}


