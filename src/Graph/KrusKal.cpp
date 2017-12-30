/*
C++邻接矩阵创建无向图
克鲁斯卡尔算法（最小生成树）
creator：lzx
编程环境：vs2015
*/
#include<iostream>
#include<iomanip>
using namespace std;

//边的结构体
class EDate
{
public:
	char start;       //边的起点
	char end;         //边的终点
	int weight;      //边的权重

public:
	EDate() {}
	EDate(char s,char e,int w):start(s),end(e),weight(w){}
};

class MatrixUDG
{
#define    MAX        100
#define    INF         (~(0x1<<31))        // 无穷大(即0X7FFFFFFF)
private:
	char mVexs[MAX];
	int mVexNum;
	int mEdgNum;
	int mMatrix[MAX][MAX];
public:
	MatrixUDG();
	MatrixUDG(char vexs[],int vlen,int matrix[][9]);
	~MatrixUDG();
	void DFS();
	void BFS();
	//克鲁斯卡尔最小生成树算法
	void kruskal();
	void PrintMatrix();
private:
	char readChar();
	int getPosition(char ch);
	int firstVertex(int v);
	int nextVertex(int v, int w);
	void DFS(int i, int *visited);
	//获取图中的边
	EDate* getEdges();
	//对边按照权值大小进行排序
	void sortEdges(EDate *edges, int vlen);
	//获取i的终点
	int getEnd(int vends[], int i);
};

