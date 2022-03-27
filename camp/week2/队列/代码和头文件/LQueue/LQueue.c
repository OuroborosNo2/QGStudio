#include "../head/LQueue.h" 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 *  @name        : void InitLQueue(LQueue **Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
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
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
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
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q){
	return Q->length == 0 ? TRUE : FALSE;
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q e 队列指针Q,返回数据指针e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
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
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status LengthLQueue(LQueue *Q){
	if(Q == NULL){
        return FALSE;
    }else{
        printf("队列长度为：%d",Q->length);
        return TRUE;
    }
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否为空
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
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
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
 *    @description : 清空队列
 *    @param         Q 队列指针Q
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
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
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
 *    @description : 操作函数
 *    @param         q 指针q
 
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



