#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <set>
#include <string>
#include <sstream>
using namespace std;

class Node 
{
private:
	int ID;
	set<int> adjacencyList;
	bool isVisited = false;
public:
	Node() {}
	~Node() {}

	void setID(int num)
	{
		ID = num;
	}
	int getID()
	{
		return ID;
	}
	void addAdjacency(int nextRule)
	{
		adjacencyList.insert(nextRule);
	}
	set<int> getAdjacencyList()
	{
		return adjacencyList;
	}
	void visited()
	{
		isVisited = true;
	}
	bool hasVisited()
	{
		return isVisited;
	}
	string toString()
	{
		ostringstream out;
		unsigned int i = 0;
		out << "R" << ID << ":";
		for (set<int>::iterator it = adjacencyList.begin(); it != adjacencyList.end(); ++it)
		{
			int num = *it;
			i++;
			out << "R" << num;
			if (i != adjacencyList.size())
			{
				out << ",";
			}
		}
		out << endl;
		return out.str();
	}
};

#endif // NODE_H