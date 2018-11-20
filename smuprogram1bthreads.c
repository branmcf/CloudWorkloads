/* John M. Medellin SMU Lyle CSE 7346 Fall 2017, Program 1 b computational exhaustion */

/* This one is multi threaded exhaustion */

/* Program name is program1b.c compiled using gcc -pthread smuprogram1bthreads.c -o smuprogram1bthreads.out */

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

// Define multi threading variables, at this point it is set for 2 threads

#define NUM_THREADS  2

// Define mutexes for critical regions

pthread_mutex_t mutexsum;
pthread_mutex_t mutextries;

/* Define counter…number of modulo matches etc. as global variables to find before 
the program finishes randum number, modulus operator to determine if it's a valid number
________________________________________________________________________________________ */

        long long int count = 0;
	int maxcount = 100;
	long long int randnum = 1;
	int powerof = 10;
	long long int modoper = 34;
	long long int numtries = 0;
	long long int totnumtries = 0;
	
	

/* This is the function where the threads do their work
_________________________________________________________ */

void *Domath (void *threadid)
{
// DEFINE EXECUTION VARIABLES HERE

// maxcount is the number of modular=0 operations to be found before termination

	maxcount = 100;

// powerof is the power of 2 to elevate the random number generated

	powerof = 10;

// modoper is the power of 2 to elevate the modulo operation

	modoper = 34;

// execute power of 2 operations to set variables

	modoper = ldexp(1,modoper);
	randnum = ldexp(1,powerof);
	
	while (count < maxcount) 
{
        	
/* Increase the number of tries counter (implied indirection declared)
______________________________________________________________________ */

		numtries ++;

/* If it is modulo that we want, report it with the number of tries, increase counter
 and zero out the number of tries so we can report the variable again
_____________________________________________________________________________________ */
		
		if ((rand() * randnum) % modoper == 0){ 
// Lock critical region and update the number of modulos found and the total number of cycles

		pthread_mutex_lock(&mutexsum);

			count ++; 
			totnumtries = totnumtries + numtries;
// Print results so far
			printf("%lli \t %lli \t %lli \t %lli \t %lli \n",randnum,modoper,(randnum/modoper),numtries,count);
			numtries = 0;
		pthread_mutex_unlock(&mutexsum);
		}
			
// OLD CODE ---> ELSE lock critical region and increase number of tries

/*		pthread_mutex_lock(&mutextries);
			numtries ++;
		pthread_mutex_unlock(&mutextries);

*/
		
}

pthread_exit(NULL);

// return 0;

}

int main (void)
{
// Declare function main variables

long i;
void *status;

// Create mutex for crit region countr in Domath

pthread_mutex_init(&mutexsum,NULL);

// Create mutex for crit region numtries in Domath

pthread_mutex_init(&mutextries,NULL);

// Instantiate threads based on default parameter set above

pthread_t threads[NUM_THREADS];
int rc;
long t;
for(t=0;t<NUM_THREADS;t++){
printf("In main: creating thread %ld\n",t);
rc = pthread_create(&threads[t],NULL,Domath,(void *)t);
if (rc){
	printf("ERROR; return code from pthread_create() is %d\n",rc);
	exit(-1); }
}

// Domath ();
// Wait on the rest of the threads

for(i=0; i<NUM_THREADS; i++)
	{
	pthread_join(threads[i], &status);
	}

printf("Total number of tries %lli \n",totnumtries);
system("ps aux");

printf("process id %d \n",getpid());

// Destroy mutexes and exit threads

pthread_mutex_destroy(&mutexsum);
pthread_mutex_destroy(&mutextries);
pthread_exit(NULL);

}


