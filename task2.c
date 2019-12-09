#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <ctype.h>
#include "functions.c"
#define MAXCHAR 10000
int main(int argc, char **argv){ //This function shows how many times a given product is sold.
    FILE *fp;
		char str[MAXCHAR];
		char filename[] = "market.txt";
		fp = fopen(filename, "r");
		if (fp == NULL){
			printf("Could not open file %s",filename); //If there is an error while file is opening, this message is given.
		}
		char product[50]="";
		strcat(product,"-");
		char givenProduct[50]="";
		if(argv[2] != NULL){ // argv represent the given product name.If argv[2] is null, product name
			strcat(product,argv[1]);  // has only one word. If argv[2] is not null, product name
			strcat(givenProduct,argv[1]);     // has more than one word like EYE LINER.
			strcat(product," "); 
			strcat(givenProduct," ");
			strcat(givenProduct,argv[2]);     
			strcat(product,argv[2]);
		}
		else{
			strcat(givenProduct,argv[1]);
			strcat(product,argv[1]); 
		}
		char products[1000]="";
		while (fgets(str, MAXCHAR, fp) != NULL){
			int len = strlen(str); 
	    	str[len-2] = '\0';  //this operation deletes \n at the end of the line
			char delim2[] = ","; 
			char *ptr2 = strtok(str, delim2);
			ptr2=strtok(NULL,delim2);
			ptr2=strtok(NULL,delim2);
			while(ptr2 !=NULL){
				ptr2=trim(ptr2,NULL); //trim function deletes space in the first and last of string
				strcat(products,"-");
				strcat(products,ptr2);
				strcat(products,"-");
				ptr2=strtok(NULL,delim2);
			}
		}
		strcat(product,"-");
		int count = 0;
		count=count+countOccurrences(products,product); //countOccurrences function finds the given
		printf("%s was sold %d times.\n",givenProduct,count); //product name in the string that has all products.
	

}