#include "../head/manu.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void homepage()
{
    fflush(stdin);
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            1�������¶���                \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            2���ж϶����Ƿ�Ϊ��            \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            3���õ���ͷԪ��              \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            4����ն���                    \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            5�������г���                \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            6�����                      \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            7������                      \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            8����������                  \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            0�����ٶ��в��˳�ϵͳ         \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    int select;
    scanf("%d", &select);
    getchar(); //��ȥ�س�
    switch (select)
    {
    case 1:
        initLQueuePage();
        break;
    case 2:
        isEmptyLQueuePage();
        break;
    case 3:
        getHeadLQueuePage();
        break;
    case 4:
        clearLQueuePage();
        break;
    case 5:
        LengthLQueuePage();
        break;
    case 6:
        enLQueuePage();
        break;
    case 7:
        deLQueuePage();
        break;
    case 8:
        traverseLQueuePage();
    case 0:
        DestroyLQueue(&Q);
        exit(0);
    default:
        printError(SELECT);
        break;
    }
    system("pause");
    homepage();
}
void initLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            �����¶���\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    InitLQueue(&Q);

    printf("������ö���������������(1:int/2:float/3:char/4:string):\n");
    type = getchar();
    getchar();
    if (type < '1' || type > '4')
    {
        printf("�������������\n");
        system("pause");
        initLQueuePage();
    }
    if (type == '4')
    {
        printf("�ַ�����󳤶ȣ�\n");
        scanf("%d",&dataSize);
    }
    else
    {
        switch (type)
        {
        case '1':
            dataSize = sizeof(int);
            break;
        case '2':
            dataSize = sizeof(float);
            break;
        case '3':
            dataSize = sizeof(char);
            break;
        }
    }
    printf("��ʼ�����гɹ�\n");

    system("pause");
    homepage();
}
void isEmptyLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            �ж϶����Ƿ�Ϊ��\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    if (IsEmptyLQueue(Q))
    {
        printf("����Ϊ��\n");
    }
    else
    {
        printf("���в�Ϊ��\n");
    }
    system("pause");
    homepage();
}
void getHeadLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            �õ���ͷԪ��\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    void *data = malloc(dataSize);
    if (GetHeadLQueue(Q, data))
    {
        printf("��ͷԪ��Ϊ��");
        LPrint(data);
        printf("\n");
    }
    else
    {
        printf("����Ϊ��\n");
    }
    system("pause");
    homepage();
}
void clearLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            ��ն���\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    ClearLQueue(Q);
    printf("���������\n");
    system("pause");
    homepage();
    
}
void LengthLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            �����г���\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    int length;
    if (LengthLQueue(Q))
    {
        
    }
    else
    {
        printf("��������\n");
    }
    system("pause");
    homepage();
}
void enLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            ���\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    void *data = malloc(dataSize);
    printf("������Ҫ��ӵ�Ԫ��");
    switch (type)
        {
        case '1':
            printf("(int)\n");
            scanf("%d",(int*)data);
            break;
        case '2':
            printf("(float)\n");
            scanf("%f",(float*)data);
            break;
        case '3':
            printf("(char)\n");
            scanf("%c",(char*)data);
            break;
        case '4':
            printf("(char[%d])\n",dataSize);
            scanf("%s",(char*)data);
            break;
        }
    
    if (EnLQueue(Q, data))
    {
        printf("��ӳɹ�\n");
    }
    else
    {
        printf("��������\n");
    }
    system("pause");
    homepage();
}
void deLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            ������\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    if (DeLQueue(Q))
    {
        printf("���ӳɹ�\n");
    }
    else
    {
        printf("����Ϊ��\n");
    }
    system("pause");
    homepage();
}
void traverseLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            ��������\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    if (TraverseLQueue(Q,LPrint))
    {
        
    }
    else
    {
        printf("����Ϊ��\n");
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
