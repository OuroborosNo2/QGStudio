#include<stdio.h>
#include<stdlib.h>
#include"Object.h"

typedef struct ListNode{//单链表
    Object data;
    struct ListNode *next;
    int index;//索引
}LNode;

LNode* createList();//新建链表，返回头结点head
void deleteList(LNode *head);//删除链表
int size(LNode *head);//获得链表长度
void addNode(LNode *head,Object data);//添加结点
LNode* getNode_d(LNode *head,Object data);//根据元素找结点,成功返回该结点，失败返回NULL warning:若有重复元素，get的是第一个
LNode* getNode_i(LNode *head,int index);//根据索引找结点,成功返回该结点，失败返回NULL
int removeNode_d(LNode *head,Object data);//根据元素删除结点,成功返回1，失败返回0 warning:若有重复元素，remove的是第一个
int removeNode_i(LNode *head,int index);//根据索引删除结点,成功返回1，失败返回0
int insertNode(LNode *head,int index,Object data);//在index后插入
int isEmpty(LNode *head);//链表是否为空

int main(){
    Object o1 = {"小明",16};
    Object o2 = {"小刚",15};
    Object o3 = {"小红",16};
    LNode *head = createList();
    printf("size:%d\n",size(head));
    addNode(head,o1);
    addNode(head,o2);
    insertNode(head,2,o3);//test插入
    printf("size:%d\n",size(head));
    int i;
    for(i=1;i<=3;i++){
        LNode *n = getNode_i(head,i);
        if(n != NULL){
            printf("the %dth element's %s\n",n->index,toString(n->data));
        }
    }
    removeNode_d(head,o1);//test元素删除
    for(i=1;i<=3;i++){
        LNode *n = getNode_i(head,i);
        if(n != NULL){
            printf("the %dth element's %s\n",n->index,toString(n->data));
        }
    }
    removeNode_i(head,2);//test索引删除
    for(i=1;i<=3;i++){
        LNode *n = getNode_i(head,i);
        if(n != NULL){
            printf("the %dth element's %s\n",n->index,toString(n->data));
        }
    }
    deleteList(head);
    return 0;
}

LNode* createList(){//新建链表，返回头结点head
    LNode *head = (LNode*)malloc(sizeof(LNode));
    head->index = 0;
    head->next = NULL;
    return head;
}

void deleteList(LNode *head){//删除链表
    LNode *current = head;//用以遍历的指针，走在前
    LNode *delP = head;//用以删除的指针，走在后
    while(current->next != NULL){
        current = current->next;
        free(delP);
        delP = current;
    }
    free(current);
    delP = NULL;
    current = NULL;
}

int size(LNode *head){//获得链表长度
    LNode *current = head;
    while(current->next != NULL){
        current = current->next;
    }
    return current->index;
}

void addNode(LNode *head,Object data){//添加结点
    LNode *current = head;
    while(current->next != NULL){//遍历至最后
        current = current->next;
    }
    LNode *n = (LNode*)malloc(sizeof(LNode));
    n->data = data;
    n->next = NULL;
    n->index = current->index+1;
    current->next = n;
    
}

LNode* getNode_d(LNode *head,Object data){//根据元素找结点,成功返回该结点，失败返回NULL warning:若有重复元素，get的是第一个
    LNode *current = head;
    while(current->next != NULL){
        current = current->next;
        if(&(current->data) == &data){//比较地址
            return current;
        }
    }
    return NULL;
}

LNode* getNode_i(LNode *head,int index){//根据索引找结点,成功返回该结点，失败返回NULL
    if(index < 0){
        return NULL;
    }else if(index == 0){
        return head;
    }
    LNode *current = head;
    while(current->next != NULL){
        current = current->next;
        if(current->index == index){
            return current;
        }
    }
    return NULL;
}

int removeNode_d(LNode *head,Object data){//根据元素删除结点,成功返回1，失败返回0 warning:若有重复元素，remove的是第一个
    LNode *current = head;
    LNode *p;//current的前一个
    while(current->next != NULL){
        p = current;
        current = current->next;
        if(equal(current->data,data)){
            p->next = current->next;//前后连接
            free(current);//释放（删除）目标
            current = p;
            while(current->next != NULL){
                current = current->next;
                current->index--;//更改后续索引
            }
            return 1;
        }
    }
    return 0;
}

int removeNode_i(LNode *head,int index){//根据索引删除结点,成功返回1，失败返回0
    if(index <= 0){//不允许删除头结点
         return 0;
    }
    LNode *p = getNode_i(head,index-1);//直接找到目标结点的前一个结点
    if(p != NULL){//找到了
        LNode *current = p->next;//目标
        p->next = current->next;//前后连接
        free(current);//释放（删除）目标
        current = p;
        while(current->next != NULL){
            current = current->next;
            current->index--;//更改后续索引
        }
        return 1;
    }else return 0;
}

int insertNode(LNode *head,int index,Object data){//在index后插入
    if(index <= 0){
         return 0;
    }
    LNode *current = getNode_i(head,index);
    if(current != NULL){//找到了
        //插入
        LNode *n = (LNode*)malloc(sizeof(LNode));
        n->data = data;
        n->next = current->next;
        current->next = n;
        n->index = current->index+1;
        //更改后续索引
        current = n;
        while(current->next != NULL){
            current = current->next;
            current->index++;
        }
        return 1;
    }else return 0;
}

int isEmpty(LNode *head){//链表是否为空
    if(head->next == NULL){
        return 1;
    }else return 0;
}

