#include<stdio.h>
#include<stdlib.h>
#include"Object.h"

typedef struct DoubleListNode{//双链表
    Object data;
    struct DoubleListNode *previous,*next;
    int index;//索引
}DLNode;

DLNode* createList();//新建链表，返回头结点head
void deleteList(DLNode *head);//删除链表
int size(DLNode *head);//获得链表长度
void addNode(DLNode *head,Object data);//添加结点
DLNode* getNode_d(DLNode *head,Object data);//根据元素找结点,成功返回该结点，失败返回NULL warning:若有重复元素，get的是第一个
DLNode* getNode_i(DLNode *head,int index);//根据索引找结点,成功返回该结点，失败返回NULL
int removeNode_d(DLNode *head,Object data);//根据元素删除结点,成功返回1，失败返回0 warning:若有重复元素，remove的是第一个
int removeNode_i(DLNode *head,int index);//根据索引删除结点,成功返回1，失败返回0
int insertNode(DLNode *head,int index,Object data);//在index后插入
int isEmpty(DLNode *head);//链表是否为空

int main(){
    Object o1 = {"小明",16};
    Object o2 = {"小刚",15};
    Object o3 = {"小红",16};
    DLNode *head = createList();
    printf("size:%d\n",size(head));
    addNode(head,o1);
    addNode(head,o2);
    insertNode(head,2,o3);//test插入
    printf("size:%d\n",size(head));
    int i;
    for(i=1;i<=3;i++){
        DLNode *n = getNode_i(head,i);
        if(n != NULL){
            printf("the %dth element's %s\n",n->index,toString(n->data));
        }
    }
    removeNode_d(head,o1);//test元素删除
    for(i=1;i<=3;i++){
        DLNode *n = getNode_i(head,i);
        if(n != NULL){
            printf("the %dth element's %s\n",n->index,toString(n->data));
        }
    }
    removeNode_i(head,2);//test索引删除
    for(i=1;i<=3;i++){
        DLNode *n = getNode_i(head,i);
        if(n != NULL){
            printf("the %dth element's %s\n",n->index,toString(n->data));
        }
    }
    deleteList(head);
    return 0;
}

DLNode* createList(){//新建链表，返回头结点head
    DLNode *head = (DLNode*)malloc(sizeof(DLNode));
    head->index = 0;
    head->previous = NULL;
    head->next = NULL;
    return head;
}

void deleteList(DLNode *head){//删除链表
    DLNode *current = head;
    while(current->next != NULL){
        current = current->next;
        free(current->previous);
    }
    free(current);
    current = NULL;
}

int size(DLNode *head){//获得链表长度
    DLNode *current = head;
    while(current->next != NULL){
        current = current->next;
    }
    return current->index;
}

void addNode(DLNode *head,Object data){//添加结点
    DLNode *current = head;
    while(current->next != NULL){//遍历至最后
        current = current->next;
    }
    DLNode *n = (DLNode*)malloc(sizeof(DLNode));
    n->data = data;
    n->previous = current;
    n->next = NULL;
    n->index = current->index+1;
    current->next = n;
}

DLNode* getNode_d(DLNode *head,Object data){//根据元素找结点,成功返回该结点，失败返回NULL warning:若有重复元素，get的是第一个
    DLNode *current = head;
    while(current->next != NULL){
        current = current->next;
        if(&(current->data) == &data){//比较地址
            return current;
        }
    }
    return NULL;
}

DLNode* getNode_i(DLNode *head,int index){//根据索引找结点,成功返回该结点，失败返回NULL
    if(index < 0){
        return NULL;
    }else if(index == 0){
        return head;
    }
    DLNode *current = head;
    while(current->next != NULL){
        current = current->next;
        if(current->index == index){
            return current;
        }
    }
    return NULL;
}

int removeNode_d(DLNode *head,Object data){//根据元素删除结点,成功返回1，失败返回0 warning:若有重复元素，remove的是第一个
    DLNode *current = head;
    while(current->next != NULL){
        current = current->next;
        if(&(current->data) == &data){//比较地址
            current->previous->next = current->next;//前后连接
            if(current->next != NULL){
                current->next->previous = current->previous;
            }
            DLNode *temp = current->previous;
            free(current);//释放（删除）目标
            current = temp;
            while(current->next != NULL){
                current = current->next;
                current->index--;//更改后续索引
            }
            return 1;
        }
    }
    return 0;
}

int removeNode_i(DLNode *head,int index){//根据索引删除结点,成功返回1，失败返回0
    if(index <= 0){//不允许删除头结点
         return 0;
    }
    DLNode *current = getNode_i(head,index);//直接找到目标结点
    if(current != NULL){//找到了
        current->previous->next = current->next;//前后连接
        if(current->next != NULL){
            current->next->previous = current->previous;
        }
        DLNode *temp = current->previous;
        free(current);//释放（删除）目标
        current = temp;
        while(current->next != NULL){
            current = current->next;
            current->index--;//更改后续索引
        }
        return 1;
    }else return 0;
}

int insertNode(DLNode *head,int index,Object data){//在index后插入
    if(index <= 0){
         return 0;
    }
    DLNode *current = getNode_i(head,index);
    if(current != NULL){//找到了
        //插入
        DLNode *n = (DLNode*)malloc(sizeof(DLNode));
        n->data = data;
        n->previous = current;
        n->next = current->next;

        if(current->next != NULL){
            current->next->previous = n;
        }
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

int isEmpty(DLNode *head){//链表是否为空
    if(head->next == NULL){
        return 1;
    }else return 0;
}

