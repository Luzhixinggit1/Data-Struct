/**
 * 直接插入排序：c++
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
 *        n ------  待排序数组的长度
 */

void inserSort(int *arr, int n)
{
	int i, j, k;

	for (i = 1; i < n; i++)
	{
		//在a[i]前面找到一个合适的位置
		for (j = i - 1; j >= 0; j--)
		{
			if (arr[j] < arr[i])
				break;   //找到了所在位置，退出内层循环
		}

		//找到了合适的位置
		if (j != i - 1)   //若等于则不需要处理
		{
			//比arr[i]大的数据往后移动
			int temp = arr[i];
			for (k = i - 1; k > j; k--)
				arr[k + 1] = arr[k];

			arr[k + 1] = temp;
		}
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

	inserSort(a, ilen);

	cout << "after  sort:";
	for (i = 0; i<ilen; i++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}
