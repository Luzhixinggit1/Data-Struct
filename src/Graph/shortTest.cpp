#pragma once
#ifndef _GRAPHHH_
#define _GRAPHHH_

#define MAX    100
#define INF         (~(0x1<<31))        // 最大值(即0X7FFFFFFF)


//边的结构体
class EData
{
public:
	int start;            //边的起点
	int end;              //边的终点
	int weight;           //边的权重
public:
	EData() {}
	EData(int s, int e, int w) :start(s), end(e), weight(w) {}
};

//邻接表
class ListGraph
{
private:
	//邻接表中对应链表的头
	class ENode
	{
	public:
		int ivex;                     //该边所指向的位置
		int weight;                   //该边的权重
		ENode *nextEdge;              //指向下一条弧的指针
	};
	class VNode
	{
	public:
		int data;
		ENode *firstEdge;
	};
private:
	int vexNum;         //顶点的数目
	int edgeNum;        //图的边数
	VNode Vexs[MAX];
public:
	//自己输入数据创建邻接表图
	ListGraph();
	//用已经提供的数据，创建邻接表
	ListGraph(int vexs[], int vlen, EData *edges[], int elen);
	~ListGraph();
	// Dijkstra最短路径
	void dijkstra(int vs, int pre[], int dist[]);
	//floyd算法求最短路径
	void floyd(int path[MAX][MAX], int dist[MAX][MAX], int vs);
	//输出图
	void PrintGraph();
private:
	void linkLast(ENode *list, ENode *node);
	// 获取边<start, end>的权值；若start和end不是连通的，则返回无穷大。
	int getWeight(int start, int end);
};
void Menu();

#endif

#include"graph.h"
#include<iostream>
using namespace std;

ListGraph::ListGraph()
{
	int i, v1, v2;
	int weight;
	ENode *node1, *node2;

	cout << "请输入顶点数： ";
	cin >> vexNum;
	cout << "请输入边数： ";
	cin >> edgeNum;
	if (vexNum < 1 || edgeNum<1 || edgeNum>(vexNum*(vexNum - 1)))
	{
		cout << "输入错误，错误的边数和顶点数！";
		return;
	}

	//初始化邻接表的顶点
	for (i = 0; i < edgeNum; i++)
	{
		Vexs[i].data = i + 1;
		Vexs[i].firstEdge = NULL;
	}
	cout << endl;

	//初始化邻接表的边
	for (i = 0; i < edgeNum; i++)
	{
		cout << "edge(" << i << "): ";

		cin >> v1;
		cin >> v2;
		cin >> weight;

		//初始化node1
		node1 = new ENode();
		node1->ivex = v2 - 1;
		node1->weight = weight;
		if (Vexs[v1 - 1].firstEdge == NULL)
			Vexs[v1 - 1].firstEdge = node1;
		else
			linkLast(Vexs[v1 - 1].firstEdge, node1);

		//因为是无向图，所以有a->b，则必有b->a;
		node2 = new ENode();
		node2->ivex = v1 - 1;
		node2->weight = weight;
		if (Vexs[v2 - 1].firstEdge == NULL)
			Vexs[v2 - 1].firstEdge = node2;
		else
			linkLast(Vexs[v2 - 1].firstEdge, node2);

	}
}

ListGraph::ListGraph(int vexs[], int vlen, EData * edges[], int elen)
{
	int i, v1, v2;
	int weight;
	ENode *node1, *node2;

	//初始化顶点数和边数
	vexNum = vlen;
	edgeNum = elen;

	//初始化顶点
	for (i = 0; i < vexNum; i++)
	{
		Vexs[i].data = vexs[i];
		Vexs[i].firstEdge = NULL;
	}

	//初始化边
	for (i = 0; i < edgeNum; i++)
	{
		v1 = edges[i]->start;
		v2 = edges[i]->end;
		weight = edges[i]->weight;

		node1 = new ENode();
		node1->ivex = v2 - 1;
		node1->weight = weight;
		if (Vexs[v1 - 1].firstEdge == NULL)
			Vexs[v1 - 1].firstEdge = node1;
		else
			linkLast(Vexs[v1 - 1].firstEdge, node1);

		node2 = new ENode();
		node2->ivex = v1 - 1;
		node2->weight = weight;
		if (Vexs[v2 - 1].firstEdge == NULL)
			Vexs[v2 - 1].firstEdge = node2;
		else
			linkLast(Vexs[v2 - 1].firstEdge, node2);
	}
}

ListGraph::~ListGraph()
{

}

