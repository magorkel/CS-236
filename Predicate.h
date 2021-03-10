#ifndef PREDICATE_H
#define PREDICATE_H
#include <string>
#include <vector>
#include <sstream>
using namespace std;
class Predicate
{
private:
	string ID;
	vector<string> parameters;
public:
	Predicate(string IDName, vector<string> paremetersName) : ID(IDName), parameters(paremetersName) {}
	Predicate() {}
	~Predicate() {}

	string& getHeader()
	{
		return ID;
	}
	vector<string>& getParametersList()
	{
		return parameters;
	}
	string toString()
	{
		ostringstream out;
		out << ID << "(";
		for (unsigned int i = 0; i < parameters.size(); ++i)
		{
			out << parameters.at(i);
			if (parameters.at(i) == "(") continue;
			if (i != parameters.size() - 1 && parameters.at(i + 1) == "+") continue;
			if (i != parameters.size() - 1 && parameters.at(i + 1) == "*") continue;
			if (parameters.at(i) == "+") continue;
			if (parameters.at(i) == "*") continue;
			if (i != parameters.size() - 1 && parameters.at(i + 1) == ")") continue;
			if (i != parameters.size() - 1)
			{
				out << ",";
			}
		}
		out << ")";
		return out.str();
	}
};
#endif //PREDICATE_H
