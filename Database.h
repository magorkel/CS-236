#ifndef DATABASE_H
#define DATABASE_H
#include <map>
#include "Relation.h"
using namespace std;
class Database : public map<string, Relation>
{
private:
	//map<string, Relation> myMap;
public:
	Database() {};
	~Database() {};
};
#endif //DATABASE_H

