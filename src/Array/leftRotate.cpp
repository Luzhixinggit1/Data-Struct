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
让我们采取同样的例子arr[]=[1、2、3、4、5、6、7),由一个2 d = 2旋转arr[]次
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

void leftRotate(int arr[], int d, int n)
{
	for (int i = 0; i < d; i++)
		leftRotateOneByOne(arr, n);
}

//三：方法三
/*
次为方法二的扩展，找到d与n的最大公约数，相当于把每一个数组分成gcd(最大公约数)个集合，每个集合都进行obebyone的移动

*/
int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a%b);
}

void leftRotate(int arr[], int d, int n)
{
	int i, j, k, temp;
	for (i = 0; i < gcd(n, d); i++)
	{
		temp = arr[i];
		j = i;
		while (1)
		{
			k = j + d;
			if (k >= n)
				k = k - n;
			if (k == i)break;
			arr[j] = arr[k];
			j = k;
		}
		arr[j] = temp;
	}
}

//四：方法四：

/*
此方法相当于把数组分成a[0]-a[d-1]和a[d]-a[n-1],分别将这两个部分反转，最后将整个数组反转
*/

void rvereseArray(int arr[], int start, int end)
{
	int temp;
	while (start < end)
	{
		temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
		start++;
		end--;
	}
}

void leftRotatef(int arr[], int d, int n)
{
	rvereseArray(arr,0, d - 1);
	rvereseArray(arr,d, n - 1);
	rvereseArray(arr,0, n - 1);
}



