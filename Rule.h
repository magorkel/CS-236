#ifndef RULE_H
#define RULE_H
#include <vector>
#include <sstream>
#include "Predicate.h"
using namespace std;
class Rule
{
private:
	Predicate headPredicate;
	vector<Predicate> predicateList;
public:
	Rule() {}
	Rule(Predicate head, vector<Predicate> list) : headPredicate(head), predicateList(list) {}
	~Rule() {}

	Predicate getHeadPredicate()
	{
		return headPredicate;
	}
	vector<Predicate> getPredicateList()
	{
		return predicateList;
	}
	string toString()
	{
		ostringstream out;
		out << headPredicate.toString() << " :- ";
		for (unsigned int i = 0; i < predicateList.size(); ++i)
		{
			out << predicateList.at(i).toString();
			if (i != predicateList.size() - 1)
			{
				out << ",";
			}
		}
		return out.str();
	}
};

#endif // RULE_H