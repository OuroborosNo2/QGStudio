//二叉排序树，会失衡

#define Node Node_LQueue
#define Status Status_LQueue
#include "LQueue.c"
#undef Node
#undef Status

#include"../inc/binary_sort_tree.h"
#undef Status

#define ElemType Node
#define Status Status_LinkStack
#include "LinkStack.c"
#undef ElemType
#undef Status

#define Status int

#include<stdio.h>
#include<stdlib.h>

LQueue *queue;
LinkStack *stack;

int elemCompare(ElemType e1, ElemType e2){
    return e1>e2 ? 1 : e1==e2 ? 0 : -1;
}

void printNode(NodePtr p){
    printf("%d",p->value);
}

Status BST_init(BinarySortTreePtr *p){
    *p = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
    if(*p != NULL){
        (*p)->root = NULL;
        return succeed;
    }else{
        return failed;
    }
}

Status BST_insert(BinarySortTreePtr BTSP, ElemType e){
    if(BTSP == NULL){
        return failed;
    }
    if(BTSP->root == NULL){//空树
        BTSP->root = (NodePtr)malloc(sizeof(Node));
        if(BTSP->root == NULL){
            return failed;
        }
        BTSP->root->value = e;
        BTSP->root->left = NULL;
        BTSP->root->right = NULL;
    }else{//非空树
        NodePtr iterator = BTSP->root;
        while(1){
            int com = elemCompare(e,iterator->value);
            switch(com){
                case 1://e大，往右走
                    if(iterator->right != NULL){
                        iterator = iterator->right;
                    }else{
                        iterator->right = (NodePtr)malloc(sizeof(Node));
                        iterator->right->value = e;
                        iterator->right->left = NULL;
                        iterator->right->right = NULL;
                        return succeed;
                    }
                    break;
                case -1://e小，往左走
                    if(iterator->left != NULL){
                        iterator = iterator->left;
                    }else{
                        iterator->left = (NodePtr)malloc(sizeof(Node));
                        iterator->left->value = e;
                        iterator->left->left = NULL;
                        iterator->left->right = NULL;
                        return succeed;
                    }
                    break;
                case 0://相等,插入失败
                    return failed;
            }
        }
    }
}

Status BST_delete(BinarySortTreePtr BTSP, ElemType e){
    if(BTSP == NULL){
        return failed;
    }
    NodePtr parent;
    NodePtr iterator = BTSP->root;
    while(iterator != NULL){
        int com = elemCompare(e,iterator->value);
        switch(com){
            case 1://e大，往右走
                parent = iterator;
                iterator = iterator->right;
                break;
            case -1://e小，往左走
                parent = iterator;
                iterator = iterator->left;
                break;
            case 0://相等,执行删除
                if(iterator->left == NULL){//左节点为空或者左右节点都为空
                    if(iterator == parent->left){//是父节点的左节点
                        parent->left = iterator->right;
                    }else{//是父节点的右节点
                        parent->right = iterator->right;
                    }
                    free(iterator);
                    iterator = NULL;
                }else if(iterator->right == NULL){//右节点为空
                    if(iterator == parent->left){//是父节点的左节点
                        parent->left = iterator->left;
                    }else{//是父节点的右节点
                        parent->right = iterator->left;
                    }
                    free(iterator);
                    iterator = NULL;
                }else{//两边都有子节点,找直接前驱/直接后继
                    ElemType *p = &iterator->value;//稍后直接修改值
                    parent = iterator;
                    iterator = iterator->left;
                    while(iterator->right != NULL){
                        parent = iterator;
                        iterator = iterator->right;
                    }
                    //此时的iterator就是直接前驱
                    if(iterator == parent->left){//是父节点的左节点
                        parent->left = iterator->left;
                    }else{//是父节点的右节点
                        parent->right = iterator->left;
                    }
                    *p = iterator->value;
                    free(iterator);
                    iterator = NULL;
                }
                return succeed;
        }
    }
    //没找到
    return failed;
}

Status BST_search(BinarySortTreePtr BTSP, ElemType e){
    if(BTSP == NULL){
        return failed;
    }
    NodePtr iterator = BTSP->root;
    while(iterator != NULL){
        int com = elemCompare(e,iterator->value);
        switch(com){
            case 1://e大，往右走
                iterator = iterator->right;
                break;
            case -1://e小，往左走
                iterator = iterator->left;
                break;
            case 0://相等
                return succeed;
        }
    }
    //没找到
    return failed;
}

