#include "../Headers/sort.h"
#include <math.h>
#include<stdlib.h>
#include<stdio.h>
//所有都是正序排序
int mypow(int n){
    int i,result=1;
    for(i=0;i<n;i++){
        result *= 10;
    }
    return result;
}
void insertSort(int *a, int n)
{
    int i, j, k;
    for (i = 1; i < n; i++)
    {
        int toInsert = a[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (toInsert >= a[j])
            { //插在a[j]后
                for (k = i; k > j + 1; k--)
                { //后移
                    a[k] = a[k - 1];
                }
                a[j + 1] = toInsert;
                break;
            }
            else if (j == 0)
            { //插在最前面
                for (k = i; k > 0; k--)
                { //后移
                    a[k] = a[k - 1];
                }
                a[0] = toInsert;
                break;
            }
        }
    }
}
void MergeArray(int *a, int begin, int mid, int end, int *temp)
{ //不理解begin用来干嘛,我用mid存合并前a的最后一位，end存temp最后一位
    int arr[mid + end + 2];
    int t1 = 0, t2 = 0, i;
    for (i = 0; i < mid + end + 2; i++)
    {
        if (t1 == mid + 1)
        { //其中一个数组遍历完则直接把另一个数组全接上
            arr[i] = temp[t2++];
        }
        else if (t2 == end + 1)
        {
            arr[i] = a[t1++];
        }
        else if (a[t1] <= temp[t2])
        {
            arr[i] = a[t1++];
        }
        else
        {
            arr[i] = temp[t2++];
        }
    }
    for (i = 0; i < mid + end + 2; i++)
    {
        a[i] = arr[i];
    }
}
void MergeSort(int *a, int begin, int end, int *temp)
{
    int i, t = 0;
    //将a的后半部分分去temp
    for (i = end / 2 + 1; i <= end; i++)
    {
        temp[t++] = a[i];
    }
    end = end / 2; //新的end（属于a）
    t--;           //此时t即temp的最后一位

    if (end != 0)
    {
        //将a继续向下对半分
        int arr1[end / 2 + 1];
        MergeSort(a, 0, end, arr1);
    }
    if (t != 0)
    {
        //将temp继续向下对半分
        int arr2[t / 2 + 1];
        MergeSort(temp, 0, t, arr2);
    }

    MergeArray(a, 0, end, t, temp); //把temp接在a后
}
void QuickSort_Recursion(int *a, int begin, int end)
{
    int i,j;    //定义变量为基本整型
    i = begin;    //将每组首个元素赋给i
    j = end;    //将每组末尾元素赋给j
    a[0]=a[begin];    //设置基准值
    while(i<j)
    {
        while(i<j&&a[0]<a[j])
        j--;    //位置左移
        if(i<j)
        {
            a[i]=a[j];    //将a[j]放到a[i]的位置上
            i++;    //位置右移
        }
        while(i<j&&a[i]<=a[0])
            i++;    //位置右移
        if(i<j)
        {
            a[j]=a[i];    //将大于基准值的a[j]放到a[i]位置
            j--;    //位置左移
        }
    }
    a[i]=a[0];    //将基准值放入指定位置
    if (begin<i)
        QuickSort_Recursion(a,begin,j-1);    //对分割出的部分递归调用qusort()函数
    if (i<end)
        QuickSort_Recursion(a,j+1,end);
    return;

}
int Partition(int *a, int begin, int end)
{ //返回三数取中法所取值的元素位置
    int left = a[begin];
    int right = a[end];
    int mid = a[(begin + end) / 2];
    if ((left > mid && left < right) || (left > right && left < mid))
    {
        return begin;
    }
    if ((mid > left && mid < right) || (mid > right && mid < left))
    {
        return (begin + end) / 2;
    }
    if ((right > mid && right < left) || (right > left && right < mid))
    {
        return end;
    }
    return begin; //有两数相等,三数取中法用不了
}
void CountSort(int *a, int size, int max)
{
    int *bucket = (int*)malloc(sizeof(int)*(max+1));
    int *arr = (int*)malloc(sizeof(int)*size);
    //int bucket[max + 1];
    //int arr[size];
    int i, t = 0;
    for (i = 0; i < max + 1; i++)
    { //初始化
        bucket[i] = 0;
    }
    for (i = 0; i < size; i++)
    { //计数
        bucket[a[i]]++;
    }
    for (i = 0; i < max + 1; i++)
    { //排序
        while (bucket[i] > 0)
        {
            arr[t++] = i;
            bucket[i]--;
        }
    }
    for (i = 0; i < size; i++)
    { //复制
        a[i] = arr[i];
    }

    free(bucket);
    free(arr);
}
void RadixCountSort(int *a, int size)
{
    int bucket[10];
    int sum[10];
    int arr[size];
    int i, j;
    int max = a[0];
    int digit = 0;
    for (i = 0; i < size; i++)
    { //求最大值
        max = max > a[i] ? max : a[i];
    }
    while (max != 0)
    { //求位数
        max /= 10;
        digit++;
    }

    for (j=1;j<=digit;j++)
    {
        for (i = 0; i < 10; i++)
        { //初始化
            bucket[i] = 0;
            sum[i] = 0;
        }
        for (i = 0; i < size; i++)
        { //初始化
            arr[i] = -1;//代表没赋值过
        }
        for (i = 0; i < size; i++)
        { //计数
            int num = a[i] % mypow(j) / mypow(j-1);//a[i]的第digit位
            bucket[num]++;
        }
        for (i = 1; i < 10; i++)
        { //累加
            sum[i] =bucket[i-1]+sum[i-1];
        }

        for(i = 0;i < size; i++){//难以用我的语言描述逻辑。。
            int num = a[i] % mypow(j) / mypow(j-1);//a[i]的第digit位
            int temp = sum[num];
            while(arr[temp] != -1){
                temp++;
            }
            arr[temp] = a[i];
        }

        for (i = 0; i < size; i++)
        { //复制
            a[i] = arr[i];
        }
    }

}


