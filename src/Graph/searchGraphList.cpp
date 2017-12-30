/*
创建过程参看前面的创建的cpp这里不再有注释
C++邻接表创建有向图
实现深度和广度优先搜索
creator：lzx
编程环境：vs2015
*/
#include<iostream>
using namespace std;
#define MAX   50

class ListDG
{
private:
	class ENode
	{
	public:
		int ivex;
		ENode *nextEdge;
	};
	class VNode
	{
	public:
		char data;
		ENode *firstEdge;
	};
private:
	int mVexNum;
	int mEdgNum;
	VNode mVexs[MAX];
public:
	ListDG();
	ListDG(char vexs[], int vlen, char edge[][2], int elen);
	~ListDG();
	void DFS();
	void BFS();
	void PrintList();
private:
	char readChar();
	int getPostion(char ch);
	void DFS(int i, int *visited);
	void LinkLast(ENode *list, ENode *node);
};

ListDG::ListDG()
{
	int c1, c2;
	int i, p1, p2;
	ENode *node;

	cout << "input vertex number: ";
	cin >> mVexNum;
	cout << "input edge number: ";
	cin >> mEdgNum;
	if (mVexNum < 1 || mEdgNum<1 || mEdgNum>(mVexNum*(mVexNum - 1)))
	{
		cout << "input error: invalid parameters!" << endl;
		cout << endl;
	}

	for (i = 0; i < mVexNum; i++)
	{
		cout << "vertex(" << i << "): ";
		mVexs[i].data = readChar();
		mVexs[i].firstEdge = NULL;
	}

	for (i = 0; i < mEdgNum; i++)
	{
		cout << "edge(" << i << "): ";
		c1 = readChar();
		c2 = readChar();

		p1 = getPostion(c1);
		p2 = getPostion(c2);

		if (p1 == -1 || p2 == -1)
		{
			cout << "input error: invalid edge!" << endl;
			return;
		}

		node = new ENode();
		node->ivex = p2;
		if (mVexs[p1].firstEdge == NULL)
			mVexs[p1].firstEdge = node;
		else
			LinkLast(mVexs[p1].firstEdge, node);
	}


}

ListDG::ListDG(char vexs[], int vlen, char edge[][2], int elen)
{
	int i, p1, p2;
	ENode *node;

	mVexNum = vlen;
	mEdgNum = elen;

	for (i = 0; i < mVexNum; i++)
	{
		mVexs[i].data = vexs[i];
		mVexs[i].firstEdge = NULL;
	}

	for (i = 0; i < mEdgNum; i++)
	{
		p1 = getPostion(edge[i][0]);
		p2 = getPostion(edge[i][1]);

		node = new ENode();

		node->ivex = p2;
		if (mVexs[p1].firstEdge == NULL)
			mVexs[p1].firstEdge = node;
		else
			LinkLast(mVexs[p1].firstEdge, node);
	}
}

ListDG::~ListDG()
{
}

void ListDG::DFS()
{
	int i;
	int visited[MAX];

	memset(visited, 0, sizeof(visited));

	cout << "DFS: ";
	for (i = 0; i < mVexNum; i++)
	{
		if (!visited[i])
		{
			DFS(i, visited);
		}
	}
	cout << endl;
}

void ListDG::BFS()
{
	int head = 0;
	int rear = 0;
	int visited[MAX];
	int queue[MAX];
	int i, j, k;
	ENode *node;

	memset(visited, 0, sizeof(visited));

	cout << "BFS: ";
	for (i = 0; i < mVexNum; i++)
	{
		if (!visited[i])
		{
			visited[i] = 1;
			cout << mVexs[i].data << " ";
			queue[rear++]=i;
		}
		while (head != rear)
		{
			j = queue[head++];
			node = mVexs[j].firstEdge;
			while (node != NULL)
			{
				k = node->ivex;
				if (!visited[k])
				{
					visited[k] = 1;
					cout << mVexs[k].data << " ";
					queue[rear++] = k;
				}
				node = node->nextEdge;
			}
		}
	}
	cout << endl;
}

void ListDG::PrintList()
{
	int i;
	ENode *node;

	cout << "ListDG Graph:" << endl;
	for (i = 0; i < mVexNum; i++)
	{
		cout << i << "(" << mVexs[i].data << "): ";
		node = mVexs[i].firstEdge;
		while (node != NULL)
		{
			cout << node->ivex << "(" << mVexs[node->ivex].data << ") ";
			node = node->nextEdge;
		}
		cout << endl;
	}
}

char ListDG::readChar()
{
	char ch;
	do
	{
		cin >> ch;
	} while (!(ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z'));
	return ch;
}

int ListDG::getPostion(char ch)
{
	int i;
	for (i = 0; i < mVexNum; i++)
		if (mVexs[i].data == ch)
			return i;

	return -1;
}

void ListDG::DFS(int i, int * visited)
{
	ENode *node;

	visited[i] = 1;
	cout << mVexs[i].data << " ";
	node = mVexs[i].firstEdge;
	while (node != NULL)
	{
		if (!visited[node->ivex])
			DFS(node->ivex, visited);
		node = node->nextEdge;
	}
}

void ListDG::LinkLast(ENode * list, ENode * node)
{
	ENode *p = list;
	while (p->nextEdge)
		p = p->nextEdge;
	p->nextEdge = node;
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
	ListDG* pG;

	// 自定义"图"(输入矩阵队列)
	//pG = new ListDG();
	// 采用已有的"图"
	pG = new ListDG(vexs, vlen, edges, elen);

	pG->PrintList();   // 打印图
	pG->DFS();     // 深度优先遍历
	pG->BFS();     // 广度优先遍历
	return 0;
}


