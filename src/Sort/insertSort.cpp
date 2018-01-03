/**
 * 快速排序：c++
 * 编程环境：VS2015
 *
 * author:lzx
 * date:2018.1.3
 */

#include<iostream>
using namespace std;

/*
 *    快速排序
 *    
 *    参数说明：
 *        arr ---   待排序的数组
 *        left ---  数组的左边界 
 *        right---  数组的右边界
 */

void quickSort(int *arr, int left, int right)
{
	if (left < right)
	{
		int i, j, x;

		i = left;
		j = right;
		x = arr[i];

		while (i < j)
		{
			while (i<j&&arr[j]>x)
				j--;
			if (i < j)
				arr[i++] = arr[j];
			while (i < j&&arr[i] < x)
				i++;
			if (i < j)
				arr[j--] = arr[i];

		}
		arr[i] = x;
		quickSort(arr, left, i - 1);
		quickSort(arr, i + 1, right);
	}
}

int main()
{

	int i;
	int a[] = { 30,40,60,10,20,50 };
	int ilen = (sizeof(a)) / (sizeof(a[0]));

	cout << "before sort:";
	for (i = 0; i<ilen; i++)
		cout << a[i] << " ";
	cout << endl;

	quickSort(a, 0, ilen - 1);

	cout << "after  sort:";
	for (i = 0; i<ilen; i++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}
