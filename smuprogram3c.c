/*
 * tsd_mods7.c
 *
 * Demonstrates the usage of threads with thread specific variables instead of mutexes to 
 * synchronize the search. Uses 4 threads to execute binary search on 486000 random numbers from a space
 * of 1 to 500,000. Initializes the arrays, reads values from the file, executes threaded binary searches
 * and writes file back out.
 *
 * Compile command is ---- gcc -pthread smuprogram3c.c -o smuprogram3c.out
 *
 * Note that it is often easier to use a statically initialized
 * mutex to accomplish the same result.
 */
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

#define NUM_THREADS  4

// Define Files

FILE *inputFile;
FILE *outputFile;


// Initialize arrays

// k is the value to look for
// j is the value column sorted
// p is the line number where the value is located

int j[486000],k[486000],p[486000],found = 0;
char comma;
int cacheflush(char *addr, int nbytes, int cache);

/*
 * Structure used as the value for thread-specific data key.
 */
typedef struct tsd_tag {
    pthread_t   thread_id;
    char        *string;
    int		location;
    int		next_one;
    int		found;
} tsd_t;

pthread_key_t tsd_key;           /* Thread-specific data key */
pthread_once_t key_once = PTHREAD_ONCE_INIT;

/*
 * One-time initialization routine used with the pthread_once
 * control block.
 */
void once_routine (void)
{
    int status;

//    printf ("initializing key\n");
    status = pthread_key_create (&tsd_key, NULL);
    if (status != 0)
        printf("Create key");
}

/*
 * Thread start routine that uses pthread_once to dynamically
 * create a thread-specific data key.
 */
void *thread_routine (void *arg) {
    tsd_t *value;
    int status;
    status = pthread_once (&key_once, once_routine);
    if (status != 0)
        printf("Once init");
    value = (tsd_t*)malloc (sizeof (tsd_t));
    if (value == NULL)
        printf("Allocate key value");
    status = pthread_setspecific (tsd_key, value);
    if (status != 0)
        printf("Set tsd");
 //   printf ("%s set tsd value %p\n", arg, value);
    value->thread_id = pthread_self ();
    value->string = (char*)arg;
    value->next_one = atoi(arg);
    value->location = 243000;    
    value->found = 0;
    value = (tsd_t*)pthread_getspecific (tsd_key);
 
// Locate values loop

// Set number of values to find in the binary search

while (value->next_one < 486000){


while (value->found == 0) {

// if it finds it, then put location into the p[] array and increase the value of looking for by the number of threads
// obtain next value, set begining of search to half of the array, obtain that value

	if (j[value->location] == k[value->next_one]){

		p[value->next_one] = value->location + 1;
		value->next_one = value->next_one + NUM_THREADS;
	        value->location = 243000;
		value->found = 1;
		if(value->next_one % 100000 == 0) printf("%i iterations \n",value->next_one);}
	else
		if ( j[value->location] - k[value->next_one] > 10) value->location = value->location - (abs(k[value->next_one]-j[value->location])/2);
		else
		if ( j[value->location] - k[value->next_one] < -10) value->location = value->location + (abs(k[value->next_one]-j[value->location])/2);
		else
		if ( j[value->location] - k[value->next_one] > 0) value->location--;
		else value->location++;
		} 
	value->found = 0;
	}
		
    return NULL;
}

int main (int argc, char *argv[])
{

// Open Files

if ((inputFile = fopen("indata.dat","r")) == NULL){
	printf("**** Input data file input.dat did not open \n");}
if ((outputFile = fopen("outdata.dat","w")) == NULL){
	printf("**** Output data file output.dat did not open \n");}

/* Load search array from the file
---------------------------------- */

int i = 0;
while (i < 486000) {
	fscanf(inputFile,"%i %c %i",&k[i],&comma,&j[i]);
//	printf(" value read is %i %c %i \n ",k[i],comma,j[i]);

	i++;
	fseek(inputFile,1,SEEK_CUR);}

// Create Threads

    pthread_t thread1, thread2, thread3, thread4;
    int status;

    status = pthread_create (
        &thread1, NULL, thread_routine, " 0");
    if (status != 0)
        printf("Create thread 1");
    status = pthread_create (
        &thread2, NULL, thread_routine, " 1");
    if (status != 0)
        printf("Create thread 2");
    status = pthread_create (
        &thread3, NULL, thread_routine, " 2");
    if (status != 0)
        printf("Create thread 3");
    status = pthread_create (
        &thread4, NULL, thread_routine, " 3");
    if (status != 0)
        printf("Create thread 4");

// Wait on threads to join

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
	pthread_join(thread4,NULL);

// Write output file

int m = 0;

while (m < 486000){
		fprintf(outputFile,"Search Val %i \t is in position %i \n",k[m],p[m]);
		m++;}

// Close files


fclose(inputFile);
fclose(outputFile);

// Request statistics from Linux

//system("ps aux");

printf("process id %d \n",getpid());

    pthread_exit (NULL);



}