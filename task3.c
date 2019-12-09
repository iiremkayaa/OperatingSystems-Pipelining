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
		char filename[] = "market.txt";
		fp = fopen(filename, "r");
		if (fp == NULL){
			printf("Could not open file %s",filename);//If there is an error while file is opening, this message is given. 
		}
		char customer[10]="CUSTOMER_";
		strcat(customer,argv[1]); //customer represent concatenation of CUSTOMER_ and given number.
		char allProduct[1000]="";
		while (fgets(str, MAXCHAR, fp) != NULL){ //If customer is in line of the file, this line is printed.
			int len = strlen(str);
	    	str[len-2] = '\0';
			char delim2[] = ",";
			char *day = strtok(str, delim2);
			char *customerStr=strtok(NULL,delim2);
			if(strcmp(customer,customerStr) == 0){
				printf("DAY: %s ",str);
				char *productStr=strtok(NULL,delim2);
				printf("PRODUCTS: ");
				while(productStr !=NULL){
					productStr=trim(productStr,NULL);
					printf("%s, ",productStr);
					strcat(allProduct,"/");
					strcat(allProduct,productStr);
					productStr=strtok(NULL,delim2);
				}
				printf("\n");
			}
			
		}
		fclose(fp); //All identified products are holds in arr. Then these products is searched in price.txt 
		char delim2[]="/"; //All price of products are added to total price.
		char *productStrName=strtok(allProduct,delim2);
		char arr[20][20];
		int i=0;
		while(productStrName !=NULL){
			strcpy(arr[i],productStrName);
			productStrName=strtok(NULL,delim2);
			i++;
		}
		int index=0;
		int totalPrice=0;
		while(index<i){
			FILE *fp2;
			char str2[MAXCHAR];
			fp2 = fopen ("price.txt","r"); 
			if (fp2 == NULL){
				printf("Could not open file"); //If there is an error while file is opening, this message is given.
			}
			while (fgets(str2, MAXCHAR, fp2) != NULL){
				char delim3[] = ":";
				char *productName = strtok(str2,delim3);
				productName=trim(productName,NULL);
				char *productPriceChar=strtok(NULL,delim3);
				int productPrice = atoi (productPriceChar);
				if(strcmp(productName,arr[index]) == 0){
					totalPrice +=productPrice;
				}
			}
			index++;
		}
		printf("Total Price that is paid by customer %s: %d.\n",argv[1],totalPrice);
}