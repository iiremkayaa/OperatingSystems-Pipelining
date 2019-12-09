#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include"time.h"
#include <unistd.h> 
#include <ctype.h>
#include"functions.c"
#define MAXCHAR 10000
#define READ_END 0
#define WRITE_END 1
void createPriceFile(){ //this functions creates price.txt that contains products and their random prices
	FILE *fp;
	char str[MAXCHAR];
	char* filename = "market.txt";
	fp = fopen(filename, "r");
	if (fp == NULL){
		printf("Could not open file %s",filename); //If there is an error while file is opening, this message is given.
	}
	char products[10000];
	srand(time(0)); 
	while (fgets(str, MAXCHAR, fp) != NULL){
		  	int len = strlen(str);
	    	str[len-2] = '\0'; //this operation deletes \n at the end of the line
			char delim2[] = ",";
			char *day = strtok(str, delim2);
			char *customer=strtok(NULL,delim2);
			char *productList=strtok(NULL,delim2);
			while(productList !=NULL){
				char *searchedProducts=trim(productList,NULL); //trim function removes space at the beginning and end of the string
				char *ret;
				append(searchedProducts,':');	
				ret = strstr(products, searchedProducts);
				if(ret == NULL){
					int price=printRandoms(1,30); //printRandoms assign random value to price of product
					char base_string[] = "";	
					char priceStr[50];
					sprintf(priceStr, "%s%d", base_string, price);
					strcat(products,productList);
					strcat(products,priceStr);
					strcat(products,"\n");
				}
				productList=strtok(NULL,delim2);
			}
	}
	fclose(fp);
	FILE * fp2;
	int i;
	fp2 = fopen ("price.txt","w");
	fprintf (fp2, products,i + 1);
	fclose (fp);
	printf("price.txt is created.\n");
}

