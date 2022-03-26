#include "LinkStack.h" 
#include <stdio.h>
#include <stdlib.h>
//��ջ

//��ʼ��ջ
Status initLStack(LinkStack **s){
    *s = (LinkStack*)malloc(sizeof(LinkStack));//�����ڴ�ռ�ʧ���򷵻�NULL
    if(*s == NULL){
        return ERROR;
    }
    (*s)->top = NULL;
    (*s)->count = 0;
    return SUCCESS;
}

//�ж�ջ�Ƿ�Ϊ��
Status isEmptyLStack(LinkStack *s){
    if(s == NULL){
        return ERROR;
    }
	return s->count == 0 ? SUCCESS : ERROR;
    //return s->top == NULL ? SUCCESS : ERROR;
}

//�õ�ջ��Ԫ��
Status getTopLStack(LinkStack *s,ElemType *e){
	if(s == NULL || isEmptyLStack(s) == 1){//ջΪ��
        return ERROR;
    }
    *e = s->top->data;
    return SUCCESS;
}

//���ջ
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

//����ջ
Status destroyLStack(LinkStack **s){
    if(*s == NULL){
        return ERROR;
    }
	clearLStack(*s);
    free(*s);
    *s = NULL;
    return SUCCESS;
}

//���ջ����
Status LStackLength(LinkStack *s,int *length){
	if(s == NULL){
        return ERROR;
    }
    *length = s->count;
    return SUCCESS;
}

//��ջ
Status pushLStack(LinkStack *s,ElemType data){
	if(s == NULL){
        return ERROR;
    }
    //Ҫ���freeʹ�������ֶ������ڴ棬ͬʱ���⣨�������ÿ���Զ�����ĵ�ַ����ͬ��
    LinkStackPtr n = (LinkStackPtr)malloc(sizeof(StackNode));
    n->data = data;
    n->next = s->top;
    s->top = n;
    s->count++;
    return SUCCESS;
}

//��ջ
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
