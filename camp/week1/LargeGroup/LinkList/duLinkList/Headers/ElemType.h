#include<String.h>
#include<stdlib.h>
#include<stdio.h>
typedef struct ElemType{//元素类型
    
    char key[15];
    char value[15];
    
   /*
   int value;
   */
}ElemType;

int elem_equal(ElemType e1,ElemType e2){
    if(!strcmp(e1.key,e2.key) && !strcmp(e1.value,e2.value)){
        return 1;
    }
    /*
    if(e1.value == e2.value){
        return 1;
    }
    */
    return 0;
}

char * elem_toString(ElemType e){
    
    char *c = (char*)malloc(40);
    *c = '\0';
    //strcat(c,"key:");
    strcat(c,e.key);
    strcat(c,"|");
    //strcat(c,"value:");
    strcat(c,e.value);
    /*
    char *c;
    itoa(e.value,c,10);
    */
    return c;
}

void printElem(ElemType e){
    printf("%s",elem_toString(e));
}
