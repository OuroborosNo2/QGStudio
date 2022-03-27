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
    printf("\t\t\t\t            1、创建新队列                \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            2、判断队列是否为空            \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            3、得到队头元素              \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            4、清空队列                    \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            5、检测队列长度                \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            6、入队                      \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            7、出队                      \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            8、遍历队列                  \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t            0、销毁队列并退出系统         \n");
    printf("\t\t\t\t                                        \n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    int select;
    scanf("%d", &select);
    getchar(); //吃去回车
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
    printf("\t\t\t\t            创建新队列\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    InitLQueue(&Q);

    printf("请输入该队列所存数据类型(1:int/2:float/3:char/4:string):\n");
    type = getchar();
    getchar();
    if (type < '1' || type > '4')
    {
        printf("输入错误，请重试\n");
        system("pause");
        initLQueuePage();
    }
    if (type == '4')
    {
        printf("字符串最大长度：\n");
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
    printf("初始化队列成功\n");

    system("pause");
    homepage();
}
void isEmptyLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            判断队列是否为空\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");
    if (IsEmptyLQueue(Q))
    {
        printf("队列为空\n");
    }
    else
    {
        printf("队列不为空\n");
    }
    system("pause");
    homepage();
}
void getHeadLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            得到队头元素\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    void *data = malloc(dataSize);
    if (GetHeadLQueue(Q, data))
    {
        printf("队头元素为：");
        LPrint(data);
        printf("\n");
    }
    else
    {
        printf("队列为空\n");
    }
    system("pause");
    homepage();
}
void clearLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            清空队列\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    ClearLQueue(Q);
    printf("队列已清空\n");
    system("pause");
    homepage();
    
}
void LengthLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            检测队列长度\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    int length;
    if (LengthLQueue(Q))
    {
        
    }
    else
    {
        printf("发生错误\n");
    }
    system("pause");
    homepage();
}
void enLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            入队\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    void *data = malloc(dataSize);
    printf("请输入要入队的元素");
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
        printf("入队成功\n");
    }
    else
    {
        printf("发生错误\n");
    }
    system("pause");
    homepage();
}
void deLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            出队列\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    if (DeLQueue(Q))
    {
        printf("出队成功\n");
    }
    else
    {
        printf("队列为空\n");
    }
    system("pause");
    homepage();
}
void traverseLQueuePage()
{
    system("cls");
    printf("\t\t\t\t*****************************************\n");
    printf("\t\t\t\t            遍历队列\n");
    printf("\t\t\t\t*****************************************\n");
    printf("\n");

    if (TraverseLQueue(Q,LPrint))
    {
        
    }
    else
    {
        printf("队列为空\n");
    }
    system("pause");
    homepage();
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
