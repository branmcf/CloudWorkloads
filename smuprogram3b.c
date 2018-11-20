/* John M. Medellin SMU Lyle CSE 7346 Fall 2017, Program 3b a strict file io program algorithm */
/* Program name is smuprogram3a.c compiled using gcc smuprogram3b.c -o smuprogram3b.out */
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
if ((outputFile = fopen("outdata3b.dat","w")) == NULL){
	printf("**** Output data file output.dat did not open \n");}



/* Read input file record, write record to output file
------------------------------------------------------ */

int i = 0, m = 0;
char comma;
while (i < 486000) {
	fscanf(inputFile,"%i %c %i",&k[i],&comma,&j[i]);
//	printf(" value read is %i %c %i \n ",k[i],comma,j[i]);
	fprintf(outputFile,"%i %c %i \n",k[i],comma,j[i]);
	i++;
	fseek(inputFile,1,SEEK_CUR);}

fclose(inputFile);
fclose(outputFile);
	

system("ps aux");

printf("process id %d \n",getpid());

}


