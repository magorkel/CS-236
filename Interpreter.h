#ifndef INTERPRETER_H
#define INTERPRETER_H
//#define DEBUG(s) cout << s;
#define DEBUG(s)
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include "Tuple.h"
#include <iostream>
#include "DatalogProgram.h"
#include "Database.h"
#include "Predicate.h"
#include "Rule.h"
using namespace std;
class Interpreter
{
private:
	DatalogProgram datalog;
	vector<Predicate> schemeVector;
	vector<Predicate> factVector;
	vector<Rule> ruleVector;
	vector<Predicate> queryVector;
	Database database;
public:
	Interpreter() {};
	~Interpreter() {};

	DatalogProgram getDatalog()
	{
		return datalog;
	}
	void buildRelation(DatalogProgram newDatalog)
	{
		datalog = newDatalog;
		schemeVector = datalog.getSchemeVector();
		factVector = datalog.getFactVector();
		ruleVector = datalog.getRuleVector();
		queryVector = datalog.getQueryVector();

		//scheme loop
		for (unsigned int i = 0; i < schemeVector.size(); ++i)
		{
			Relation relation;
			string attributes = schemeVector.at(i).getHeader();
			relation.setName(attributes);
			Tuple scheme;
			for (unsigned int j = 0; j < schemeVector.at(i).getParametersList().size(); ++j)
			{
				scheme.push_back(schemeVector.at(i).getParametersList().at(j));
			}
			relation.setScheme(scheme);
			database.insert(pair<string, Relation>(attributes, relation));
		}
		//fact loop
		for (unsigned int i = 0; i < factVector.size(); ++i)
		{
			Tuple tuple;
			for (unsigned int j = 0; j < factVector.at(i).getParametersList().size(); ++j)
			{
				tuple.push_back(factVector.at(i).getParametersList().at(j));
			}
			database.at(factVector.at(i).getHeader()).addTuple(tuple);
		}
		//rule loop
		cout << "Dependency Graph" << endl;
		datalog.makeGraph();
		vector<set<int>> v = datalog.makeReverseGraph().getV();
		cout << endl;
		cout << "Rule Evaluation" << endl;
		int preCount = 0;
		int postCount = 0;
		for (unsigned int i = 0; i < v.size(); ++i)
		{
			int numberOfPasses = 0;
			cout << "SCC: ";
			ostringstream out;
			for (set<int>::iterator it2 = v.at(i).begin(); it2 != v.at(i).end(); ++it2)
			{
				out << "R" << *it2;
				if (it2 != v.at(i).end())
				{
					out << ",";
				}
			}
			string output = out.str();
			if (output.size() != 0)
			{
				output.pop_back();
			}
			cout << output;
			cout << endl;
			do
			{
				preCount = count();
				bool yes = false;
				for (set<int>::iterator it2 = v.at(i).begin(); it2 != v.at(i).end(); ++it2)
				{
					evaluateRule(ruleVector.at(*it2));
					if ((v.at(i).size() == 1) && (!datalog.found(datalog.getGraph(), *it2)))
					{
						yes = true;
					}
				}
				postCount = count();
				numberOfPasses++;
				if (yes) goto exit;
			} while (preCount != postCount);
		exit:
			//cout << "Schemes populated after " << numberOfPasses << " passes through the Rules." << endl;
			cout << numberOfPasses << " passes: " << output << endl;
		}
		//query loop
		cout << endl << "Query Evaluation" << endl;
		for (unsigned int i = 0; i < queryVector.size(); ++i)
		{
			Relation temp = evaluateQuery(queryVector.at(i));
			cout << queryVector.at(i).toString() << "?";
			if (temp.getMyRelation().size() > 0)
			{
				cout << " Yes(" << temp.getMyRelation().size() << ")" << endl;
				cout << temp.toString();
			}
			else
			{
				cout << " No" << endl;
				cout << temp.toString();
			}
		}
	}
	int count()
	{
		int numTups = 0;
		for (map<string, Relation>::iterator it = database.begin(); it != database.end(); ++it)
		{
			numTups += it->second.getRelationSize();
		}
		return numTups;
	}
	void evaluateRule(Rule rule)
	{
		Relation relation = evaluateQuery(rule.getPredicateList().at(0));
		for (unsigned int i = 1; i < rule.getPredicateList().size(); ++i)
		{
			Relation r2 = evaluateQuery(rule.getPredicateList().at(i));
			relation = relation.join(r2);
		}
		vector<int> index;
		for (unsigned int i = 0; i < rule.getHeadPredicate().getParametersList().size(); ++i)
		{
			for (unsigned int j = 0; j < relation.getScheme().size(); ++j)
			{
				if (rule.getHeadPredicate().getParametersList().at(i) == relation.getScheme().at(j))
				{
					index.push_back(j);
				}
			}
		}
		relation = relation.project(index);
		string name = rule.getHeadPredicate().getHeader();
		for (unsigned int i = 0; i < relation.getScheme().size(); ++i)
		{
			for (unsigned int j = 0; j < schemeVector.size(); ++j)
			{
				if (name == schemeVector.at(j).getHeader())
				{
					relation.rename(i, schemeVector.at(j).getParametersList().at(i));
				}
			}
		}
		cout << rule.toString() << "." << endl;
		for (unsigned int j = 0; j < rule.getPredicateList().size(); ++j)
		{
			relation = database.at(name).unionF(relation);
		}
	}
	Relation evaluateQuery(Predicate query)
	{
		//DEBUG(query.toString() << endl );
		Relation temp = database[query.getHeader()];
		vector<int> indexNums;
		vector<string> remembered;
		for (unsigned int i = 0; i < query.getParametersList().size(); ++i)
		{
			if (query.getParametersList().at(i).at(0) != '\'')
			{
				temp = temp.select2(i, query.getParametersList());
				remembered.push_back(query.getParametersList().at(i));
				indexNums.push_back(i);
				temp.rename(i, query.getParametersList().at(i));
				for (unsigned int j = 0; j < remembered.size() - 1; ++j)
				{
					if (remembered.at(j) == query.getParametersList().at(i))
					{
						remembered.pop_back();
						indexNums.pop_back();
						break;
					}
				}
			}
			if (query.getParametersList().at(i).at(0) == '\'')
			{
				temp = temp.select1(i, query.getParametersList().at(i));
				temp.rename(i, query.getParametersList().at(i));
			}
		}
		if (indexNums.size() > 0)
		{
			temp = temp.project(indexNums);
		}
		/*cout << query.toString() << "?";
		if (temp.getMyRelation().size() > 0)
		{
			cout << " Yes(" << temp.getMyRelation().size() << ")" << endl;
			cout << temp.toString();
		}
		else
		{
			cout << " No" << endl;
			cout << temp.toString();
		}*/
		return temp;
	}
	string toString()
	{
		ostringstream out;
		for (map<string, Relation>::iterator it = database.begin(); it != database.end(); ++it)
		{
			out << it->first << ":" << endl;
			out << it->second.toString() << endl;
		}
		return out.str();
	}
};
#endif //INTERPRETER_H