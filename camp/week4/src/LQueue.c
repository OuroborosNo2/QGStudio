#include "../inc/LQueue.h" 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 *  @name        : void InitLQueue(LQueue **Q)
 *    @description : ��ʼ������
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void InitLQueue(LQueue **Q){
    *Q = (LQueue*)malloc(sizeof(LQueue));
    (*Q)->front = NULL;
    (*Q)->rear = NULL;
    (*Q)->length = 0;
}

/**
 *  @name        : void DestoryLQueue(LQueue **Q)
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void DestroyLQueue(LQueue **Q){
	ClearLQueue(*Q);
    free(*Q);
    *Q = NULL;
    type = 0;
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q){
	return Q->length == 0 ? TRUE : FALSE;
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : �鿴��ͷԪ��
 *    @param         Q e ����ָ��Q,��������ָ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadLQueue(LQueue *Q, void *e){
	if(Q == NULL || IsEmptyLQueue(Q)){
        return FALSE;
    }else{
        memcpy(e,Q->front->data,dataSize);
        return TRUE;
    }
}

/**
 *  @name        : Status LengthLQueue(LQueue *Q)
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status LengthLQueue(LQueue *Q){
	if(Q == NULL){
        return FALSE;
    }else{
        printf("%d",Q->length);
        return TRUE;
    }
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ�Ϊ��
 */
Status EnLQueue(LQueue *Q, void *data){
    if(Q == NULL){
        return FALSE;
    }else{
        Node *n = (Node*)malloc(sizeof(Node));
        n->data = malloc(dataSize);
        memcpy(n->data,data,dataSize);
        if(IsEmptyLQueue(Q) == FALSE){
            Q->rear->next = n;
        }else{
            Q->front = n;
        }
        Q->rear = n;
        n->next = NULL;
        Q->length++;
        return TRUE;
    }
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q){
	if(Q == NULL || IsEmptyLQueue(Q)){
        return FALSE;
    }else{
        Node *p = Q->front;
        Q->front = p->next;
        free(p);
        p=NULL;
        Q->length--;
        return TRUE;
    }
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q){
        while(Q->front != NULL){
            DeLQueue(Q);
        }
        Q->rear = NULL;
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q)){
    if(Q == NULL || Q->front == NULL){
        return FALSE;
    }
    printf("[front]");
    Node *current = Q->front;
	while(current != NULL){
        foo(current->data);
        printf("->");
        current = current->next;
    }
    printf("[rear]\n");
    return TRUE;
}

/**
 *  @name        : void LPrint(void *q)
 *    @description : ��������
 *    @param         q ָ��q
 
 *  @notice      : None
 */
void LPrint(void *q){
	switch(type){
        case '1':
            printf("%d",*(int*)q);
            break;
        case '2':
            printf("%f",*(float*)q);
            break;
        case '3':
            printf("%c",*(char*)q);
            break;
        case '4':
            printf("%s",(char*)q);
            break;
    }
}

/**************************************************************
 *    End-Multi-Include-Prevent Section
 **************************************************************/



