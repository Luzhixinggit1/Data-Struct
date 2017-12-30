/*
C++邻接矩阵创建无向图
实现深度和广度优先搜索
creator：lzx
编程环境：vs2015
*/
#include<iostream>
using namespace std;
#define MAX   50

class MatrixUDG
{
private:
	char mVexs[MAX];
	int mVexNum;
	int mEdgNum;
	int mMatrix[MAX][MAX];
public:
	MatrixUDG();
	MatrixUDG(char vexs[], int vlen, char edges[][2], int elen);
	~MatrixUDG();
	//深度优先搜索遍历图
	void DFS();
	//广度优先搜索遍历图
	void BFS();
	//打印邻接矩阵
	void PrintMatrix();
private:
	char readChar();
	int getPosition(char ch);
	//返回顶点V第一个邻接点的索引，失败则返回-1
	int firstVertex(int v);
	//返回顶点V相对于W下一个邻接点的索引，失败则返回-1
	int nextVertex(int v, int w);
	//深度优先搜索图的递归实现
	void DFS(int i, int *visited);
};

MatrixUDG::MatrixUDG()
{
	char c1, c2;
	int i, p1, p2;

	memset(mMatrix, 0, sizeof(mMatrix));

	cout << "input vertex number: ";
	cin >> mVexNum;
	cout << "input edge number: ";
	cin >> mEdgNum;

	if (mVexNum < 1 || mEdgNum<1 || (mEdgNum>(mVexNum*(mVexNum - 1))))
	{
		cout << "input error: invalid parameters!" << endl;
		return;
	}

	for (i = 0; i < mVexNum; i++)
	{
		cout << "vertex(" << i << "): ";
		mVexs[i] = readChar();
	}

	for (i = 0; i < mEdgNum; i++)
	{
		cout << "edge(" << i << "): ";

		c1 = readChar();
		c2 = readChar();

		p1 = getPosition(c1);
		p2 = getPosition(c2);
		if (p1 == -1 || p2 == -1)
		{
			cout << "input error: invalid edge!";
			return;
		}

		mMatrix[p1][p2] = 1;
		mMatrix[p2][p1] = 1;
	}
}

MatrixUDG::MatrixUDG(char vexs[], int vlen, char edges[][2], int elen)
{
	int i, p1, p2;

	memset(mMatrix, 0, sizeof(mMatrix));

	mVexNum = vlen;
	mEdgNum = elen;

	for (i = 0; i < mVexNum; i++)
		mVexs[i] = vexs[i];

	for (i = 0; i < mEdgNum; i++)
	{
		p1 = getPosition(edges[i][0]);
		p2 = getPosition(edges[i][1]);
		
		mMatrix[p1][p2] = 1;
		mMatrix[p2][p1] = 1;
	}


}

//深度优先搜索
void MatrixUDG::DFS()
{
	int i;
	int visited[MAX];

	//初始化所有顶点都没有被访问
	memset(visited, 0, sizeof(visited));

	cout << "DFS:  ";
	for (i = 0; i < mVexNum; i++)
	{
		if (!visited[i])
			DFS(i, visited);
	}
	cout << endl;
}

//广度优先搜索
void MatrixUDG::BFS()
{
	int head = 0;
	int rear = 0;
	int queue[MAX];          //辅组队列
	int visited[MAX];
	int i, j, k;

	//初始化未被访问的为0
	memset(visited, 0, sizeof(visited));

	cout << "BFS :";
	for (i = 0; i < mVexNum; i++)
	{
		if (!visited[i])
		{
			visited[i] = 1;
			cout << mVexs[i] << " ";
			queue[rear++] = i;
		}
		while (head != rear)
		{
			j = queue[head++];
			for (k = firstVertex(j); k >= 0; k = nextVertex(j, k))  //k是访问的邻接点
			{
				if (!visited[k])
				{
					visited[k] = 1;
					cout << mVexs[k] << " ";
					queue[rear++] = k;
				}
			}
		}
	}
	cout << endl;
}

//打印矩阵队列图
void MatrixUDG::PrintMatrix()
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

//深度优先搜索图的递归实现
void MatrixUDG::DFS(int i, int *visited)
{
	int w;
	visited[i] = 1;
	cout << mVexs[i] << " ";
	//遍历该顶点所有的邻接点，如果没有访问过，那么继续走下去
	for (w = firstVertex(i); w >= 0; w = nextVertex(i, w))
	{
		if (!visited[w])
			DFS(w, visited);
	}
}

int MatrixUDG::getPosition(char ch)
{
	int i;
	for (i = 0; i < mVexNum; i++)
		if (mVexs[i] == ch)
			return i;

	return -1;
}

//返回顶点V第一个邻接点的索引，失败则返回-1
int MatrixUDG::firstVertex(int v)
{
	int i;
	if (v<0 || v>(mVexNum - 1))
		return -1;
	for (i = 0; i < mVexNum; i++)
		if (mMatrix[v][i] == 1)
			return i;

	return -1;
}

//返回顶点V相对于w下一个邻接点的索引
int MatrixUDG::nextVertex(int v, int w)
{
	int i;
	if (v<0 || v>(mVexNum - 1) || w<0 || w>(mVexNum - 1))
		return -1;

	for (i = w + 1; i < mVexNum; i++)
		if (mMatrix[v][i] == 1)
			return i;

	return -1;
}


char MatrixUDG::readChar()
{
	char ch;
	do
	{
		cin >> ch;
	} while (!(ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z'));

	return ch;
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
	pG->DFS();     // 深度优先遍历
	pG->BFS();     // 广度优先遍历
	return 0;
}
