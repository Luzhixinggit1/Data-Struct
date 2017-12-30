/*
创建过程参看前面的创建的cpp这里不再有注释
C++邻接矩阵创建有向图
实现深度和广度优先搜索
creator：lzx
编程环境：vs2015
*/
#include<iostream>
using namespace std;
#define MAX   50

class MatrixDG
{
private:
	char mVexs[MAX];
	int mMatrix[MAX][MAX];
	int mVexNum;
	int mEdgNum;
public:
	MatrixDG();
	MatrixDG(char vexs[], int vlen, char edge[][2], int elen);
	~MatrixDG();
	void DFS();
	void BFS();
	void PrintMatrix();
private:
	char readChar();
	int getPosition(char ch);
	int firsrEdge(int v);
	int nextEdge(int v, int w);
	void DFS(int i, int *visited);

};

MatrixDG::MatrixDG()
{
	int i, p1, p2;
	char c1, c2;

	memset(mMatrix, 0, sizeof(mMatrix));

	cout << "input vertex number: ";
	cin >> mVexNum;
	cout << "input edge number:";
	cin >> mEdgNum;
	if (mVexNum < 1 || mEdgNum<1 || mEdgNum>(mVexNum*(mVexNum - 1)))
	{
		cout << "input error: invalid parameters!" << endl;
		return;
	}
	
	for (i = 0; i < mVexNum; i++)
	{
		cout << "vextex(" << i << "): ";
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
			cout << "input error: invalid edge!" << endl;
			return;
		}
		mMatrix[p1][p2] = 1;
	}


}

MatrixDG::MatrixDG(char vexs[], int vlen, char edge[][2], int elen)
{

	memset(mMatrix, 0, sizeof(mMatrix));

	int i, p1, p2;

	mVexNum = vlen;
	mEdgNum = elen;

	for (i = 0; i < mVexNum; i++)
		mVexs[i] = vexs[i];

	for (i = 0; i < mEdgNum; i++)
	{
		p1 = getPosition(edge[i][0]);
		p2 = getPosition(edge[i][1]);

		mMatrix[p1][p2] = 1;
	}
}

MatrixDG::~MatrixDG()
{
}

//深度优先搜索
void MatrixDG::DFS()
{
	int i;
	int visited[MAX];

	memset(visited, 0, sizeof(visited));

	cout << "DFS: ";
	for (i = 0; i < mVexNum; i++)
	{
		if (!visited[i])
			DFS(i, visited);
	}
	cout << endl;
}

void MatrixDG::BFS()
{
	int head = 0;
	int rear = 0;
	int queue[MAX];
	int visited[MAX];
	int i, j, k;

	memset(visited, 0, sizeof(visited));

	cout << "BFS: ";
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
			for (k = firsrEdge(j); k >= 0; k = nextEdge(j, k))
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


char MatrixDG::readChar()
{
	char ch;
	do
	{
		cin >> ch;
	} while (!(ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z'));
	return ch;
}

int MatrixDG::getPosition(char ch)
{
	int i;
	for (i = 0; i < mVexNum; i++)
		if (mVexs[i] == ch)
			return i;
	return -1;
}

int MatrixDG::firsrEdge(int v)
{
	int i;

	if (v<0 || v>(mVexNum - 1))
		return -1;

	for (i = 0; i < mVexNum; i++)
		if (mMatrix[v][i] == 1)
			return i;

	return -1;
}

int MatrixDG::nextEdge(int v, int w)
{
	int i;

	if (v<0 || v>(mVexNum - 1) || w<0 || w>(mVexNum - 1))
		return -1;

	for (i = w + 1; i < mVexNum; i++)
		if (mMatrix[v][i] == 1)
			return i;

	return -1;
}

void MatrixDG::DFS(int i, int * visited)
{
	int w;
	visited[i] = 1;
	cout << mVexs[i] << " ";
	for (w = firsrEdge(i); w >= 0; w = nextEdge(i, w))
	{
		if (!visited[w])
			DFS(w, visited);
	}

}

int main()
{
	char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
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
	int elen = sizeof(edges) / sizeof(edges[0]);
	MatrixDG* pG;

	// 自定义"图"(输入矩阵队列)
	//pG = new MatrixDG();
	// 采用已有的"图"
	pG = new MatrixDG(vexs, vlen, edges, elen);

	pG->PrintMatrix();   // 打印图
	pG->DFS();     // 深度优先遍历
	pG->BFS();     // 广度优先遍历
	return 0;
}


