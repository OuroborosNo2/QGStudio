
#include "../Headers/testData.h"
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


int createData(int min,int max,unsigned int quantity,char *dataIndex){
    if(max<=min || quantity==0){//参数不合规,max须大于min
        return 0;
    }
    srand((unsigned int)time(0));
    int range = max-min+1;
    
    char str[30] = "";
    strcat(str,dataIndex);
    strcat(str,".dat");
    FILE *f;
    if(fopen(str,"r") != NULL){//文件已存在
        remove(str);
    }
    f = fopen(str,"w");//不存在则新建
    fprintf(f,"------------------------dataParams-------------------------\n");
    fprintf(f,"min:%d\n",min);
    fprintf(f,"max:%d\n",max);
    fprintf(f,"quantity:%d\n",quantity);
    fprintf(f,"-----------------------------------------------------------\n\n");

    int i;
    for(i=0;i<quantity;i++){
        fprintf(f,"%d\n",rand()%range+min);
    }

    fclose(f);
    return 1;
}


void readData(char *dataIndex,int *arr){
    FILE *f;
    char str[30] = "";
    strcat(str,dataIndex);
    strcat(str,".dat");
    f=fopen(str,"r");
    if(f == NULL){//文件不存在
        return;
    }
    int quantity;
    char line[1024];
    fgets(line,1024,f);
    fgets(line,1024,f);
    fgets(line,1024,f);
    fscanf(f,"quantity:%d\n",&quantity);
    fgets(line,1024,f);
    fgets(line,1024,f);

    int i;
    //int arr[quantity];//static修饰，但static修饰的前提是数组大小函数里面的局部数组在函数结束后会被清除，必须要手动为其开辟空间或者用是常量
    //arr = (int*)malloc(sizeof(int)*quantity);
    for(i=0;i<quantity;i++){
       fscanf(f,"%d\n",&arr[i]);
    }
    
    /*测试
    for(i=0;i<10;i++){
        printf("%d\n",arr[i]);
    }*/
    
    //return arr;
}


void testTime(int quantity,int times){
    remove("data.dat");
    createData(1,quantity,quantity,"data");

    //int arr[quantity];
    int *arr = (int*)malloc(sizeof(int)*quantity);
    
    int i;
    clock_t start;
    clock_t end;
    printf("%d * %d次排序花费时间：\n",quantity,times);

    start = clock();
    for(i=0;i<times;i++){
        readData("data",arr);
        insertSort(arr,quantity);
    }
    end = clock();
    printf("插入排序用时：%dms\n",end-start);

    int temp[quantity/2+1]; 
    start = clock();
    for(i=0;i<times;i++){
        readData("data",arr);
        MergeSort(arr,0,quantity-1,temp);
    }
    end = clock();
    printf("归并排序用时：%dms\n",end-start);

    start = clock();
    for(i=0;i<times;i++){
        readData("data",arr);
        QuickSort_Recursion(arr,0,quantity-1);
    }
    end = clock();
    printf("快速排序用时：%dms\n",end-start);

    start = clock();
    for(i=0;i<times;i++){
        readData("data",arr);
        CountSort(arr,quantity,quantity);
    }
    end = clock();
    printf("计数排序用时：%dms\n",end-start);

    start = clock();
    for(i=0;i<times;i++){
        readData("data",arr);
        RadixCountSort(arr,quantity);
    }
    end = clock();
    printf("基数排序用时：%dms\n",end-start);
    
    

    printf("-----------------------------------------------------\n");
    free(arr);
    remove("data.dat");
}