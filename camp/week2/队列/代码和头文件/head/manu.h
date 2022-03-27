#ifndef MANU_H
#define MANU_H
#include "LQueue.h"

LQueue *Q;
typedef enum ErrorType{SELECT,NUMBER,LETTER,RANGE} ErrorType;

void initLQueuePage();
void isEmptyLQueuePage();
void getHeadLQueuePage();
void clearLQueuePage();
void LengthLQueuePage();
void enLQueuePage();
void deLQueuePage();
void traverseLQueuePage();
void printError(ErrorType et);

#endif