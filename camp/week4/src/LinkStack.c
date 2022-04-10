#include "../inc/LinkStack.h" 
#include <stdio.h>
#include <stdlib.h>
//链栈

//初始化栈
Status initLStack(LinkStack **s){
    *s = (LinkStack*)malloc(sizeof(LinkStack));//申请内存空间失败则返回NULL
    if(*s == NULL){
        return ERROR;
    }
    (*s)->top = NULL;
    (*s)->count = 0;
    return SUCCESS;
}

//判断栈是否为空
Status isEmptyLStack(LinkStack *s){
    if(s == NULL){
        return ERROR;
    }
	return s->count == 0 ? SUCCESS : ERROR;
    //return s->top == NULL ? SUCCESS : ERROR;
}

//得到栈顶元素
Status getTopLStack(LinkStack *s,ElemType *e){
	if(s == NULL || isEmptyLStack(s) == 1){//栈为空
        return ERROR;
    }
    *e = s->top->data;
    return SUCCESS;
}

//清空栈
Status clearLStack(LinkStack *s){
    if(s == NULL){
        return ERROR;
    }
    StackNode *p;
    while(s->top != NULL){
        p = s->top;
        s->top = p->next;
        free(p);
        s->count--;
    }
    p = NULL;
    return SUCCESS;
}

//销毁栈
Status destroyLStack(LinkStack **s){
    if(*s == NULL){
        return ERROR;
    }
	clearLStack(*s);
    free(*s);
    *s = NULL;
    return SUCCESS;
}

//检测栈长度
Status LStackLength(LinkStack *s,int *length){
	if(s == NULL){
        return ERROR;
    }
    *length = s->count;
    return SUCCESS;
}

//入栈
Status pushLStack(LinkStack *s,ElemType data){
	if(s == NULL){
        return ERROR;
    }
    //要配合free使用所以手动分配内存，同时避免（不清楚）每次自动分配的地址都相同
    LinkStackPtr n = (LinkStackPtr)malloc(sizeof(StackNode));
    n->data = data;
    n->next = s->top;
    s->top = n;
    s->count++;
    return SUCCESS;
}

//出栈
Status popLStack(LinkStack *s,ElemType *data){
	if(s == NULL || isEmptyLStack(s) == 1){
        return ERROR;
    }
    *data = s->top->data;
    StackNode *p = s->top;
    s->top = s->top->next;
    free(p);
    p = NULL;
    s->count--;
    return SUCCESS;
}
