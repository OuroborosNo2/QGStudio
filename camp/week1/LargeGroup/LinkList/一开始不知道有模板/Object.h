#include<string.h>
#include<stdlib.h>
typedef struct Object{//元素类型
    //Person
    char name[20];
    int age;
}Object;

int equal(Object o1,Object o2){
    if(!strcmp(o1.name,o2.name) && o1.age==o2.age){
        return 1;
    }
    return 0;
}

char * toString(Object o){
    char *c = (char*)malloc(40);
    *c = '\0';
    strcat(c,"name:");
    strcat(c,o.name);
    strcat(c,",age:");
    char i[5];
    itoa(o.age,i,10);
    strcat(c,i);
    return c;
}
