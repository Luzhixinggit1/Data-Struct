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

//二：方法二：
/*

存储临时arr[0]在一个临时变量,将arr[1]arr[0],arr[2]arr[1]…最后临时arr(n - 1)
让我们采取同样的例子arr[]=[1、2、3、4、5、6、7),由一个2 d = 2旋转arr[]times
我们得到[2,3,4,5,6,7,1]之后第一个旋转和[3、4、5、6、7、1、2]之后第二次旋转。
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

void leftRotateOneByOne(int arr[], int n)
{
	int i, temp;
	temp = arr[0];
	for (i = 0; i < n - 1; i++)
		arr[i] = arr[i + 1];
	arr[n - 1] = temp;
}

void leftRotate0(int arr[], int d, int n)
{
	for (int i = 0; i < d; i++)
		leftRotateOneByOne(arr, n);
}
