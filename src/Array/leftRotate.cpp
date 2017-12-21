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

/*
五、方法五：
将数组分成A[0,..d-1]，和B[d.。。n-1]
按照下面的规则分割A和B直到A等于B
a,如果A更短，则把B分成Bl(左)和Br(右)两部分，且Br的长度等于A，交换Br和A,此时的A就处在它最终的位置
  将接下来的B部分分割成A和B和前面一样
b,如果A更长，则把A分成Al(左）和Ar(右）两部分，且Al的部分等于B,交换Al和B,此时的B就处在最终的位置
  将接下来的A继续进行前面的操作
c,A等于B,任务完成
*/

//将数组的某两个部分交换
void swap(int array[], int fi, int si, int d)
{
	int i, temp;
	for (i = 0; i < d; i++)
	{
		temp = array[fi + i];
		array[fi + i] = array[si + i];
		array[si + i] = temp;
	}
}

void leftRotate(int arr[], int d, int n)
{
	if (d == 0 || d == n)
		return;
	//如果A等于B则直接交换
	if (n - d == d)
	{
		swap(arr, 0, n - d, d);
		return;
	}
	//A更短
	else if (d < n - d)
	{
		swap(arr, 0, n - d, d);
		leftRotate(arr, d, n - d);
	}
	//A更长
	else
	{
		swap(arr, 0, d, n - d);
		leftRotate(arr + n - d, 2 * d - n, d);
	}
}

