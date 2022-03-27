#include "../head/manu.h"
#include <stdio.h>
#include <stdlib.h>

void homepage()
{
    fflush(stdin);
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            1����������ջ                \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            2���ж�ջ�Ƿ�Ϊ��            \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            3���õ�ջ��Ԫ��              \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            4�����ջ                    \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            5�����ջ����                \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            6����ջ                      \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            7����ջ                      \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            0��������ջ���˳�ϵͳ         \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    int select;
    scanf("%d", &select);
    getchar(); //��ȥ�س�
    switch (select)
    {
    case 1:
        initLStackPage();
        break;
    case 2:
        isEmptyLStackPage();
        break;
    case 3:
        getTopLStackPage();
        break;
    case 4:
        clearLStackPage();
        break;
    case 5:
        LStackLengthPage();
        break;
    case 6:
        pushLStackPage();
        break;
    case 7:
        popLStackPage();
        break;
    case 0:
        destroyLStack(&s);
        exit(0);
    default:
        printError(SELECT);
        break;
    }
    system("pause");
    homepage();
}
void initLStackPage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            ��������ջ\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    if (initLStack(&s))
    {
        printf("��ʼ����ջ�ɹ�\n");
    }
    else
    {
        printf("��ʼ����ջʧ�ܣ��������ڴ治��\n");
    }
    system("pause");
    homepage();
}
void isEmptyLStackPage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            �ж�ջ�Ƿ�Ϊ��\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    if (isEmptyLStack(s))
    {
        printf("��ջΪ��\n");
    }
    else
    {
        printf("��ջ��Ϊ��\n");
    }
    system("pause");
    homepage();
}
void getTopLStackPage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            �õ�ջ��Ԫ��\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    ElemType data;
    if (getTopLStack(s, &data))
    {
        printf("ջ��Ԫ��Ϊ��%c\n", data);
    }
    else
    {
        printf("��ջΪ��\n");
    }
    system("pause");
    homepage();
}
void clearLStackPage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            ���ջ\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    if (clearLStack(s))
    {
        printf("ջ�����\n");
    }
    else
    {
        printf("��������\n");
    }
    system("pause");
    homepage();
}
void LStackLengthPage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            ���ջ����\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    int length;
    if (LStackLength(s, &length))
    {
        printf("ջ����Ϊ��%d\n", length);
    }
    else
    {
        printf("��������\n");
    }
    system("pause");
    homepage();
}
void pushLStackPage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            ��ջ\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    printf("������Ҫ��ջ��Ԫ��(char)\n");
    ElemType data = (char)getchar();
    if (pushLStack(s, data))
    {
        printf("��ջ�ɹ�\n");
    }
    else
    {
        printf("��������\n");
    }
    system("pause");
    homepage();
}
void popLStackPage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            ��ջ\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    ElemType data;
    if (popLStack(s, &data))
    {
        printf("ջ��Ԫ��:%c �ѳ�ջ\n", data);
    }
    else
    {
        printf("��ջΪ��\n");
    }
    system("pause");
    homepage();
}
void printError(ErrorType et)
{
    switch (et)
    {
    case SELECT:
        printf("error:�������\n");
        break;
    case NUMBER:
        printf("error:ֻ����������(0~9)\n");
        break;
    case LETTER:
        printf("error:ֻ��������ĸ(a~z,A~Z)\n");
        break;
    case RANGE:
        printf("error:ֻ������0~100��\n");
        break;
    }
}
