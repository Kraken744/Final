#include <Arduino.h>
#include <avr\io.h>
#include "tempConv.h"

int convToF (int celsius){

int tempF = -500;
tempF = (celsius * 9)/5 + 32;

    return tempF;
}

void convToStr(int num, char* str){
    
int n = num;
int i = 0;
bool isNeg = n<0;
unsigned int n1 = isNeg ? -n : n;

while(n1!=0){
    str[i++] = n1%10+'0';
    n1=n1/10;
}

if(isNeg)
    str[i++] = '-';

str[i] = '\0';

for(int t = 0; t < i/2; t++){
    str[t] ^= str[i-t-1];
    str[i-t-1] ^= str[t];
    str[t] ^= str[i-t-1];
}

if(n == 0){
    str[0] = '0';
    str[1] = '\0';
}   

return;
}