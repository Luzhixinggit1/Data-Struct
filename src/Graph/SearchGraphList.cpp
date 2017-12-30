/*
创建过程参看前面的创建的cpp这里不再有注释
C++邻接表创建无向图
实现深度和广度优先搜索
creator：lzx
编程环境：vs2015
*/
#include<iostream>
using namespace std;
#define MAX   50

class ListUDG
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
	int mEdgeNum;
	VNode mVexs[MAX];
public:
	ListUDG();
	ListUDG(char vexs[],int vlen,char edges[][2],int elen);
	~ListUDG();
	void DFS();
	void BFS();
	void PrintList();
private:
	char readChar();
	int getPosition(char ch);
	void DFS(int i, int *visited);
	void LinkLast(ENode *list, ENode *node);
};


ListUDG::ListUDG()
{
	char c1, c2;
	int i, p1, p2;
	ENode *node1, *node2;

	cout << "input vertex number: ";
	cin >> mVexNum;
	cout << "input edge number: ";
	cin >> mEdgeNum;

	if (mVexNum < 1 || mEdgeNum<1 || mEdgeNum>(mVexNum*(mVexNum - 1)))
	{
		cout << "input error: invalid paramaters!" << endl;
		return;
	}

	for (i = 0; i < mVexNum; i++)
	{
		cout << "vertex(" << i << "): ";
		mVexs[i].data = readChar();
		mVexs[i].firstEdge = NULL;
	}

	for (i = 0; i < mEdgeNum; i++)
	{
		cout << "edge(" << i << "):";
		c1 = readChar();
		c2 = readChar();

		p1 = getPosition(c1);
		p2 = getPosition(c2);

		node1 = new ENode();
		node1->ivex = p2;
		if (mVexs[p1].firstEdge == NULL)
			mVexs[p1].firstEdge = NULL;
		else
			LinkLast(mVexs[p1].firstEdge, node1);

		node2 = new ENode();
		node2->ivex = p1;
		if (mVexs[p2].firstEdge == NULL)
			mVexs[p2].firstEdge = node2;
		else
			LinkLast(mVexs[p2].firstEdge, node2);
	}
}

ListUDG::ListUDG(char vexs[], int vlen, char edges[][2], int elen)
{
	int i, p1, p2;
	ENode *node1, *node2;

	mVexNum = vlen;
	mEdgeNum = elen;

	for (i = 0; i < mVexNum; i++)
	{
		mVexs[i].data = vexs[i];
		mVexs[i].firstEdge = NULL;
	}
		

	for (i = 0; i < mEdgeNum; i++)
	{
		p1 = getPosition(edges[i][0]);
		p2 = getPosition(edges[i][1]);

		node1 = new ENode();
		node1->ivex = p2;
		if (mVexs[p1].firstEdge == NULL)
			mVexs[p1].firstEdge = node1;
		else
			LinkLast(mVexs[p1].firstEdge, node1);

		node2 = new ENode();
		node2->ivex = p1;
		if (mVexs[p2].firstEdge == NULL)
			mVexs[p2].firstEdge = node2;
		else
			LinkLast(mVexs[p2].firstEdge, node2);
	}
}

ListUDG::~ListUDG()
{

}

//深度优先搜索
void ListUDG::DFS()
{
	int i;
	int visited[MAX];;

	//将未被初始化的顶点初始化为0
	memset(visited, 0, sizeof(visited));

	cout << "DFS :";
	for (i = 0; i < mVexNum; i++)
	{
		if (!visited[i])
			DFS(i, visited);
	}
	cout << endl;
}

//广度优先搜索
void ListUDG::BFS()
{
	int head=0;
	int rear=0;
	int queue[MAX];
	int visited[MAX];
	int i, j, k;
	ENode *node;

	//初始化未被访问的顶点为0
	memset(visited, 0, sizeof(visited));

	cout << "BFS: ";
	for (i = 0; i < mVexNum; i++)
	{
		if (!visited[i])
		{
			visited[i] = 1;
			cout << mVexs[i].data << " ";
			queue[rear++] = i;
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

void ListUDG::PrintList()
{
	int i;
	ENode *node;

	cout << "List Graph:" << endl;
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

char ListUDG::readChar()
{
	char ch;
	do
	{
		cin >> ch;
	} while (!(ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z'));
	return ch;
}

int ListUDG::getPosition(char ch)
{
	int i;
	for (i = 0; i < mVexNum; i++)
		if (mVexs[i].data == ch)
			return i;

	return -1;
}

void ListUDG::DFS(int i, int * visited)
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

void ListUDG::LinkLast(ENode * list, ENode * node)
{
	ENode *p;
	p = list;
	while (p->nextEdge)
		p = p->nextEdge;
	p->nextEdge = node;
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
	ListUDG* pG;

	// 自定义"图"(输入矩阵队列)
	//pG = new ListUDG();
	// 采用已有的"图"
	pG = new ListUDG(vexs, vlen, edges, elen);

	pG->PrintList();   // 打印图
	pG->DFS();     // 深度优先遍历
	pG->BFS();     // 广度优先遍历
	return 0;
}
