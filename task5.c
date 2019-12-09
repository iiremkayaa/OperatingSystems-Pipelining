#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <ctype.h>
#include "functions.c"
#define MAXCHAR 10000

int main(int argc, char **argv){
	FILE *fp;
	char str[MAXCHAR];
	char* filename = "market.txt";
	fp = fopen(filename, "r");
	if (fp == NULL){
		printf("Could not open file %s",filename); //If there is an error while file is opening, this message is given. 
	}
	char dayList[100];
	while (fgets(str, MAXCHAR, fp) != NULL){
			char delim2[] = ",";
			char *day = strtok(str, delim2);
			append(day,':');
			char *ret=strstr(dayList,day);
			if(ret == NULL){
				strcat(dayList,day);
			}
	}
	fclose(fp);
	char *end_str;
	char *token=strtok_r(dayList,":",&end_str);
	char day_product[10000]="";
	while(token != NULL){
		FILE *fp2;
		char str2[MAXCHAR];
		fp2 = fopen(filename, "r");
		if (fp2 == NULL){
			printf("Could not open file %s",filename); //If there is an error while file is opening, this message is given. 
		}
		strcat(day_product,token);
		strcat(day_product,",");
		while (fgets(str2, MAXCHAR, fp2) != NULL){
				int len = strlen(str2);
	    		str[len-2] = '\0';  //This operation deletes \n in end of line
				char *end_str2;
				char *day=strtok_r(str2,",",&end_str2);
				char *customer=strtok_r(NULL,",",&end_str2);
				if(strcmp(token,day)==0){
					char *productList=strtok_r(NULL,",",&end_str2);
					productList=trim(productList,NULL);
					while(productList !=NULL){
						char *products=trim(productList,NULL);
						strcat(day_product,products);
						strcat(day_product,",");
						productList=strtok_r(NULL,",",&end_str2);
					}		
				}
		}
		strcat(day_product,"\n");//each day is seperated by \n
		fclose(fp2);
		token = strtok_r(NULL, ":", &end_str);
	}
	char maxPrice_day[1000]="";
	int maxPrice=0;
	char *end_str3;
	char *dayProductToken=strtok_r(day_product,"\n",&end_str3);
	while(dayProductToken!=NULL){ //dayProductToken represent the day that has maximum total price.
		int price=0;  //Firstly, maxPrice is 0. If price of the day is  
		char *end_str4; //greater than maxPrice, maxPrice is this price of this day
		char *dayToken=strtok_r(dayProductToken,",",&end_str4);
		char *productToken=strtok_r(NULL,",",&end_str4);
		while(productToken!=NULL){
			FILE *fp3;
			char str3[MAXCHAR];
			char *file_name="price.txt";
			fp3 = fopen(file_name, "r");
			if (fp3 == NULL){
				printf("Could not open file %s",filename); //If there is an error while file is opening,
			}                                               // this message is given.
			while (fgets(str3, MAXCHAR, fp3) != NULL){
				char *end_str5;
				char *productName=strtok_r(str3,":",&end_str5);
				char *productPrice=strtok_r(NULL,":",&end_str5);
				if(strcmp(productName,productToken)==0){
					price+=atoi(productPrice);
				}
			}
			fclose(fp3);
			productToken=strtok_r(NULL,",",&end_str4);
		}
		if(price>maxPrice){ 
			maxPrice=price;
			strcpy(maxPrice_day,dayToken);
		}
		dayProductToken=strtok_r(NULL,"\n",&end_str3);
	}
	printf("Profitable day:%s  Price : %d\n",maxPrice_day,maxPrice);
}