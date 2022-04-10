#ifndef MANU_H
#define MANU_H

typedef enum ErrorType{SELECT,NUMBER,LETTER,RANGE} ErrorType;

void initPage();
void insertPage();
void deletePage();
void searchPage();
void traversalPage();
void printError(ErrorType et);

#endif