char MatrixUDG::readChar()
{
	char ch;
	do
	{
		cin >> ch;
	} while (!(ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z'));

	return ch;
}

int MatrixUDG::getPosition(char ch)
{
	int i;
	for (i = 0; i < mVexNum; i++)
		if (mVexs[i] == ch)
			return i;

	return -1;
}

int MatrixUDG::firstVertex(int v)
{
	int i;
	if (v<0 || v>(mVexNum - 1))
		return -1;

	for (i = 0; i < mVexNum; i++)
		if (mMatrix[v][i] != 0 && mMatrix[v][i] != INF)
			return i;

	return -1;
}

int MatrixUDG::nextVertex(int v, int w)
{
	int i;

	if (v<0 || v>(mVexNum - 1) || w<0 && w>(mVexNum - 1))
		return -1;

	for (i = w + 1; i < mVexNum; i++)
		if (mMatrix[v][i] != 0 && mMatrix[v][i] != INF)
			return i;

	return -1;
}

void MatrixUDG::DFS(int i, int * visited)
{
	int w;
	visited[i] = 1;
	cout << mVexs[i] << " ";

	for (w = firstVertex(i); w >= 0; w = nextVertex(i, w))
		if (!visited[w])
			DFS(w, visited);

}

//获取边的信息
EDate * MatrixUDG::getEdges()
{
	int i, j;
	int index = 0;
	EDate *edge;

	edge = new EDate[mEdgNum];
	for (i = 0; i < mVexNum; i++)
	{
		for (j = 0; j < mVexNum; j++)
		{
			if (mMatrix[i][j] != INF)
			{
				edge[index++].start = i;
				edge[index++].end = j;
				edge[index++].weight = mMatrix[i][j];
				index++;
			}
		}
	}
	return edge;
}

//对边的权值按照大小排序
void MatrixUDG::sortEdges(EDate * edges, int vlen)
{
	int i, j;

	for (i = 0; i < vlen; i++)
	{
		for (j = i+1; j < vlen; j++)
		{
			if (edges[i].weight > edges[j].weight)
				swap(edges[i], edges[j]);
		}
	}
}

//获取i的终点
int MatrixUDG::getEnd(int vends[], int i)
{
	while (vends[i] != 0)
		i = vends[i];

	return i;
}

MatrixUDG::MatrixUDG()
{
	char c1, c2;
	int i, j, weight, p1, p2;

	cout << "input vertex number: ";
	cin >> mVexNum;
	cout << "input edge numbr: ";
	cin >> mEdgNum;
	if (mVexNum < 1 || mEdgNum<1 || mEdgNum>(mVexNum*(mVexNum - 1)))
	{
		cout << "input error: invalid parameter!" << endl;
		return;
	}

	for (i = 0; i < mVexNum; i++)
	{
		cout << "vertex(" << i << "): ";
		mVexs[i] = readChar();
	}

	//初始化边的权值
	for (i = 0; i < mEdgNum; i++)
	{
		for (j = 0; j < mEdgNum; j++)
		{
			if (i == j)
				mMatrix[i][j] = 0;
			else
				mMatrix[i][j] = INF;
		}
	}

	//初始化边的权值，根据用户的输入初始化
	for (i = 0; i < mVexNum; i++)
	{
		cout << "edge(" << i << "): ";

		c1 = readChar();
		c2 = readChar();
		cin >> weight;

		p1 = getPosition(c1);
		p2 = getPosition(c2);
		if (p1 == -1 || p2 == -1)
		{
			cout << "input error: invalid edge!" << endl;
			return;
		}

		mMatrix[p1][p2] = weight;
		mMatrix[p2][p1] = weight;
	}

}

MatrixUDG::MatrixUDG(char vexs[], int vlen, int matrix[][9])
{
	int i, j;

	//初始化顶点数
	mVexNum = vlen;
	mEdgNum = 0;

	//初始化顶点
	for (i = 0; i < mVexNum; i++)
		mVexs[i] = vexs[i];

	//初始化边
	for (i = 0; i < mVexNum; i++)
		for (j = 0; j < mVexNum; j++)
			mMatrix[i][j] = matrix[i][j];

	//统计边的数目
	for (i = 0; i < mVexNum; i++)
		for (j = 0; j < mVexNum; j++)
			if (i != j&&mMatrix[i][j] != INF)
				mEdgNum++;

	mEdgNum /= 2;

}

MatrixUDG::~MatrixUDG()
{
}

void MatrixUDG::DFS()
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

void MatrixUDG::BFS()
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
			for (k = firstVertex(j); k >= 0; k = nextVertex(j, k))
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

void MatrixUDG::kruskal()
{
	int i, m, n, p1, p2;
	int length;
	int index = 0;
	int vends[MAX] = { 0 };
	EDate rets[MAX];
	EDate *edges;

	//获取图中所有的边
	edges = getEdges();
	//对边按照权重排序
	sortEdges(edges, mEdgNum);
	
	for (i = 0; i < mEdgNum; i++)
	{
		p1 = getPosition(edges[i].start);
		p2 = getPosition(edges[i].end);

		m = getEnd(vends, p1);
		n = getEnd(vends, p2);

		if (m != n)
		{
			vends[m] = n;
			rets[index++] = edges[i];
		}
	}
	delete[]edges;

	//统计并且打印最小生成树的信息
	length = 0;
	for (i = 0; i < index; i++)
		length += rets[i].weight;

	cout << "Kruskal=" << length << ": ";
	for (i = 0; i < index; i++)
		cout << "(" << rets[i].start << "," << rets[i].end << ") ";
	cout << endl;
}

//打印图的邻接矩阵
void MatrixUDG::PrintMatrix()
{
	int i, j;

	cout << "Matrix Graph:" << endl;
	for (i = 0; i < mVexNum; i++)
	{
		for (j = 0; j < mVexNum; j++)
			cout << setw(10) << mMatrix[i][j] << " ";
		cout << endl;
	}
}


int main()
{
	char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	int matrix[][9] = {
		/*A*//*B*//*C*//*D*//*E*//*F*//*G*/
		/*A*/{ 0,  12, INF, INF, INF,  16,  14 },
		/*B*/{ 12,   0,  10, INF, INF,   7, INF },
		/*C*/{ INF,  10,   0,   3,   5,   6, INF },
		/*D*/{ INF, INF,   3,   0,   4, INF, INF },
		/*E*/{ INF, INF,   5,   4,   0,   2,   8 },
		/*F*/{ 16,   7,   6, INF,   2,   0,   9 },
		/*G*/{ 14, INF, INF, INF,   8,   9,   0 } };
	int vlen = sizeof(vexs) / sizeof(vexs[0]);
	MatrixUDG* pG;

	// 自定义"图"(输入矩阵队列)
	//pG = new MatrixUDG();
	// 采用已有的"图"
	pG = new MatrixUDG(vexs, vlen, matrix);

	//pG->print();   // 打印图
	//pG->DFS();     // 深度优先遍历
	//pG->BFS();     // 广度优先遍历
	//pG->prim(0);   // prim算法生成最小生成树

	pG->kruskal();   // Kruskal算法生成最小生成树

	return 0;
}



