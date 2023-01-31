#include <iostream>>
#include <vector>
#include <unordered_map>
using namespace std;

class DisJointSet
{
public:
	unordered_map<int, int> parent;
	unordered_map<int, int> rank;

	void makeSet(vector<int> const& universe)
	{
		for (int i = 0; i < universe.size(); i++)
		{
			parent[i] = i;
			rank[i] = 1;
		}
	}
	int Find(int k)
	{
		if (parent[k] == k)
			return k;
		return Find(parent[k]);
	}

	bool Union(int a, int b)
	{
		int x = Find(a);
		int y = Find(b);
		if (x == y)
		{
			return false;
		}
		if (rank[x] > rank[y])
		{
			parent[y] = x; rank[x]++;
			return true;
		}
		else
		{
			parent[x] = y; rank[y]++;
			return true;
		}
	}
};

struct Edge 
{
	int src, dest;
	Edge()
	{}
	Edge(int x, int y)
	{
		src = x;
		dest = y;
	}
};
class Graph 
{
public:
	vector<Edge> adjList;

	Graph(vector<Edge> const& edges)
	{
		adjList = edges;
	}
	bool DetectCycle()
	{
		DisJointSet set;
		vector<int> parent;
		parent.resize(adjList.size() * 2);
		set.makeSet(parent);
		for (int i = 0; i < adjList.size(); i++)
		{
			if (set.Union(adjList[i].src, adjList[i].dest) == false)
			{
				return true;
			}
		}
		return false;
	}
	void printGraph()
	{
		for (int i = 0; i < adjList.size(); i++)
		{
			cout << adjList[i].src << "--> " << adjList[i].dest;
			cout << endl;
		}
	}
};



int main()
{
	vector<Edge> edges1;
	edges1.push_back(Edge(0, 1));
	edges1.push_back(Edge(0, 2));
	edges1.push_back(Edge(1, 3));
	edges1.push_back(Edge(1, 4));

	vector<Edge> edges2;
	edges2.push_back(Edge(0, 1));
	edges2.push_back(Edge(0, 2));
	edges2.push_back(Edge(1, 3));
	edges2.push_back(Edge(1, 4));
	edges2.push_back(Edge(3, 4));

	Graph graph1(edges1);
	Graph graph2(edges2);

	cout << "Graph1: " << endl;
	graph1.printGraph();
	if (graph1.DetectCycle())
	{
		cout << "There exists a cycle in the first graph" << endl;
	}
	else cout << "There is not a cycle in the first graph" << endl;
	cout << endl;
	cout << "Graph2: " << endl;
	graph2.printGraph();
	if (graph2.DetectCycle())
	{
		cout << "There exists a cycle in the second graph" << endl;
	}
	else cout << "There is not a cycle in the second graph" << endl;

	
	

	system("pause");
	return 0;
	
}

