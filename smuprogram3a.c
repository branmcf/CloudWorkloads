/* John M. Medellin SMU Lyle CSE 7346 Fall 2017, Program 3 a memory exhaustion algorithm */
/* Program name is smuprogram3a.c compiled using gcc smuprogram3a.c -o smuprogram3a.out */
/* Define Includes */
/* ----------------*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>

// Define Files

FILE *inputFile;
FILE *outputFile;

/* Define array variables j is search array, k is value we are looking for
_________________________________________________________ */

		int j[486000],k[486000],found = 0;
	
        


int main (void)
{


// Open Files

if ((inputFile = fopen("indata.dat","r")) == NULL){
	printf("**** Input data file input.dat did not open \n");}
if ((outputFile = fopen("outdata.dat","w")) == NULL){
	printf("**** Output data file output.dat did not open \n");}



/* Load search array from the file
---------------------------------- */

int i = 0, m = 0;
char comma;
while (i < 486000) {
	fscanf(inputFile,"%i %c %i",&k[i],&comma,&j[i]);
//	printf(" value read is %i %c %i \n ",k[i],comma,j[i]);

	i++;
	fseek(inputFile,1,SEEK_CUR);}

// Rewind File


fseek(inputFile,0,SEEK_SET);



// Perform binary searches and write file out



i = 0;

while (i < 486000) {

// read record to get the value to look for set binary search at half of 486K
	fscanf(inputFile,"%i %c %i",&k[i],&comma,&j[i]);
	m = 486000/2;
	found = 0;

// start the search

while (found == 0) {

	if (j[m] == k[i]){
		fprintf(outputFile,"Search Val %i \t is in position %i \n",j[m],m+1);
		found = 1;
		i++;
		if(i % 100000 == 0) printf("%i iterations \n",i);}
	else
		if ( j[m] - k[i] > 10) m = m - (abs(k[i]-j[m])/2);
		else
		if ( j[m] - k[i] < -10) m = m + (abs(k[i]-j[m])/2);
		else
		if ( j[m] - k[i] > 0) m--;
		else m++;
	} 

}

fclose(inputFile);
fclose(outputFile);
	

system("ps aux");

printf("process id %d \n",getpid());

}


