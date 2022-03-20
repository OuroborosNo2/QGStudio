/***************************************************************************************
 *	File Name				:	linkedList.h
 *	CopyRight				:	2020 QG Studio
 *	SYSTEM					:   win10
 *	Create Data				:	2020.3.28
 *
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *
 *
 ***************************************************************************************/

 /**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include<stdlib.h>
#include"ElemType.h"

/**************************************************************
*	Macro Define Section
**************************************************************/

#define OVERFLOW -1

/**************************************************************
*	Struct Define Section
**************************************************************/

// define element type
//typedef int ElemType;

// define struct of linked list
typedef struct LNode {
	ElemType data;
  	struct LNode *next;
} LNode, *LinkedList;

// define Status
typedef enum Status {
	ERROR,
	SUCCESS
} Status;


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : Status InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList(LinkedList *L){
	*L = (LinkedList)malloc(sizeof(LNode));
	if(*L == NULL){//内存分配不成功
		return ERROR;
	}else{
    	(*L)->next = NULL;
    	return SUCCESS;
	}
}

/**
 *  @name        : void DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void DestroyList(LinkedList *L){
	/*if(*L == NULL || L == NULL){
		return;
	}*/
	LNode *current = *L;//用以遍历的指针，走在前
    LNode *delP = current;//用以删除的指针，走在后
    while(current->next != NULL){
        current = current->next;
        free(delP);
        delP = current;
    }
    free(current);
    delP = NULL;
    current = NULL;
	*L = NULL;
	L = NULL;
}

/**
 *  @name        : Status InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : Status
 *  @notice      : None
 */
Status InsertList(LNode *p, LNode *q){
	if(p == NULL){
		return ERROR;
	}else if(q != NULL){
		q->next = p->next;
	}
	p->next = q;
	return SUCCESS;
}

/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : Status
 *  @notice      : None
 */
Status DeleteList(LNode *p, ElemType *e){
	/*if(p == NULL){
		return ERROR;
	}*/
	if(p->next != NULL){
		LNode *temp = p->next;
		*e = temp->data;
		p->next = temp->next;
		free(temp);
		return SUCCESS;
	}
	return ERROR;
}

/**
 *  @name        : void TraverseList(LinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : None
 *  @notice      : None
 */
void TraverseList(LinkedList L, void (*visit)(ElemType e)){
	/*if(L == NULL){
		return;
	}*/
	while(L->next != NULL){
		L = L->next;
		visit(L->data);
	}
}

/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */
Status SearchList(LinkedList L, ElemType e){
	/*if(L == NULL){
		return ERROR;
	}*/
	while(L->next != NULL){
		L = L->next;
		if(elem_equal(e,L->data)){
			return SUCCESS;
		}
	}
	return ERROR;
}

/**
 *  @name        : Status ReverseList(LinkedList *L)
 *	@description : reverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status ReverseList(LinkedList *L){
	//递归实现
	if(*L == NULL || (*L)->next == NULL){
		return ERROR;
	}
	LNode *current = (*L)->next;
	if(current->next != NULL){//往后一个结点存在
		if(current->next->next != NULL){//往后第二结点存在
			ReverseList(&current->next);
			(*L)->next = NULL;//目的是将反转后的最后一个指向NULL
			current->next->next = current;
			return SUCCESS;
		}else{//往后第一个结点已是链表末尾 或 全链表只有两个结点（包括头结点）
			(*L)->next = current->next;
			current->next->next = current;
			return SUCCESS;
		}
	}else{//全链表只有一个节点，反转不反转都一样
		return SUCCESS;
	}	

	/*
	//TODO迭代实现
	LNode *o,*p,*q;	
	if(*L != NULL){//第一个
		o = *L;
		if(o->next !=NULL){//第二个
			p = o->next;
		}else{

		}
	}else{
		return ERROR;
	}
	*/																
}

/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L){
	/*if(L == NULL){
		return ERROR;
	}*/
	LNode *slow = L,*fast = L;
	while(fast->next != NULL || fast->next->next != NULL){
		slow = slow->next;
		fast = fast->next->next;
		if(slow == fast){
			return SUCCESS;
		}
	}
	return ERROR;

}

/**
 *  @name        : LNode* ReverseEvenList(LinkedList *L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish
 */
LNode* ReverseEvenList(LinkedList *L){
	LNode *first = *L;
	while(first->next != NULL){
		LNode *second = first->next;
		if(second->next != NULL){
			LNode *third = second->next;
			second->next = third->next;
			third->next = second;
			first->next = third;
			first = third;
		}
	}
	return (*L);
}

/**
 *  @name        : LNode* FindMidNode(LinkedList *L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish
 */
LNode* FindMidNode(LinkedList *L){
	LNode *slow = *L,*fast = *L;
	while(fast->next != NULL){
		slow = slow->next;
		if(fast->next->next != NULL){
			fast = fast->next->next;
		}else{
			fast = fast->next;
		}
	}
	return slow;
}

 /**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif
