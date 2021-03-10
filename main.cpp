#include <iostream>
#include <fstream>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Tuple.h"
#include "Interpreter.h"
#include "Relation.h"
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int main(int argc, char* argv[])
{
	VS_MEM_CHECK
		ifstream in(argv[1]);
	if (!in) return 1;
	//ofstream out(argv[2]);
	//if (!out) return 2;

	Scanner wholeFile;
	vector<Token> listOfTokens;
	wholeFile.scanLine(argv[1], listOfTokens);
#if 0
	for (unsigned int i = 0; i < listOfTokens.size(); ++i)
	{
		cout << listOfTokens.at(i).toString() << endl;
	}
	cout << "Total Tokens = " << listOfTokens.size() << endl;
#endif

	Parser parser;
#if 0
	if (parser.datalogProgram(listOfTokens))
	{
		cout << "Success!" << endl;
		cout << parser.toString();
	}
	else
	{
		cout << "Failure!" << endl;
		cout << "  " << listOfTokens.at(parser.getNextToken()).toString();
	}
#endif

	Interpreter test;
	test.buildRelation(parser.returnDatalogProgram(listOfTokens));

	//lab 3 unit testing
#if 0
	cout << endl << "Test" << endl;
	//make scheme
	Relation testRelation;
	string name = "snap";
	testRelation.setName(name);
	Tuple tup;
	tup.push_back("A");
	tup.push_back("B");
	testRelation.setScheme(tup);
	//make fact
	Tuple tup2;
	tup2.push_back("'a'");
	tup2.push_back("'b'");
	testRelation.addTuple(tup2);
	//make query
	vector<Tuple> numTups;
	Tuple tup3;
	numTups.push_back(tup3);
	tup3.push_back("'a'");
	tup3.push_back("B");
	//evaluate query
	vector<int> index;
	index.push_back(1);
	Relation temp;
	temp = testRelation.project(index);
	cout << name << "(" << tup3.at(0) << "," << tup3.at(1) << ")? Yes(" << numTups.size() << ")" << endl;
	cout << temp.toString();
#endif

	//lab 4 unit testing 
#if 0
	//test #1
	cout << endl << endl;
	Relation r1;
	r1.setName("r1");
	Tuple r1Scheme;
	r1Scheme.push_back("a");
	r1Scheme.push_back("b");
	r1.setScheme(r1Scheme);
	Tuple r1Tup1;
	r1Tup1.push_back("h");
	r1Tup1.push_back("i");
	r1.addTuple(r1Tup1);
	Tuple r1Tup2;
	r1Tup2.push_back("x");
	r1Tup2.push_back("y");
	r1.addTuple(r1Tup2);
	cout << "r1" << endl << r1.toString() << endl;

	Relation r2;
	r2.setName("r2");
	Tuple r2Scheme;
	r2Scheme.push_back("c");
	r2Scheme.push_back("d");
	r2.setScheme(r2Scheme);
	Tuple r2Tup1;
	r2Tup1.push_back("x");
	r2Tup1.push_back("z");
	r2.addTuple(r2Tup1);
	cout << "r2" << endl << r2.toString() << endl;

	Relation r3;
	r3 = r1.join(r2);
	cout << "r3" << endl << r3.toString() << endl;

	vector<int> index;
	index.push_back(1);
	index.push_back(2);
	r3 = r3.project(index);
	cout << "r3" << endl << r3.toString() << endl;

	r3.rename(0, "a");
	r3.rename(1, "b");
	cout << "r3" << endl << r3.toString() << endl;

	cout << "new tuples added to r1" << endl;
	r1.unionF(r3);
	cout << endl << "r1" << endl << r1.toString() << endl;
#endif
#if  0
	//test #2
	cout << endl << endl;
	Relation r1;
	r1.setName("r1");
	Tuple r1Scheme;
	r1Scheme.push_back("a");
	r1Scheme.push_back("b");
	r1.setScheme(r1Scheme);
	Tuple r1Tup1;
	r1Tup1.push_back("x");
	r1Tup1.push_back("y");
	r1.addTuple(r1Tup1);
	Tuple r1Tup2;
	r1Tup2.push_back("q");
	r1Tup2.push_back("u");
	r1.addTuple(r1Tup2);
	cout << "r1" << endl << r1.toString() << endl;
	
	Relation r2;
	r2.setName("r2");
	Tuple r2Scheme;
	r2Scheme.push_back("a");
	r2Scheme.push_back("b");
	r2.setScheme(r2Scheme);
	Tuple r2Tup1;
	r2Tup1.push_back("x");
	r2Tup1.push_back("y");
	r2.addTuple(r2Tup1);
	Tuple r2Tup2;
	r2Tup2.push_back("x");
	r2Tup2.push_back("j");
	r2.addTuple(r2Tup2);
	cout << "r2" << endl << r2.toString() << endl;

	Relation r3;
	r3 = r1.join(r2);
	cout << "r3" << endl << r3.toString() << endl;
#endif
#if 0
	//test #3
	cout << endl << endl;
	Relation r1;
	r1.setName("r1");
	Tuple r1Scheme;
	r1Scheme.push_back("a");
	r1Scheme.push_back("b");
	r1.setScheme(r1Scheme);
	Tuple r1Tup1;
	r1Tup1.push_back("x");
	r1Tup1.push_back("y");
	r1.addTuple(r1Tup1);
	Tuple r1Tup2;
	r1Tup2.push_back("i");
	r1Tup2.push_back("h");
	r1.addTuple(r1Tup2);
	Tuple r1Tup3;
	r1Tup3.push_back("z");
	r1Tup3.push_back("q");
	r1.addTuple(r1Tup3);
	cout << "r1" << endl << r1.toString() << endl;

	Relation r2;
	r2.setName("r2");
	Tuple r2Scheme;
	r2Scheme.push_back("b");
	r2Scheme.push_back("c");
	r2.setScheme(r2Scheme);
	Tuple r2Tup1;
	r2Tup1.push_back("h");
	r2Tup1.push_back("i");
	r2.addTuple(r2Tup1);
	Tuple r2Tup2;
	r2Tup2.push_back("h");
	r2Tup2.push_back("q");
	r2.addTuple(r2Tup2);
	Tuple r2Tup3;
	r2Tup3.push_back("c");
	r2Tup3.push_back("x");
	r2.addTuple(r2Tup3);
	cout << "r2" << endl << r2.toString() << endl;

	Relation r3;
	r3 = r1.join(r2);
	cout << "r3" << endl << r3.toString() << endl;

	vector<int> index;
	index.push_back(0);
	index.push_back(1);
	r3 = r3.project(index);
	cout << "r3" << endl << r3.toString() << endl;

	cout << "new tuples added to r1" << endl;
	r1.unionF(r3);
	cout << endl << "r1" << endl << r1.toString() << endl;
#endif
	
#if 0
	//lab 5 unit testing
	cout << endl << endl << "Unit 5 testing:" << endl;
	cout << "Dependency Graph:" << endl;
	test.getDatalog().makeGraph();
	cout << endl << "Reverse Graph:" << endl;
	cout << test.getDatalog().makeReverseGraph().toString();
	cout << endl;
	cout << test.getDatalog().makeReverseGraph().outPutPostOrder();
	cout << endl << "SCC's" << endl;
	test.getDatalog().makeReverseGraph().outV();
#endif

	return 0;
}