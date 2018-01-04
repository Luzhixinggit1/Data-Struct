
/**
 * 希尔排序：c++
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

void shellSort(int *arr, int n)
{
	int i, j, grap;

	//graph为步长，每次为原来的一半
	for (grap = n / 2; grap > 0; grap /= 2)
	{
		//共有graph个组，每个组进行插入排序
		for (i = 0; i < grap; i++)
		{
			for (j = i + grap; j < n; j += grap)
			{
				if (arr[j] < arr[j - grap])
				{
					int temp = arr[j];
					int k = j - grap;
					while (k >= 0 && arr[k]>temp)
					{
						arr[k + grap] = arr[k];
						k -= grap;
					}
					arr[k + grap] = temp;
				}
			}
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

	shellSort(a, ilen);

	cout << "after  sort:";
	for (i = 0; i<ilen; i++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}
