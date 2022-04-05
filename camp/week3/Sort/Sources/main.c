#include "../Headers/sort.h"
#include "../Headers/testData.h"

//#include "sort.c"
//#include "testData.c"
#include<stdio.h>

#define QUANTITY 200000

int main(){
    while(1){
        int quantity;//数据量大小
        int times;//排序次数
        fflush(stdin);
        system("cls");
        printf("请选择模式\n");
        printf("1.大数据量\n");
        printf("2.大量小数据量\n");
        printf("3.自定义\n");
        char select = getchar();
        getchar();
        if(select == '1'){
            testTime(10000,1);
            testTime(50000,1);
            testTime(200000,1);
        }else if(select == '2'){
            testTime(100,100000);
        }else if(select == '3'){
            printf("请输入数据量大小：\n");
            scanf("%d",&quantity);
            printf("请输入排序次数：\n");
            scanf("%d",&times);
            testTime(quantity,times);
        }else{
            printf("输入错误！\n");
            continue;
        }

        system("pause");
    }

    /*int *arr = (int*)malloc(sizeof(int)*200000);
    remove("data.dat");
    createData(1,200000,200000,"data");
    readData("data",arr);
    int i;
    printf("-------------------------------\n");
    for(i=0;i<200000;i++){
        printf("%d\n",arr[i]);
    }
    printf("-------------------------------\n");
    CountSort(arr,200000,200000);
    for(i=0;i<200000;i++){
        printf("%d\n",arr[i]);
    }
    printf("-----------sorted--------------\n");
    getchar();*/
    //system("pause");
    return 1;
}