Status BST_preorderI(BinarySortTreePtr BTSP, void (*visit)(NodePtr)){
    if(BTSP == NULL){
        return failed;
    }

    initLStack(&stack);
    Node iterator = *BTSP->root;//不要用指针，否则一会会影响二叉树中的值
    pushLStack(stack,iterator);

    while(!isEmptyLStack(stack)){
        popLStack(stack,&iterator);//会直接修改参数data指向的值
        visit(&iterator);
        printf("\n");

        if(iterator.right != NULL){
           pushLStack(stack,*iterator.right);
        }
        if(iterator.left != NULL){
           pushLStack(stack,*iterator.left);
        }
    }
    destroyLStack(&stack);
    return succeed;
}

Status BST_preorderR(BinarySortTreePtr BTSP, void (*visit)(NodePtr)){
    if(BTSP == NULL || BTSP->root == NULL){
        return failed;
    }
    NodePtr root = BTSP->root;

    visit(root);
    printf("\n");
    BinarySortTree temp;
    temp.root = root->left;
    BST_preorderR(&temp,visit);
    temp.root = root->right;
    BST_preorderR(&temp,visit);
    return succeed;
}

Status BST_inorderI(BinarySortTreePtr BTSP, void (*visit)(NodePtr)){
    if(BTSP == NULL){
        return failed;
    }

    initLStack(&stack);
    Node iterator = *BTSP->root;//不要用指针，否则一会会影响二叉树中的值
    pushLStack(stack,iterator);

    while(iterator.left != NULL){
        iterator = *iterator.left;
        pushLStack(stack,iterator);
    }

    while(!isEmptyLStack(stack)){
        popLStack(stack,&iterator);//会直接修改参数data指向的值
        visit(&iterator);
        printf("\n");

        if(iterator.right != NULL){
            iterator = *iterator.right;
            pushLStack(stack,iterator);
            while(iterator.left != NULL){
                iterator = *iterator.left;
                pushLStack(stack,iterator);
            }
        }
    }
    destroyLStack(&stack);
    return succeed;
}

Status BST_inorderR(BinarySortTreePtr BTSP, void (*visit)(NodePtr)){
    if(BTSP == NULL || BTSP->root == NULL){
        return failed;
    }
    NodePtr root = BTSP->root;

    BinarySortTree temp;
    temp.root = root->left;
    BST_inorderR(&temp,visit);
    visit(root);
    printf("\n");
    temp.root = root->right;
    BST_inorderR(&temp,visit);
    return succeed;
}

Status BST_postorderI(BinarySortTreePtr BTSP, void (*visit)(NodePtr)){
    if(BTSP == NULL){
        return failed;
    }

    initLStack(&stack);
    Node iterator = *BTSP->root;//不要用指针，否则一会会影响二叉树中的值
    pushLStack(stack,iterator);

    while(iterator.left != NULL){
        iterator = *iterator.left;
        pushLStack(stack,iterator);
    }

    while(!isEmptyLStack(stack)){
        Node prev = iterator;
        getTopLStack(stack,&iterator);
        if(iterator.right != NULL && iterator.right->value != prev.value){
            iterator = *iterator.right;
            pushLStack(stack,iterator);
            if(iterator.right != NULL){
                pushLStack(stack,*iterator.right);
            }
            while(iterator.left != NULL){
                iterator = *iterator.left;
                pushLStack(stack,iterator);
            }
        }
        popLStack(stack,&iterator);//会直接修改参数data指向的值
        visit(&iterator);
        printf("\n");
    }
    destroyLStack(&stack);
    return succeed;
}

Status BST_postorderR(BinarySortTreePtr BTSP, void (*visit)(NodePtr)){
    if(BTSP == NULL || BTSP->root == NULL){
        return failed;
    }
    NodePtr root = BTSP->root;

    BinarySortTree temp;
    temp.root = root->left;
    BST_postorderR(&temp,visit);
    temp.root = root->right;
    BST_postorderR(&temp,visit);
    visit(root);
    printf("\n");
    return succeed;
}

Status BST_levelOrder(BinarySortTreePtr BTSP, void (*visit)(NodePtr)){
    if(BTSP == NULL || BTSP->root == NULL){
        return failed;
    }

    InitLQueue(&queue);
    dataSize = sizeof(Node);
    Node iterator = *BTSP->root;//不要用指针，否则一会会影响二叉树中的值
    EnLQueue(queue,(void*)&iterator);

    while(!IsEmptyLQueue(queue)){
        GetHeadLQueue(queue,(void*)&iterator);//会直接修改参数e指向的值
        visit(&iterator);
        printf("\n");
        DeLQueue(queue);

        if(iterator.left != NULL){
           EnLQueue(queue,iterator.left);
        }
        if(iterator.right != NULL){
           EnLQueue(queue,iterator.right);
        }
    }
    DestroyLQueue(&queue);
    return succeed;
}


