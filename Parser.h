#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <sstream>
#include "Token.h"
#include "Predicate.h"
#include "DatalogProgram.h"
#include "Rule.h"
class Parser
{
private:
	int nextToken;
	string IDString;
	vector<string> predicateVector;
	Predicate myPredicate;
	Predicate headPred;
	vector<Predicate> vectorOfPredicates;
	DatalogProgram myDatalogProgram;
	Rule myRule;

	bool isConstant(Token predicate)
	{
		if (predicate.getToken() == STRING) return true;
		else return false;
	}

	//schemeList->scheme schemeList | lambda
	bool schemeList(vector<Token>& token)
	{
		predicateVector.clear();
		if (token.at(nextToken).getToken() != FACTS)
		{
			if (!scheme(token)) return false;
			if (!schemeList(token)) return false;
		}
		return true;
	}
	//factList	->	fact factList | lambda
	bool factList(vector<Token>& token)
	{
		predicateVector.clear();
		if (token.at(nextToken).getToken() != RULES)
		{
			if (!fact(token)) return false;
			if (!factList(token)) return false;
		}
		return true;
	}
	//ruleList	->	rule ruleList | lambda
	bool ruleList(vector<Token>& token)
	{
		predicateVector.clear();
		if (token.at(nextToken).getToken() != QUERIES)
		{
			if (!rule(token)) return false;
			if (!ruleList(token)) return false;
		}
		return true;
	}
	//queryList	->	query queryList | lambda
	bool queryList(vector<Token>& token)
	{
		predicateVector.clear();
		if (token.at(nextToken).getToken() != END)
		{
			if (!query(token)) return false;
			if (!queryList(token)) return false;
		}
		return true;
	}
	//scheme->ID LEFT_PAREN ID idList RIGHT_PAREN // RIGHT_PAREN is in idList
	bool scheme(vector<Token>& token)
	{
		IDString = token.at(nextToken).getActualString();
		if (token.at(nextToken++).getToken() != ID) return false;
		if (token.at(nextToken++).getToken() != LEFT_PAREN) return false;
		predicateVector.push_back(token.at(nextToken).getActualString());//
		if (token.at(nextToken++).getToken() != ID) return false;
		if (!idList(token)) return false;
		myPredicate = Predicate(IDString, predicateVector);
		//predicateVector.clear();
		myDatalogProgram.pushScheme(myPredicate);
		return true;
	}
	//fact->ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD // RIGHT_PAREN is included in stringList
	bool fact(vector<Token>& token)
	{
		IDString = token.at(nextToken).getActualString();
		if (token.at(nextToken++).getToken() != ID) return false;
		if (token.at(nextToken++).getToken() != LEFT_PAREN) return false;
		predicateVector.push_back(token.at(nextToken).getActualString());
		if (token.at(nextToken++).getToken() != STRING) return false;
		if (!stringList(token)) return false;
		myPredicate = Predicate(IDString, predicateVector);
		myDatalogProgram.pushFact(myPredicate);
		if (token.at(nextToken++).getToken() != PERIOD) return false;
		return true;
	}
	//rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
	bool rule(vector<Token>& token)
	{
		if (!headPredicate(token)) return false;
		headPred = Predicate(IDString, predicateVector);
		if (token.at(nextToken++).getToken() != COLON_DASH) return false;
		predicateVector.clear();
		IDString = token.at(nextToken).getActualString();
		if (!predicate(token)) return false;
		if (!predicateList(token)) return false;
		if (token.at(nextToken++).getToken() != PERIOD) return false;
		myRule = Rule(headPred, vectorOfPredicates);
		myDatalogProgram.pushRule(myRule);
		vectorOfPredicates.clear();
		return true;
	}
	//query	        ->      predicate Q_MARK
	bool query(vector<Token>& token)
	{
		if (!predicate(token)) return false;
		myDatalogProgram.pushQuery(myPredicate);
		if (token.at(nextToken++).getToken() != Q_MARK) return false;
		return true;
	}
	//headPredicate->ID LEFT_PAREN ID idList RIGHT_PAREN
	bool headPredicate(vector<Token>& token)
	{
		IDString = token.at(nextToken).getActualString();
		if (token.at(nextToken++).getToken() != ID) return false;
		if (token.at(nextToken++).getToken() != LEFT_PAREN) return false;
		predicateVector.push_back(token.at(nextToken).getActualString());
		if (token.at(nextToken++).getToken() != ID) return false;
		if (!idList(token)) return false;
		return true;
	}
	//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN// RIGHT_PAREN is in parameterList
	bool predicate(vector<Token>& token)
	{
		IDString = token.at(nextToken).getActualString();
		if (token.at(nextToken++).getToken() != ID) return false;
		if (token.at(nextToken++).getToken() != LEFT_PAREN) return false;
		if (!parameter(token)) return false;
		if (!parameterList(token)) return false;
		myPredicate = Predicate(IDString, predicateVector);
		vectorOfPredicates.push_back(myPredicate);
		return true;
	}
	//predicateList	->	COMMA predicate predicateList | lambda 
	bool predicateList(vector<Token>& token)
	{
		predicateVector.clear();
		if (token.at(nextToken).getToken() == PERIOD) return true;
		if (token.at(nextToken++).getToken() != COMMA) return false;
		if (!predicate(token)) return false;
		if (!predicateList(token)) return false;
		return true;
	}
	//parameterList	-> 	COMMA parameter parameterList | lambda
	bool parameterList(vector<Token>& token)
	{
		if (token.at(nextToken).getToken() == RIGHT_PAREN)
		{
			nextToken++;
			return true;
		}
		if (token.at(nextToken).getToken() == RIGHT_PAREN) return true;
		if (token.at(nextToken++).getToken() != COMMA) return false;
		if (!parameter(token)) return false;
		if (token.at(nextToken).getToken() != RIGHT_PAREN) parameterList(token);
		else nextToken++;
		return true;
	}
	//stringList->COMMA STRING stringList | lambda
	bool stringList(vector<Token>& token)
	{
		if (token.at(nextToken).getToken() == RIGHT_PAREN)
		{
			nextToken++;
			return true;
		}
		if (token.at(nextToken++).getToken() != COMMA) return false;
		predicateVector.push_back(token.at(nextToken).getActualString());
		if (token.at(nextToken).getToken() == ID) return false;
		if (token.at(nextToken++).getToken() != STRING) return false;
		if (token.at(nextToken).getToken() != RIGHT_PAREN) stringList(token);
		else nextToken++;
		return true;
	}
	//idList->COMMA ID idList | lambda // ends with RIGHT_PAREN
	bool idList(vector<Token>& token)
	{
		if (token.at(nextToken).getToken() == RIGHT_PAREN)
		{
			nextToken++;
			return true;
		}
		//else nextToken++;
		if (token.at(nextToken++).getToken() != COMMA) return false;
		predicateVector.push_back(token.at(nextToken).getActualString());
		if (token.at(nextToken++).getToken() != ID) return false;
		if (token.at(nextToken).getToken() != RIGHT_PAREN) idList(token);
		else nextToken++;
		return true;
	}
	//parameter	->	STRING | ID | expression
	bool parameter(vector<Token>& token)
	{
		TokenType tokenType = (TokenType)token.at(nextToken).getToken();
		switch (tokenType)
		{
		case STRING://bunch of cases that just break for every enum. on lab machines
			predicateVector.push_back(token.at(nextToken).getActualString());
			nextToken++;
			break;
		case ID:
			predicateVector.push_back(token.at(nextToken).getActualString());
			nextToken++;
			break;
		default:
			if (!expression(token))
			{
				return false;
			}
			break;
		}
		return true;
	}
	//expression	-> 	LEFT_PAREN parameter operator parameter RIGHT_PAREN
	bool expression(vector<Token>& token)
	{
		predicateVector.push_back(token.at(nextToken).getActualString());
		if (token.at(nextToken++).getToken() != LEFT_PAREN) return false;
		if (!parameter(token)) return false;
		if (!op(token)) return false;
		if (!parameter(token)) return false;
		predicateVector.push_back(token.at(nextToken).getActualString());
		if (token.at(nextToken++).getToken() != RIGHT_PAREN) return false;
		return true;
	}
	//operator	->	ADD | MULTIPLY
	bool op(vector<Token>& token)
	{
		predicateVector.push_back(token.at(nextToken).getActualString());
		if (token.at(nextToken).getToken() != ADD && token.at(nextToken).getToken() != MULTIPLY) return false;
		nextToken++;
		return true;
	}

public:
	Parser() : nextToken(0) {}
	~Parser() {}
	bool datalogProgram(vector<Token>& token)
	{
		/*datalogProgram->SCHEMES COLON scheme schemeList
			FACTS COLON factList
			RULES COLON ruleList
			QUERIES COLON query queryList*/

		//SCHEMES
		if (token.at(nextToken++).getToken() != SCHEMES) return false;
		if (token.at(nextToken++).getToken() != COLON) return false;
		if (!scheme(token)) return false;
		if (!schemeList(token)) return false;

		//FACTS
		if (token.at(nextToken++).getToken() != FACTS) return false;
		if (token.at(nextToken++).getToken() != COLON) return false;
		//if (!fact(token)) return false;
		if (!factList(token)) return false;

		//RULES
		if (token.at(nextToken++).getToken() != RULES) return false;
		if (token.at(nextToken++).getToken() != COLON) return false;
		//if (!rule(token)) return false;
		if (!ruleList(token)) return false;

		//QUERIES
		if (token.at(nextToken++).getToken() != QUERIES) return false;
		if (token.at(nextToken++).getToken() != COLON) return false;
		if (!query(token)) return false;
		if (!queryList(token)) return false;

		if (token.at(nextToken).getToken() != END) return false;
		
		return true;
	}
	int getNextToken()
	{
		return --nextToken;
	}
	string toString()
	{
		ostringstream out;
		out << myDatalogProgram.toString();
		return out.str();
	}
	DatalogProgram returnDatalogProgram(vector<Token> tokens)
	{
		datalogProgram(tokens);
		return myDatalogProgram;
	}
};
#endif //PARSER_H

