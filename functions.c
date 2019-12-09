#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <ctype.h>

int countOccurrences(char * str, char * toSearch) //this functions return how many toSearch is in str
{
    int i, j, found, count;
    int stringLen, searchLen;
    stringLen = strlen(str);    
    searchLen = strlen(toSearch); 
    count = 0;
    for(i=0; i <= stringLen-searchLen; i++) {
        found = 1;
        for(j=0; j<searchLen; j++){
            if(str[i + j] != toSearch[j]){
                found = 0;
                break;
            }
        }
        if(found == 1){
            count++;
        }
    }
    return count;
}
char *rtrim(char *str, const char *seps) //this function does trim operation in right of the string
{
    int i;
    if (seps == NULL) {
        seps = " ";
    }
    i = strlen(str) - 1;
    while (i >= 0 && strchr(seps, str[i]) != NULL) {
        str[i] = '\0';
        i--;
    }
    return str;
}
char *ltrim(char *str, const char *seps) //this function does trim operation in left of the string
{
    size_t totrim;
    if (seps == NULL) {
        seps = " ";
    }
    totrim = strspn(str, seps);
    if (totrim > 0) {
        size_t len = strlen(str);
        if (totrim == len) {
            str[0] = '\0';
        }
        else {
            memmove(str, str + totrim, len + 1 - totrim);
        }
    }
    return str;
}
char *trim(char *str, const char *seps) //this function does trim operation that removes spaces at the end and beginning of the string
{
    return ltrim(rtrim(str, seps), seps);
}
int printRandoms(int lower, int upper){ // this function returns random value between lower and upper
        int num = (rand() % (upper - lower + 1)) + lower; 
        return num;
}
void append(char* s, char c) //this function appends char to char pointer
{
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}
int deleteItem(int arr[], int n, int x) //this functions delete x in arr that has n array size 
{ 
   int i; 
   for (i=0; i<n; i++) 
      if (arr[i] == x) 
         break;   
   if (i < n) 
   { 
     n = n - 1; 
     for (int j=i; j<n; j++) 
        arr[j] = arr[j+1]; 
   } 
  
   return n; 
} 
