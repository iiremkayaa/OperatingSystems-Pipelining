#include "functions.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <ctype.h>
#define MAXCHAR 10000
int main(int argc, char **argv){ //This function shows the total number of products and their price.
    char array[MAXCHAR];
		FILE *fp;
		char str[MAXCHAR];
		char* filename = "price.txt";  
		fp = fopen(filename, "r");
		if (fp == NULL){
			printf("Could not open file %s",filename); //If there is an error while file is opening, this message is given.
		}
		int productNumber=0;
		while (fgets(str, MAXCHAR, fp) != NULL){ //productNumber represent the total number of different products
			productNumber++;
			printf("%s",str);
		}
		printf("There are %d products.\n",productNumber);
}