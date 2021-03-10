#ifndef TUPLE_H
#define TUPLE_H
#include <vector>
#include <string>
#include<set>
#include <sstream>
using namespace std;
class Tuple : public vector<string> 
{
private:
public:
	Tuple() {};
	~Tuple() {};

	string toString()
	{
		ostringstream out;
		for (unsigned int i = 0; i < this->size(); ++i)
		{
			out << this->at(i) << " ";
		}
		return out.str();
	}

	/*bool operator< (const Tuple& other) const
	{
		return this.vec < other.vec;
	}*/

};
#endif //TUPLE_H

