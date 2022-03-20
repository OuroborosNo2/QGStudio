#include<stdio.h>
#include "linkedList.h"

LinkedList L;
typedef enum ErrorType{SELECT,NUMBER,LETTER,RANGE} ErrorType;

void homepage(){
    fflush(stdin);
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            1、创建新链表                \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            2、插入新节点                \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            3、输出链表                  \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            4、将链表反向                \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            5、找到单链表中点            \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            6、判断是否成环              \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            7、删除节点取值              \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            8、奇偶反转                  \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            9、查询数据是否在表中         \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            10、构造循环链表             \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            0、删除链表并退出系统         \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    char select = getchar();
    getchar();//吃去回车
    switch(select){
        case '1':
            initListPage();
            break;
        case '2':
            insertListPage();
            break;
        case '3':
            printListPage();
            break;
        case '4':
            reverseListPage();
            break;
        case '5':
            FindMidNodePage();
            break;
        case '6':
            isLoopListPage();
            break;
        case '7':
            deleteListPage();
            break;
        case '8':
            reverseEvenListPage();
            break;
        case '9':
            searchListPage();
            break;
        case '10':
            makeLoopListPage();
            break;
        case '0':
            DestroyList(&L);
            exit(0);
        default:
            printError(SELECT);
            break;
    }
    system("pause");
    homepage();
}
void initListPage(){
        system("cls");
            printf("\t\t\t\t*****************************************\n");
            printf("\t\t\t\t            创建新链表\n");
            printf("\t\t\t\t*****************************************\n");
            printf("\n");
            if(InitList(&L)){
                printf("初始化链表成功\n");
            }else{
                printf("初始化链表失败，可能是内存不足\n");
                system("pause");
                homepage();
            }
            printf("请输入你要构建的节点数:");
            int num,i;
            scanf("%d",&num);
            LNode *p = L;
            for(i=1;i<=num;i++){
                printf("请输入第%d个节点的数据(格式：key value):\n",i);
                char key[15],value[15];
                scanf("%s %s",key,value);
                //字符数组不能直接赋值
                ElemType *e = (ElemType*)malloc(sizeof(ElemType));
                strcpy(e->key,key);
                strcpy(e->value,value);
                LNode *q = (LNode*)malloc(sizeof(LNode));
                q->data = *e;
                InsertList(p,q);
                p = q;
            }
}
void insertListPage(){
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            插入新节点\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    printf("请输入你要插入到的位置的前一个节点的数据(格式：key value):\n");
    char key1[15],value1[15];
                scanf("%s %s",key1,value1);
                //字符数组不能直接赋值
                ElemType *e1 = (ElemType*)malloc(sizeof(ElemType));
                strcpy(e1->key,key1);
                strcpy(e1->value,value1);
    LNode *current = L;
    while(current->next != NULL){
		current = current->next;
		if(elem_equal(*e1,current->data)){ 
            printf("请输入你要插入节点的数据\n");
            char key2[15],value2[15];
                scanf("%s %s",key2,value2);
                //字符数组不能直接赋值
                ElemType *e2 = (ElemType*)malloc(sizeof(ElemType));
                strcpy(e2->key,key2);
                strcpy(e2->value,value2);
                LNode *q = (LNode*)malloc(sizeof(LNode));
                q->data = *e2;
            InsertList(current,q);
			return;
		}
	}
    printf("该数据不存在表中！\n");
}
void searchListPage(){
        system("cls");
            printf("\t\t\t\t*****************************************\n");
            printf("\t\t\t\t            查询数据是否在表中\n");
            printf("\t\t\t\t*****************************************\n");
            printf("\n");

            printf("请输入你要查找的节点的数据(格式：key value):\n");
            char key[15],value[15];
                scanf("%s %s",key,value);
                //字符数组不能直接赋值
                ElemType *e = (ElemType*)malloc(sizeof(ElemType));
                strcpy(e->key,key);
                strcpy(e->value,value);
            if(SearchList(L,*e)){
                printf("该数据存在表中！\n");
            }else{
                printf("该数据不存在表中！\n");
            }
}
void printListPage(){
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            输出链表\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    if(IsLoopList(L)){
        printf("链表成环，无法操作！\n");
    }else{
    printf("当前链表为:\n");
    TraverseList(L,printElem);
    printf("NULL\n");
    }
}
void reverseListPage(){
    
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            将链表反向\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    if(IsLoopList(L)){
        printf("链表成环，无法操作！\n");
    }else{
    if(ReverseList(&L)){
        printf("反序成功\n");
    }else{
        printf("反序失败\n");
    }

    }
}
void FindMidNodePage(){
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            找到单链表中点\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    if(IsLoopList(L)){
        printf("链表成环，无法操作！\n");
    }else{
        LNode *node = FindMidNode(&L);
        if(node != NULL){
            printElem(node->data);
            printf("\n");
        }else{
            printf("操作失败！\n");
        }
    }
}
void isLoopListPage(){
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            判断是否成环\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    if(IsLoopList(L)){
        printf("链表成环！\n");
    }else{
        printf("链表未成环！\n");
    }
}
void makeLoopListPage(){
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            构造循环链表\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    if(IsLoopList(L)){
        printf("链表已成环！\n");
    }else{
    LNode *current = L;
    while(current->next != NULL){
		current = current->next;
	}
    current->next = L;
    printf("构造成功\n");

    }
}
void deleteListPage(){
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            删除节点取值\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    if(IsLoopList(L)){
        printf("链表成环，无法操作！\n");
    }else{
        printf("请输入你要删除后节点的前节点数据(格式：key value):\n");
    char key[15],value[15];
                scanf("%s %s",key,value);
                //字符数组不能直接赋值
                ElemType *e = (ElemType*)malloc(sizeof(ElemType));
                strcpy(e->key,key);
                strcpy(e->value,value);
    LNode *current = L;
    while(current->next != NULL){
		current = current->next;
		if(elem_equal(*e,current->data)){ 
            ElemType assign;
            DeleteList(current,&assign);
            printf("已经成功删除数据%s\n",elem_toString(assign));
			return;
		}
	}
    printf("该数据不存在表中！\n");
    }
}
void reverseEvenListPage(){
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            奇偶反转\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    if(IsLoopList(L)){
        printf("链表已成环！\n");
    }else{
        ReverseEvenList(&L);
    }
}
void printError(ErrorType et){
    switch(et){
        case SELECT:
            printf("error:输入错误！\n");
            break;
        case NUMBER:
            printf("error:只能输入数字(0~9)\n");
            break;
        case LETTER:
            printf("error:只能输入字母(a~z,A~Z)\n"); 
            break;
        case RANGE:
            printf("error:只能输入0~100！\n");
            break;
    }
}