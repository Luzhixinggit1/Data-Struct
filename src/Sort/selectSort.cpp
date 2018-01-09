/**
 * 选择排序：c++
 * 编程环境：VS2015
 *
 * author:lzx
 * date:2018.1.3
 */

#include<iostream>
using namespace std;

/*
 *    选择排序
 *    
 *    参数说明：
 *        arr ---   待排序的数组
 *        n ------  待排序数组的长度
 */
void seletSort(int *arr, int n)
{
	int i, j, min;

	for (i = 0; i < n; i++)
	{
		//找出a[i+1]到a[n]之间的最小元素
		min = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min])
				min = j;
		}
		// 若min!=i，则交换 a[i] 和 a[min]。
		// 交换之后，保证了a[0] ... a[i] 之间的元素是有序的。
		if (min != i)
		{
			int tmp = arr[i];
			arr[i] = arr[min];
			arr[min] = tmp;
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

	seletSort(a, ilen);

	cout << "after  sort:";
	for (i = 0; i<ilen; i++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}
