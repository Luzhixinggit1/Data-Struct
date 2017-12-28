/*
C++邻接表创建无向图
creator：lzx
编程环境：vs2015
*/
#include<iostream>
using namespace std;

#define MAX   50


class ListUDG
{
private:
	//内部类
	class ENode
	{
	public:                        //邻接表中表对应的顶点
		int ivex;                  //改变所指向的位置如边A->G则ivex为G所在位置的值
		ENode *nextEdge;           //指向下一条弧的指针
	};
	class VNode
	{
	public:                       
		char data;                   //顶点信息
		ENode *firstEdge;            //指向第一条依附该项的弧
	};
private:
	int mVexNum;                     //图的顶点数目
	int mEdgeNUM;                    //图的边数目
	VNode mVexs[MAX];                   
public:
	ListUDG();
	ListUDG(char vexs[],int vlen,char edges[][2],int elen);
	~ListUDG();
	void PrintUDG();
private:
	char readChar();
	int getPosition(char ch);
	void LinkLast(ENode *list, ENode *node);
};

//创建邻接表无向图（自己输入）
ListUDG::ListUDG()
{
	char c1, c2;
	int i, p1, p2;
	ENode *node1, *node2;



	//输入顶点数和边数
	cout << "input vertex number: ";
	cin >> mVexNum;
	cout << "input endge number: ";
	cin >> mEdgeNUM;
	if (mVexNum < 1 || mEdgeNUM<1 || (mEdgeNUM>(mVexNum*(mVexNum - 1))))
	{
		cout << "input error: invalid parameters!" << endl;
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
	for (i = 0; i < mVexNum; i++)
	{
		cout << "edge(" << i << "): ";

		c1 = readChar();
		c2 = readChar();

		p1 = getPosition(c1);
		p2 = getPosition(c2);

		//初始化node1
		node1 = new ENode();
		node1->ivex = p2;
		//将node1链接到p1所在链表的末尾
		if (mVexs[p1].firstEdge == NULL)
			mVexs[p1].firstEdge = node1;
		else
			LinkLast(mVexs[p1].firstEdge, node1);

		//初始化node2
		node2 = new ENode();
		node2->ivex = p1;
		if (mVexs[p2].firstEdge == NULL)
			mVexs[p2].firstEdge = node2;
		else
			LinkLast(mVexs[p2].firstEdge,node2);
	}
}

//创建邻接表无向图（用提供的数据）
ListUDG::ListUDG(char vexs[], int vlen, char edges[][2], int elen)
{
	int c1, c2;
	int i, p1, p2;
	ENode *node1, *node2;

	//初始化顶点数和边数
	mVexNum = vlen;
	mEdgeNUM = elen;

	//初始化邻接表的顶点
	for (i = 0; i < mVexNum; i++)
	{
		mVexs[i].data = vexs[i];
		mVexs[i].firstEdge = NULL;
	}

	//初始化邻接表的边
	for (i = 0; i < mVexNum; i++)
	{
		//读取边的起始顶点和结束顶点
		c1 = edges[i][0];
		c2 = edges[i][1];

		p1 = getPosition(c1);
		p2 = getPosition(c2);

		//初始化node1
		node1 = new ENode();
		node1->ivex = p2;
		if (mVexs[p1].firstEdge == NULL)
			mVexs[p1].firstEdge = node1;
		else
			LinkLast(mVexs[p1].firstEdge, node1);

		//初始化node2
		node2 = new ENode();
		node2->ivex = p1;
		if (mVexs[p2].firstEdge == NULL)
			mVexs[p2].firstEdge = node2;
		else
			LinkLast(mVexs[p2].firstEdge, node2);
	}
}

//析构函数
ListUDG::~ListUDG()
{

}

//将node节点连接到list的最后
void ListUDG::LinkLast(ENode *list, ENode *node)
{
	ENode *p;
	p = list;

	while (p->nextEdge)
	{
		p = p->nextEdge;
	}
	p->nextEdge = node;
}

//返回ch的位置
int ListUDG::getPosition(char ch)
{
	int i;
	for (i = 0; i < mVexNum; i++)
		if (mVexs[i].data == ch)
			return i;
	return -1;
}

//读取一个输入字符
char ListUDG::readChar()
{
	char ch;
	do
	{
		cin >> ch;
	} while (!(ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z'));

	return ch;

}


//打印邻接表
void ListUDG::PrintUDG()
{
	int i, j;
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




int main()
{
	/*char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	char edges[][2] = {
		{ 'A', 'C' },
		{ 'A', 'D' },
		{ 'A', 'F' },
		{ 'B', 'C' },
		{ 'C', 'D' },
		{ 'E', 'G' },
		{ 'F', 'G' } };
	int vlen = sizeof(vexs) / sizeof(vexs[0]);
	int elen = sizeof(edges) / sizeof(edges[0]);*/
	ListUDG* pG;

	// 自定义"图"(输入矩阵队列)
	pG = new ListUDG();
	// 采用已有的"图"
	//pG = new ListUDG(vexs, vlen, edges, elen);

	pG->PrintUDG();   // 打印图

	return 0;
}