//dijikstra最短路径算法
void ListGraph::dijkstra(int vs, int pre[], int dist[])
{
	int i, j, k;
	int tmp;
	int min;
	int flag[MAX];

	for (i = 0; i < vexNum; i++)
	{
		flag[i] = 0;                    //flag[i] = 1说明该点的最短路径已经找到
		pre[i] = 0;                     //i的前驱结点初始化为0
		dist[i] = getWeight(vs, i);     //i到j的距离为权重
	}

	flag[vs] = 1;
	dist[vs] = 0;

	for (i = 1; i < vexNum; i++)
	{
		min = INF;
		for (j = 0; j < vexNum; j++)
		{
			if (flag[j] == 0 && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}
		flag[k] = 1;
		for (j = 0; j < vexNum; j++)
		{
			tmp = getWeight(k, j);
			tmp = (tmp == INF ? INF : min + tmp);
			if (flag[j] == 0 && tmp < dist[j])
			{
				dist[j] = tmp;
				pre[j] = k;
			}
		}

	}

	// 打印dijkstra最短路径的结果
	/*cout << "dijkstra(" << Vexs[vs].data << "): " << endl;*/
	for (i = 0; i < vexNum; i++)
		cout << "  shortest(" << Vexs[vs].data << " -> " << Vexs[i].data << ")=" << dist[i] << endl;
}

/*
path:表示路径，path[i][j] = k表示顶点i到顶点j的路径经过顶点k
dist:长度数组，如dist[i][j] = m表示路径i，到j的距离是m

*/
void ListGraph::floyd(int path[MAX][MAX], int dist[MAX][MAX], int vs)
{
	int i, j, k;
	int temp;

	//个顶点之间距离进行初始化
	for (i = 0; i < vexNum; i++)
	{
		for (j = 0; j < vexNum; j++)
		{
			dist[i][j] = getWeight(i, j);     //i到j的距离是i到j的权重
			path[i][j] = j;                   //i到j的距离经过j
		}
	}

	//计算最短路径
	for (k = 0; k < vexNum; k++)
	{
		for (i = 0; i < vexNum; i++)
		{
			for (j = 0; j < vexNum; j++)
			{
				//如果经过下标为k顶点的路径比i到j还短ze更新dist[i][j]和path[i][j]
				temp = (dist[i][k] == INF || dist[k][j] == INF) ? INF : (dist[i][k] + dist[k][j]);
				if (dist[i][j]>temp)
				{
					//如果经过k这个顶点的距离比直接经过j的距离短，则更新数据
					dist[i][j] = temp;
					//不能直接设置为k因为k也有邻边
					path[i][j] = path[i][k];
				}
			}
		}
	}

	//打印最短路径的结果
	for (i = 0; i < vexNum; i++)
	{
		cout << "  shortest(" << Vexs[vs].data << " -> " << Vexs[i].data << ")=" << dist[vs][i];
		cout << endl;
	}

}



void ListGraph::PrintGraph()
{
	int i;
	ENode *node;

	cout << "List Graph:" << endl;
	for (i = 0; i < vexNum; i++)
	{
		cout << Vexs[i].data << "->";
		node = Vexs[i].firstEdge;
		while (node != NULL)
		{
			cout << Vexs[node->ivex].data << "->";
			node = node->nextEdge;
		}
		cout << "NULL" << endl;
	}
}

void ListGraph::linkLast(ENode * list, ENode * node)
{
	ENode *p = list;
	while (p->nextEdge)
		p = p->nextEdge;
	p->nextEdge = node;
}

int ListGraph::getWeight(int start, int end)
{
	ENode *node;

	if (start == end)
		return 0;

	node = Vexs[start].firstEdge;
	while (node != NULL)
	{
		if (end == node->ivex)             //一个顶点可能有多个邻接点
			return node->weight;
		else
			node = node->nextEdge;
	}

	return INF;                //如果不是邻接点，则返回无穷大
}

void Menu()
{
	cout << "程序说明：" << endl;
	cout << "1，2，3，4，5分别代表综合楼，文科教学楼，教学楼，信科楼，音乐楼。" << endl;
	cout << "0,推出程序!" << endl;

}



int main()
{
	int prev[MAX] = { 0 };
	int dist[MAX] = { 0 };

	int path[MAX][MAX] = { 0 };    // 用于保存floyd路径
	int floy[MAX][MAX] = { 0 };    // 用于保存floyd长度
	// 顶点
	int vexs[] = { 1,2,3,4,5 };
	// 边
	EData *edges[] = {
		// 起点 终点 权
		new EData(1, 2, 180),
		new EData(1, 3, 100),
		new EData(1,4, 150),
		new EData(2,4, 50),
		new EData(3, 4,80),
		new EData(4,5, 120),
		new EData(2,5, 130),
	};
	int vlen = sizeof(vexs) / sizeof(vexs[0]);
	int elen = sizeof(edges) / sizeof(edges[0]);
	ListGraph* pG;

	// 自定义"图"(输入矩阵队列)
	//pG = new ListUDG();
	// 采用已有的"图"
	pG = new ListGraph(vexs, vlen, edges, elen);
	int i;
	Menu();
	cout << "请输入你要求的楼栋到其他楼栋的最小路径: " << endl;
	while (cin >> i)
	{
		if (i == 0)
		{
			break;
		}
		pG->floyd(path, floy, i - 1);
	}





	return 0;
}



