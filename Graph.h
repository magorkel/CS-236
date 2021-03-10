#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <set>
#include <iterator>
#include <sstream>
#include <iostream>
#include <stack>
#include "Node.h"
using namespace std;

class Graph : public map<int, Node>
{
private:
	stack<int> postOrder;
	stack<int> postOrder2;
	vector<set<int>> v;
public:
	Graph() {}
	~Graph() {}

	vector<set<int>> getV()
	{
		return v;
	}
	void outV()
	{
		for (unsigned int i = 0; i < v.size(); ++i)
		{
			for (set<int>::iterator it = v.at(i).begin(); it != v.at(i).end(); ++it)
			{
				cout << *it << " ";
			}
			cout << endl;
		}
	}
	void driver(Graph g)
	{
		for (map<int, Node>::iterator it = this->begin(); it != this->end(); ++it)
		{
			Node node = it->second;
			if (!DFS(node));
		}
		while (!postOrder.empty())
		{
			set<int> s;
			if (!SCC(g, postOrder.top(), s)) v.push_back(s);//scc = v
			postOrder.pop();
		}
	}
	bool SCC(Graph& g, int top, set<int>& s)
	{
		if (g.at(top).hasVisited()) return true;
		g.at(top).visited();
		for (int i : g.at(top).getAdjacencyList())
		{
			if (SCC(g, i, s)) continue;
		}
		s.insert(top);
		return false;
	}
	bool DFS(Node& node)
	{
		int id = node.getID();
		if (this->at(id).hasVisited()) return true;
		this->at(id).visited();
		for (int i : node.getAdjacencyList())
		{
			if (DFS(this->at(i))) continue;
		}
		postOrder.push(node.getID());
		postOrder2.push(node.getID());
		return false;
	}
	stack<int>& getPostOrder()
	{
		return postOrder;
	}
	string outPutPostOrder()
	{
		ostringstream out;
		out << "Post Order List: ";
		while (!postOrder2.empty())
		{
			out << "R" << postOrder2.top() << " ";
			postOrder2.pop();
		}
		out << endl;
		return out.str();
	}
	string toString()
	{
		ostringstream out;
		for (map<int, Node>::iterator it = this->begin(); it != this->end(); ++it)
		{
			Node value = it->second;
			out << value.toString();
		}
		return out.str();
	}
};

#endif //GRAPH_H
