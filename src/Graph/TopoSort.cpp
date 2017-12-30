/*
C++邻接表创建有向图
拓扑排序及其测试
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
		int ivex;                   //该边所指向的位置
		ENode *nextEdge;            //指向下一条弧
	};
	//邻接表中表的顶点
	class VNode
	{
	public:
		char data;                //顶点信息
		ENode *firstEdge;          //与该顶点相邻的点
	};
private:
	int mVexNum;              //顶点数目
	int mEdgNum;              //边数
	VNode mVexs[MAX];
public:
	//创建邻接表，自己输入数据
	ListDG();
	//创建邻接表，用提供的数据
	ListDG(char vexs[], int vlen, char edge[][2], int elen);
	//析构函数
	~ListDG();
	//打印邻接表图
	void PrintList();
	//拓扑排序
	int TopologicalSort();
private:
	//读取字符
	char readChar();
	//返回ch所在位置
	int getPosition(char ch);
	//将node节点连接到list的最后
	void LinkLast(ENode *list, ENode *node);
};

ListDG::ListDG()
{
	int i, p1, p2;
	char c1, c2;
	ENode *node;

	//输入顶点数和边数
	cout << "input vertex number： ";
	cin >> mVexNum;
	cout << "input edge number: ";
	cin >> mEdgNum;

	if (mVexNum < 1 || mEdgNum<1 || (mEdgNum>(mVexNum*(mVexNum - 1))))
	{
		cout << "input error: invalid edge!" << endl;
		return;
	}

	//初始化邻接表的顶点
	for (i = 0; i < mVexNum; i++)
	{
		cout << "vertex(" << i << "): ";
		mVexs[i].data = readChar();
		mVexs[i].firstEdge = NULL;
	}

	//初始化邻接表的边
	for (i = 0; i < mEdgNum; i++)
	{
		//读取边的起始点和结束点
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

		//初始化node1；
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

	//初始化顶点数和边数
	mVexNum = vlen;
	mEdgNum = elen;

	//初始化邻接表的边
	for (i = 0; i < mVexNum; i++)
	{
		mVexs[i].data = vexs[i];
		mVexs[i].firstEdge = NULL;
	}

	//初始化邻接表的边
	for (i = 0; i < mEdgNum; i++)
	{
		p1 = getPosition(edge[i][0]);
		p2 = getPosition(edge[i][1]);


		//初始化node1
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

void ListDG::PrintList()
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

/*
返回值：
        -1，失败，由于内存不足等原因导致
		0，成功排序并输入结果
		1，失败，该有向图是环形的

*/
int ListDG::TopologicalSort()
{
	int i, j;
	int index = 0;
	int head = 0;              //辅助队列的头
	int rear = 0;              //辅助队列的尾部
	int *queue;                //辅助队列
	int *ins;                  //入度数组
	char *top;                  //top排序结果数组，记录每个节点排序后的序号
	ENode *node;

	queue = new int[mVexNum];
	ins = new int[mVexNum];
	top = new char[mVexNum];
	memset(queue, 0, mVexNum*sizeof(int));
	memset(ins, 0, mVexNum*sizeof(int));
	memset(top, 0, mVexNum*sizeof(char));

	//统计每个顶点的入度数
	for (i = 0; i < mVexNum; i++)
	{
		node = mVexs[i].firstEdge;
		while (node != NULL)
		{
			ins[node->ivex]++;
			node = node->nextEdge;
		}
	}

	//将所有顶点度数为0的进入队列
	for (i = 0; i < mVexNum; i++)
		if (ins[i] == 0)
			queue[rear++] = i;   //入队队列

	while (head != rear)        //队列非空
	{
		j = queue[head++];
		top[index++] = mVexs[j].data;
		node = mVexs[j].firstEdge;

		while (node != NULL)
		{
			ins[node->ivex]--;
			if (ins[node->ivex] == 0)
				queue[rear++] = node->ivex;   //入队队列

			node = node->nextEdge;
		}
	}

	if (index != mVexNum)
	{
		cout << "Graph has a cycle!" << endl;
		delete[]queue;
		delete[]ins;
		delete[]top;

		return 1;
	}

	//打印排序结果
	cout << "==TopSort==: ";
	for (i = 0; i < mVexNum; i++)
		cout << top[i] << " ";
	cout << endl;

	delete[]queue;
	delete[]ins;;
	delete[]top;

	return 0;

}

int ListDG::getPosition(char ch)
{
	int i;
	for (i = 0; i < mVexNum; i++)
		if (mVexs[i].data == ch)
			return i;

	return -1;
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

void ListDG::LinkLast(ENode *list, ENode *node)
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
		{ 'A', 'G' },
		{ 'B', 'A' },
		{ 'B', 'D' },
		{ 'C', 'F' },
		{ 'C', 'G' },
		{ 'D', 'E' },
		{ 'D', 'F' } };
	int vlen = sizeof(vexs) / sizeof(vexs[0]);
	int elen = sizeof(edges) / sizeof(edges[0]);
	ListDG* pG;

	// 自定义"图"(输入矩阵队列)
	//pG = new ListDG();
	// 采用已有的"图"
	pG = new ListDG(vexs, vlen, edges, elen);

	pG->PrintList();   // 打印图
				   //pG->DFS();     // 深度优先遍历
				   //pG->BFS();     // 广度优先遍历
	pG->TopologicalSort();     // 拓扑排序
	return 0;
}