void executeTask(char readmessage[]){
	char delimiter[] = "-";
		char *task = strtok(readmessage, delimiter);
		if(strcmp(task,"1")==0){
			char* args[] = {"./task1",NULL};
      		execv(args[0],args); //in this line task1 is executed
		}
		if(strcmp(task,"2")==0){ //if task number is 2,parent process sends product name to child process
			char *info2=strtok(NULL,delimiter);
			char allInfo[50]="";
			strcat(allInfo,info2);
			char *info2First=strtok(allInfo," ");
			char *info2Second=strtok(NULL," ");
			if(info2Second == NULL){ //this operation checks whether product name has more than one word.
				char* args[] = {"./task2",info2,NULL};
      			execv(args[0],args); //in this line task2 is executed
			}
			else{
				char* args[] = {"./task2",info2First,info2Second,NULL};
      			execv(args[0],args); //in this line task2 is executed
			}
		}if(strcmp(task,"3")==0){
			char *info3=strtok(NULL,delimiter); //if task number is 3, parent process sends customer id to child process
			char* args[] = {"./task3",info3,NULL};
      		execv(args[0],args); //in this line task3 is executed

		}if(strcmp(task,"4")==0){
			char* args[] = {"./task4",NULL};
      		execv(args[0],args); //in this line task4 is executed
			
		}if(strcmp(task,"5")==0){
			char* args[] = {"./task5",NULL};
      		execv(args[0],args); //in this line task5 is executed
		}
}
int main(int argc, char* argv[]){
	createPriceFile();
	char customerNumber[50]="";
	char pipeMessage[MAXCHAR]="";
	int pipeforChild1[2]; //there are 7 different pipe because parent process sends the task to child processes via pipes.
	int pipeforChild2[2]; //there are 7 childs because of 3 fork so number of pipe is 7.
	int pipeforChild3[2];
	int pipeforChild4[2];
	int pipeforChild5[2];
	int pipeforChild6[2];	
	int pipeforChild7[2];	
	int returnstatus1=pipe(pipeforChild1);
	int returnstatus2=pipe(pipeforChild2);
	int returnstatus3=pipe(pipeforChild3);
	int returnstatus4=pipe(pipeforChild4);
	int returnstatus5=pipe(pipeforChild5);
	int returnstatus6=pipe(pipeforChild6);
	int returnstatus7=pipe(pipeforChild7);
	if (returnstatus1 == -1) {  //If pipe failed, this message is given.
      printf("Unable to create pipe\n");
      return 1;
   }if (returnstatus2 == -1) { //If pipe failed, this message is given.
      printf("Unable to create pipe\n");
      return 1;
   }if (returnstatus3 == -1) { //If pipe failed, this message is given.
      printf("Unable to create pipe\n");
      return 1;
   }if (returnstatus4 == -1) { //If pipe failed, this message is given.
      printf("Unable to create pipe\n");
      return 1;
   }if (returnstatus5 == -1) { //If pipe failed, this message is given.
      printf("Unable to create pipe\n");
      return 1;
   }if (returnstatus6 == -1) { //If pipe failed, this message is given.
      printf("Unable to create pipe\n");
      return 1;
   }if (returnstatus7 == -1) { //If pipe failed, this message is given.
      printf("Unable to create pipe\n");
      return 1;
   }
   	pid_t pid1,pid2,pid3;
	pid_t child_pids[3];
	pid1=fork(); //Seven childs must be so there are three fork. if number of fork is n, there are 2^n-1 childs. 
	pid2=fork();
	pid3=fork();
	char readmessage1[MAXCHAR];
	char readmessage2[MAXCHAR];
	char readmessage3[MAXCHAR];
	char readmessage4[MAXCHAR];
	char readmessage5[MAXCHAR];
	char readmessage6[MAXCHAR];
	char readmessage7[MAXCHAR];
	int arr[]={1,2,3,4,5,6,7}; //This array represents array of child processes

	if (pid1 > 0 && pid2 > 0 && pid3 > 0) { //This section is done by parent process
		for(int i=0;i<7;i++){
			int randomIndex = rand() % (7-i);
			int processNumber = arr[randomIndex];
			int n = sizeof(arr)/sizeof(arr[0]); 
			int x = processNumber;
			n = deleteItem(arr, n-i, x); //in each while loop, one child process is selected and deleted from arr.
			int taskNumber=printRandoms(1,5);
			char enteredProduct[50];
			char taskNumberStr[50]; 
			if(taskNumber == 2){ //if the task number is 2, parent process take an input for product name
				printf("Enter a product:\n");
				scanf("%[^\n]%*c", enteredProduct); // this usage provides string that contains 
				char base_string[] = "";	 //space character.For example:EYE LINER.
				sprintf(taskNumberStr, "%s%d", base_string, taskNumber);
				strcat(taskNumberStr,"-");
				strcat(taskNumberStr,enteredProduct);
			}
			else if(taskNumber==3){ //if the task number is 3, parent process take an input for customer id
				printf("Enter a customer number:\n");
				scanf("%[^\n]%*c", customerNumber); 
				char base_string[] = "";	
				sprintf(taskNumberStr, "%s%d", base_string, taskNumber);
				strcat(taskNumberStr,"-");
				strcat(taskNumberStr,customerNumber);
			}
			else{
				char base_string[] = "";	
				sprintf(taskNumberStr, "%s%d", base_string, taskNumber);
				strcat(taskNumberStr,"-");
			}
			switch (processNumber)
				{
				case 1: // each task is sended to child process via pipeforChildX.X represents child number.
					write(pipeforChild1[1], taskNumberStr, sizeof(taskNumberStr)); //message is sent to pipe
					break;
				case 2: //If task number is 2 or 3, message in pipe includes information taken from user
					write(pipeforChild2[1], taskNumberStr, sizeof(taskNumberStr)); //message is sent to pipe
					break;
				case 3:
					write(pipeforChild3[1], taskNumberStr, sizeof(taskNumberStr)); //message is sent to pipe
					break;
				case 4:
					write(pipeforChild4[1], taskNumberStr, sizeof(taskNumberStr)); //message is sent to pipe
					break;
				case 5:
					write(pipeforChild5[1], taskNumberStr, sizeof(taskNumberStr)); //message is sent to pipe
					break;
				case 6:
					write(pipeforChild6[1], taskNumberStr, sizeof(taskNumberStr)); //message is sent to pipe
					break;
				case 7:
					write(pipeforChild7[1], taskNumberStr, sizeof(taskNumberStr)); //message is sent to pipe
					break;
				default:
					break;
				}		
		}
    }
	sleep(10); //To take an input from user sleep time is 10 second.
	if (pid1 > 0 && pid2 > 0 && pid3==0) { 
		printf("1. child is executing...\n");
		read(pipeforChild1[0], readmessage1, sizeof(readmessage6)); //message is retrieved from the pipe
		executeTask(readmessage1);
    }
	sleep(5); 
	if (pid1 > 0 && pid2 == 0 && pid3>0) {
		printf("2. child is executing...\n");
		read(pipeforChild2[0], readmessage2, sizeof(readmessage6)); //message is retrieved from the pipe
		executeTask(readmessage2);
    }
	sleep(5);
	if (pid1== 0 && pid2 > 0 && pid3>0) { 
		printf("3. child is executing...\n");
		read(pipeforChild3[0], readmessage3, sizeof(readmessage6)); //message is retrieved from the pipe
		executeTask(readmessage3);
    }	
	sleep(5);
	if (pid1 == 0 && pid2 == 0 && pid3>0) {
		printf("4. child is executing...\n");
		read(pipeforChild4[0], readmessage4, sizeof(readmessage6)); //message is retrieved from the pipe
		executeTask(readmessage4);
    }
	sleep(5);
	if (pid1 > 0 && pid2 == 0 && pid3==0) { 
		printf("5. child is executing...\n");
		read(pipeforChild5[0], readmessage5, sizeof(readmessage6)); //message is retrieved from the pipe
		executeTask(readmessage5);
    }
	sleep(5);
	if (pid1 == 0 && pid2 > 0 && pid3==0) { 
		printf("6. child is executing...\n");
		read(pipeforChild6[0], readmessage6, sizeof(readmessage6)); //message is retrieved from the pipe
		executeTask(readmessage6);
    }
	sleep(5);
	if (pid1 == 0 && pid2 == 0 && pid3==0) {
		printf("7. child is executing...\n");
		read(pipeforChild7[0], readmessage7, sizeof(readmessage6)); //message is retrieved from the pipe
		executeTask(readmessage7);
    }
	return 0;

}
