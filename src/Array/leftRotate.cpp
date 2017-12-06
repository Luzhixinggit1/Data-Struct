//长度为n左旋转d位
/*
一：方法一
eg:输入arr[]=[1,2,3,4,5,6,7],d = 2,n = 7
1)d元素存储在一个临时数组temp[]=[1,2]
2)转变的arr[]
arr[]=[3、4、5、6、7、6、7]
3)存储回d元素arr[]=[3、4、5、6、7、1、2]
*/
void leftRotate(int arr[], int d, int n)
{
	if (d > n)
	{
		d = d%n;
	}
	int *temp = new int[d];
	for (int i = 0; i < d; i++)
		temp[i] = arr[i];
	for (int i = 0, j = 0; i < n&&j < d; i++)
	{
		if (i < n - d)
			arr[i] = arr[i + d];
		else
		{
			arr[i] = temp[j];
			j++;
		}		
	}
}
