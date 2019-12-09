#include "functions.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <ctype.h>
#define MAXCHAR 10000

int main(int argc, char **argv){
	FILE *fp;
	char str[MAXCHAR];
	char* filename = "market.txt";
	fp = fopen(filename, "r");
	if (fp == NULL){
		printf("Could not open file %s",filename); //If there is an error while file is opening, this message is given.
	}
	char customerList[100];
	while (fgets(str, MAXCHAR, fp) != NULL){ 
			char delim2[] = ",";
			char *day = strtok(str, delim2);
			char *customer=strtok(NULL,delim2);
			append(customer,':');
			char *ret=strstr(customerList,customer); //strstr function return null when customer is in customerList
			if(ret == NULL){
				strcat(customerList,customer);
			}
	}
	fclose(fp);
	char *end_str;
	char *token=strtok_r(customerList,":",&end_str); 
	int max=0;
	char *maxProduct_customer;
	while(token != NULL){ //maxProduct_customer represents customer that who purchase the most items
		FILE *fp2; //Firstly max is 0 but if the number of product is greater than last max, max is this number.
		char str2[MAXCHAR];
		fp2 = fopen(filename, "r");
		if (fp2 == NULL){
			printf("Could not open file %s",filename); //If there is an error while file is opening, this message is given.
		}
		int productNum=0;
		while (fgets(str2, MAXCHAR, fp2) != NULL){
				char *end_str2;
				char *day=strtok_r(str2,",",&end_str2);
				char *customer=strtok_r(NULL,",",&end_str2);
				if(strcmp(token,customer)==0){
					char *productList=strtok_r(NULL,",",&end_str2);
					while(productList !=NULL){
						productNum++;
						productList=strtok_r(NULL,",",&end_str2);
					}			
				}		
		}
		if(productNum>max){
			max=productNum;
			maxProduct_customer=token;
		}
		token = strtok_r(NULL, ":", &end_str);
	}
	printf("%s is the customer that purchase the most item. \nNumber of the product that is purchased from this customer: %d\n",maxProduct_customer,max);
}