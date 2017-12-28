#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

#define MAX 100

class MatrixUDG
{
private:
	char mVexs[MAX];               //顶点集合
	int  mVexNum;                  //顶点数
	int  mEdgNum;                  //边数
	int  mMarix[MAX][MAX];         //邻接矩阵  
public:
	//创建图,（自己输入数据）
	MatrixUDG();         
	//创建图（用已经提供的数据）
	MatrixUDG(char vex[],int vlen,char edges[][2],int elen);

	~MatrixUDG();
	//打印矩阵的图
	void PrintMatrix();
private:
	//读取一个输入字符
	char readChar();
	//返回ch在矩阵中的位置
	int getPosition(char ch);
};

//创建图（自己输入数据）
MatrixUDG::MatrixUDG()
{
	char c1, c2;
	int i, p1, p2;

	//将数组初始化为0；
	memset(mMarix, 0, sizeof(mMarix));

	//输入定点数和边数
	cout << "input vertex number: ";
	cin >> mVexNum;
	cout << "input edge number: ";
	cin >> mEdgNum;

	if (mVexNum < 1 || mEdgNum<1 || (mEdgNum)>(mVexNum*(mVexNum - 1)))
	{
		cout << "input errors: invalid paramet ers!" << endl;;
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
			cout << "input errors: invalid edge !";
			return;
		}

		mMarix[p1][p2] = 1;
		mMarix[p2][p1] = 1;
	}
}

//创建图(用已经提供的数据)
MatrixUDG::MatrixUDG(char vexp[], int vlen, char edges[][2], int elen)
{
	int i, p1, p2;
	
	//将数组初始化为0；
	memset(mMarix, 0, sizeof(mMarix));

	//初始化顶点数和边数
	mVexNum = vlen;
	mEdgNum = elen;
	//初始化顶点
	for (i = 0; i < mVexNum; i++)
		mVexs[i] = vexp[i];

	//初始化边
	for (i = 0; i < mEdgNum; i++)
	{
		p1 = getPosition(edges[i][0]);
		p2 = getPosition(edges[i][1]);

		mMarix[p1][p2] = 1;
		mMarix[p2][p1] = 1;
	}
}

MatrixUDG::~MatrixUDG()
{

}

//读取一个输入字符
char MatrixUDG::readChar()
{
	char ch;

	do
	{
		cin >> ch;
	} while (!(ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z'));

	return ch;
}

//返回ch在矩阵中的位置
int MatrixUDG::getPosition(char ch)
{
	int i;

	for (i = 0; i < mVexNum; i++)
		if (mVexs[i] == ch)
			return i;
	return -1;
}

void MatrixUDG::PrintMatrix()
{
	int i, j;

	cout << "Matrix Graph: " << endl;
	for (i = 0; i < mVexNum; i++)
	{
		for (j = 0; j < mVexNum; j++)
			cout << mMarix[i][j] << " ";
		cout << endl;
	}
		
}

int main()
{
	char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	char edges[][2] = {
		{ 'A', 'C' },
		{ 'A', 'D' },
		{ 'A', 'F' },
		{ 'B', 'C' },
		{ 'C', 'D' },
		{ 'E', 'G' },
		{ 'F', 'G' } };
	int vlen = sizeof(vexs) / sizeof(vexs[0]);
	int elen = sizeof(edges) / sizeof(edges[0]);
	MatrixUDG* pG;

	// 自定义"图"(输入矩阵队列)
	//pG = new MatrixUDG();
	// 采用已有的"图"
	pG = new MatrixUDG(vexs, vlen, edges, elen);

	pG->PrintMatrix();   // 打印图
	return 0；
}
