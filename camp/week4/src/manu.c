#include "../inc/manu.h"
#include "../inc/binary_sort_tree.h"
#include <stdio.h>
#include <stdlib.h>

BinarySortTreePtr BSTP = NULL;
void homepage()
{
    fflush(stdin);
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            1、创建二叉树              \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            2、插入            \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            3、删除             \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            4、查找                   \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            5、遍历                \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            0、退出         \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    int select;
    scanf("%d", &select);
    getchar(); //��ȥ�س�
    switch (select)
    {
    case 1:
        initPage();
        break;
    case 2:
        insertPage();
        break;
    case 3:
        deletePage();
        break;
    case 4:
        searchPage();
        break;
    case 5:
        traversalPage();
        break;
    case 0:
        exit(0);
    default:
        printError(SELECT);
        break;
    }
    system("pause");
    homepage();
}
void initPage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            初始化二叉树\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    if (BST_init(&BSTP))
    {
        printf("初始化成功\n");
    }
    else
    {
        printf("初始化失败\n");
    }
    system("pause");
    homepage();
}
void insertPage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            插入\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    if (BSTP == NULL)
    {
        printf("二叉树未初始化\n");
    }
    else
    {
        ElemType e;
        printf("请输入要插入的数据：\n");
        scanf("%d", &e);
        if (BST_insert(BSTP, e))
        {
            printf("插入成功\n");
        }
        else
        {
            printf("插入失败，不能有重复数据\n");
        }
    }
}
void deletePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            删除\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    if (BSTP == NULL || BSTP->root == NULL)
    {
        printf("二叉树为空\n");
    }
    else
    {
        ElemType e;
        printf("请输入要删除的数据：\n");
        scanf("%d", &e);
        if (BST_delete(BSTP, e))
        {
            printf("删除成功\n");
        }
        else
        {
            printf("删除失败，无此数据\n");
        }
    }
}
void searchPage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t           查找\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    if (BSTP == NULL || BSTP->root == NULL)
    {
        printf("二叉树为空\n");
    }
    else
    {
        ElemType e;
        printf("请输入要查找的数据：\n");
        scanf("%d", &e);
        if (BST_search(BSTP, e))
        {
            printf("查找成功\n");
        }
        else
        {
            printf("查找失败，无此数据\n");
        }
    }
}
void traversalPage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            遍历\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    if (BSTP == NULL || BSTP->root == NULL)
    {
        printf("二叉树为空\n");
    }
    else
    {
        printf("请选择遍历方式：\n");
        printf("1、先序遍历（非递归）\n");
        printf("2、先序遍历（递归）\n");
        printf("3、中序遍历（非递归）\n");
        printf("4、中序遍历（递归）\n");
        printf("5、后序遍历（非递归）\n");
        printf("6、后序遍历（递归）\n");
        printf("7、层次遍历\n");
        int select;
        scanf("%d", &select);
        getchar(); //��ȥ�س�
        printf("\n");
        switch (select)
        {
        case 1:
            BST_preorderI(BSTP, printNode);
            break;
        case 2:
            BST_preorderR(BSTP, printNode);
            break;
        case 3:
            BST_inorderI(BSTP, printNode);
            break;
        case 4:
            BST_inorderR(BSTP, printNode);
            break;
        case 5:
            BST_postorderI(BSTP, printNode);
            break;
        case 6:
            BST_postorderR(BSTP, printNode);
            break;
        case 7:
            BST_levelOrder(BSTP, printNode);
            break;
        default:
            printError(SELECT);
            break;
        }
    }
}
void printError(ErrorType et)
{
    switch (et)
    {
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
