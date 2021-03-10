#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include <vector>
#include <sstream>
#include <string>
#include <set>
#include "Predicate.h"
#include "Rule.h"
#include "Graph.h"
#include "Node.h"
using namespace std;
class DatalogProgram
{
private:
	vector<Predicate> schemeVector;
	vector<Predicate> factVector;
	vector<Rule> ruleVector; 
	vector<Predicate> queryVector;
	set<string> domainSet;
	Graph graph;
	Graph reverseGraph;
public:
	vector<Predicate>& getSchemeVector()
	{
		return schemeVector;
	}
	vector<Predicate>& getFactVector()
	{
		return factVector;
	}
	vector<Rule>& getRuleVector()
	{
		return ruleVector;
	}
	vector<Predicate>& getQueryVector()
	{
		return queryVector;
	}
	void pushScheme(Predicate current)
	{
		schemeVector.push_back(current);
	}
	void pushFact(Predicate current)
	{
		factVector.push_back(current);
	}
	void pushRule(Rule current)
	{
		ruleVector.push_back(current);
	}
	void pushQuery(Predicate current)
	{
		queryVector.push_back(current);
	}
	Graph getGraph()
	{
		return graph;
	}
	Graph makeGraph()
	{
		for (unsigned int i = 0; i < ruleVector.size(); ++i)
		{
			Node node;
			node.setID(i);
			for (unsigned int j = 0; j < ruleVector.at(i).getPredicateList().size(); ++j)
			{
				string predHeader = ruleVector.at(i).getPredicateList().at(j).getHeader();
				for (unsigned int k = 0; k < ruleVector.size(); ++k)
				{
					string ruleHeader = ruleVector.at(k).getHeadPredicate().getHeader();
					if (predHeader == ruleHeader)
					{
						node.addAdjacency(k);
					}
				}
			}
			graph.insert(pair<int, Node>(i, node));
		}
		cout << graph.toString();
		return graph;
	}
	Graph makeReverseGraph()
	{
		for (unsigned int i = 0; i < ruleVector.size(); ++i)
		{
			Node node;
			node.setID(i);
			reverseGraph.insert(pair<int, Node>(i, node));
		}
		for (map<int, Node>::iterator it1 = graph.begin(); it1 != graph.end(); ++it1)
		{
			int ID = it1->first;
			set<int> adjList = it1->second.getAdjacencyList();
			for (set<int>::iterator it2 = adjList.begin(); it2 != adjList.end(); ++it2)
			{
				reverseGraph.at(*it2).addAdjacency(ID);
			}
		}
		//cout << endl << reverseGraph.toString() << endl;
		reverseGraph.driver(graph);
		//cout << reverseGraph.outPutPostOrder() << endl;
		//reverseGraph.outV();
		return reverseGraph;
	}
	bool found(Graph g, int i)
	{
		Node node = g.at(i);
		set<int> al = node.getAdjacencyList();
		for (set<int>::iterator it = al.begin(); it != al.end(); ++it)
		{
			if (node.getID() == *it) return true;
		}
		return false;//want false
	}
	void addToSet(vector<string>& predicateVector, set<string>& domainSet)
	{
		for (unsigned int i = 0; i < predicateVector.size(); ++i)
		{
			domainSet.insert(predicateVector.at(i));
		}
	}
	string toString()
	{
		ostringstream out;
		out << "Schemes(" << schemeVector.size() << "):" << endl;
		for (unsigned int i = 0; i < schemeVector.size(); ++i)
		{
			out << "  " << schemeVector.at(i).toString() << endl;
		}
		out << "Facts(" << factVector.size() << "):" << endl;
		for (unsigned int i = 0; i < factVector.size(); ++i)
		{
			addToSet(factVector.at(i).getParametersList(), domainSet);
			out << "  " << factVector.at(i).toString() << "." << endl;
		}
		out << "Rules(" << ruleVector.size() << "):" << endl;
		for (unsigned int i = 0; i < ruleVector.size(); ++i)
		{
			out << "  " << ruleVector.at(i).toString() << "." << endl;
		}
		out << "Queries(" << queryVector.size() << "):" << endl;
		for (unsigned int i = 0; i < queryVector.size(); ++i)
		{
			out << "  " << queryVector.at(i).toString() << "?" << endl;
		}
		set<string> ::iterator itr;
		out << "Domain(" << domainSet.size() << "):" << endl;
		for (itr = domainSet.begin(); itr != domainSet.end(); ++itr)
		{
			out << *itr << endl;
		}
		return out.str();
	}
};
#endif //DATALOGPROGRAM_H

