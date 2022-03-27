#ifndef MANU_H
#define MANU_H
#include "LinkStack.h"

LinkStack *s;
typedef enum ErrorType{SELECT,NUMBER,LETTER,RANGE} ErrorType;

void initLStackPage();
void isEmptyLStackPage();
void getTopLStackPage();
void clearLStackPage();
void destroyLStackPage();
void LStackLengthPage();
void pushLStackPage();
void popLStackPage();
void printError(ErrorType et);

#endif