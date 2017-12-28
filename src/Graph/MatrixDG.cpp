/*
C++邻接矩阵创建有向图
creator：lzx
编程环境：vs2015
*/
#include<iostream>
using namespace std;
#define MAX   50

class MatrixDG
{
private:
	char mVexs[MAX];        //顶点集合
	int mVexNum;            //顶点数
	int mEdgNum;            //边数
	int mMatrix[MAX][MAX];  //邻接矩阵
public:
	//创建有向图（自己输入 数据）
	MatrixDG();
	//创建有向图（用提供的数据）
	MatrixDG(char vexs[],int vlen,char edge[][2],int elen);
	//析构函数
	~MatrixDG();
	//输出矩阵
	void PrintMatrix();
private:
	//读取一个输入字符
	char readChar();
	//返回字符ch所在矩阵的位置
	int getPosition(char ch);
};

//创建图，自己输入数据
MatrixDG::MatrixDG()
{

	//把数组初始化为0
	memset(mMatrix, 0, sizeof(mMatrix));

	char c1, c2;
	int i, p1, p2;

	//输入顶点数和边数
	cout << "input vertex number: ";
	cin >> mVexNum;
	cout << "input edge number: ";
	cin >> mEdgNum;
	if (mVexNum < 1 || mEdgNum<1 || (mEdgNum>(mVexNum*(mVexNum - 1))))
	{
		cout << "input error: invalid parameters!\n";
		return;
	}

	//初始化顶点
	for (i = 0; i < mVexNum; i++)
	{
		cout << "vertex(" << i << "): ";
		mVexs[i] = readChar();
	}

	//初始化边
	for (i = 0; i < mEdgNum; i++)
	{
		cout << "edge(" << i << "): ";

		c1 = readChar();
		c2 = readChar();

		p1 = getPosition(c1);
		p2 = getPosition(c2);

		if (p1 == -1 || p2 == -1)
		{
			cout << "input error: invalid edge!" << endl;
			return;
		}

		mMatrix[p1][p2] = 1;
	}
}

//创建图，自己提供的数据
MatrixDG::MatrixDG(char vexs[], int vlen, char edge[][2], int elen)
{
	//先把数组初始化为0
	memset(mMatrix, 0, sizeof(mMatrix));
	
	int i, p1, p2;
	//初始化顶点数和边数
	mVexNum = vlen;
	mEdgNum = elen;

	//初始化顶点
	for (i = 0; i < mVexNum; i++)
		mVexs[i] = vexs[i];

	//初始化边
	for (i = 0; i < mVexNum; i++)
	{
		p1 = getPosition(edge[i][0]);
		p2 = getPosition(edge[i][1]);
		
		mMatrix[p1][p2] = 1;
	}
}

//析构函数
MatrixDG::~MatrixDG()
{

}

//输出邻接矩阵
void MatrixDG::PrintMatrix()
{
	int i, j;
	cout << "Matrix Graph:" << endl;
	for (i = 0; i < mVexNum; i++)
	{
		for (j = 0; j < mVexNum; j++)
			cout << mMatrix[i][j] << " ";
		cout << endl;
	}
}

//读取一个输入字符
char MatrixDG::readChar()
{
	char ch;
	do
	{
		cin >> ch;
	} while (!(ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z'));

	return ch;
}

//返回字符ch所在位置
int MatrixDG::getPosition(char ch)
{
	int i;
	for (i = 0; i < mVexNum; i++)
		if (mVexs[i] == ch)
			return i;

	return -1;
}


int main()
{
	/*char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	char edges[][2] = {
		{ 'A', 'B' },
		{ 'B', 'C' },
		{ 'B', 'E' },
		{ 'B', 'F' },
		{ 'C', 'E' },
		{ 'D', 'C' },
		{ 'E', 'B' },
		{ 'E', 'D' },
		{ 'F', 'G' } };
	int vlen = sizeof(vexs) / sizeof(vexs[0]);
	int elen = sizeof(edges) / sizeof(edges[0]);*/
	MatrixDG* pG;

	// 自定义"图"(输入矩阵队列)
	pG = new MatrixDG();
	// 采用已有的"图"
	//pG = new MatrixDG(vexs, vlen, edges, elen);

	pG->PrintMatrix();   // 打印图

	return 0;
}
