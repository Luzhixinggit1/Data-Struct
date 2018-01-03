/*
编程环境：VS2015
author:lzx
date:2018.1.3
*/

#include<iostream>
using namespace std;
/* 
a,待排序的数组
n,待排序数组的长度

*/
void bubbleSort1(int *a, int n)
{
	int i, j, temp;

	for (i = n - 1; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (a[j] > a[j + 1])
			{
				//把打的值冒泡到后面
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}

/*
冒泡排序改进版
a,待排序数组
n,待排序数组的长度

*/

void bubbleSort2(int *a, int n)
{
	int i, j, temp;
	int flag;                  //标记

	for (i = n - 1; i > 0; i--)
	{
		flag = 0;                      //初始化标记为0
		for (j = 0; j < i; j++)
		{
			if (a[j] > a[j + 1])
			{
				//交换a[j]和a[j+1]
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				flag = 1;              //若交换过，则标记置为1
			}
		}
		if (flag == 0)  //没有发生交换，说明已经排好序
			break;
	}
}

int main()
{

	int i;
	int a[] = { 20,40,30,10,60,50 };
	int ilen = (sizeof(a)) / (sizeof(a[0]));

	cout << "before sort:";
	for (i = 0; i<ilen; i++)
		cout << a[i] << " ";
	cout << endl;

	bubbleSort2(a, ilen);
	//bubbleSort2(a, ilen);

	cout << "after  sort:";
	for (i = 0; i<ilen; i++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}
