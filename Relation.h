#ifndef RELATION_H
#define RELATION_H
//#define DEBUG(s) cout << s;
#define DEBUG(s)
#include <set>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Tuple.h"
using namespace std;

class Relation
{
private:
	string name;
	Tuple scheme;//Header
	set<Tuple> myRelation;
	map<int, int> match;//key: where in this relation, second multiple spots in r2
public:
	Relation(string rName, Tuple rScheme) : name(rName), scheme(rScheme) {};
	Relation() {};
	~Relation() {};

	string getName()
	{
		return name;
	}
	int getRelationSize()
	{
		int size = 0;
		for (set<Tuple>::iterator it = myRelation.begin(); it != myRelation.end(); ++it)
		{
			size++;
		}
		return size;
	}
	set<Tuple>& getMyRelation()
	{
		return myRelation;
	}
	string setName(string newName)
	{
		name = newName;
		return name;
	}
	Tuple setScheme(Tuple newScheme)
	{
		scheme = newScheme;
		return scheme;
	}
	Relation select1(int index, string value)
	{
		Relation temp(this->name, this->scheme);
		//DEBUG(temp.toString() << endl);
		for (Tuple currentTuple : myRelation)
		{
			if (currentTuple.at(index) == value)
			{
				temp.addTuple(currentTuple);
			}
		}
		//DEBUG(temp.toString() << endl);
		return temp;
	}
	Relation select2(int index, vector<string> value)
	{
		Relation temp(this->name, this->scheme);
		string tv;
		string queryParameter = value.at(index);
		for (Tuple currentTuple : myRelation)
		{
			tv = currentTuple.at(index);
			bool same = false;
			for (int i = 0; i < index; ++i)
			{
				if ((value.at(i) == value.at(index)) && (tv != currentTuple.at(i)))
				{
					same = true;
					break;
				}
			}
			if (!same) temp.addTuple(currentTuple);
		}
		//DEBUG(temp.toString() << endl);
		return temp;
	}
	Relation project(vector<int> index)
	{
		Relation temp(this->name, this->scheme);
		if (this->getRelationSize() == 0)
		{
			Tuple newScheme;
			for (unsigned int i = 0; i < index.size(); ++i)
			{
				for (int j = 0; j < (int)this->scheme.size(); ++j)
				{
					if (index.at(i) == j)
					{
						newScheme.push_back(scheme.at(index.at(i)));
					}
				}
			}
			temp.scheme = newScheme;
		}
		for (Tuple currentTuple : myRelation)
		{
			Tuple newTup;
			Tuple newScheme;
			for (unsigned int i = 0; i < index.size(); ++i)
			{
				for (int j = 0; j < (int)this->scheme.size(); ++j)
				{
					if (index.at(i) == j)
					{
						newTup.push_back(currentTuple.at(index.at(i)));
						newScheme.push_back(scheme.at(index.at(i)));
					}
				}
			}
			//don't delete: worked for lab 3
			/*for (unsigned int i = 0; i < this->scheme.size(); ++i)
			{
				for (unsigned int j = 0; j < index.size(); ++j)
				{
					int k = index.at(j);
					if (i == k)//(i == j)
					{
						newTup.push_back(currentTuple.at(index.at(i)));//
						newScheme.push_back(scheme.at(index.at(i)));
					}
				}
			}*/
			temp.scheme = newScheme;
			temp.addTuple(newTup);
		}
		return temp;
	}
	void rename(int i, string val)
	{
		scheme.at(i) = val;
	}
	bool isJoinable(Tuple& tup1, Tuple& tup2)
	{
		Tuple newTup;
		for (unsigned int i = 0; i < tup1.size(); ++i)
		{
			newTup.push_back(tup1.at(i));
		}
		for (unsigned int i = 0; i < tup2.size(); ++i)
		{
			newTup.push_back(tup2.at(i));
		}
		bool yes = true;
		for (pair<int, int> p : match)
		{
			int key = p.first;
			int value = p.second;
			if (newTup.at(key) == (newTup.at(value))) yes = true;
			else
			{
				yes = false;
				break;
			}
		}
		return yes;
	}
	Tuple combineSchemes(Relation& r)
	{
		set<string> attributes;
		Tuple temp;
		Tuple combinedTup;
		Tuple tup1 = this->getScheme();
		Tuple tup2 = r.getScheme();
		for (unsigned int i = 0; i < tup1.size(); ++i)
		{
			temp.push_back(tup1.at(i));
		}
		for (unsigned int i = 0; i < tup2.size(); ++i)
		{
			temp.push_back(tup2.at(i));
		}
		for (unsigned int i = 0; i < temp.size(); ++i)
		{
			for (unsigned int j = i; j < temp.size(); ++j)
			{
				if (i != j)
				{
					if (temp.at(i) == temp.at(j))
					{
						match.insert(pair<int, int>(i, j));
					}
				}
			}
		}
		for (unsigned int i = 0; i < temp.size(); ++i)
		{
			bool found = false;
			for (map<int, int>::iterator it = match.begin(); it != match.end(); ++it)
			{
				unsigned int value = it->second;
				if (i == value)
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				combinedTup.push_back(temp.at(i));
			}
		}
		return combinedTup;
	}
	Tuple combineTuples(Tuple& tup1, Tuple& tup2)
	{
		Tuple newTup;
		Tuple combinedTup;
		for (unsigned int i = 0; i < tup1.size(); ++i)
		{
			newTup.push_back(tup1.at(i));
		}
		for (unsigned int i = 0; i < tup2.size(); ++i)
		{
			newTup.push_back(tup2.at(i));
		}
		for (unsigned int i = 0; i < newTup.size(); ++i)
		{
			bool found = false;
			for (map<int, int>::iterator it = match.begin(); it != match.end(); ++it)
			{
				unsigned int value = it->second;
				if (i == value)
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				combinedTup.push_back(newTup.at(i));
			}
		}
		return combinedTup;
	}
	Relation join(Relation& r)
	{
		Relation temp;
 		temp.setScheme(this->combineSchemes(r));
		for (set<Tuple>::iterator it1 = this->getMyRelation().begin(); it1 != this->getMyRelation().end(); ++it1)
		{
			Tuple tup1 = *it1;
			for (set<Tuple>::iterator it2 = r.getMyRelation().begin(); it2 != r.getMyRelation().end(); ++it2)
			{
				Tuple tup2 = *it2;
				if (isJoinable(tup1, tup2))
				{ 
					temp.addTuple(combineTuples(tup1, tup2));
				}
			}
		}
		return temp;
	}
	Relation unionF(Relation& r)
	{
		for (set<Tuple>::iterator it = r.getMyRelation().begin(); it != r.getMyRelation().end(); ++it)
		{
			int preCount = this->getRelationSize();//number of tuples
			this->addTuple(*it);
			Tuple tup = *it;
			if (this->getRelationSize() != preCount)
			{
				cout << "  ";
				for (unsigned int i = 0; i < scheme.size(); ++i)
				{
					if (scheme.at(i).at(0) != '\'')
					{
						cout << scheme.at(i) << "=" << tup.at(i);
						if (i < (scheme.size() - 1))//
						{
							cout << ", ";
						}
					}
				}
				cout << endl;
			}
		}
		return *this;
	}
	Tuple getScheme()
	{
		return scheme;
	}
	void addTuple(Tuple myTuple)
	{
		myRelation.insert(myTuple);
	}
	string toString()
	{
		ostringstream out;
		set<Tuple>::iterator it;
		bool yes = true;
		for (it = myRelation.begin(); it != myRelation.end(); ++it)
		{
			vector<string> tups = *it;
			if (tups.at(0) != scheme.at(0))
			{
				out << "  ";
			}
			for (unsigned int i = 0; i < scheme.size(); ++i)
			{
				if (scheme.at(i).at(0) != '\'')
				{
					out << scheme.at(i) << "=" << tups.at(i);
					if (i < (scheme.size()-1))//
					{
						out << ", ";
					}
				}
				if (tups.at(i) == scheme.at(i))
				{
					yes = false;
				}
			}
			if (yes) out << endl;
		}
		return out.str();
	}
};
#endif //RELATION_H

