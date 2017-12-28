class Node
{
public:
	int dest;
	Node *next;
};

class Graph
{
private:
	int V;
	Node* array;
public:
	Graph(int V);
	void addEdge(int src, int dest);
	void printGraph();
	~Graph();
};

Graph::~Graph()
{
	delete[]array;
}

Graph::Graph(int V)
{
	this->V = V;
	/*Node *a = new Node[V];*/
	this->array = new Node[V];
	for (int i = 0; i < V; i++)
		this->array[i].next = NULL;
}

void Graph::addEdge(int src, int dest)
{
	Node *newNode = new Node;
	newNode->dest = dest;
	newNode->next = this->array[src].next;
	this->array[src].next = newNode;
	Node *newNode0 = new Node;
  /*因为是无向图，所以a->b则应该有b->a*/
	newNode0->dest = src;
	newNode0->next = this->array[dest].next;
	this->array[dest].next = newNode0;
}

void Graph::printGraph()
{
	int v;
	for (v = 0; v < this->V; ++v)
	{
		Node* pCrawl = this->array[v].next;
		printf("\n Adjacency list of vertex %d\n head ", v);
		while (pCrawl)
		{
			printf("-> %d", pCrawl->dest);
			pCrawl = pCrawl->next;
		}
		printf("\n");
	}
}


int main()
{
	int V = 5;
	Graph G(5);
	G.addEdge(0, 1);
	G.addEdge(0, 4);
	G.addEdge(1, 2);
	G.addEdge(1, 3);
	G.addEdge(1, 4);
	G.addEdge(2, 3);
	G.addEdge(3, 4);

	G.printGraph();

	return 0;
}
