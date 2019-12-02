#include <Arduino.h>
#include <avr/io.h>
#include "tempConv.h"

int convToF (int celsius){

int tempF = -500;
tempF = (celsius * 9)/5 + 32;

    return tempF;
}